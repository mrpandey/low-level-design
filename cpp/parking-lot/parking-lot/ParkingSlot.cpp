#include <stdexcept>
#include "ParkingSlot.h"

ParkingSlot::ParkingSlot() : empty(true) {}

ParkingSlot::ParkingSlot(KeyToParkingSlot key, int slot_number, ParkingSlotType slot_type, bool empty) : empty(empty), slot_type(slot_type), number(slot_number) {}

void ParkingSlot::ParkVehicle()
{
    if (!empty)
    {
        throw logic_error("Parking Slot Already Occupied.");
    }
    empty = false;
}

void ParkingSlot::UnparkVehicle()
{
    if (empty)
    {
        throw logic_error("Parking Slot Empty. Cannot Unpark.");
    }
    empty = true;
}

bool ParkingSlot::IsOccupied() const
{
    return !empty;
}

int ParkingSlot::GetNumber() const
{
    return number;
}

ParkingSlotType ParkingSlot::GetSlotType() const
{
    return slot_type;
}