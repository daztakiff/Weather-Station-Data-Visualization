//
// Created by Zachary Takiff on 4/19/21.
//

#include "data_retrieval/receiver.h"

namespace receiver {

    using std::string;
    using receiver::Request;
    using httplib::Client;
    using weather_data::Hour;
    using weather_data::Location;

    Request::Request() {}

    void Request::GetData(string city, string time) {

        string request = BuildRequest(city, time);

        HTTPResponse response = HTTPClient::request(HTTPClient::GET,
                                                    URI(request));

        if (!response.success) {
            cout << "Request failed!" << endl;
            throw std::invalid_argument("response did not go through");
        }

        cerr << "Request success" << endl;

        cerr << "Server protocol: " << response.protocol << endl;
        cerr << "Response code: " << response.response << endl;
        cerr << "Response string: " << response.responseString << endl;

        string json_string = CleanUpBody(response);

        ProcessResponse(json_string);
    }

    weather_data::WeatherData Request::GetWeatherData() {
        return weatherData;
    }

    string Request::BuildRequest(string city, string time) {

        string http_string = "http://api.weatherapi.com/v1/history.json?";

        string kAPI_Key = "09712c999f1343ab926184459211704";

        http_string.append("key=");

        http_string.append(kAPI_Key);

        http_string.append("&q=");

        http_string.append(city);

        http_string.append("&dt=");

        http_string.append(time);

        return http_string;

    }

    void Request::ProcessResponse(string to_process) {
        json j = json::parse(to_process);
        
        vector<Hour> hours;

        //goes through json object and looks for certain bits of information to fill weather_data object
        for (const auto &info_type : j.items()) {

            //fills location data
            if (info_type.key() == "location") {

                for (const auto &current_location : info_type.value().items()) {

                    if (current_location.key() == "name") {
                        weatherData.location_.name = current_location.value();
                    } else if (current_location.key() == "region") {
                        weatherData.location_.region = current_location.value();
                    } else if (current_location.key() == "country") {
                        weatherData.location_.country = current_location.value();
                    } else if (current_location.key() == "lat") {
                        weatherData.location_.lat = current_location.value();
                    } else if (current_location.key() == "lon") {
                        weatherData.location_.lon = current_location.value();
                    }
                }
            } else if (info_type.key() == "forecast") {
                for (const auto &forecast : info_type.value().items()) {
                    for (const auto &forecast_day : forecast.value().items()) {
                        for (const auto &forecast_info : forecast_day.value().items()) {
                            
                            //fills all hour data
                            if (forecast_info.key() == "hour") {
                                int hour_count = 1;
                                for (const auto &hour_num : forecast_info.value().items()) {
                                    
                                    Hour current_hour;

                                    for (const auto &hour_data : hour_num.value().items()) {

                                        if (hour_data.key() == "time") {
                                            //covert time_ to number from string
                                            current_hour.time = hour_data.value();
                                        } else if (hour_data.key() == "temp_f") {
                                            current_hour.temp_f = hour_data.value();
                                        } else if (hour_data.key() == "cloud") {
                                            current_hour.cloud = hour_data.value();
                                        } else if (hour_data.key() == "wind_degree") {
                                            current_hour.wind_degree = hour_data.value();
                                        } else if (hour_data.key() == "wind_kph") {
                                            current_hour.wind_kph = hour_data.value();
                                        } else if (hour_data.key() == "condition") {
                                            for (const auto &condition_type : hour_data.value().items()) {
                                                if (condition_type.key() == "code") {
                                                    current_hour.condition = condition_type.value();
                                                }
                                            }
                                        } else if (hour_data.key() == "dewpoint_f") {
                                            current_hour.dewpoint_f = hour_data.value();
                                        } else if (hour_data.key() == "pressure_mb") {
                                            current_hour.pressure_mb = hour_data.value();
                                        } else if (hour_data.key() == "windchill_f") {
                                            current_hour.windchill_f = hour_data.value();
                                        } else if (hour_data.key() == "heatindex_f") {
                                            current_hour.heatindex_f = hour_data.value();
                                        }
                                    }
                                    hours.push_back(current_hour);
                                    hour_count++;
                                }
                            }
                        }
                    }
                }
            }
        }
        weatherData.hours_ = hours;
    }

    string Request::CleanUpBody(HTTPResponse response) {

        string to_split = response.body;
        std::stringstream ss;
        string to;
        string correct_string_parts;

        ss << to_split;

        //only picks out odd numbers as even lines are used as status updated for some reason
        int count = 0;
        while (std::getline(ss, to, '\n')) {

            if (count % 2 != 0) {
                correct_string_parts.append(to);
            }
            count++;
        }
        
        //erase \n and \r which are appended for some reason on the request body
        correct_string_parts.erase(std::remove(correct_string_parts.begin(), correct_string_parts.end(), '\n'),
                                   correct_string_parts.end());

        correct_string_parts.erase(std::remove(correct_string_parts.begin(), correct_string_parts.end(), '\r'),
                                   correct_string_parts.end());
        
        return correct_string_parts;

    }
}
