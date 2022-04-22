#ifndef __VEHICLE_BASE_CPP__
#define __VEHICLE_BASE_CPP__

#include "VehicleBase.h"

int VehicleBase::vehicleCount = 0;

//Constuctor
VehicleBase::VehicleBase(){}

//Constuctor
VehicleBase::VehicleBase(VehicleType type, Direction direction, bool turnRight)
    : vehicleID(VehicleBase::vehicleCount++),
      vehicleType(type),
      vehicleDirection(direction),
      turnRight(turnRight)
{
  //Sets corresponding lengths for each type of car
  if(type == VehicleType::car){
        this -> length = 2;
    }
    else if(type == VehicleType::suv){
        this -> length = 3;
    }
    else{
        this -> length = 4;
    }
}

//Constructor
VehicleBase::VehicleBase(VehicleType type, Direction direction)
  : vehicleID(VehicleBase::vehicleCount++),
      vehicleType(type),
      vehicleDirection(direction)
{
  if(type == VehicleType::car){
        this -> length = 2;
    }
    else if(type == VehicleType::suv){
        this -> length = 3;
    }
    else{
        this -> length = 4;
    }
}

//Copy Constructor
VehicleBase::VehicleBase(const VehicleBase &other)
    : vehicleID(other.vehicleID),
      vehicleType(other.vehicleType),
      vehicleDirection(other.vehicleDirection),
      turnRight(other.turnRight)
{
  if(other.vehicleType == VehicleType::car){
        this -> length = 2;
    }
    else if(other.vehicleType == VehicleType::suv){
        this -> length = 3;
    }
    else{
        this -> length = 4;
    }
}

//Destructor
VehicleBase::~VehicleBase() {}


#endif