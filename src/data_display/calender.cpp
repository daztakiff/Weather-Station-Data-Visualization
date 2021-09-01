//
// Created by Zachary Takiff on 5/2/21.
//

#include "data_display/calender.h"
#include "string"

namespace calender {


    Calendar::Calendar() {}

    void Calendar::SetupCalendar(std::string day_info) {

        date_string = day_info;

        year = stoi(day_info.substr(0, 4));

        month = stoi(day_info.substr(5, 2));

        day = stoi(day_info.substr(8, 2));
    }

    std::string Calendar::GetDate() {

        std::string day_string;
        std::string month_string;
        
        if (day < 10) {
            day_string = "0" + std::to_string(day);
        } else {
            day_string = std::to_string(day);
        }

        if (month < 10) {
            month_string = "0" + std::to_string(month);
        } else {
            month_string = std::to_string(month);
        }

        std::string date = std::to_string(year) + "-" + month_string + "-" + day_string;

        date_string = date;
        
        return date_string;
    }

    void Calendar::IncrementDay() {

        if (days_past > 0) {
            switch (month) {
                case 1:
                case 3:
                case 5:
                case 7:
                case 8:
                case 10:
                case 12:
                    if (day < 31) {
                        day++;
                        days_past--;
                        break;
                    } else {
                        month++;
                        day = 1;
                        days_past--;
                        break;
                    }
                case 4:
                case 6:
                case 9:
                case 11:
                    if (day < 30) {
                        day++;
                        days_past--;
                        break;
                    } else {
                        month++;
                        day = 1;
                        days_past--;
                        break;
                    }
                case 2:
                    if (day < 28) {
                        day++;
                        days_past--;
                        break;
                    } else {
                        month++;
                        day = 1;
                        days_past--;
                        break;
                    }
            }
        }
    }

    void Calendar::DecrementDay() {

        if (days_past < 6) {
            if (day > 1) {
                day--;
                days_past++;
            } else {
                switch (month) {
                    case 1:
                    case 2:
                    case 4:
                    case 6:
                    case 8:
                    case 9:
                    case 11:
                        month--;
                        day = 31;
                        days_past++;
                        break;
                    case 5:
                    case 7:
                    case 10:
                    case 12:
                        month--;
                        day = 30;
                        days_past++;
                        break;
                    case 3:
                        month--;
                        day = 29;
                        days_past++;
                        break;
                }
            }
        }
    }
}