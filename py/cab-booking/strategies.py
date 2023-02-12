from abc import ABC, abstractmethod
from typing import List, Union

from models import Location, Driver, Price


class IDriverMatchingStrategy(ABC):
    @abstractmethod
    def match_driver(self, pickup: Location, drop: Location, drivers: List[Driver], **kwargs) -> Union[Driver, None]:
        """
        Pick a driver from list of drivers for the ride criteria.
        """
        raise NotImplementedError


class ShortestDistanceMatching(IDriverMatchingStrategy):
    def match_driver(self, pickup: Location, drop: Location, drivers: List[Driver], **kwargs) -> Union[Driver, None]:
        selected_driver = None
        min_dist = None

        for driver in drivers:
            dist = pickup.distance_from(driver.location)

            if not min_dist or dist < min_dist:
                min_dist = dist
                selected_driver = driver
        
        return selected_driver
            

class IPricingStrategy(ABC):
    @abstractmethod
    def get_price(self, pickup: Location, drop: Location, driver: Driver, **kwargs) -> Price:
        """
        Calculate price for the ride.
        """
        raise NotImplementedError


class PerKMPricing(IPricingStrategy):
    def __init__(self, per_km_rate: Price) -> None:
        self.PR_KM_RATE = per_km_rate

    def get_price(self, pickup: Location, drop: Location, driver: Driver, **kwargs) -> Price:
        dist = drop.distance_from(pickup)
        amount = round(dist*self.PR_KM_RATE.amount, 2)
        return Price(amount)
