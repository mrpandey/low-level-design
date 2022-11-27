#pragma once
#include <string>
#include "Vehicle.h"

using namespace std;

class Ticket
{
private:
    int floor_no;
    int slot_no;
    string parking_lot_id;
    string id;
    Vehicle vehicle;

public:
    Ticket(string ticket_id);
    Ticket(int floor_no, int slot_no, string lot_id, Vehicle vehicle);
    int GetFloorNumber() const;
    int GetSlotNumber() const;
    ParkingSlotType GetSlotType() const;
    string GetId() const;
    Vehicle GetVehicle() const;
    bool operator==(const Ticket &) const;
    struct Compare
    {
        bool operator()(const Ticket &a, const Ticket &b) const
        {
            return a.GetId() < b.GetId();
        }
    };
};
