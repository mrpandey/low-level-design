#include "ParkingFloorConfiguration.h"

ParkingFloorConfiguration &ParkingFloorConfiguration::AddSlotTypeCount(ParkingSlotType slot_type, int count)
{
    slot_type_count.push_back(make_pair(slot_type, count));
    return *this;
}