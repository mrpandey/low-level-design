from abc import ABC, abstractmethod
from typing import List
from decimal import Decimal

from .ledger import Person, Balance, Ledger, PersonalBalanceSummary
from .helpers import round_down


class PercentShare:
    def __init__(self, person: Person, share: str) -> None:
        self.person = person
        self.share = Decimal(share)
        if self.share <= Decimal("0.0") or self.share > Decimal("100.0"):
            raise Exception(f"Invalid percentage share for person {person.name}")


class ExactShare:
    def __init__(self, person: Person, share: str) -> None:
        self.person = person
        self.share = Decimal(share)
        if self.share <= Decimal("0"):
            raise Exception(f"Invalid share for person {person.name}")


class Expense(ABC):
    def __init__(self, paid_by: Person, amount: str) -> None:
        super().__init__()
        self.paid_by = paid_by
        self.amount = Decimal(amount)

        if self.amount <= Decimal("0"):
            raise Exception("Invalid amount.")

    @abstractmethod
    def split(self) -> List[Balance]:
        raise NotImplementedError


class EqualExpense(Expense):
    def __init__(self, paid_by: Person, amount: str, split_among: List[Person]) -> None:
        super().__init__(paid_by, amount)
        self.split_among = set(split_among)

        if len(self.split_among) < 2:
            raise Exception("Need at least two person to split the amount.")

    def split(self) -> List[Balance]:
        balances = []
        split_size = len(self.split_among)
        rest_split = round_down(self.amount / split_size)
        first_split = self.amount - rest_split * (split_size - 1)
        zero = Decimal("0.00")

        for person in self.split_among:
            split_amount = rest_split
            if first_split >= zero:
                split_amount = first_split
                first_split = -1

            if person is self.paid_by:
                continue

            balances.append(Balance(self.paid_by, person, split_amount))

        return balances


class PercentExpense(Expense):
    def __init__(
        self, paid_by: Person, amount: str, split_among: List[PercentShare]
    ) -> None:
        super().__init__(paid_by, amount)

        # validate split_among
        persons = set()
        percentage_sum = Decimal("0.00")

        for percent_share in split_among:
            if percent_share.person in persons:
                raise Exception(
                    f"Person {percent_share.person} appears more than once in expense."
                )
            persons.add(percent_share.person)

            if percent_share.share != round_down(percent_share.share):
                raise Exception(
                    "Percentage can have at most two digits after decimal point."
                )
            percentage_sum += percent_share.share

        if percentage_sum != Decimal("100"):
            raise Exception("Sum of percentage should be exactly 100.")

        self.split_among = split_among

    def split(self) -> List[Balance]:
        balances = []
        amount_sum = Decimal("0.00")

        for i, percent_share in enumerate(self.split_among):
            person_amount = round_down((percent_share.share * self.amount) / 100)

            if i == len(self.split_among) - 1:
                person_amount = self.amount - amount_sum

            if self.paid_by is not percent_share.person:
                balances.append(
                    Balance(self.paid_by, percent_share.person, person_amount)
                )

            amount_sum += person_amount

        return balances


class ExactExpense(Expense):
    def __init__(
        self, paid_by: Person, amount: str, split_among: List[ExactShare]
    ) -> None:
        super().__init__(paid_by, amount)

        share_sum = Decimal("0")
        person_set = set()
        for exact_share in split_among:
            if exact_share.person in person_set:
                raise Exception(
                    f"Person {exact_share.person.name} appears more than once in expense."
                )
            person_set.add(exact_share.person)

            if exact_share.share != round_down(exact_share.share):
                raise Exception(
                    "A share can have at most two digits after decimal point."
                )
            share_sum += exact_share.share

        if share_sum != self.amount:
            raise Exception(
                f"The given shares does not add upto given amount {self.amount}"
            )

        self.split_among = split_among

    def split(self) -> List[Balance]:
        balances = []

        for exact_share in self.split_among:
            balances.append(
                Balance(self.paid_by, exact_share.person, exact_share.share)
            )

        return balances


class ExpenseManager:
    def __init__(self) -> None:
        self.ledger = Ledger()

    def add_expense(self, expense: Expense) -> None:
        balances = expense.split()

        for balance in balances:
            self.ledger.add_balance(balance)

    def add_balance(self, balance: Balance) -> None:
        self.ledger.add_balance(balance)

    def get_person_balance(self, person: Person) -> PersonalBalanceSummary:
        if person not in self.ledger.person_balance:
            raise Exception(f"The person {person.name} does not exist in records.")
        return self.ledger.person_balance[person].balance_summary
