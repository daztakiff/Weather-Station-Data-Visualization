//
// Created by Zachary Takiff on 4/20/21.
//

#include "data_display/scaled_weather_station.h"
#include <glm/vec2.hpp>
#include <math.h>
#include "cinder/app/app.h"

namespace weather_station {

    using glm::vec2;

    ScaledWeatherStation::ScaledWeatherStation() {
        current_hour_ = 0;
    }

    ScaledWeatherStation::ScaledWeatherStation(const WeatherData &set_data) {
        data_drawn_ = set_data;
        current_hour_ = 0;
    }

    ScaledWeatherStation &ScaledWeatherStation::operator=(const ScaledWeatherStation &source) {

        this->current_hour_ = 0;
        this->data_drawn_ = source.data_drawn_;

        return *this;
    }

    void ScaledWeatherStation::DrawWeatherStation() {
        //splits work into helper functions
        DrawBackgroundAndWarnings();
        DrawCenterAndCloudCover();
        DrawWeatherCondition();
        DrawLocationData();
        DrawWeatherCondition();
        DrawTempDewPointAndPressure();
        DrawWindBarAndSpeed();

    }

    void ScaledWeatherStation::DrawBackgroundAndWarnings() {

        if (data_drawn_.hours_[current_hour_].windchill_f < -22) {
            ci::gl::color(ci::Color("blue"));
            ci::gl::drawSolidRoundedRect(
                    ci::Rectf(kCenterX - (7 * kMargin), kCenterY - (9 * kMargin), kCenterX + (7 * kMargin),
                              kCenterY + (7 * kMargin)), 30);

            DrawText("*Windchill Warning In Effect*", kCenterX - (7 * kMargin) + 75, kCenterY - (9 * kMargin) + 30, 50,
                     ci::Font("Arial", 20));
        }

        if (data_drawn_.hours_[current_hour_].heatindex_f > 105) {
            ci::gl::color(ci::Color("red"));
            ci::gl::drawSolidRoundedRect(
                    ci::Rectf(kCenterX - (7 * kMargin), kCenterY - (9 * kMargin), kCenterX + (7 * kMargin),
                              kCenterY + (7 * kMargin)), 30);

            DrawText("*Excessive Heat Warning In Effect*", kCenterX - (7 * kMargin) + 55, kCenterY - (9 * kMargin) + 30,
                     50, ci::Font("Arial", 20));
        }
        ci::gl::color(kBackgroundColor);
        ci::gl::drawSolidRoundedRect(
                ci::Rectf(kCenterX - (7 * kMargin), kCenterY - (7 * kMargin), kCenterX + (7 * kMargin),
                          kCenterY + (7 * kMargin)), 30);
    }

    void ScaledWeatherStation::DrawCenterAndCloudCover() {

        //gets cloud data and sorts by what inner circle file we are displaying
        int cloud_cover = data_drawn_.hours_[current_hour_].cloud;

        if (cloud_cover == 0) {
            DrawCloudCoverFromImage(
                    "cloud_cover_centers/station_clear.jpg");
        } else if (cloud_cover > 0 && cloud_cover <= 12) {
            DrawCloudCoverFromImage(
                    "cloud_cover_centers/station_12.jpg");
        } else if (cloud_cover > 12 && cloud_cover <= 35) {
            DrawCloudCoverFromImage(
                    "cloud_cover_centers/station_25.jpg");
        } else if (cloud_cover > 35 && cloud_cover <= 60) {
            DrawCloudCoverFromImage(
                    "cloud_cover_centers/station_50.jpg");
        } else if (cloud_cover > 60 && cloud_cover <= 85) {
            DrawCloudCoverFromImage(
                    "cloud_cover_centers/station_75.jpg");
        } else if (cloud_cover > 59 && cloud_cover <= 100) {
            DrawCloudCoverFromImage(
                    "cloud_cover_centers/station_overcast.jpg");
        } else {
            DrawCloudCoverFromImage(
                    "cloud_cover_centers/station_obscured.jpg");
        }
    }

