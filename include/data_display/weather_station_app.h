#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "../data_retrieval/weather_data.h"
#include "scaled_weather_station.h"
#include "../data_retrieval/receiver.h"
#include "menu.h"
#include "map.h"

namespace weather_station {

/**
 * An app for visualizing the behavior of an ideal gas.
 */
    class WeatherStationApp : public ci::app::App {
    public:
        
        /**
         * App that displays weather stations and can draw them with respective data
         */
        WeatherStationApp();

        void draw() override;

        void mouseMove(ci::app::MouseEvent event) override;

        void mouseDown(ci::app::MouseEvent event) override;
        
        void keyDown(ci::app::KeyEvent event) override;
        
        /**
         * switches to next menu screen
         */
        void IncreaseState();
        
        /**
         * switches to the past menu screen
         */
        void DecreaseState();


        /**
         * Example can use with any city or time_ in right format
         * @param city city name zip code and other ways to look up place_ on weatherapi.com
         * @param time time_ must be in year-month-day format
         */
        void LoadStation();
        
        /**
         * Loads the textures of the background images at startup
         */
        void LoadTextures();
        
        ScaledWeatherStation station = ScaledWeatherStation();

        const int kWindowStationSizeX = 875;
        const int kWindowStationSizeY = 875;
        const int kWindowMapSizeX = 757;
        const int kWindowMapSizeY = 616;
        const int kWindowMenuSizeX = 960;
        const int kWindowMenuSizeY = 635;
        const int kMargin = 150;

    private:
        
        int state = 0;
        std::string place_ = "Urbana";
        std::string time_ = "2021-09-13";

        ci::gl::Texture2dRef menu_texture_;
        ci::gl::Texture2dRef map_texture_;
        ci::gl::Texture2dRef station_texture_;
        
        menu::Menu menu_;
        
        world_map::World_Map map_;
        
        weather_station::ScaledWeatherStation weather_station_;
    };

}  // namespace idealgas