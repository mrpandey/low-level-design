from typing import List, Dict
from bisect import insort

from .room import RoomManager, Room
from .meeting import Meeting
from .strategies import BookingStrategy


class MeetingManager:
    def __init__(
        self, room_manager: RoomManager, booking_strategy: BookingStrategy
    ) -> None:
        self.room_manager = room_manager
        self.booking_strategy = booking_strategy
        self.room_meetings_map: Dict[str][List[Meeting]] = {}

    def get_meetings(self, room: Room) -> List[Meeting]:
        try:
            return self.room_meetings_map[room.id]
        except KeyError as e:
            raise Exception(f"The requested room {room.room_no} does not exist.")

    def book(self, meeting: Meeting, room: Room) -> bool:
        if room.id not in self.room_manager.rooms:
            raise Exception(f"Invalid room {room.room_no}")

        if room.id not in self.room_meetings_map:
            self.room_meetings_map[room.id] = []

        if self.booking_strategy.book(meeting, room, self.get_meetings(room)):
            insort(self.room_meetings_map[room.id], meeting)
            return True

        return False