    void ScaledWeatherStation::DrawWindBarAndSpeed() {
        double wind_speed_kph = data_drawn_.hours_[current_hour_].wind_kph;
        int wind_knots = ceil(wind_speed_kph * .54);

        int wind_degree = data_drawn_.hours_[current_hour_].wind_degree;

        double wind_radian = (wind_degree * M_PI) / 180;
        CalculatePointsOnWindLine(wind_radian);

        int num_flags = 0;
        int num_long_barbs = 0;
        int num_short_barbs = 0;

        int quotient_50 = (wind_knots + 2) / 50;
        int remainder_50 = (wind_knots + 2) % 50;

        if (quotient_50 > 0) {
            num_flags = quotient_50;
        }

        if (remainder_50 > 0) {
            int quotient_10 = remainder_50 / 10;
            int remainder_10 = remainder_50 % 10;

            if (quotient_10 > 0) {
                num_long_barbs = quotient_10;
            }

            if (remainder_10 > 0) {
                int quotient_5 = remainder_10 / 5;

                if (quotient_5 > 0) {
                    num_short_barbs = quotient_5;
                }
            }
        }

        //draws the line coming off of weather station
        ci::gl::color(kStationColor);
        ci::gl::drawLine(inner_points[7], inner_points[0]);

        switch (num_flags) {
            case 0:
                switch (num_long_barbs) {
                    case 0:
                        if (num_short_barbs == 1) {
                            ci::gl::drawLine(inner_points[0], half_points[0]);
                        }
                        break;
                    case 1:
                        ci::gl::drawLine(inner_points[0], outer_points[0]);
                        if (num_short_barbs == 1) {
                            ci::gl::drawLine(inner_points[1], half_points[1]);
                        }
                        break;
                    case 2:
                        ci::gl::drawLine(inner_points[0], outer_points[0]);
                        ci::gl::drawLine(inner_points[1], outer_points[1]);
                        if (num_short_barbs == 1) {
                            ci::gl::drawLine(inner_points[2], half_points[2]);
                        }
                        break;
                    case 3:
                        ci::gl::drawLine(inner_points[0], outer_points[0]);
                        ci::gl::drawLine(inner_points[1], outer_points[1]);
                        ci::gl::drawLine(inner_points[2], outer_points[2]);
                        if (num_short_barbs == 1) {
                            ci::gl::drawLine(inner_points[3], half_points[3]);
                        }
                        break;
                    case 4:
                        ci::gl::drawLine(inner_points[0], outer_points[0]);
                        ci::gl::drawLine(inner_points[1], outer_points[1]);
                        ci::gl::drawLine(inner_points[2], outer_points[2]);
                        ci::gl::drawLine(inner_points[3], outer_points[3]);
                        if (num_short_barbs == 1) {
                            ci::gl::drawLine(inner_points[4], half_points[4]);
                        }
                        break;
                }
                break;
            case 1:
                ci::gl::drawSolidTriangle(inner_points[0], inner_points[1], outer_points[7]);
                switch (num_long_barbs) {
                    case 0:
                        if (num_short_barbs == 1) {
                            ci::gl::drawLine(inner_points[1], half_points[1]);
                        }
                        break;
                    case 1:
                        ci::gl::drawLine(inner_points[1], outer_points[1]);
                        if (num_short_barbs == 1) {
                            ci::gl::drawLine(inner_points[2], half_points[2]);
                        }
                        break;
                    case 2:
                        ci::gl::drawLine(inner_points[1], outer_points[1]);
                        ci::gl::drawLine(inner_points[2], outer_points[2]);
                        if (num_short_barbs == 1) {
                            ci::gl::drawLine(inner_points[3], half_points[3]);
                        }
                        break;
                    case 3:
                        ci::gl::drawLine(inner_points[1], outer_points[1]);
                        ci::gl::drawLine(inner_points[2], outer_points[2]);
                        ci::gl::drawLine(inner_points[3], outer_points[3]);
                        if (num_short_barbs == 1) {
                            ci::gl::drawLine(inner_points[4], half_points[4]);
                        }
                        break;
                    case 4:
                        ci::gl::drawLine(inner_points[1], outer_points[1]);
                        ci::gl::drawLine(inner_points[2], outer_points[2]);
                        ci::gl::drawLine(inner_points[3], outer_points[3]);
                        ci::gl::drawLine(inner_points[4], outer_points[4]);
                        if (num_short_barbs == 1) {
                            ci::gl::drawLine(inner_points[5], half_points[5]);
                        }
                        break;
                }
                break;
            case 2:
                ci::gl::drawSolidTriangle(inner_points[0], inner_points[1], outer_points[7]);
                ci::gl::drawSolidTriangle(inner_points[1], inner_points[2], outer_points[8]);
                break;
        }
    }

