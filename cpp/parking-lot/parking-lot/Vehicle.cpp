#include "Vehicle.h"
#include "ParkingSlot.h"

using namespace std;

Vehicle::Vehicle() {}

Vehicle::Vehicle(string reg_no, string color, ParkingSlotType slot_type) : slot_type(slot_type), reg_no(reg_no), color(color) {}

string Vehicle::GetRegistrationNumber() const
{
    return reg_no;
}

string Vehicle::GetColor() const
{
    return color;
}

ParkingSlotType Vehicle::GetParkingSlotType() const
{
    return slot_type;
}

bool Vehicle::operator==(const Vehicle &v) const
{
    return (reg_no == v.GetRegistrationNumber() && color == v.GetColor() && slot_type == v.GetParkingSlotType());
}
