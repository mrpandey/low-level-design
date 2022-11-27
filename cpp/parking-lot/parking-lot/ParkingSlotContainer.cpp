#include <stdexcept>
#include "ParkingSlotContainer.h"
#include "ParkingSlotType.h"

ParkingSlotContainer::ParkingSlotContainer(KeyToParkingSlotContainer key, ParkingSlotType slot_type, int slot_count, int first_slot_number) : slot_type(slot_type), first_free_idx(0)
{
    if (slot_count < 0)
    {
        throw logic_error("Number of slots cannot be less than zero.");
    }

    if (!slot_count)
    {
        first_free_idx = -1;
        return;
    }

    for (int i = 0, slot_number; i < slot_count; i++)
    {
        slot_number = first_slot_number + i;
        slots.push_back(make_shared<ParkingSlot>(KeyToParkingSlot(), slot_number, slot_type));
        index_of_slot[slot_number] = i;
    }
}

bool ParkingSlotContainer::HasFreeSlot()
{
    return first_free_idx != -1;
}

void ParkingSlotContainer::AddSlot(int slot_number)
{
    slots.push_back(make_shared<ParkingSlot>(KeyToParkingSlot(), slot_number, slot_type));
    index_of_slot[slot_number] = slots.size() - 1;
    if (first_free_idx == -1)
    {
        first_free_idx = slots.size() - 1;
    }
}

shared_ptr<ParkingSlot> ParkingSlotContainer::ParkVehicle()
{
    if (first_free_idx == -1)
    {
        throw logic_error("No parking slot free in the container.");
    }

    slots[first_free_idx]->ParkVehicle();
    int park_idx = first_free_idx;

    while (first_free_idx < slots.size() && slots[first_free_idx]->IsOccupied())
    {
        first_free_idx++;
    }

    if (first_free_idx == slots.size())
    {
        first_free_idx = -1;
    }

    return slots[park_idx];
}

void ParkingSlotContainer::UnparkVehicle(int slot_number)
{
    if (index_of_slot.find(slot_number) == index_of_slot.end())
    {
        throw logic_error("Given slot number not found in container.");
    }

    int slot_idx = index_of_slot[slot_number];
    slots[slot_idx]->UnparkVehicle();
    if (first_free_idx > slot_idx)
    {
        first_free_idx = slot_idx;
    }
}

int ParkingSlotContainer::GetFreeSlotCount() const
{
    int ctr = 0;
    for (auto const slot_ptr : slots)
    {
        if (!slot_ptr->IsOccupied())
        {
            ctr++;
        }
    }
    return ctr;
}

vector<ParkingSlot> ParkingSlotContainer::GetFreeSlots() const
{
    vector<ParkingSlot> free_slots;
    for (auto const slot_ptr : slots)
    {
        if (!slot_ptr->IsOccupied())
        {
            free_slots.push_back(*slot_ptr);
        }
    }
    return free_slots;
}

vector<ParkingSlot> ParkingSlotContainer::GetOccupiedSlots() const
{
    vector<ParkingSlot> occupied_slots;
    for (auto const slot_ptr : slots)
    {
        if (slot_ptr->IsOccupied())
        {
            occupied_slots.push_back(*slot_ptr);
        }
    }
    return occupied_slots;
}