    void ScaledWeatherStation::DrawTempDewPointAndPressure() {

        ci::gl::color(kStationColor);
        double temp_f = data_drawn_.hours_[current_hour_].temp_f;
        double dewpoint_f = data_drawn_.hours_[current_hour_].dewpoint_f;
        double pressure_mb = data_drawn_.hours_[current_hour_].pressure_mb;
        if (current_hour_ > 3) {
            double pressure_mb_last = data_drawn_.hours_[current_hour_ - 3].pressure_mb;
            double pressure_change = pressure_mb - pressure_mb_last;

            pressure_change *= 10;
            pressure_change = ceil(pressure_change);
            pressure_change /= 10;
            std::string pressure_change_string = std::to_string(pressure_change);
            pressure_change_string = pressure_change_string.substr(0, pressure_change_string.find(".", 0));

            DrawText(pressure_change_string, kCenterX + (2 * kMargin), kCenterY - 5, 20, kDataFont);

            if (pressure_change > 0) {
                ci::gl::drawLine(vec2(kCenterX + (2 * kMargin) + 25, kCenterY + 20),
                                 vec2(kCenterX + (2 * kMargin) + 40, kCenterY));
            } else if (pressure_change < 0) {
                ci::gl::drawLine(vec2(kCenterX + (2 * kMargin) + 35, kCenterY),
                                 vec2(kCenterX + (2 * kMargin) + 50, kCenterY + 20));
            } else {
                ci::gl::drawLine(vec2(kCenterX + (2 * kMargin) + 25, kCenterY + 10),
                                 vec2(kCenterX + (2 * kMargin) + 40, kCenterY + 10));
            }
        }
        temp_f *= 10;
        dewpoint_f *= 10;
        pressure_mb *= 10;

        temp_f = ceil(temp_f);
        dewpoint_f = ceil(dewpoint_f);
        pressure_mb = ceil(pressure_mb);

        temp_f /= 10;
        dewpoint_f /= 10;
        pressure_mb /= 10;

        std::string temp_string = std::to_string(temp_f);
        std::string dew_string = std::to_string(dewpoint_f);
        std::string pres_string = std::to_string(pressure_mb);

        temp_string = temp_string.substr(0, temp_string.find(".", 0) + 2);
        dew_string = dew_string.substr(0, dew_string.find(".", 0) + 2);
        pres_string = pres_string.substr(0, pres_string.find(".", 0) + 2);

        DrawText(temp_string, kCenterX - (5 * kMargin), kCenterY - kMargin - 20, 20, kDataFont);
        DrawText(dew_string, kCenterX - (5 * kMargin), kCenterY + kMargin, 20, kDataFont);
        DrawText(pres_string, kCenterX + (2 * kMargin), kCenterY - kMargin - 20, 20, kDataFont);


        //draw text in right position of temperature,  pressure, and dewpoint
    }

