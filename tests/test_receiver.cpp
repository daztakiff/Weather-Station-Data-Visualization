#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

#include "data_retrieval/receiver.h"


using receiver::Request;

TEST_CASE("test receiver generates a correct request to server and sets up data correctly for multiple cities and times") {
    
    Request request_london = Request();
    request_london.GetData("London", "2021-05-04");
    Request request_london_later = Request();
    request_london_later.GetData("London", "2021-05-03");
    Request request_tokyo = Request();
    request_tokyo.GetData("Tokyo", "2021-05-04");
    
    
    SECTION("test location setup for London request_london in past 7 days") {
        
        REQUIRE(request_london.GetWeatherData().location_.name == "London");
        REQUIRE(request_london.GetWeatherData().location_.region == "City of London, Greater London");
        REQUIRE(request_london.GetWeatherData().location_.country == "United Kingdom");
        REQUIRE(request_london.GetWeatherData().location_.lat == 51.52);
        REQUIRE(request_london.GetWeatherData().location_.lon == -0.11);
    }
    
    SECTION("test first hour is set up correctly according to json but only hour struct values are set") {
        
        REQUIRE(request_london.GetWeatherData().hours_[0].time == "2021-05-04 00:00");
        REQUIRE(request_london.GetWeatherData().hours_[0].temp_f == 45.9);
        REQUIRE(request_london.GetWeatherData().hours_[0].cloud == 100);
        REQUIRE(request_london.GetWeatherData().hours_[0].condition == 1189);
        REQUIRE(request_london.GetWeatherData().hours_[0].wind_degree == 243);
        REQUIRE(request_london.GetWeatherData().hours_[0].wind_kph == 28.1);
        REQUIRE(request_london.GetWeatherData().hours_[0].dewpoint_f == 41.4);
        REQUIRE(request_london.GetWeatherData().hours_[0].pressure_mb == 997.0);
        REQUIRE(request_london.GetWeatherData().hours_[0].windchill_f == 38.7);
        REQUIRE(request_london.GetWeatherData().hours_[0].heatindex_f == 45.9);
    }

    SECTION("test 5th hour is set up correctly according to json but only hour struct values are set") {

        REQUIRE(request_london.GetWeatherData().hours_[4].time == "2021-05-04 04:00");
        REQUIRE(request_london.GetWeatherData().hours_[4].temp_f == 45.2);
        REQUIRE(request_london.GetWeatherData().hours_[4].cloud == 100);
        REQUIRE(request_london.GetWeatherData().hours_[4].condition == 1153);
        REQUIRE(request_london.GetWeatherData().hours_[4].wind_degree == 255);
        REQUIRE(request_london.GetWeatherData().hours_[4].wind_kph == 28.3);
        REQUIRE(request_london.GetWeatherData().hours_[4].dewpoint_f == 41.2);
        REQUIRE(request_london.GetWeatherData().hours_[4].pressure_mb == 996.0);
        REQUIRE(request_london.GetWeatherData().hours_[4].windchill_f == 37.8);
        REQUIRE(request_london.GetWeatherData().hours_[4].heatindex_f == 45.2);
    }

    SECTION("test 16th hour is set up correctly according to json but only hour struct values are set") {

        REQUIRE(request_london.GetWeatherData().hours_[15].time == "2021-05-04 15:00");
        REQUIRE(request_london.GetWeatherData().hours_[15].temp_f == 53.8);
        REQUIRE(request_london.GetWeatherData().hours_[15].cloud == 87);
        REQUIRE(request_london.GetWeatherData().hours_[15].condition == 1063);
        REQUIRE(request_london.GetWeatherData().hours_[15].wind_degree == 296);
        REQUIRE(request_london.GetWeatherData().hours_[15].wind_kph == 25.6);
        REQUIRE(request_london.GetWeatherData().hours_[15].dewpoint_f == 32.9);
        REQUIRE(request_london.GetWeatherData().hours_[15].pressure_mb == 1004.0);
        REQUIRE(request_london.GetWeatherData().hours_[15].windchill_f == 49.3);
        REQUIRE(request_london.GetWeatherData().hours_[15].heatindex_f == 53.8);
    }

    SECTION("test 24th hour is set up correctly according to json but only hour struct values are set") {

        REQUIRE(request_london.GetWeatherData().hours_[23].time == "2021-05-04 23:00");
        REQUIRE(request_london.GetWeatherData().hours_[23].temp_f == 41.7);
        REQUIRE(request_london.GetWeatherData().hours_[23].cloud == 42);
        REQUIRE(request_london.GetWeatherData().hours_[23].condition == 1003);
        REQUIRE(request_london.GetWeatherData().hours_[23].wind_degree == 288);
        REQUIRE(request_london.GetWeatherData().hours_[23].wind_kph == 14.2);
        REQUIRE(request_london.GetWeatherData().hours_[23].dewpoint_f == 37);
        REQUIRE(request_london.GetWeatherData().hours_[23].pressure_mb == 1006.0);
        REQUIRE(request_london.GetWeatherData().hours_[23].windchill_f == 36.1);
        REQUIRE(request_london.GetWeatherData().hours_[23].heatindex_f == 41.7);
    }

    SECTION("test location setup for London request_london in past 7 days different date") {

        REQUIRE(request_london.GetWeatherData().location_.name == "London");
        REQUIRE(request_london.GetWeatherData().location_.region == "City of London, Greater London");
        REQUIRE(request_london.GetWeatherData().location_.country == "United Kingdom");
        REQUIRE(request_london.GetWeatherData().location_.lat == 51.52);
        REQUIRE(request_london.GetWeatherData().location_.lon == -0.11);
    }
    
    SECTION("test first hour set up correctly different date still London") {

        REQUIRE(request_london_later.GetWeatherData().hours_[0].time == "2021-05-03 00:00");
        REQUIRE(request_london_later.GetWeatherData().hours_[0].temp_f == 43.9);
        REQUIRE(request_london_later.GetWeatherData().hours_[0].cloud == 79);
        REQUIRE(request_london_later.GetWeatherData().hours_[0].condition == 1240);
        REQUIRE(request_london_later.GetWeatherData().hours_[0].wind_degree == 231);
        REQUIRE(request_london_later.GetWeatherData().hours_[0].wind_kph == 9.7);
        REQUIRE(request_london_later.GetWeatherData().hours_[0].dewpoint_f == 41.2);
        REQUIRE(request_london_later.GetWeatherData().hours_[0].pressure_mb == 1021.0);
        REQUIRE(request_london_later.GetWeatherData().hours_[0].windchill_f == 40.3);
        REQUIRE(request_london_later.GetWeatherData().hours_[0].heatindex_f == 43.9);
        
    }

    SECTION("test 9th hour set up correctly different date still London") {

        REQUIRE(request_london_later.GetWeatherData().hours_[8].time == "2021-05-03 08:00");
        REQUIRE(request_london_later.GetWeatherData().hours_[8].temp_f == 48.3);
        REQUIRE(request_london_later.GetWeatherData().hours_[8].cloud == 82);
        REQUIRE(request_london_later.GetWeatherData().hours_[8].condition == 1009);
        REQUIRE(request_london_later.GetWeatherData().hours_[8].wind_degree == 222);
        REQUIRE(request_london_later.GetWeatherData().hours_[8].wind_kph == 15.4);
        REQUIRE(request_london_later.GetWeatherData().hours_[8].dewpoint_f == 38.2);
        REQUIRE(request_london_later.GetWeatherData().hours_[8].pressure_mb == 1018.0);
        REQUIRE(request_london_later.GetWeatherData().hours_[8].windchill_f == 44.3);
        REQUIRE(request_london_later.GetWeatherData().hours_[8].heatindex_f == 48.3);

    }

    SECTION("test 18th hour set up correctly different date still London") {

        REQUIRE(request_london_later.GetWeatherData().hours_[17].time == "2021-05-03 17:00");
        REQUIRE(request_london_later.GetWeatherData().hours_[17].temp_f == 47.7);
        REQUIRE(request_london_later.GetWeatherData().hours_[17].cloud == 100);
        REQUIRE(request_london_later.GetWeatherData().hours_[17].condition == 1189);
        REQUIRE(request_london_later.GetWeatherData().hours_[17].wind_degree == 209);
        REQUIRE(request_london_later.GetWeatherData().hours_[17].wind_kph == 34.2);
        REQUIRE(request_london_later.GetWeatherData().hours_[17].dewpoint_f == 41.6);
        REQUIRE(request_london_later.GetWeatherData().hours_[17].pressure_mb == 1006.0);
        REQUIRE(request_london_later.GetWeatherData().hours_[17].windchill_f == 40.4);
        REQUIRE(request_london_later.GetWeatherData().hours_[17].heatindex_f == 47.7);

    }

    SECTION("test last hour set up correctly different date still London") {

        REQUIRE(request_london_later.GetWeatherData().hours_[23].time == "2021-05-03 23:00");
        REQUIRE(request_london_later.GetWeatherData().hours_[23].temp_f == 43.1);
        REQUIRE(request_london_later.GetWeatherData().hours_[23].cloud == 100);
        REQUIRE(request_london_later.GetWeatherData().hours_[23].condition == 1189);
        REQUIRE(request_london_later.GetWeatherData().hours_[23].wind_degree == 233);
        REQUIRE(request_london_later.GetWeatherData().hours_[23].wind_kph == 30.7);
        REQUIRE(request_london_later.GetWeatherData().hours_[23].dewpoint_f == 42.6);
        REQUIRE(request_london_later.GetWeatherData().hours_[23].pressure_mb == 997.0);
        REQUIRE(request_london_later.GetWeatherData().hours_[23].windchill_f == 38.3);
        REQUIRE(request_london_later.GetWeatherData().hours_[23].heatindex_f == 44.9);

    }
    
    SECTION("test program works for different city Tokyo location test") {
        
        REQUIRE(request_tokyo.GetWeatherData().location_.name == "Tokyo");
        REQUIRE(request_tokyo.GetWeatherData().location_.region == "Tokyo");
        REQUIRE(request_tokyo.GetWeatherData().location_.country == "Japan");
        REQUIRE(request_tokyo.GetWeatherData().location_.lat == 35.69);
        REQUIRE(request_tokyo.GetWeatherData().location_.lon == 139.69);
        
    }
    
    SECTION("test program works for different city first hour") {
        
        REQUIRE(request_tokyo.GetWeatherData().hours_[0].time == "2021-05-04 00:00");
        REQUIRE(request_tokyo.GetWeatherData().hours_[0].temp_f == 74.8);
        REQUIRE(request_tokyo.GetWeatherData().hours_[0].cloud == 2);
        REQUIRE(request_tokyo.GetWeatherData().hours_[0].condition == 1003);
        REQUIRE(request_tokyo.GetWeatherData().hours_[0].wind_kph == 2.9);
        REQUIRE(request_tokyo.GetWeatherData().hours_[0].wind_degree == 277);
        REQUIRE(request_tokyo.GetWeatherData().hours_[0].dewpoint_f == 50.9);
        REQUIRE(request_tokyo.GetWeatherData().hours_[0].pressure_mb == 1017.0);
        REQUIRE(request_tokyo.GetWeatherData().hours_[0].windchill_f == 74.8);
        REQUIRE(request_tokyo.GetWeatherData().hours_[0].heatindex_f == 76.6);
        
    }

    SECTION("test program works for different city 12th hour") {

        REQUIRE(request_tokyo.GetWeatherData().hours_[11].time == "2021-05-04 11:00");
        REQUIRE(request_tokyo.GetWeatherData().hours_[11].temp_f == 71.1);
        REQUIRE(request_tokyo.GetWeatherData().hours_[11].cloud == 2);
        REQUIRE(request_tokyo.GetWeatherData().hours_[11].condition == 1003);
        REQUIRE(request_tokyo.GetWeatherData().hours_[11].wind_kph == 18.0);
        REQUIRE(request_tokyo.GetWeatherData().hours_[11].wind_degree == 187);
        REQUIRE(request_tokyo.GetWeatherData().hours_[11].dewpoint_f == 42.3);
        REQUIRE(request_tokyo.GetWeatherData().hours_[11].pressure_mb == 1019.0);
        REQUIRE(request_tokyo.GetWeatherData().hours_[11].windchill_f == 71.1);
        REQUIRE(request_tokyo.GetWeatherData().hours_[11].heatindex_f == 74.6);

    }


    SECTION("test program works for different city 24th hour") {

        REQUIRE(request_tokyo.GetWeatherData().hours_[23].time == "2021-05-04 23:00");
        REQUIRE(request_tokyo.GetWeatherData().hours_[23].temp_f == 64.7);
        REQUIRE(request_tokyo.GetWeatherData().hours_[23].cloud == 37);
        REQUIRE(request_tokyo.GetWeatherData().hours_[23].condition == 1003);
        REQUIRE(request_tokyo.GetWeatherData().hours_[23].wind_kph == 16.1);
        REQUIRE(request_tokyo.GetWeatherData().hours_[23].wind_degree == 189);
        REQUIRE(request_tokyo.GetWeatherData().hours_[23].dewpoint_f == 51.5);
        REQUIRE(request_tokyo.GetWeatherData().hours_[23].pressure_mb == 1019.0);
        REQUIRE(request_tokyo.GetWeatherData().hours_[23].windchill_f == 64.7);
        REQUIRE(request_tokyo.GetWeatherData().hours_[23].heatindex_f == 66.5);

    }
}

