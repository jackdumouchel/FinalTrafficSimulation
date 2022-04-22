#ifndef __MOVEVEHICLE_CPP__
#define __MOVEVEHICLE_CPP__

#include "MoveVehicle.h"
#include "VehicleBase.h"
#include <iostream>
#include "Intersection.h"
using namespace std;

// Typical use constructor for Vehicle
MoveVehicle::MoveVehicle(VehicleType vehicleType, Direction direction, int vehicleLength, bool willTurnRight) : VehicleBase(vehicleType, direction)
{
   this->length = vehicleLength;
   this->willTurnRight = willTurnRight; // Whether Vehicle will turn right or now
}

MoveVehicle::~MoveVehicle()
{
}

// Getter methods

/*
 *  Return the length of the Vehicle
 */
int MoveVehicle::getLength()
{
   return length;
}

/*
 *  Return the current direction of the Vehicle
 */
Direction MoveVehicle::getCurrDirection()
{
   return this->currDirection;
}

/*
 * Private method, sets all the tiles between head and tail to occupied. Also accounts
 * for turns. 
 */
void MoveVehicle::setOccupiedTiles()
{
   // Set the Tile where head is to occupied
   this->hptr->setOccupiedTile(this);

   // Start from tail, setting all Tiles in between to occupied
   Tile *currTile = this->tptr;
   while (currTile != this->hptr)
   {
      // Set the tile to occupied
      currTile->setOccupiedTile(this);

      // Check the current tile is an IntersectionTile to account for turns
      if (this->isTurningRight && currTile->getName() == "Intersection")
      {
         currTile = dynamic_cast<Intersection *>(currTile)->getRight();
      }
      // If the next is not IntersectionTile, keep going straight
      else
      {
         currTile = currTile->getNext();
      }
   }
}

/*
 *  Called when vehicle should "drive" itself on to the road. Passed a pointer to  
 *  the first available tile on a Road, as retrieved by Road.getQueueHead()
 */
void MoveVehicle::enterRoad(Tile *hptr)
{
   this->hptr = hptr; // Set head pointer
   this->tptr = hptr; // Tail is initially same as head

   // Move the tail backward the length of the car to "drive" on to the Road
   for (int i = 0; i < this->length - 1; i++)
   {
      this->tptr = this->tptr->getPrev();
   }

   // Set all the Tiles between head and tail to occupied
   this->setOccupiedTiles();
}

/*
 *   Moves the vehicle forward regardless. This is a private method, and should only be called
 *   from move() to avoid errors.
 */
void MoveVehicle::moveForward()
{
   // Set the previous tile to unoccupied
   Tile *prevt = this->tptr;

   // Move each pointer forward
   this->hptr = this->hptr->getNext();
   this->tptr = this->tptr->getNext();

   // Unassign last position
   prevt->setOpenTile();

   // Set the tiles between head and tail to occupied
   this->setOccupiedTiles();
}

/*
 *  Called for every 'click' of time. Moves the vehicle one Tile and handles turning
 *  by calling external method when the Vehicle reaches an intersection.
 */
void MoveVehicle::move()
{

   // If we are turning right, let turnRight() handle the move logic
   if (this->isTurningRight)
   {
      turnRight();
      return;
   }

   // Get the next Tile
   Tile *next = this->hptr->getNext();

   // Check if next Tile 1) exists and 2) is unoccupied
   if (next != nullptr && !next->containsVehicle())
   {

      // The next tile is an IntersectionTile and we don't already have a green light
      if (next->getName() == "Intersection" && !this->hasGreen)
      {
         // Cast Tile to IntersectionTile
         Intersection *it = dynamic_cast<Intersection *>(next);

         // Get the light color from IntersectionTile
         LightColor lightColor = it->getTrafficLight()->getLightColor();

         // If the light is yellow, only Vehicle can make it
         if (lightColor == LightColor::yellow)
         {
            if (it->getTrafficLight()->getTimeChange() >= this->length + 1 && this->willTurnRight)
            {
               turnRight();
               return;
            }

            if (it->getTrafficLight()->getTimeChange() >= this->length + 2)
            {
               this->hasGreen = true;
               this->moveForward();
            }
         }
         else if (lightColor == LightColor::green)
         {
            this->hasGreen = true;

            // If the light is green and Vehicle is turning right, just do it
            if (this->willTurnRight)
            {
               turnRight();
               return;
            }

            this->moveForward();
         }
      }
      else
      {
         // Move forward to the next Tile
         this->moveForward();
      }
   }
   else if (next == NULL)
   {
      this->reachedEndOfRoad = true;

      Tile *tail = this->tptr;

      while (tail != hptr)
      {
         tail->setOpenTile();
         tail = tail->getNext();
      }

      this->hptr->setOpenTile();
   }
}