    void ScaledWeatherStation::DrawWeatherCondition() {

        int condition = data_drawn_.hours_[current_hour_].condition;

        switch (condition) {
            case 1030:
                DrawConditionFromImage("conditions/fog_thin.jpg");
                //thin fog
                break;
            case 1135:
            case 1147:
                DrawConditionFromImage("conditions/fog_thick.jpg");
                //thick fog
                break;
            case 1114:
            case 1210:
            case 1213:
                DrawConditionFromImage("conditions/light_snow.jpg");
                //light snow
                break;
            case 1216:
            case 1219:
                DrawConditionFromImage("conditions/moderate_snow.jpg");
                //moderate snow
                break;
            case 1117:
            case 1222:
            case 1225:
                DrawConditionFromImage("conditions/heavy_snow.jpg");
                //heavy snow
                break;
            case 1150:
                DrawConditionFromImage("conditions/drizzle.jpg");
                //drizzle
                break;
            case 1168:
            case 1171:
                DrawConditionFromImage("conditions/freezing_drizzle.jpg");
                //freezing drizzle
                break;
            case 1180:
            case 1183:
                DrawConditionFromImage("conditions/light_rain.jpg");
                //light rain
                break;
            case 1186:
            case 1189:
                DrawConditionFromImage("conditions/moderate_rain.jpg");
                //moderate rain
                break;
            case 1192:
            case 1195:
                DrawConditionFromImage("conditions/heavy_rain.jpg");
                //heavy rain
                break;
            case 1198:
            case 1201:
                DrawConditionFromImage("conditions/freezing_rain.jpg");
                //freezing rain
                break;
            case 1204:
            case 1207:
            case 1249:
            case 1252:
                DrawConditionFromImage("conditions/sleet.jpg");
                //sleet or sleet showers
                break;
            case 1240:
            case 1243:
            case 1246:
                DrawConditionFromImage("conditions/shower_rain.jpg");
                //rain showers
                break;
            case 1255:
            case 1258:
                DrawConditionFromImage("conditions/shower_snow.jpg");
                //snow showers
                break;
            case 1273:
            case 1276:
                DrawConditionFromImage("conditions/thunder_rain.jpg");
                //thunder rain
                break;
            case 1279:
            case 1282:
                DrawConditionFromImage("conditions/thunder_snow.jpg");
                //thunder snow
                break;
            case 1087:
                DrawConditionFromImage("conditions/thunder.jpg");
                //thunder
                break;


        }

        //draw symbol set for what type of weather is occurring sort by string name
    }

    void ScaledWeatherStation::DrawLocationData() {

        std::string time = data_drawn_.hours_[current_hour_].time;
        std::string city = data_drawn_.location_.name;
        std::string region = data_drawn_.location_.region;
        std::string country = data_drawn_.location_.country;
        double lat = data_drawn_.location_.lat;
        double lon = data_drawn_.location_.lon;

        ci::gl::color(kStationColor);
        DrawText("Date and Time:", kMargin / 2, kMargin, 30, kLocationFont);
        DrawText(time, (7 * kMargin) + 10, kMargin, 30, kLocationFont);
        DrawText("City:", kMargin / 2, 2 * kMargin, 30, kLocationFont);
        DrawText(city, 3 * kMargin, 2 * kMargin, 30, kLocationFont);
        DrawText("Country:", kMargin / 2, 3 * kMargin, 30, kLocationFont);
        DrawText(country, (5 * kMargin) - 10, 3 * kMargin, 30, kLocationFont);
        DrawText("Region:", kMargin / 2, 4 * kMargin, 30, kLocationFont);
        DrawText(region, 4 * kMargin, 4 * kMargin, 30, kLocationFont);
        DrawText("Latitude:", 600, 40, 30, kLocationFont);
        DrawText("Longitude:", 600, 100, 30, kLocationFont);
        DrawText(std::to_string(lat), 720, 40, 30, kLocationFont);
        DrawText(std::to_string(lon), 740, 100, 30, kLocationFont);


    }

