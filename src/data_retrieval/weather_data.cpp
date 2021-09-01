#include "data_retrieval/weather_data.h"


namespace weather_data {
    
    WeatherData::WeatherData() {}

    WeatherData &WeatherData::operator=(const WeatherData &source) {
        this->hours_ = source.hours_;
        this->location_ = source.location_;
        
        return *this;
    }

    Location &Location::operator=(const Location &location) {
        name = location.name;
        country = location.country;
        lat = location.lat;
        lon = location.lon;
        region = location.region;

        return *this;
    }
}
