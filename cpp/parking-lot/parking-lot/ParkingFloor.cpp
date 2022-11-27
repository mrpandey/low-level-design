#include <stdexcept>
#include "ParkingFloor.h"

ParkingFloor::ParkingFloor(KeyToParkingFloor key, int floor_no, ParkingFloorConfiguration floor_config) : floor_number(floor_no), total_slots(0)
{
    for (auto const &pair_st_int : floor_config.slot_type_count)
    {
        slots[pair_st_int.first] = make_shared<ParkingSlotContainer>(KeyToParkingSlotContainer(), pair_st_int.first, pair_st_int.second, total_slots + 1);
        total_slots += pair_st_int.second;
    }
}

int ParkingFloor::GetNumber() const
{
    return floor_number;
}

void ParkingFloor::AddSlot(ParkingSlotType slot_type)
{
    if (slots.find(slot_type) != slots.end())
    {
        slots[slot_type]->AddSlot(total_slots+1);
        total_slots += 1;
    }
}

shared_ptr<ParkingSlotContainer> ParkingFloor::GetSlotContainer(ParkingSlotType slot_type) const
{
    if (slots.find(slot_type) != slots.end())
    {
        return slots.at(slot_type);
    }

    throw logic_error("Requested slot type is not avaialble on floor number " + to_string(floor_number));
}