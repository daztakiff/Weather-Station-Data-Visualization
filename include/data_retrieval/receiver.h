//
// Created by Zachary Takiff on 4/19/21.
//
#include "../../httplib.h"
#include <iostream>
#include "weather_data.h"
#include "json.hpp"
#include "picohttpclient.hpp"
#include "sstream"


#ifndef FINAL_PRODUCT_API_RECEIVER_H
#define FINAL_PRODUCT_API_RECEIVER_H

namespace receiver {

    using std::string;
    using nlohmann::json;

    class Request {

    public:

        /**
         * Default constructor
         */
        Request();

        /**
         * Should populate the weather_data object with json data right now just returns built request to send
         * @param city city we are calling api for must be capitalize
         * @param time time_ we are calling api for must be in year-mont-day format and because we are sing non-payed
         * version of api we can only call on last 7 days
         * @return 
         */
        void GetData(string city, string time);

        /**
         * Returns weather_data object data is public from here
         * @return 
         */
        weather_data::WeatherData GetWeatherData();

    private:

        /**
         * helper method that puts together the http request from url used to extract data from weather API
         * @param city city we are getting data from
         * @param time time_ in form year-month-day must be in form to make valid request
         * @return string request to the server in correct format for API
         */
        static string BuildRequest(string city, string time);

        /**
         * Should be used to pass in api request to website and get back json once json is returned populate
         * weather_data object
         */
        void ProcessResponse(string to_process);

        /**
         * Cleans up json response by only appending actual json lines and removing \n and \r from string returned from
         * request
         * @param response input must have been from http request made by piohttpclient.hpp
         * @return cleaned up json string ready to parse
         */
        static string CleanUpBody(HTTPResponse response);

        weather_data::WeatherData weatherData;
    };
}


#endif //FINAL_PRODUCT_API_RECEIVER_H
