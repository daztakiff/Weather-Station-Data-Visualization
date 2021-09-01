#include "data_display/weather_station_app.h"

using weather_station::WeatherStationApp;

void prepareSettings(WeatherStationApp::Settings* settings) {
    settings->setResizable(false);

    settings->setFrameRate(20);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(WeatherStationApp, ci::app::RendererGl, prepareSettings);
