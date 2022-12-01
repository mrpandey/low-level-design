#pragma once
#include "Vehicle.h"

using namespace std;

class KeyToParkingSlot{
    friend class ParkingSlotContainer;
    KeyToParkingSlot() = default;
};

class ParkingSlot
{
private:
    bool empty;
    int number;
    ParkingSlotType slot_type;

public:
    ParkingSlot();
    ParkingSlot(KeyToParkingSlot key, int slot_number, ParkingSlotType slot_type, bool empty = true);
    void ParkVehicle();
    void UnparkVehicle();
    bool IsOccupied() const;
    int GetNumber() const;
    ParkingSlotType GetSlotType() const;
};
