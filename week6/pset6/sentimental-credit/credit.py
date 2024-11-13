# Credit!
# https://docs.python.org/3/howto/regex.html#regex-howto

from sys import exit
import re
from math import floor

while True:
    try:
        n = int(input("Number: "))
        break
    except ValueError:
        continue

string = str(n)
counter = 0
even_sum = 0
odd_sum = 0
passes_Luhn = False

while n > 0:
    digit = n % 10
    n = floor(n / 10)
    if counter % 2 == 0:
        even_sum += digit
    else:
        temp = digit * 2
        while temp > 0:
            odd_sum += temp % 10
            temp = floor(temp / 10)
    counter += 1

if (even_sum + odd_sum) % 10 == 0:
    passes_Luhn = True
else:
    print("INVALID")
    exit(1)

AMEX = "3[47]............."
MASTERCARD = "5[1-5].............."
VISA1 = "4............"
VISA2 = "4..............."

AMEX_pattern = re.compile(AMEX)
MASTERCARD_pattern = re.compile(MASTERCARD)
VISA1_pattern = re.compile(VISA1)
VISA2_pattern = re.compile(VISA2)

if AMEX_pattern.search(string) is not None:
    print("AMEX")
elif MASTERCARD_pattern.search(string) is not None:
    print("MASTERCARD")
elif (
    VISA1_pattern.search(string) is not None or VISA2_pattern.search(string) is not None
):
    print("VISA")
else:
    print("INVALID")
