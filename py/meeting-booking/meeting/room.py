from uuid import uuid4
from typing import List


class Room:
    def __init__(self, room_no: int) -> None:
        self.id = uuid4().hex
        self.room_no = room_no


class RoomManager:
    def __init__(self, rooms: List[Room] = []) -> None:
        self.rooms = {room.id: room for room in rooms}

    def add_room(self, room: Room) -> None:
        self.rooms[room.id] = room
