from typing import List, Dict
from decimal import Decimal


class Person:
    def __init__(self, name: str) -> None:
        self.name = name


class Balance:
    def __init__(self, paid_by: Person, paid_to: Person, amount: Decimal) -> None:
        if paid_by is paid_to:
            raise Exception("A person cannot pay to themself.")

        self.paid_by = paid_by
        self.paid_to = paid_to
        self.amount = amount

    def is_involved(self, person: Person) -> bool:
        return person is self.paid_by or person is self.paid_to

    def get_user_balance(self, person: Person) -> Decimal:
        if person is self.paid_to:
            return -self.amount

        if person is self.paid_by:
            return self.amount

        raise Exception("Person not involved in this balance.")

    def __add__(self, other: "Balance") -> "Balance":
        pass


class PersonalBalanceSummary:
    def __init__(self, person: Person) -> None:
        self.person = person
        self.balances: Dict[Person][Decimal] = {}
        self.net_balance = Decimal(0.0)

    def add_balance(self, balance: Balance) -> None:
        amount_owed = balance.get_user_balance(self.person)
        other_person = (
            balance.paid_by if self.person is balance.paid_to else balance.paid_to
        )

        if other_person not in self.balances:
            self.balances[other_person] = Decimal(0.0)

        self.balances[other_person] += amount_owed
        self.net_balance += amount_owed


class PersonalBalance:
    def __init__(self, person: Person) -> None:
        self.person = person
        self.balances = []
        self.balance_summary = PersonalBalanceSummary(person)

    def add_balance(self, balance: Balance) -> None:
        self.balance_summary.add_balance(balance)
        self.balances.append(balance)


class Ledger:
    def __init__(self) -> None:
        self.balances: List[Balance] = []
        self.person_balance: Dict[Person][PersonalBalance] = {}

    def add_balance(self, balance: Balance):
        persons = [balance.paid_by, balance.paid_to]
        self.balances.append(balance)

        for person in persons:
            if person not in self.person_balance:
                self.person_balance[person] = PersonalBalance(person)
            self.person_balance[person].add_balance(balance)
