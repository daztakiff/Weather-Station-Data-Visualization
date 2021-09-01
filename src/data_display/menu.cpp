//
// Created by Zachary Takiff on 5/1/21.
//

#include "data_display/menu.h"

namespace menu {
    
    Menu::Menu() {}

    void Menu::DrawMenu() {
        DrawInstructions();
        DrawCredits();
    }

    void Menu::DrawInstructions() {
        ci::gl::drawString("Press enter/return to go to the map and station", glm::vec2(280, 300), kTextColor, ci::Font("Arial", 15));
        ci::gl::drawString("Press backspace/delete to go back a menu at any point", glm::vec2(280, 315), kTextColor, ci::Font("Arial", 15));
        ci::gl::drawString("Use up and down arrows to navigate by", glm::vec2(280, 330), kTextColor, ci::Font("Arial", 15));
        ci::gl::drawString("date and by hour in the map and station menu", glm::vec2(280, 345), kTextColor, ci::Font("Arial", 15));
    }

    void Menu::DrawCredits() {
        ci::gl::drawString("Weather Station Model", glm::vec2(20, 10), kTextColor, ci::Font("Arial", 30));
        ci::gl::drawString("Developed by Zachary Takiff", glm::vec2(20, 40), kTextColor, ci::Font("Arial", 30));
    }
}
