#include "data_display/weather_station_app.h"

namespace weather_station {

    using weather_station::WeatherStationApp;

// added 2 just to make a cool looking outline
    WeatherStationApp::WeatherStationApp() {

        ci::app::setWindowSize(kWindowMenuSizeX, kWindowMenuSizeY);
        LoadTextures();
        map_.SetCalendar(time_);
    }

    void WeatherStationApp::draw() {

        switch (state) {
            case 0:
                ci::gl::color(ci::Color("white"));
                ci::gl::draw(menu_texture_, ci::Rectf(0, 0, kWindowMenuSizeX, kWindowMenuSizeY));
                menu_.DrawMenu();
                break;
            case 1:
                ci::gl::color(ci::Color("white"));
                ci::gl::draw(map_texture_, ci::Rectf(0, 0, kWindowMapSizeX, kWindowMapSizeY));
                map_.DrawLockedAndHoverLocation();
                map_.DrawCurrentTime();
                break;
            case 2:
                ci::gl::color(ci::Color("white"));
                ci::gl::draw(station_texture_, ci::Rectf(0, 0, kWindowStationSizeX, kWindowStationSizeY));

                weather_station_.DrawWeatherStation();
                break;
        }
    }

    void WeatherStationApp::mouseDown(ci::app::MouseEvent event) {
        switch (state) {
            case 1:
                map_.HandleClick();
                place_ = std::to_string(map_.GetLockedInCoords().y) + "," + std::to_string(map_.GetLockedInCoords().x);
        }
    }

    void WeatherStationApp::mouseMove(ci::app::MouseEvent event) {
        switch (state) {
            case 1:
                map_.HandleMouse(event.getPos());
                break;
        }
    }

    void WeatherStationApp::keyDown(ci::app::KeyEvent event) {

        switch (state) {
            case 0:
                switch (event.getCode()) {
                    case ci::app::KeyEvent::KEY_RETURN:
                        IncreaseState();
                        ci::app::setWindowSize(kWindowMapSizeX, kWindowMapSizeY);
                        //go to map_
                        break;
                }
                break;
            case 1:
                switch (event.getCode()) {
                    case ci::app::KeyEvent::KEY_DOWN:
                        map_.IncreaseDate();
                        time_ = map_.GetStringToDisplay();
                        //change day back by one
                        break;
                    case ci::app::KeyEvent::KEY_UP:
                        map_.DecreaseDate();
                        time_ = map_.GetStringToDisplay();
                        //change day up one by bounds
                        break;
                    case ci::app::KeyEvent::KEY_RETURN:
                        LoadStation();
                        ci::app::setWindowSize(kWindowStationSizeX, kWindowStationSizeY);
                        IncreaseState();
                        break;
                    case ci::app::KeyEvent::KEY_BACKSPACE:
                        ci::app::setWindowSize(kWindowMenuSizeX, kWindowMenuSizeY);
                        DecreaseState();
                        break;
                }
                break;
            case 2:
                switch (event.getCode()) {
                    case ci::app::KeyEvent::KEY_DOWN:
                        weather_station_.IncrementCurrentHour();
                        break;
                    case ci::app::KeyEvent::KEY_UP:
                        weather_station_.DecrementCurrentHour();
                        break;
                    case ci::app::KeyEvent::KEY_BACKSPACE:
                        ci::app::setWindowSize(kWindowMapSizeX, kWindowMapSizeY);
                        DecreaseState();
                        break;
                }
                break;
        }
    }

    void WeatherStationApp::LoadStation() {

        //makes request with input and fills data
        receiver::Request request_place = receiver::Request();

        request_place.GetData(place_, time_);

        ScaledWeatherStation test_fill_data = ScaledWeatherStation(request_place.GetWeatherData());

        weather_station_ = test_fill_data;
    }

    void WeatherStationApp::IncreaseState() {
        if (state < 2) {
            state++;
        }
    }

    void WeatherStationApp::DecreaseState() {
        if (state > 0) {
            state--;
        }
    }

    void WeatherStationApp::LoadTextures() {

        auto menu_image = ci::loadImage(ci::app::loadAsset("backgrounds/cloud_main_screen.jpg")
        );
        menu_texture_ = ci::gl::Texture2d::create(menu_image);

        auto map_image = ci::loadImage(ci::app::loadAsset("backgrounds/world_map.jpg")
        );
        map_texture_ = ci::gl::Texture2d::create(map_image);

        auto station_image = ci::loadImage(ci::app::loadAsset("backgrounds/mammatus_clouds.jpeg")
        );
        station_texture_ = ci::gl::Texture2d::create(station_image);
    }

}  // namespace idealgas
