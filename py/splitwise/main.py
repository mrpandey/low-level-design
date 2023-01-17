from typing import List

from app.ledger import Person, PersonalBalanceSummary
from app.expense import (
    ExpenseManager,
    PercentExpense,
    EqualExpense,
    ExactExpense,
    PercentShare,
    ExactShare,
)

# TODO: handle concurrency
# TODO: add tests
# TODO: simplify expense
# QUESTION: how much modification will be needed to support groups


def print_person_balance(manager: ExpenseManager, person: Person) -> None:
    pbs: PersonalBalanceSummary = manager.get_person_balance(person)
    amount_owed = pbs.net_balance

    if amount_owed < 0:
        print(f"{pbs.person.name} owes {-amount_owed} in total.")
    else:
        print(f"{pbs.person.name} is owed {amount_owed} in total.")

    for other_person, amount in pbs.balances.items():
        if amount >= 0:
            print(f"Owed {amount} by {other_person.name}")
        else:
            print(f"Owes {-amount} to {other_person.name}")

    print("")


def print_multiple_person_balance(manager: ExpenseManager, persons: List[Person]):
    for person in persons:
        print_person_balance(manager, person)


if __name__ == "__main__":
    manager = ExpenseManager()

    avinash = Person("avinash")
    pandey = Person("pandey")
    arun = Person("arun")
    sharma = Person("sharma")

    expense1 = EqualExpense(avinash, "85", [avinash, pandey, arun])
    manager.add_expense(expense1)

    expense2 = EqualExpense(pandey, "62", [avinash, arun, sharma])
    manager.add_expense(expense2)

    print_multiple_person_balance(manager, [avinash, pandey, arun, sharma])

    expense3 = PercentExpense(
        arun,
        "100",
        [
            PercentShare(arun, "34.45"),
            PercentShare(avinash, "31.49"),
            PercentShare(sharma, "34.06"),
        ],
    )
    manager.add_expense(expense3)

    print_multiple_person_balance(manager, [avinash, pandey, arun, sharma])

    expense4 = ExactExpense(
        sharma, "98.14", [ExactShare(avinash, "44.02"), ExactShare(arun, "54.12")]
    )
    manager.add_expense(expense4)

    print_multiple_person_balance(manager, [avinash, pandey, arun, sharma])
