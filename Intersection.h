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
        Intersection(const Intersection& other);
        Intersection(Intersection&& other);
        Intersection& operator=(Intersection&& other);
        Intersection& operator=(Intersection& other);

        Tile *getNext() override;
        Tile *getPrev() override;
        Tile *getRight();
        TrafficLight *getTrafficLight();

        inline Tile *getNorth() { return north; };
        inline Tile *getEast() { return east; };
        inline Tile *getSouth() { return south; };
        inline Tile *getWest() { return west; };

        // Setter methods
        inline void setNorth(Tile *north) { this->north = north; }
        inline void setEast(Tile *east) { this->east = east; }
        inline void setSouth(Tile *south) { this->south = south; }
        inline void setWest(Tile *west) { this->west = west; }


};
#endif
