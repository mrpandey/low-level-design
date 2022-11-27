#pragma once
#include <string>
#include <vector>
#include <utility>
#include "ParkingSlotType.h"

using namespace std;

class ParkingFloorConfiguration
{
private:
    friend class ParkingFloor;
    vector<pair<ParkingSlotType, int>> slot_type_count;

public:
    ParkingFloorConfiguration &AddSlotTypeCount(ParkingSlotType slot_type, int count);
};