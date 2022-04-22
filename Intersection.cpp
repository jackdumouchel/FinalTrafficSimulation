#ifndef __INTERSECTION_CPP__
#define __INTERSECTION_CPP__

#include "Tile.h"
#include "Intersection.h"
#include "TrafficLight.h"
#include "VehicleBase.h"
#include <iostream>

/*
 *  Typical use: IntersectionTile should have a traffic light
 */
Intersection::Intersection(TrafficLight *trafficLight) : Tile()
{
  this->name = "Intersection";
  this->trafficLight = trafficLight;
}

Intersection::~Intersection(){}


Intersection::Intersection(const Intersection& other) {
  north = other.north;
  south = other.south;
  east = other.east;
  west = other.west;
  trafficLight = other.trafficLight;
}

Intersection::Intersection(Intersection&& other) {
  north = other.north;
  south = other.south;
  east = other.east;
  west = other.west;
  trafficLight = other.trafficLight;

  other.north = nullptr;
  other.south = nullptr;
  other.east = nullptr;
  other.west = nullptr;
  other.trafficLight = nullptr;
}

Intersection& Intersection::operator=(Intersection&& other) {
  if (this == &other) {
    return *this;
  }
  north = other.north;
  south = other.south;
  east = other.east;
  west = other.west;
  trafficLight = other.trafficLight;

  other.north = nullptr;
  other.south = nullptr;
  other.east = nullptr;
  other.west = nullptr;
  other.trafficLight = nullptr;

  return *this;


}

Intersection& Intersection::operator=(Intersection& other){
  if (this == &other) {
    return *this;
  }
  north = other.north;
  south = other.south;
  east = other.east;
  west = other.west;
  trafficLight = other.trafficLight;

  return *this;
}

/*
 * Override of Tile's getStraight(), determines what direction the vehicle occupying it
 * is going in and returns "straight" for that Vehicle
 */
Tile* Intersection::getNext() {
  if (getCurrentVehicle() -> getVehicleOriginalDirection() == Direction::north) {
    return north;
  }
  else if (getCurrentVehicle() -> getVehicleOriginalDirection() == Direction::south) {
    return south;
  }
  else if (getCurrentVehicle() -> getVehicleOriginalDirection() == Direction::east) {
    return east;
  }
  else if (getCurrentVehicle() -> getVehicleOriginalDirection() == Direction::west) {
    return west;
  }
  else {
    return Tile::getNext();
  }
}

Tile* Intersection::getPrev() {
  if (getCurrentVehicle() -> getVehicleOriginalDirection() == Direction::north) {
    return south;
  }
  else if (getCurrentVehicle() -> getVehicleOriginalDirection() == Direction::south) {
    return north;
  }
  else if (getCurrentVehicle() -> getVehicleOriginalDirection() == Direction::east) {
    return west;
  }
  else if (getCurrentVehicle() -> getVehicleOriginalDirection() == Direction::west) {
    return east;
  }
  else {
    return Tile::getPrev();
  }
}


Tile* Intersection::getRight(){
  if (getCurrentVehicle() -> getVehicleOriginalDirection() == Direction::north) {
    return east;
  }
  else if (getCurrentVehicle() -> getVehicleOriginalDirection() == Direction::south) {
    return west;
  }
  else if (getCurrentVehicle() -> getVehicleOriginalDirection() == Direction::east) {
    return south;
  }
  else if (getCurrentVehicle() -> getVehicleOriginalDirection() == Direction::west) {
    return north;
  }
  else {
    return Tile::getNext();
  }
}


TrafficLight* Intersection::getTrafficLight() {
  return trafficLight;
}

#endif
