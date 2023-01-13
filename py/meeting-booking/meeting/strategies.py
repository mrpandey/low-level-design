from abc import ABC, abstractmethod
from typing import List

from .meeting import Meeting
from .room import Room, RoomManager

class BookingStrategy(ABC):
    @abstractmethod
    def book(self, meeting: Meeting, room: Room, meetings: List[Meeting]) -> bool:
        """
        Book the meeting in the given room if possible.

        :param meetings: the list of meetings already booked for the given room
        """
        raise NotImplementedError


class TimeBookingStrategy(BookingStrategy):
    def book(self, meeting: Meeting, room: Room, meetings: List[Meeting]) -> bool:
        for booked_meeting in meetings:
            if not ( meeting.end_time <= booked_meeting.start_time or booked_meeting.end_time <= meeting.start_time ):
                return False
        
        return True