/*
 *  When the Vehicle is turning, effectively takes the place of move(); should only be called
 *  by move(). Also, will be called when the head is already on the IntersectionTile
 */
void MoveVehicle::turnRight()
{

   // Set turning right to true if it isn't already
   if (!this->isTurningRight)
   {
      this->isTurningRight = true;
      this->movesLeftInTurn = this->length + 1;
   }

   if (this->movesLeftInTurn != 0)
   {
      // Set prev tiles
      Tile *prevt = this->tptr;
      Tile *prevh = this->hptr;

      // Check if the head is on an IntersectionTile (it should be initally)
      if (this->hptr->getName() == "Intersection")
      {
         // Downcast to IntersectionTile
         Intersection *headIntersection = dynamic_cast<Intersection *>(this->hptr);

         // Set the head to the right of the IntersectionTile
         this->hptr = headIntersection->getRight();

         // Manually move tail pointer
         this->tptr->setOpenTile();
         this->tptr = this->tptr->getNext();

         // Set the spot where the head was to unoccupied (unescessary but for consistency)
         prevh->setOpenTile();
      }
      // Check if the tail is on an IntersectionTile
      else if (this->tptr->getName() == "Intersection")
      {
         // Downcast to IntersectionTile
         Intersection *tailIntersectionTile = dynamic_cast<Intersection *>(this->tptr);

         // Set the tail to the right of the IntersectionTile
         this->tptr = tailIntersectionTile->getRight();

         // Manually move head pointer
         this->hptr->setOpenTile();
         this->hptr = this->hptr->getNext();

         // Set the spot where the tail was to unoccupied (unescessary but for consistency)
         prevt->setOpenTile();
      }
      else
      {
         // If the head and tail are not on IntersectionTiles, move head and tail forward
         moveForward();
      }
      this->setOccupiedTiles();
      movesLeftInTurn--;
   }

   // If the movesLeftInTurn are used up, set isTurningRight to false
   if (movesLeftInTurn == 0)
   {
      this->isTurningRight = false;
   }
}

/*
 * Not currently used, but for left turns might be important.
 */
void MoveVehicle::setCurrDirection(Direction direction)
{
   this->currDirection = direction;
}

/*
 * Check if a Vehicle can turn right on a red light
 */
bool MoveVehicle::canTurnRight(Intersection *it)
{

   if (it->getTrafficLight()->getLightColor() == LightColor::green)
   {
      return true;
   }

   Intersection *it2;
   switch (this->getVehicleOriginalDirection())
   {
   case Direction::north:
      it2 = dynamic_cast<Intersection *>(it->getWest());
      break;
   case Direction::east:
      it2 = dynamic_cast<Intersection *>(it->getNorth());
      break;
   case Direction::south:
      it2 = dynamic_cast<Intersection *>(it->getEast());
   case Direction::west:
      it2 = dynamic_cast<Intersection *>(it->getSouth());
   }

   if (it2->containsVehicle())
   {
      return false;
   }

   Tile *checkTile = it2->getPrev();
   for (int i = 0; i < this->length - 1; i++)
   {
      if (checkTile->containsVehicle())
      {
         return false;
      }
      checkTile = checkTile->getPrev();
   }

   return true;
}

#endif