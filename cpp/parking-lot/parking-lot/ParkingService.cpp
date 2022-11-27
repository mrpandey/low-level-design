#include "ParkingService.h"
#include "Helpers.h"
#include <iostream>
#include <stdexcept>

string ParkingService::default_parking_lot_id = "";

ParkingService::ParkingService() : stop(false){};

shared_ptr<ParkingLot> ParkingService::GetDefaultParkingLot()
{
    if (default_parking_lot_id.empty())
    {
        throw logic_error("No default parking lot available.");
    }

    return parking_lots[default_parking_lot_id];
}

void ParkingService::Start()
{
    string cmd;
    while (!stop)
    {
        getline(cin, cmd);
        try
        {
            HandleInput(cmd);
        }
        catch (const exception &e)
        {
            cout << e.what() << endl;
        }
    }
}

void ParkingService::HandleInput(string cmd)
{
    vector<string> split_cmd = SplitString(cmd);
    if (split_cmd.empty())
        return;

    string main_cmd = split_cmd[0];

    if (main_cmd == "exit")
    {
        stop = true;
        return;
    }

    vector<string> cmd_args = vector<string>(split_cmd.begin() + 1, split_cmd.end());

    if (main_cmd == "display")
    {
        Display(cmd_args);
    }
    else if (main_cmd == "park_vehicle")
    {
        ParkVehicle(cmd_args);
    }
    else if (main_cmd == "unpark_vehicle")
    {
        UnparkVehicle(cmd_args);
    }
    else if (main_cmd == "create_parking_lot")
    {
        CreateParkingLot(cmd_args);
    }
    else
    {
        throw invalid_argument("Invalid command");
    }
}

void ParkingService::CreateParkingLot(vector<string> &args)
{
    if (args.size() < 3)
    {
        throw invalid_argument("Insufficient arguments");
    }

    string lot_id = args[0];
    int floor_count = stoi(args[1]);
    int slots_per_floor = stoi(args[2]);

    if (parking_lots.find(lot_id) != parking_lots.end())
    {
        throw invalid_argument("Parking lot with this ID already exists.");
    }

    parking_lots[lot_id] = make_shared<ParkingLot>(KeyToParkingLot(), lot_id, floor_count, slots_per_floor);
    if (parking_lots.size() == 1)
    {
        default_parking_lot_id = lot_id;
    }

    cout << "Created parking lot with " << floor_count << " floors and " << slots_per_floor << " slots per floor" << endl;
}

void ParkingService::ParkVehicle(vector<string> &args)
{
    if (args.size() < 3)
    {
        throw invalid_argument("Insufficient arguments");
    }

    string slot_type = args[0];
    string reg_no = args[1];
    string color = args[2];

    try {
        Vehicle vehicle(reg_no, color, {slot_type});
        Ticket ticket = GetDefaultParkingLot()->ParkVehicle(vehicle);
        cout << "Parked vehicle. Ticket ID: " << ticket.GetId() << endl;
    }
    catch (const exception &e){
        cout << e.what() << endl;
    }
}

void ParkingService::UnparkVehicle(vector<string> &args)
{
    if (args.empty())
    {
        throw invalid_argument("Invalid Ticket");
    }

    try {
        string ticket_id = args[0];
        Vehicle vehicle = GetDefaultParkingLot()->UnparkVehicle({ticket_id});
        cout << "Unparked vehicle with Registration Number: " << vehicle.GetRegistrationNumber() << " and Color: " << vehicle.GetColor() << endl;
    }
    catch (const exception &e){
        cout << e.what() << endl;
    }
}

void ParkingService::Display(vector<string> &args)
{
    if (args.size() < 2)
    {
        throw invalid_argument("Insufficient arguments");
    }

    string display_type = args[0];
    string slot_type = args[1];

    if (display_type == "free_count")
    {
        GetDefaultParkingLot()->DisplayFreeSlotCount({slot_type});
    }
    else if (display_type == "free_slots")
    {
        GetDefaultParkingLot()->DisplayFreeSlots({slot_type});
    }
    else if (display_type == "occupied_slots")
    {
        GetDefaultParkingLot()->DisplayOccupiedSlots({slot_type});
    }
    else
    {
        throw invalid_argument("Invalid arguments");
    }
}