from typing import List

from app.ledger import Person, PersonLedger
from app.expense import (
    PercentExpense,
    EqualExpense,
    ExactExpense,
    PercentShare,
    ExactShare,
)
from app.expense_manager import ExpenseManager

# TODO: handle concurrency
# TODO: add tests
# TODO: simplify expense: only in a group
# QUESTION: how much modification will be needed to support list expenses, groups, balance settlement
# balance settlement: add method in ExpenseManager which takes two person and adds the appropirate amount to ledger
# list expenses: store expenses in a list in ledger, we can add circular reference to each other between expense and splits
# groups: store groups in ExpenseManager, each group will have its own ledger with a restriction that an expense can only be shared between the group members


def print_person_balance(manager: ExpenseManager, person: Person) -> None:
    person_ledger: PersonLedger = manager.get_person_ledger(person)
    amount_owed = person_ledger.net_balance

    if amount_owed < 0:
        print(f"{person_ledger.person.name} owes {-amount_owed} in total.")
    else:
        print(f"{person_ledger.person.name} is owed {amount_owed} in total.")

    for other_person, amount in person_ledger.balances.items():
        if amount == 0:
            continue
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