    void ScaledWeatherStation::CalculatePointsOnWindLine(double wind_radian) {

        inner_points.clear();
        half_points.clear();
        outer_points.clear();

        vec2 inner_tangent_point = vec2(kCenterX + kCircleRadius * (cos(wind_radian)),
                                        kCenterY - kCircleRadius * (sin(wind_radian)));

        vec2 outer_tangent_point = vec2(kCenterX + 5 * kCircleRadius * (cos(wind_radian)),
                                        kCenterY - 5 * kCircleRadius * (sin(wind_radian)));

        vec2 inner_mid_one = vec2(kCenterX + 3.2 * kCircleRadius * (cos(wind_radian)),
                                  kCenterY - 3.2 * kCircleRadius * (sin(wind_radian)));

        vec2 inner_mid_two = vec2(kCenterX + 3.5 * kCircleRadius * (cos(wind_radian)),
                                  kCenterY - 3.5 * kCircleRadius * (sin(wind_radian)));

        vec2 inner_mid_three = vec2(kCenterX + 3.8 * kCircleRadius * (cos(wind_radian)),
                                    kCenterY - 3.8 * kCircleRadius * (sin(wind_radian)));

        vec2 inner_mid_four = vec2(kCenterX + 4.1 * kCircleRadius * (cos(wind_radian)),
                                   kCenterY - 4.1 * kCircleRadius * (sin(wind_radian)));

        vec2 inner_mid_five = vec2(kCenterX + 4.4 * kCircleRadius * (cos(wind_radian)),
                                   kCenterY - 4.4 * kCircleRadius * (sin(wind_radian)));

        vec2 inner_mid_six = vec2(kCenterX + 4.7 * kCircleRadius * (cos(wind_radian)),
                                  kCenterY - 4.7 * kCircleRadius * (sin(wind_radian)));

        vec2 flag_one = vec2(kCenterX + 4.4 * kCircleRadius * (cos(wind_radian)),
                             kCenterY - 4.4 * kCircleRadius * (sin(wind_radian)));

        vec2 flag_two = vec2(kCenterX + 4.8 * kCircleRadius * (cos(wind_radian)),
                             kCenterY - 4.8 * kCircleRadius * (sin(wind_radian)));

        inner_points.push_back(outer_tangent_point);
        inner_points.push_back(inner_mid_six);
        inner_points.push_back(inner_mid_five);
        inner_points.push_back(inner_mid_four);
        inner_points.push_back(inner_mid_three);
        inner_points.push_back(inner_mid_two);
        inner_points.push_back(inner_mid_one);
        inner_points.push_back(inner_tangent_point);

        double slope = tan(wind_radian);

        double m = 1 / slope;

        double outer_y_final = ((kDiffX * sin(wind_radian)) * m) + outer_tangent_point.y;
        double outer_x_final = (kDiffX * sin(wind_radian)) + outer_tangent_point.x;

        vec2 outer_tangent_line_end = vec2(outer_x_final, outer_y_final);

        double mid_1_y_final = ((kDiffX * sin(wind_radian)) * m) + inner_mid_one.y;
        double mid_1_x_final = (kDiffX * sin(wind_radian)) + inner_mid_one.x;

        vec2 mid_one_end = vec2(mid_1_x_final, mid_1_y_final);

        double mid_2_y_final = ((kDiffX * sin(wind_radian)) * m) + inner_mid_two.y;
        double mid_2_x_final = (kDiffX * sin(wind_radian)) + inner_mid_two.x;

        vec2 mid_two_end = vec2(mid_2_x_final, mid_2_y_final);

        double mid_3_y_final = ((kDiffX * sin(wind_radian)) * m) + inner_mid_three.y;
        double mid_3_x_final = (kDiffX * sin(wind_radian)) + inner_mid_three.x;

        vec2 mid_three_end = vec2(mid_3_x_final, mid_3_y_final);

        double mid_4_y_final = ((kDiffX * sin(wind_radian)) * m) + inner_mid_four.y;
        double mid_4_x_final = (kDiffX * sin(wind_radian)) + inner_mid_four.x;

        vec2 mid_four_end = vec2(mid_4_x_final, mid_4_y_final);

        double mid_5_y_final = ((kDiffX * sin(wind_radian)) * m) + inner_mid_five.y;
        double mid_5_x_final = (kDiffX * sin(wind_radian)) + inner_mid_five.x;

        vec2 mid_five_end = vec2(mid_5_x_final, mid_5_y_final);

        double mid_6_y_final = ((kDiffX * sin(wind_radian)) * m) + inner_mid_six.y;
        double mid_6_x_final = (kDiffX * sin(wind_radian)) + inner_mid_six.x;

        vec2 mid_six_end = vec2(mid_6_x_final, mid_6_y_final);

        double flag1_y_final = ((kDiffX * sin(wind_radian)) * m) + flag_one.y;
        double flag1_x_final = (kDiffX * sin(wind_radian)) + flag_one.x;

        vec2 flag_end_one = vec2(flag1_x_final, flag1_y_final);

        double flag2_y_final = ((kDiffX * sin(wind_radian)) * m) + flag_two.y;
        double flag2_x_final = (kDiffX * sin(wind_radian)) + flag_two.x;

        vec2 flag_end_two = vec2(flag2_x_final, flag2_y_final);

        outer_points.push_back(outer_tangent_line_end);
        outer_points.push_back(mid_six_end);
        outer_points.push_back(mid_five_end);
        outer_points.push_back(mid_four_end);
        outer_points.push_back(mid_three_end);
        outer_points.push_back(mid_two_end);
        outer_points.push_back(mid_one_end);
        outer_points.push_back(flag_end_two);
        outer_points.push_back(flag_end_one);

        double outer_half_y_final = ((kDiffXOverTwo * sin(wind_radian)) * m) + outer_tangent_point.y;
        double outer_half_x_final = (kDiffXOverTwo * sin(wind_radian)) + outer_tangent_point.x;

        vec2 outer_tangent_line_half = vec2(outer_half_x_final, outer_half_y_final);

        double mid_1_y_half = ((kDiffXOverTwo * sin(wind_radian)) * m) + inner_mid_one.y;
        double mid_1_x_half = (kDiffXOverTwo * sin(wind_radian)) + inner_mid_one.x;

        vec2 mid_one_half = vec2(mid_1_x_half, mid_1_y_half);

        double mid_2_y_half = ((kDiffXOverTwo * sin(wind_radian)) * m) + inner_mid_two.y;
        double mid_2_x_half = (kDiffXOverTwo * sin(wind_radian)) + inner_mid_two.x;

        vec2 mid_two_half = vec2(mid_2_x_half, mid_2_y_half);

        double mid_3_y_half = ((kDiffXOverTwo * sin(wind_radian)) * m) + inner_mid_three.y;
        double mid_3_x_half = (kDiffXOverTwo * sin(wind_radian)) + inner_mid_three.x;

        vec2 mid_three_half = vec2(mid_3_x_half, mid_3_y_half);

        double mid_4_y_half = ((kDiffXOverTwo * sin(wind_radian)) * m) + inner_mid_four.y;
        double mid_4_x_half = (kDiffXOverTwo * sin(wind_radian)) + inner_mid_four.x;

        vec2 mid_four_half = vec2(mid_4_x_half, mid_4_y_half);

        double mid_5_y_half = ((kDiffXOverTwo * sin(wind_radian)) * m) + inner_mid_five.y;
        double mid_5_x_half = (kDiffXOverTwo * sin(wind_radian)) + inner_mid_five.x;

        vec2 mid_five_half = vec2(mid_5_x_half, mid_5_y_half);

        double mid_6_y_half = ((kDiffXOverTwo * sin(wind_radian)) * m) + inner_mid_six.y;
        double mid_6_x_half = (kDiffXOverTwo * sin(wind_radian)) + inner_mid_six.x;

        vec2 mid_six_half = vec2(mid_6_x_half, mid_6_y_half);

        half_points.push_back(outer_tangent_line_half);
        half_points.push_back(mid_six_half);
        half_points.push_back(mid_five_half);
        half_points.push_back(mid_four_half);
        half_points.push_back(mid_three_half);
        half_points.push_back(mid_two_half);
        half_points.push_back(mid_one_half);
    }

