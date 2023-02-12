from typing import List, Dict, Union

from models import *
from strategies import *


class RiderManager:
    def __init__(self) -> None:
        self._riders: Dict[str][Rider] = {}

    def get_rider(self, id: str) -> Rider:
        if id in self._riders:
            return self._riders[id]

        raise Exception("Rider does not exist.")

    def add_rider(self, name: str) -> Rider:
        rider = Rider(name)
        self._riders[rider.id] = rider
        return rider


class DriverManager:
    def __init__(self) -> None:
        self._drivers: Dict[str][Driver] = {}

    def get_driver(self, id: str) -> Driver:
        if id in self._drivers:
            return self._drivers[id]

        raise Exception("Driver does not exist.")

    def add_driver(self, name: str, cab: Cab, location: Location) -> Rider:
        driver = Driver(name, cab, location)
        self._drivers[driver.id] = driver
        return driver

    def update_location(self, driver_id: str, location: Location) -> None:
        driver = self.get_driver(driver_id)
        driver.location = location

    def update_availability(self, driver_id: str, available: bool) -> None:
        driver = self.get_driver(driver_id)
        driver.available = available

    def get_drivers_in_radius(self, pickup: Location, radius: float) -> None:
        if radius <= 0:
            raise Exception(f"Invalid radius {radius}.")

        drivers_in_radius = []

        for id, driver in self._drivers.items():
            if driver.available and driver.location.distance_from(pickup) <= radius:
                drivers_in_radius.append(driver)

        return drivers_in_radius


class RideManager:
    def __init__(
        self,
        driver_manager: DriverManager,
        rider_manager: RiderManager,
        driver_matching_strategy: IDriverMatchingStrategy,
        pricing_strategy: IPricingStrategy,
    ) -> None:
        self._rides: Dict[str][Ride] = {}
        self._driver_manager = driver_manager
        self._rider_manager = rider_manager
        self._driver_matching_strategy = driver_matching_strategy
        self._pricing_strategy = pricing_strategy
        self.SEARCH_RADIUS_KM = 8

    def get_ride_history(self, rider_id: str) -> List[Ride]:
        ride_history = []

        for id, ride in self._rides.items():
            if ride.rider.id == rider_id:
                ride_history.append(ride)

        return ride_history

    def get_ride(self, ride_id: str) -> Ride:
        if ride_id in self._rides:
            return self._rides[ride_id]

        raise Exception("Ride not found.")

    def update_ride_status(self, ride_id: str, status: RideStatus) -> None:
        ride = self.get_ride(ride_id)
        ride.status = status

    def end_ride(self, ride_id: str) -> None:
        ride = self.get_ride(ride_id)
        ride.status = RideStatus.COMPLETE
        ride.driver.available = True
        ride.driver.current_ride = None
        ride.rider.current_ride = None

    def book_ride(self, rider_id: str, pickup: Location, drop: Location) -> Ride:
        rider = self._rider_manager.get_rider(rider_id)
        closeby_drivers = self._driver_manager.get_drivers_in_radius(
            pickup, self.SEARCH_RADIUS_KM
        )

        if not closeby_drivers:
            raise Exception("No drivers available.")

        driver = self._driver_matching_strategy.match_driver(
            pickup, drop, closeby_drivers
        )
        price = self._pricing_strategy.get_price(pickup, drop, driver)

        ride = Ride(pickup, drop, rider, driver, price)
        
        ride.rider.current_ride = ride
        ride.driver.current_ride = ride
        ride.driver.available = False

        self._rides[ride.id] = ride

        return ride
