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

Intersection::~Intersection()
{
}

/*
 * Override of Tile's getStraight(), determines what direction the vehicle occupying it 
 * is going in and returns "straight" for that Vehicle
 */
Tile *Intersection::getNext()
{
  switch (this->getCurrentVehicle()->getVehicleOriginalDirection())
  {
  case Direction::north:
    return this->north;
    break;
  case Direction::east:
    return this->east;
    break;
  case Direction::south:
    return this->south;
    break;
  case Direction::west:
    return this->west;
    break;
  default:
    return Tile::getNext();
  }
}

/**
 * Similair to IntersectionTile::getStraight(), returns pointer to the "right" Tiles based on
 * the current direction of the Vehicle occupying it. 
 */
Tile *Intersection::getRight()
{
  switch (this->getCurrentVehicle()->getVehicleOriginalDirection())
  {
  case Direction::north:
    return this->east;
    break;
  case Direction::east:
    return this->south;
    break;
  case Direction::south:
    return this->west;
    break;
  case Direction::west:
    return this->north;
    break;
  }
}

Tile *Intersection::getPrev()
{

  if (this->getCurrentVehicle() == nullptr)
  {
    return Tile::getPrev();
  }

  switch (this->getCurrentVehicle()->getVehicleOriginalDirection())
  {
  case Direction::north:
    return this->south;
    break;
  case Direction::east:
    return this->west;
    break;
  case Direction::south:
    return this->north;
    break;
  case Direction::west:
    return this->east;
    break;
  }
}

/*
 * Returns reference to TrafficLight to be used in Vehicle
 */
TrafficLight *Intersection::getTrafficLight()
{
  return this->trafficLight;
}

#endif