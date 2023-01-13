from time import strptime, strftime

from meeting.meeting import Meeting, MeetingParticipant
from meeting.room import Room, RoomManager
from meeting.strategies import TimeBookingStrategy
from meeting.meeting_manager import MeetingManager


def booking_helper(meeting_manager: MeetingManager, meeting: Meeting, room: Room) -> None:
    try:
        is_meeting_booked = meeting_manager.book(meeting=meeting, room=room)
    except Exception as e:
        print(e)
    else:
        if is_meeting_booked:
            start_time = strftime("%d %b %Y %H:%M %z", meeting.start_time)
            end_time = strftime("%d %b %Y %H:%M %z", meeting.end_time)
            print(f"Booked meeting in room {room.room_no} from {start_time} to {end_time}")
        else:
            print(f"Meeting cannot be booked")


def print_room_meetings(meeting_manager: MeetingManager, room: Room) -> None:
    print(f"Meetings in room {room.room_no}:")
    for meeting in meeting_manager.get_meetings(room=room):
        start_time = strftime("%d %b %Y %H:%M %z", meeting.start_time)
        end_time = strftime("%d %b %Y %H:%M %z", meeting.end_time)
        print(f"{start_time} - {end_time}")


# TODO: write proper tests

if __name__ == "__main__":
    room1 = Room(1)
    room2 = Room(2)
    room3 = Room(3)

    avinash = MeetingParticipant("Avinash")
    pandey = MeetingParticipant("Pandey")

    room_manager = RoomManager(rooms=[room1, room2])
    meeting_manager = MeetingManager(room_manager, TimeBookingStrategy())

    time_format_str = "%d %m %Y %H:%M %z"

    meet1 = Meeting(start_time=strptime("14 01 2022 17:30 +0530", time_format_str), end_time=strptime("14 01 2022 18:00 +0530", time_format_str), participants=[avinash, pandey], organizer=avinash)

    meet2 = Meeting(start_time=strptime("14 01 2022 17:55 +0530", time_format_str), end_time=strptime("14 01 2022 18:30 +0530", time_format_str), participants=[avinash, pandey], organizer=avinash)
    
    meet3 = Meeting(start_time=strptime("14 01 2022 18:30 +0530", time_format_str), end_time=strptime("14 01 2022 18:45 +0530", time_format_str), participants=[avinash, pandey], organizer=avinash)
    
    meet4 = Meeting(start_time=strptime("14 01 2022 16:30 +0530", time_format_str), end_time=strptime("14 01 2022 16:45 +0530", time_format_str), participants=[avinash, pandey], organizer=avinash)

    booking_helper(meeting_manager, meet1, room3)   # room not managed by room_manager
    
    booking_helper(meeting_manager, meet1, room1)
    booking_helper(meeting_manager, meet2, room1)   # collision


    booking_helper(meeting_manager, meet2, room2)
    booking_helper(meeting_manager, meet3, room2)
    booking_helper(meeting_manager, meet4, room2)

    # meeting list is maintained in sorted order
    print_room_meetings(meeting_manager, room2)