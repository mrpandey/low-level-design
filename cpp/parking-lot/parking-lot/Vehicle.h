#pragma once
#include <string>
#include "ParkingSlotType.h"

using namespace std;

class Vehicle
{
private:
    string reg_no;
    string color;
    ParkingSlotType slot_type;

public:
    Vehicle();
    Vehicle(string reg_no, string color, ParkingSlotType slot_type);
    string GetRegistrationNumber() const;
    string GetColor() const;
    ParkingSlotType GetParkingSlotType() const;
    bool operator==(const Vehicle&) const;
};