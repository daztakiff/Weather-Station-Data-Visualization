//
// Created by Zachary Takiff on 5/1/21.
//

#ifndef FINAL_PROJECT_MENU_H
#define FINAL_PROJECT_MENU_H

#include <cinder/Color.h>
#include "cinder/gl/gl.h"
#include "cinder/Font.h"

namespace menu {

    class Menu {

    public:
        
        /**
         * Menu screen has credits and directions for the program
         */
        Menu();
        
        /**
         * Draws the menu on the screen called in draw when state is set to the menu state
         */
        void DrawMenu();
        
    private:

        /**
         * Draws the instruction around the cloud in the center of the screen
         */
        void DrawInstructions();

        /**
         * draws the credits at the top left corner of the screen
         */
        void DrawCredits();
        
        const ci::Color kTextColor = ci::Color("black");
    };
};


#endif //FINAL_PROJECT_MENU_H
