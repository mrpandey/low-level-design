from typing import List, Dict
from decimal import Decimal

class Person:
    def __init__(self, name: str) -> None:
        self.name = name


class Split:
    def __init__(self, paid_by: Person, paid_to: Person, amount: Decimal) -> None:
        if paid_by is paid_to:
            raise Exception("A person cannot pay to themself.")

        self.paid_by = paid_by
        self.paid_to = paid_to
        self.amount = amount

    def is_involved(self, person: Person) -> bool:
        return person is self.paid_by or person is self.paid_to

    def get_person_amount(self, person: Person) -> Decimal:
        if person is self.paid_to:
            return -self.amount

        if person is self.paid_by:
            return self.amount

        raise Exception("Person not involved in this split.")


class PersonLedger:
    def __init__(self, person: Person) -> None:
        self.person: Person = person
        self.split_list: List[Split] = []
        self.balances: Dict[Person][Decimal] = {}
        self.net_balance: Decimal = Decimal(0.0)

    def add_split(self, split: Split) -> None:
        amount_owed = split.get_person_amount(self.person)
        other_person = (
            split.paid_by if self.person is split.paid_to else split.paid_to
        )

        if other_person not in self.balances:
            self.balances[other_person] = Decimal(0.0)

        self.split_list.append(split)
        self.balances[other_person] += amount_owed
        self.net_balance += amount_owed


class Ledger:
    def __init__(self) -> None:
        self.split_list: List[Split] = []
        self.person_ledger: Dict[Person][PersonLedger] = {}

    def add_split(self, split: Split):
        persons = [split.paid_by, split.paid_to]
        self.split_list.append(split)

        for person in persons:
            if person not in self.person_ledger:
                self.person_ledger[person] = PersonLedger(person)
            self.person_ledger[person].add_split(split)
