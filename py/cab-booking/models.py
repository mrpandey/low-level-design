from typing import List
from uuid import uuid4
from enum import Enum
from math import sqrt


# skipping getters and setters


class RideStatus(Enum):
    ARRIVING = 'arriving'
    ARRIVED = 'arrived'
    ON_WAY = 'on way'
    COMPLETE = 'complete'


class Rider:
    def __init__(self, name: str) -> None:
        self.name = name
        self.id = uuid4().hex
        self.current_ride = None


class Cab:
    def __init__(self) -> None:
        self.id = uuid4().hex


class Location:
    def __init__(self, x: float, y: float) -> None:
        self.x = x
        self.y = y
    
    def distance_from(self, other: 'Location') -> float:
        x_delta = other.x - self.x
        y_delta = other.y - self.y
        return sqrt(x_delta*x_delta + y_delta*y_delta)


class Driver:
    def __init__(self, name: str, cab: Cab, location: Location) -> None:
        self.name = name
        self.cab = cab
        self.id = uuid4().hex
        self.available = True
        self.location = location
        self.current_ride = None


class Price:
    def __init__(self, amount: float, currency: str = 'INR') -> None:
        self.amount = amount
        self.currency = currency


class Ride:
    def __init__(self, pickup: Location, drop: Location, rider: Rider, driver: Driver, price: Price) -> None:
        self.pickup = pickup
        self.drop = drop
        self.rider = rider
        self.driver = driver
        self.id = uuid4().hex
        self.price: Price = price
        self.status = RideStatus.ARRIVING