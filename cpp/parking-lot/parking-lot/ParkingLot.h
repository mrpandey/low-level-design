#pragma once
#include<vector>
#include<string>
#include<set>
#include "ParkingFloor.h"
#include "Ticket.h"
#include "ParkingSlotType.h"
#include "ParkingFloorConfiguration.h"

class KeyToParkingLot{
    friend class ParkingService;
    KeyToParkingLot() = default;
};

class ParkingLot
{
private:
    string id;
    map<string, ParkingSlotType> valid_slot_types;
    vector<ParkingFloor> floors;
    set<Ticket, Ticket::Compare> tickets;

public:
    ParkingLot();
    ParkingLot(KeyToParkingLot key, string id);
    ParkingLot(KeyToParkingLot key, string id, int number_of_floors, int slots_per_floor);
    ParkingLot& AddFloor(ParkingFloorConfiguration &floor_config);
    Ticket ParkVehicle(Vehicle vehicle);
    Vehicle UnparkVehicle(Ticket ticket);
    void DisplayFreeSlotCount(ParkingSlotType slot_type);
    void DisplayFreeSlots(ParkingSlotType slot_type);
    void DisplayOccupiedSlots(ParkingSlotType slot_type);
};
