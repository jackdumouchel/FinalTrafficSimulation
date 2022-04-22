#ifndef __INTERSECTION_H__
#define __INTERSECTION_H__

#include "Tile.h"
#include "TrafficLight.h"

class Intersection : public Tile {
    private:
        Tile *north;
        Tile *south;
        Tile *east;
        Tile *west;
        TrafficLight *trafficLight;

    public:
        Intersection(TrafficLight* trafficLight);
        ~Intersection();
        Tile *getNext() override;
        Tile *getPrev() override;
        Tile *getRight();
        TrafficLight *getTrafficLight();

        inline Tile *getNorth() { return this->north; };
        inline Tile *getEast() { return this->east; };
        inline Tile *getSouth() { return this->south; };
        inline Tile *getWest() { return this->west; };

        // Setter methods
        inline void setNorth(Tile *north) { this->north = north; }
        inline void setEast(Tile *east) { this->east = east; }
        inline void setSouth(Tile *south) { this->south = south; }
        inline void setWest(Tile *west) { this->west = west; }


};
#endif