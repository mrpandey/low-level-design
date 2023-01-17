from decimal import Decimal

EXPONENT = Decimal("0.01")


def round_down(number: Decimal) -> Decimal:
    return number.quantize(EXPONENT)
