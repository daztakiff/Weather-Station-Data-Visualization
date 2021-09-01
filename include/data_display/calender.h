//
// Created by Zachary Takiff on 5/2/21.
//

#ifndef FINAL_PROJECT_CALENDER_H
#define FINAL_PROJECT_CALENDER_H

#include "iostream"

namespace calender {

 class Calendar {

 public:
     
     /**
      * Calender used to keep record of how many days are in each month can be used to store current date increment
      * or decrement by the day and get back a different month
      */
     Calendar();
     
     /**
      * using a string set up in year-month-day will fill all values of the calendar
      * @param day_info string set up in year-month-day
      */
     void SetupCalendar(std::string day_info);
     
     /**
      * Increases day goes over from 31/30/28 depending on the month to 1 of the subsequent month
      */
     void IncrementDay();
     
     /**
      * Decreases day goes over from 1 depending on the month to 31/30/28 of the previous month
      */
     void DecrementDay();

     /**
      * Takes in the current ints for day month and year and puts together a string to return
      * @return string of recent year-month-day
      */
     std::string GetDate();

 private:
     
     int days_past = 0;
     std::string date_string;
     
     int day;
     int month;
     int year;
     
 };   
    
}


#endif //FINAL_PROJECT_CALENDER_H
