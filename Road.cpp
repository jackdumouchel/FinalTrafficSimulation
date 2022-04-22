#ifndef __ROAD_CPP__
#define __ROAD_CPP__

#include "Road.h"
#include <vector>
#include "VehicleBase.h"
#include "Tile.h"
#include "Intersection.h"

using namespace std;

//Constructor
//Road::Road(){}


//Consturcotr
Road::Road(int number_of_sections_before_intersection, Intersection* it1, Intersection* it2, Direction direction){

    //Ensures there is at least one tile before the intersection
    if (number_of_sections_before_intersection < 1) {
      string str = "Invalid road length (Check input file): ";
      throw runtime_error(str.c_str());
    }
    //Length of road not including invisible tiles
    this -> roadLength = number_of_sections_before_intersection * 2 + 2;
    this -> direction = direction;
    Tile* prevTile = NULL;

   //Adds tiles to the vector including the invisible tiles.
    for (int i = 0; i < number_of_sections_before_intersection + 4; i++) {
      Tile* tile = new Tile();

      if(prevTile != NULL){
        tile->setPrevTile(prevTile);
        prevTile->setNextTile(tile);
      }
      prevTile = tile;
      this->road.push_back(tile);
    }


    road.push_back(it1);
    road.push_back(it2);

    prevTile->setNextTile(it1);
    it1->setPrevTile(prevTile);

    Tile* transition = new Tile();

    if(direction == Direction::north){
      it1 -> setSouth(prevTile);
      it1 -> setNorth(it2);
      it2 -> setSouth(it1);
      it2 -> setNorth(transition);
    }
    if(direction == Direction::east){
      it1 -> setWest(prevTile);
      it1 -> setEast(it2);
      it2 -> setWest(it1);
      it2 -> setEast(transition);
    }
    if(direction == Direction::west){
      it1 -> setEast(prevTile);
      it1 -> setWest(it2);
      it2 -> setEast(it1);
      it2 -> setWest(transition);
    }
    if(direction == Direction::south){
      it1 -> setNorth(prevTile);
      it1 -> setSouth(it2);
      it2 -> setNorth(it1);
      it2 -> setSouth(transition);
    }

    road.push_back(transition);
    prevTile = transition;

    for(int i = 0; i < number_of_sections_before_intersection + 3; i++){
      Tile* tile = new Tile();

      if(prevTile != NULL){
        tile->setPrevTile(prevTile);
        prevTile->setNextTile(tile);
      }
      prevTile = tile;
      this->road.push_back(tile);
    }
  }

//Destructor
Road::~Road() {
  for (int i = 0; i < this -> road.size(); i++) {
    if(road[i]->getName() == "Tile"){
      delete this -> road[i];
    }
  }
  road.clear();
}

//Connects all of the tiles together in the vector

//Returns the road length
int Road::getLength() {
  return this->roadLength;
}

//Returns the direction
Direction Road::getDirection() {
  return this->direction;
}

//If it is possible for a vehicle to be deleted
bool Road::canDeleteVehicle() {
  if (road.at(roadLength + 7) -> getTileStatus() == true) {
    return false;
  }
  else {
    return true;
  }
}

//If the vehicle can be spawned in the invisible tile area at beginning of road
bool Road::canCreateVehicle(VehicleBase* vehicle) {
  for (int i = 0; i < vehicle -> getLength(); i++) {
    if (this->road.at(i) -> getTileStatus() == false) {
      return false;
    }
  }
  return true;
}

//Sets invisible tiles to occupied
void Road::CreateVehicle(VehicleBase* vehicle) {
  if (canCreateVehicle(vehicle)) {
    for (int i = 0; i < vehicle->getLength(); i++) {
      this -> getTile(i)->setOccupiedTile(vehicle);
    }
  }
}

//Removes the vehicle once it reaches the end of the road (invisible tiles)
void Road::DeleteVehicle(VehicleBase* vehicle) {
  if (canDeleteVehicle()) {
    for (int i = 0; i < vehicle->getLength(); i++) {
      this -> getTile(this -> road.size() -1 - i) -> setOpenTile();
    }
  }
  //Destroys the vehicle
  delete vehicle;
}

//Returns a tile in the vector at a specified index
Tile* Road::getTile(int index) {
  return this -> road.at(index);
}

Tile* Road::findBackofCar(int index) {
  if (getTile(index) == road.at(0)) {
    return getTile(index);
  }
  else {
    int length = getTile(index) -> getCurrentVehicle() -> getLength();
    for (int i = 1; i< length; i++) {
      if (index -i == 0) {
        return getTile(index-i);
      }
      else {
        if (getTile(index-i) -> containsVehicle() == false) {
          return getTile(index-i+1);
        }
        else {
          if (getTile(index-i)-> getCurrentVehicle()->getVehicleID() != getTile(index) -> getCurrentVehicle()->getVehicleID()) {
            return getTile(index-i+1);
          }
        }
      }
    }
  }
  return nullptr;
}

void Road::moveVehicleForward(int tileIndex) {
  if(isFrontofVehicle(tileIndex)){
    if(getTile(tileIndex)->getNext()->getTileStatus()){
      getTile(tileIndex) -> getNext() -> setOccupiedTile(getTile(tileIndex)->getCurrentVehicle());
      findBackofCar(tileIndex) -> setOpenTile();
     }
  }
}


void Road::moveVehicles(int number_of_sections_before_intersection, Intersection* turnTile, TrafficLight light) {
  for (int i = road.size() - 2; i >= 0; i--) {
    if (getTile(i) -> containsVehicle()) {
      moveVehicleForward(i);
    }
  }
}

vector<VehicleBase *> Road::currVehicles() {
	// Initialize vector
	vector<VehicleBase *> snapshot(roadLength, nullptr);

	// Loop through Tiles and add Vehicle if it is on a Tile
	for (int i = 0; i < roadLength; i++)
	{
    if(road[i+4]->containsVehicle()){
      snapshot[i] = road.at(i + 4) -> getCurrentVehicle();
    }
	}
	return snapshot;
}

void Road::setOccupiedTiles(VehicleBase vehicle){
  for(int i = 4; i < vehicle.getLength()+4; i++){
    this->road.at(i)->setOccupiedTile(&vehicle);
  }
}
#endif
