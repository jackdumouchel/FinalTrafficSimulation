#ifndef __MOVEVEHICLE_H__
#define __MOVEVEHICLE_H__

#include "VehicleBase.h"
#include "Tile.h"
#include "Intersection.h"

class MoveVehicle : public VehicleBase
{

  enum Turn
  {
    LEFT,
    RIGHT,
    STRAIGHT
  };

private:
  int length;                  // Vehicle length
  Tile *hptr;                  // Pointer to Tile where head of Vehicle is
  Tile *tptr;                  // Pointer to Tile where tail of Vehicle is
  bool willTurnRight;          // Vehicle is destined to turn right
  bool isTurningRight = false; // Vehicle is currently turning right
  int movesLeftInTurn;         // Number of moves left in a turn
  Direction currDirection;     // Current direction of the Vehicle
  bool hasGreen = false;
  bool reachedEndOfRoad = false;

  void setOccupiedTiles(); // Set all Tiles between head and tail to occupied
  void moveForward();      // Move the car forward a Tile
  bool canTurnRight(Intersection *it);

public:
  // Typical use: hptr here is a the queueHead in Road. tptr calculated in constructor based on length
  MoveVehicle(VehicleType vehicleType, Direction direction, int vehicleLength, bool willTurnRight);

  // Destructor
  ~MoveVehicle();

  // Getter methods
  int getLength();
  Direction getCurrDirection();
  Tile *getHptr();
  Tile *getTptr();
  Turn getTurn();
  inline bool hasReachedEndOfRoad() { return this->reachedEndOfRoad; }

  // Setter methods
  void setCurrDirection(Direction direction);

  // Actions
  void move();                // Tell the Vehicle to move
  void turnRight();           // Takes place of move() when turning
  void enterRoad(Tile *tptr); // Called after construction, point Vehicle to Road
};

#endif