    void ScaledWeatherStation::DrawCloudCoverFromImage(std::string path) {
        ci::gl::color(kBackgroundColor);
        ci::gl::Texture2dRef texture;
        auto image = ci::loadImage(ci::app::loadAsset(path)
        );
        texture = ci::gl::Texture2d::create(image);
        ci::gl::draw(texture, ci::Rectf(vec2(kCenterX - kCircleRadius, kCenterY - kCircleRadius),
                                        vec2(kCenterX + kCircleRadius, kCenterY + kCircleRadius)));
    }

    void ScaledWeatherStation::DrawConditionFromImage(std::string path) {
        ci::gl::color(kBackgroundColor);
        ci::gl::Texture2dRef texture;
        auto image = ci::loadImage(ci::app::loadAsset(path)
        );
        texture = ci::gl::Texture2d::create(image);
        ci::gl::draw(texture,
                     ci::Rectf(kCenterX - (5 * kMargin), kCenterY - 20, kCenterX - (2 * kMargin), kCenterY + 30));
    }

    void
    ScaledWeatherStation::DrawText(std::string to_draw, int x_position, int y_position, int size, ci::Font font) const {
        ci::gl::drawString(to_draw, vec2(x_position, y_position), kStationColor, font);
    }

    void ScaledWeatherStation::IncrementCurrentHour() {
        if (current_hour_ < 23) {
            current_hour_++;
        }
    }

    void ScaledWeatherStation::DecrementCurrentHour() {
        if (current_hour_ > 0) {
            current_hour_--;
        }
    }
}
