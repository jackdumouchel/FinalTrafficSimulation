#ifndef __TILE_H__
#define __TILE_H__
#include <iostream>
using namespace std;

#include "VehicleBase.h"

class Tile {
  private :
    bool emptyTile;
    VehicleBase *currentVehicle = nullptr;
    Tile *nextTile;
    Tile *prevTile;

  public :
    std::string name;
    Tile();
    ~Tile();
    Tile(const Tile& other);
    Tile(Tile&& other);
    Tile& operator=(Tile&& other);
    Tile& operator=(Tile& other);

    virtual Tile *getNext();
    virtual Tile *getPrev();
    bool getTileStatus();

    inline string getName() {return name;}
    void setOccupiedTile(VehicleBase* vehicle);
    void setOpenTile();
    VehicleBase* getCurrentVehicle();
    void setNextTile(Tile* next);
    void setPrevTile(Tile* prev);
    inline bool containsVehicle() {return getCurrentVehicle() != nullptr;};
    void setLeftTile(Tile* left);
    void setRightTile(Tile* right);

};
#endif
