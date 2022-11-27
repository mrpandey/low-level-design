#include <stdexcept>
#include <iostream>
#include "ParkingLot.h"
#include "ParkingSlotType.h"

using namespace std;

ParkingLot::ParkingLot(KeyToParkingLot key, string id) : id(id)
{
    valid_slot_types["car"] = ParkingSlotType("car");
    valid_slot_types["bike"] = ParkingSlotType("bike");
    valid_slot_types["truck"] = ParkingSlotType("truck");
}

ParkingLot::ParkingLot(KeyToParkingLot key, string id, int number_of_floors, int slots_per_floor) : ParkingLot(key, id)
{
    if (slots_per_floor < 4)
    {
        throw invalid_argument("Insufficient slots for a floor.");
    }

    ParkingFloorConfiguration floor_config;
    floor_config.AddSlotTypeCount({"truck"}, 1);
    floor_config.AddSlotTypeCount({"bike"}, 2);
    floor_config.AddSlotTypeCount({"car"}, slots_per_floor - 3);
    for (int i = 0; i < number_of_floors; i++)
    {
        AddFloor(floor_config);
    }
}

ParkingLot &ParkingLot::AddFloor(ParkingFloorConfiguration &floor_config)
{
    int floor_count = floors.size();
    ParkingFloor floor({}, ++floor_count, floor_config);
    floors.push_back(floor);
    return *this;
}

Ticket ParkingLot::ParkVehicle(Vehicle vehicle)
{
    for (auto const &floor : floors)
    {
        try
        {
            auto &slot_container = *floor.GetSlotContainer(vehicle.GetParkingSlotType());
            if (slot_container.HasFreeSlot())
            {
                auto const &slot = *slot_container.ParkVehicle();
                Ticket ticket(floor.GetNumber(), slot.GetNumber(), id, vehicle);
                tickets.insert(ticket);
                return ticket;
            }
        }
        catch (const exception &e)
        {
            continue;
        }
    }

    throw logic_error("Parking Lot Full");
}

Vehicle ParkingLot::UnparkVehicle(Ticket ticket)
{
    auto it = tickets.find(ticket);
    if (it != tickets.end())
    {
        try
        {
            ticket = *it;
            auto &slot_container = *floors[ticket.GetFloorNumber() - 1].GetSlotContainer(ticket.GetSlotType());
            slot_container.UnparkVehicle(ticket.GetSlotNumber());
            return ticket.GetVehicle();
        }
        catch (const exception &e)
        {
            throw logic_error("Invalid Ticket");
        }
    }

    throw logic_error("Invalid Ticket");
}

void ParkingLot::DisplayFreeSlotCount(ParkingSlotType slot_type)
{
    for (auto const &floor : floors)
    {
        cout << "No. of free slots for " << slot_type.GetSlotType() << " on Floor " << floor.GetNumber() << ": " << floor.GetSlotContainer(slot_type)->GetFreeSlotCount() << endl;
    }
}

void ParkingLot::DisplayFreeSlots(ParkingSlotType slot_type)
{
    vector<ParkingSlot> free_slots;
    for (auto const &floor : floors)
    {
        free_slots = floor.GetSlotContainer(slot_type)->GetFreeSlots();
        cout << "Free slots for " << slot_type.GetSlotType() << " on Floor " << floor.GetNumber() << ":";
        for (int i = 0; i < free_slots.size(); i++)
        {
            auto const &slot = free_slots[i];
            cout << " " << slot.GetNumber();
            if (i + 1 < free_slots.size())
            {
                cout << ",";
            }
        }
        cout << endl;
    }
}

void ParkingLot::DisplayOccupiedSlots(ParkingSlotType slot_type)
{
    vector<ParkingSlot> occupied_slots;
    for (auto const &floor : floors)
    {
        occupied_slots = floor.GetSlotContainer(slot_type)->GetOccupiedSlots();
        cout << "Occupied slots for " << slot_type.GetSlotType() << " on Floor " << floor.GetNumber() << ":";
        for (int i = 0; i < occupied_slots.size(); i++)
        {
            auto const &slot = occupied_slots[i];
            cout << " " << slot.GetNumber();
            if (i + 1 < occupied_slots.size())
            {
                cout << ",";
            }
        }
        cout << endl;
    }
}