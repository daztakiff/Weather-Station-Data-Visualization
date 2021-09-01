//
// Created by Zachary Takiff on 5/1/21.
//

#include "data_display/map.h"

namespace world_map {
    
    World_Map::World_Map() {}
    
    void World_Map::DrawCurrentTime() {
        ci::gl::drawString(calendar_.GetDate(), glm::vec2(620, 30), ci::Color("black"), ci::Font("Courier", 20));
    }
    
    void World_Map::DrawLockedAndHoverLocation() {
        
        ci::gl::color(kTextColor);
        ci::gl::drawString("clicked Lat and Lon (" + std::to_string(current_coords_.y) + ", " + std::to_string(current_coords_.x) + ") click to lock in coords to search", glm::vec2(300, 10), kTextColor, ci::Font("Arial", 10));
        ci::gl::drawString("Lat and Lon to search (" + std::to_string(locked_in_coords_.y) + ", " + std::to_string(locked_in_coords_.x) + ") press enter to search", glm::vec2(300, 30), kTextColor, ci::Font("Arial", 10));

    }
    
    void World_Map::HandleMouse(const glm::ivec2 &position) {
        
        current_coords_.x = position.x;
        current_coords_.y = position.y;
        
        if (current_coords_.x < left_longitude_point.x) {
            current_coords_.x = 0;
        } else if (current_coords_.x > left_longitude_point.x + (22 * kDistancePerTenLon)) {
            current_coords_.x = 0;
        } else {
            current_coords_.x = ((current_coords_.x - left_longitude_point.x) * kDegreePerPixelLon) - 150;
        }
        
        if (current_coords_.y < top_lat_point.y) {
            current_coords_.y = 0;
        } else if (current_coords_.y > bottom_lat_point.y) {
            current_coords_.y = 0;
        } else if (current_coords_.y >= top_lat_point.y && current_coords_.y < sixty_six_lat_point.y) {
            current_coords_.y = (75 - ((current_coords_.y - top_lat_point.y) * kDegreePerPixel75And66Lat));
        } else if (current_coords_.y >= sixty_six_lat_point.y && current_coords_.y < sixty_lat_point.y) {
            current_coords_.y = (66.5 - ((current_coords_.y - sixty_six_lat_point.y) * kDegreePerPixel66And60Lat));
        } else if (current_coords_.y >= sixty_lat_point.y && current_coords_.y < forty_five_lat_point.y) {
            current_coords_.y = (60 - ((current_coords_.y - sixty_lat_point.y) * kDegreePerPixel60And45Lat));
        } else if (current_coords_.y >= forty_five_lat_point.y && current_coords_.y < thirty_lat_point.y) {
            current_coords_.y = (45 - ((current_coords_.y - forty_five_lat_point.y) * kDegreePerPixel45And30Lat));
        } else if (current_coords_.y >= thirty_lat_point.y && current_coords_.y < twenty_three_lat_point.y) {
            current_coords_.y = (30 - ((current_coords_.y - thirty_lat_point.y) * kDegreePerPixel30And23Lat));
        } else if (current_coords_.y >= twenty_three_lat_point.y && current_coords_.y < fifteen_lat_point.y) {
            current_coords_.y = (23.5 - ((current_coords_.y - twenty_three_lat_point.y) * kDegreePerPixel23And15Lat));
        } else if (current_coords_.y >= fifteen_lat_point.y && current_coords_.y < zero_lat_point.y) {
            current_coords_.y = (15 - ((current_coords_.y - fifteen_lat_point.y) * kDegreePerPixel15And0Lat));
        } else if (current_coords_.y >= zero_lat_point.y && current_coords_.y < neg_fifteen_lat_point.y) {
            current_coords_.y = (0 - ((current_coords_.y - zero_lat_point.y) * kDegreePerPixel0And15Lat));
        } else if (current_coords_.y >= neg_fifteen_lat_point.y && current_coords_.y < neg_twenty_three_lat_point.y) {
            current_coords_.y = (-15 - ((current_coords_.y - neg_fifteen_lat_point.y) * kDegreePerPixel15And23Lat));
        } else if (current_coords_.y >= twenty_three_lat_point.y && current_coords_.y < neg_thirty_lat_point.y) {
            current_coords_.y = (-23.5 - ((current_coords_.y - neg_twenty_three_lat_point.y) * kDegreePerPixel23And30Lat));
        } else if (current_coords_.y >= neg_thirty_lat_point.y && current_coords_.y < bottom_lat_point.y) {
            current_coords_.y = (-30 - ((current_coords_.y - neg_thirty_lat_point.y) * kDegreePerPixel30And45Lat));
            
        }
    }

    void World_Map::HandleClick() {

        locked_in_coords_ = current_coords_;
    }

    const glm::dvec2 &World_Map::GetLockedInCoords() const {
        return locked_in_coords_;
    }

    void World_Map::SetCalendar(const std::string time) {
        calendar_.SetupCalendar(time);
    }

    void World_Map::IncreaseDate() {
        calendar_.IncrementDay();
        to_display = calendar_.GetDate();
    }

    void World_Map::DecreaseDate() {
        calendar_.DecrementDay();
        to_display = calendar_.GetDate();
    }

    const std::string &World_Map::GetStringToDisplay() {
        return to_display;
    }

}