#pragma once
#include "ParkingLot.h"
#include "ParkingFloorConfiguration.h"

class ParkingService
{
private:
    map<string, shared_ptr<ParkingLot>> parking_lots;
    static string default_parking_lot_id;
    bool stop;

    shared_ptr<ParkingLot> GetDefaultParkingLot();
    void CreateParkingLot(vector<string> &args);
    void ParkVehicle(vector<string> &args);
    void UnparkVehicle(vector<string> &args);
    void Display(vector<string> &args);
    void HandleInput(string cmd);

public:
    ParkingService();
    void Start();
};