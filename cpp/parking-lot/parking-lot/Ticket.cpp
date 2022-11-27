#include <stdexcept>
#include "Ticket.h"
#include "Helpers.h"

using namespace std;

Ticket::Ticket(string ticket_id) : id(ticket_id)
{
    vector<string> ticket_id_split = SplitStringByUnderscore(ticket_id);
    if (ticket_id_split.size() < 3)
    {
        throw invalid_argument("Invalid Ticket ID.");
    }

    int split_size = ticket_id_split.size();

    floor_no = stoi(ticket_id_split[split_size - 2]);
    slot_no = stoi(ticket_id_split[split_size - 1]);
    parking_lot_id = JoinStringsByUnderscore(vector<string>(ticket_id_split.begin(), ticket_id_split.begin() + split_size - 2));
}

Ticket::Ticket(int floor_no, int slot_no, string lot_id, Vehicle vehicle) : floor_no(floor_no), slot_no(slot_no), parking_lot_id(lot_id), vehicle(vehicle)
{
    id = parking_lot_id + "_" + to_string(floor_no) + "_" + to_string(slot_no);
}

int Ticket::GetFloorNumber() const
{
    return floor_no;
}

int Ticket::GetSlotNumber() const
{
    return slot_no;
}

ParkingSlotType Ticket::GetSlotType() const
{
    return vehicle.GetParkingSlotType();
}

string Ticket::GetId() const
{
    return id;
};

Vehicle Ticket::GetVehicle() const
{
    return vehicle;
}

bool Ticket::operator==(const Ticket &t) const
{
    return id == t.GetId();
}