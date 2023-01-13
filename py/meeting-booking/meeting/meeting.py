from time import struct_time
from uuid import uuid4
from typing import List


class MeetingParticipant:
    def __init__(self, name: str) -> None:
        self.name = name
        self.id = uuid4().hex


class Meeting:
    def __init__(
        self,
        start_time: struct_time,
        end_time: struct_time,
        participants: List[MeetingParticipant],
        organizer: MeetingParticipant,
    ) -> None:
        if start_time >= end_time:
            raise Exception("Invalid meeting interval")
        self.start_time = start_time
        self.end_time = end_time
        self.participants = participants
        self.organizer = organizer
    
    def __lt__(self, other: 'Meeting') -> bool:
        if isinstance(other, Meeting):
            return self.start_time < other.start_time
        
        raise Exception("The operator < can only compare a Meeting instance with a Meeting instance.")
