#pragma once
#include <vector>
#include <map>
#include <memory>
#include "ParkingSlot.h"

using namespace std;

class KeyToParkingSlotContainer
{
    friend class ParkingFloor;
    KeyToParkingSlotContainer() = default;
};

class ParkingSlotContainer
{
private:
    vector<shared_ptr<ParkingSlot>> slots;
    map<int, int> index_of_slot;
    ParkingSlotType slot_type;
    int first_free_idx;

public:
    ParkingSlotContainer(KeyToParkingSlotContainer key, ParkingSlotType slot_type, int slot_count, int first_slot_number);
    bool HasFreeSlot();
    void AddSlot(int slot_number);
    shared_ptr<ParkingSlot> ParkVehicle();
    void UnparkVehicle(int slot_number);
    int GetFreeSlotCount() const;
    vector<ParkingSlot> GetFreeSlots() const;
    vector<ParkingSlot> GetOccupiedSlots() const;
};