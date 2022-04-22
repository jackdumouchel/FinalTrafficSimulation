#ifndef __ROAD_H__
#define __ROAD_H__

#include "VehicleBase.h"
#include "TrafficLight.h"
#include "Tile.h"
#include "Intersection.h"
#include <vector>

class Road {
    private:
        vector<Tile *> road;
        int roadLength;
        Direction direction;
        inline bool isFrontofVehicle(int tileIndex){return (road.at(tileIndex)->getCurrentVehicle()->getVehicleID() != road.at(tileIndex)->getNext()->getCurrentVehicle()->getVehicleID());};
        inline bool isBackofVehicle(int tileIndex){return (road.at(tileIndex)->getCurrentVehicle()->getVehicleID() != road.at(tileIndex)->getPrev()->getCurrentVehicle()->getVehicleID());};


    public:
        //Road();
        Road(int number_of_sections_before_intersection, Intersection* it1, Intersection* it2, Direction direction);
        ~Road();

        Tile* getTile(int index);
        void setTiles();
        int getLength();
        Direction getDirection();
        bool canDeleteVehicle();
        bool canCreateVehicle(VehicleBase* vehicle);
        void CreateVehicle(VehicleBase* vehicle);
        void DeleteVehicle(VehicleBase* vehicle);
        void moveVehicleForward(int tileIndex);
        void moveVehicleRight(int tileIndex, Tile* right);
        Tile* findBackofCar(int index);
        void moveVehicles(int number_of_sections_before_intersection, Intersection* turnTile, TrafficLight light);
        vector<VehicleBase *> currVehicles();
        void setOccupiedTiles(VehicleBase vehicle);

};

#endif
