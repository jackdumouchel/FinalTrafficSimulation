#ifndef __TRAFFICLIGHT_H__
#define __TRAFFICLIGHT_H__

#include "VehicleBase.h"

class TrafficLight {
    private:
        LightColor lightColor;
        int timeGreen;
        int timeRed;
        int timeYellow;
        int timeChange;
    public:
        TrafficLight();
        TrafficLight(LightColor lightColor, int timeGreen, int timeRed, int timeYellow);
        TrafficLight(const TrafficLight &other);
        TrafficLight(TrafficLight &&other);
        TrafficLight& operator=(const TrafficLight& other);
        TrafficLight& operator=(TrafficLight&& other);
        ~TrafficLight();
        LightColor getLightColor();
        LightColor setLightColor(LightColor lightColor);
        int getTimeGreen();
        int getTimeRed();
        int getTimeYellow();
        int getTimeChange();
        void decreaseTime();
};
#endif
