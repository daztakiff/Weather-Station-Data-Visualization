//
// Created by Zachary Takiff on 4/19/21.
//

#ifndef FINAL_PRODUCT_WEATHER_DATA_H
#define FINAL_PRODUCT_WEATHER_DATA_H

#include <string>
#include "vector"

namespace weather_data {
    
    using std::vector;
    using std::string;

    struct Hour {
        string time;
        double temp_f;
        double wind_kph;
        int wind_degree;
        int condition;
        double dewpoint_f;
        int cloud;
        double pressure_mb;
        double windchill_f;
        double heatindex_f;
    };
    
    struct Location {
        string name;
        string region;
        string country;

        double lat;
        double lon;

        Location& operator=(const Location& location);
    };
    
    class WeatherData {
        
    public:
        
        /**
         * Default constructor
         */
        WeatherData();

        /**
         * Operator overload assigns location and hour array of similar object
         * @param source object we are taking data from
         * @return updated weather_data object
         */
        WeatherData& operator=(const WeatherData& source);

        vector<Hour> hours_;
        
        Location location_;

    private:
        
    };
}


#endif //FINAL_PRODUCT_WEATHER_DATA_H
