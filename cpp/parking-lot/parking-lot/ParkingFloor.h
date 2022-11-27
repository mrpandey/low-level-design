#pragma once
#include <map>
#include <vector>
#include <memory>
#include "ParkingSlotContainer.h"
#include "ParkingSlot.h"
#include "ParkingFloorConfiguration.h"

class KeyToParkingFloor
{
    friend class ParkingLot;
};

class ParkingFloor
{
private:
    int floor_number;
    int total_slots;
    map<ParkingSlotType, shared_ptr<ParkingSlotContainer>, ParkingSlotType::Compare> slots;

public:
    ParkingFloor(KeyToParkingFloor key, int floor_no, ParkingFloorConfiguration floor_config);
    int GetNumber() const;
    void AddSlot(ParkingSlotType slot_type);
    shared_ptr<ParkingSlotContainer> GetSlotContainer(ParkingSlotType slot_type) const;
};