from managers import *
from models import *
from strategies import *


def print_ride_details(ride: Ride) -> None:
    print(f"rider={ride.rider.name}")
    print(f"driver={ride.driver.name}")
    print(f"price={ride.price.amount}")
    print(f"status={ride.status}")
    print()


def print_ride_history(history: List[Ride]) -> None:
    print('Ride history ...')

    for ride in history:
        print_ride_details(ride)


def main() -> None:
    pricing_strat = PerKMPricing(Price(40))
    driver_matching_strat = ShortestDistanceMatching()

    driver_manager = DriverManager()
    rider_manager = RiderManager()
    ride_manager = RideManager(driver_manager, rider_manager, driver_matching_strat, pricing_strat)


    rider1 = rider_manager.add_rider('rider1')
    driver1 = driver_manager.add_driver('driver1', Cab(), Location(4,5))
    driver2 = driver_manager.add_driver('driver2', Cab(), Location(6,11))
    driver3 = driver_manager.add_driver('driver3', Cab(), Location(3,5))
    driver4 = driver_manager.add_driver('driver4', Cab(), Location(2,3))

    driver_manager.update_location(driver3.id, Location(6,5))
    driver_manager.update_availability(driver4.id, False)

    ride1 = ride_manager.book_ride(rider1.id, Location(0,0), Location(7,9))
    print_ride_details(ride1)

    ride_manager.update_ride_status(ride1.id, RideStatus.ARRIVED)
    ride_manager.update_ride_status(ride1.id, RideStatus.ON_WAY)

    driver_manager.update_location(ride1.driver.id, Location(7,9))
    ride_manager.end_ride(ride1.id)
    print_ride_details(ride1)

    ride_history = ride_manager.get_ride_history(rider1.id)
    print_ride_history(ride_history)


if __name__ == '__main__':
    main()