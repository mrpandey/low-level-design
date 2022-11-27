#include <cctype>
#include <algorithm>
#include "ParkingSlotType.h"

ParkingSlotType::ParkingSlotType() {}

ParkingSlotType::ParkingSlotType(string slot_type)
{
    transform(slot_type.begin(), slot_type.end(), slot_type.begin(), ::tolower);
    this->slot_type = slot_type;
}

string ParkingSlotType::GetSlotType() const
{
    return slot_type;
}

bool ParkingSlotType::operator==(const ParkingSlotType &p) const
{
    return slot_type == p.GetSlotType();
}