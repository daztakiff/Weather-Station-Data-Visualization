//
// Created by Zachary Takiff on 5/1/21.
//

#ifndef FINAL_PROJECT_MAP_H
#define FINAL_PROJECT_MAP_H

#include <glm/vec2.hpp>
#include <cinder/Color.h>
#include "cinder/gl/gl.h"
#include "cinder/Font.h"
#include "calender.h"

namespace world_map {

    class World_Map {

    public:
        
        /**
         * Map display screen handles all map features including the mouse movement on the screen and day and location
         * in longitude and latitude you are hovering over or have locked in
         */
        World_Map();
        
        
        /**
         * Deals with where the mouse is hovering ad lets you see where you are hovering over
         * @param position position in a vector of the location the mouse is hovering over
         */
        void HandleMouse(const glm::ivec2 &position);

        /**
         * The procedure that goes over whenever you click will lock in the latitude and longitude you make a request to
         */
        void HandleClick();
        
        /**
         * Will draw the current time in a date string that you get from the calendar object that map contains
         */
        void DrawCurrentTime();

        /**
         * Draws the string of longitude and latitude so that you can see where you are hovering over and what is currently locked in
         */
        void DrawLockedAndHoverLocation();

        /**
         * Returns a const reference of the coordinates that are currently locked in meaning when enter is hit it will
         * search for weather station at that longitude and latitude
         * @return vec2 of x and y latitude
         */
        const glm::dvec2 &GetLockedInCoords() const;

        /**
         * Sets up calendar with the starting time is called in the constructor of the weather_app file
         * @param time 
         */
        void SetCalendar(const std::string time);
        
        /**
         * Will increase the date as long as it is not past the present day
         */
        void IncreaseDate();
        
        /**
         * Will decrease the date to the past as long as it is not more then 7 days in the past since API free version only has data for last 7 days
         */
        void DecreaseDate();
        
        /**
         * String that you display for current time called in each draw method
         * @return 
         */
        const std::string &GetStringToDisplay();
        
    private:

        glm::dvec2 current_coords_;
        
        glm::dvec2 locked_in_coords_;
        
        calender::Calendar calendar_;
        
        std::string to_display;
        
        const ci::Color kTextColor = ci::Color("black");
        
        const int kDistancePerTenLon = 31;
        const double kDegreePerPixelLon = 0.48387096774;
        const double kDegreePerPixel75And66Lat = 0.15454545454;
        const double kDegreePerPixel66And60Lat = 0.22413793103;
        const double kDegreePerPixel60And45Lat = 0.28846153846;
        const double kDegreePerPixel45And30Lat = 0.38461538461;
        const double kDegreePerPixel30And23Lat = 0.46428571428;
        const double kDegreePerPixel23And15Lat = 0.47222222222;
        const double kDegreePerPixel15And0Lat = 0.46875;
        const double kDegreePerPixel0And15Lat = 0.48387096774;
        const double kDegreePerPixel15And23Lat = 0.44736842105;
        const double kDegreePerPixel23And30Lat = 0.46428571428;
        const double kDegreePerPixel30And45Lat = 0.38461538461;
        
        const glm::vec2 left_longitude_point = glm::vec2(41, 48);
        
        const glm::vec2 top_lat_point = glm::vec2(41, 156);
        
        const glm::vec2 sixty_six_lat_point = glm::vec2(41, 211);
        const glm::vec2 sixty_lat_point = glm::vec2(41, 240);
        const glm::vec2 forty_five_lat_point = glm::vec2(41, 293);
        const glm::vec2 thirty_lat_point = glm::vec2(41, 332);
        const glm::vec2 twenty_three_lat_point = glm::vec2(41, 346);
        const glm::vec2 fifteen_lat_point = glm::vec2(41, 364);
        const glm::vec2 zero_lat_point = glm::vec2(41, 396);
        const glm::vec2 neg_fifteen_lat_point = glm::vec2(41, 427);
        const glm::vec2 neg_twenty_three_lat_point = glm::vec2(41, 446);
        const glm::vec2 neg_thirty_lat_point = glm::vec2(41, 460);
        
        const glm::vec2 bottom_lat_point = glm::vec2(41, 499);
    };
}


#endif //FINAL_PROJECT_MAP_H
