#pragma once
#include <string>

using namespace std;

class ParkingSlotType
{
    string slot_type;

public:
    ParkingSlotType();
    ParkingSlotType(string slot_type);
    string GetSlotType() const;
    bool operator==(const ParkingSlotType &) const;
    struct Compare
    {
        bool operator()(const ParkingSlotType &a, const ParkingSlotType &b) const
        {
            return a.GetSlotType() < b.GetSlotType();
        }
    };
};