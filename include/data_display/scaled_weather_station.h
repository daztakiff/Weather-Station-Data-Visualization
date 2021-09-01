//
// Created by Zachary Takiff on 4/20/21.
//

#ifndef FINAL_PROJECT_SCALED_WEATHER_STATION_H
#define FINAL_PROJECT_SCALED_WEATHER_STATION_H

#include "data_retrieval/weather_data.h"
#include <cinder/Color.h>
#include "cinder/gl/gl.h"
#include "cinder/Font.h"

namespace weather_station {

    using ci::Color;
    using weather_data::WeatherData;

    /**
     * class that deals with actually displaying and getting data from the data object in cinder app will use these
     * draw methods for different hours
     */
    class ScaledWeatherStation {

    public:

        /**
         * Default constructor
         */
        ScaledWeatherStation();

        /**
         * Will set up a weather station with data passed in and current hour as 0 can use for testing by making one of
         * these objects
         * @param set_data data passed in must have location_ data and the current hour data to draw everything
         */
        ScaledWeatherStation(const WeatherData &set_data);

        /**
         * Copy assignment operator
         * @param source what we are copying
         * @return the object that is now a copy of the object we are copying from
         */
        ScaledWeatherStation &operator=(const ScaledWeatherStation &source);

        /**
         * Draw weather station uses many helper methods to initialize the actual object made up of cloud cover center,
         * pressure, temp, dewpoint, and wind speed ad barbs. Additionally would like to add functionality regarding wind
         * chill and head index
         */
        void DrawWeatherStation();

        /**
         * increases current hour to get a different section of data
         */
        void IncrementCurrentHour();

        /**
         * decreases current hour to get a different section of data
         */
        void DecrementCurrentHour();

    private:

        /**
         * Draw function that draws the middle circle in a way to represent cloud cover. Circle should always be in the
         * same spot of kCenter
         */
        void DrawCenterAndCloudCover();

        /**
         * Draws the wind bar coming off of the circle at the right angles and having the right number of respective
         * wind_speed_knots_flags and barbs to represent the wind speed in knots
         */
        void DrawWindBarAndSpeed();

        /**
         * Draws 3 text boxes in the right places so that for each hour you will always display temp, pressure and
         * dewpoint in the right places
         */
        void DrawTempDewPointAndPressure();

        /**
         * Draws the specialty weather condition if there is one see
         * https://www.wpc.ncep.noaa.gov/html/stationplot.shtml 
         * and look at weather section for more comprehensive definition
         */
        void DrawWeatherCondition();

        /**
         * Displays location data and current hour
         */
        void DrawLocationData();

        /**
         * used to help draw text in different fonts
         * @param to_draw 
         * @param x_position 
         * @param y_position 
         * @param size 
         */
        void DrawText(std::string to_draw, int x_position, int y_position, int size, ci::Font font) const;

        /**
         * Draws blank circle outline to represent clear skies
         */
        void DrawCloudCoverFromImage(std::string path);

        /**
         * Calculates and populates 3 vectors of 2vec points that are the positions of where we draw the weather_barbs
         * for whatever angle the line is currently displayed at
         * @param wind_radian 
         */
        void CalculatePointsOnWindLine(double wind_radian);

        /**
         * Condition currently displayed called with the path to the conditions folder in assets to draw the image of
         * conditions in the right spot on the weather station area
         * @param path 
         */
        void DrawConditionFromImage(std::string path);

        /**
         * Draws a red or a blue top area if heat or cold is to a point where there is either a cold warning or a heat
         * warning in effect
         */
        void DrawBackgroundAndWarnings();
        
        const int kMargin = 30;
        const int kCenterX = 445;
        const int kCenterY = 500;
        const int kCircleRadius = 50;
        const double kDiffX = 70;
        const double kDiffXOverTwo = 35;
        const ci::Font kLocationFont = ci::Font("Times-Bold", 30);
        const ci::Font kDataFont = ci::Font("Arial", 40);

        const Color kStationColor = Color("black");
        const Color kBackgroundColor = Color("white");

        int current_hour_;

        WeatherData data_drawn_;
        
        std::vector<glm::vec2> inner_points;
        std::vector<glm::vec2> half_points;
        std::vector<glm::vec2> outer_points;

    };
}

#endif //FINAL_PROJECT_SCALED_WEATHER_STATION_H
