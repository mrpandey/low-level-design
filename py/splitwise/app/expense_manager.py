from .expense import Expense
from .ledger import Ledger, Split, Person, PersonLedger

class ExpenseManager:
    def __init__(self) -> None:
        self.ledger = Ledger()

    def add_expense(self, expense: Expense) -> None:
        split_list = expense.split()

        for split in split_list:
            self.ledger.add_split(split)

    def get_person_ledger(self, person: Person) -> PersonLedger:
        if person not in self.ledger.person_ledger:
            raise Exception(f"The person {person.name} does not exist in ledger.")
        return self.ledger.person_ledger[person]