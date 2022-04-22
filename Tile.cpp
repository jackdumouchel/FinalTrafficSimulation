#ifndef __TILE_CPP__
#define __TILE_CPP__
#include "Tile.h"

//Constuctor
Tile::Tile() {
  this -> name = "Tile";
  this -> emptyTile = true;
  this -> nextTile = nullptr;
  this -> prevTile = nullptr;
}

//Destructor
Tile::~Tile() {
  delete this;
}

Tile::Tile(const Tile& other) {
  emptyTile = other.emptyTile;
  currentVehicle = other.currentVehicle;
  nextTile = other.nextTile;
  prevTile = other.prevTile;
}

Tile::Tile(Tile&& other) {
  emptyTile = other.emptyTile;
  currentVehicle = other.currentVehicle;
  nextTile = other.nextTile;
  prevTile = other.prevTile;

  other.emptyTile = true;
  other.currentVehicle = nullptr;
  other.nextTile = nullptr;
  other.prevTile = nullptr;
}


Tile& Tile::operator=(Tile&& other) {
  if (this == &other) {
    return *this;
  }
  emptyTile = other.emptyTile;
  currentVehicle = other.currentVehicle;
  nextTile = other.nextTile;
  prevTile = other.prevTile;

  other.emptyTile = true;
  other.currentVehicle = nullptr;
  other.nextTile = nullptr;
  other.prevTile = nullptr;


  return *this;
}

Tile& Tile::operator=(Tile& other) {
  if (this == &other) {
    return *this;
  }
  emptyTile = other.emptyTile;
  currentVehicle = other.currentVehicle;
  nextTile = other.nextTile;
  prevTile = other.prevTile;

  return *this;
}

//Finds the next tile on the road
Tile* Tile:: getNext() {
  return nextTile;
}

//Finds the previous tile on the road
Tile* Tile:: getPrev() {
  return prevTile;
}

//Sees if the tile is empty or not
bool Tile:: getTileStatus() {
  return  emptyTile;
}

//Sets the status of a tile to occupied
void Tile:: setOccupiedTile(VehicleBase* vehicle) {
  this -> emptyTile = false;
  this -> currentVehicle = vehicle;
}

//Sets the status of a tile to open (able for a vehicle to move to)
void Tile :: setOpenTile() {
  emptyTile = true;
  this -> currentVehicle = nullptr;
}

//Returns a vehicle occupying that tile
VehicleBase* Tile :: getCurrentVehicle(){
  return this -> currentVehicle;
}

//Sets the next tile
void Tile :: setNextTile(Tile *next) {
  this -> nextTile = next;
}

//Sets the previous tile
void Tile :: setPrevTile(Tile *prev) {
  this -> prevTile = prev;
}

#endif
