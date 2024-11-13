# python test.py to run

for i in range(4):
    print("Hello!")

x = int(input("x: "))
y = int(input("y: "))

z = x / y
print(f"{z:.50f}")

if x in [1, 2]:
    print("1 or 2")
elif x in [3, 4]:
    print("3 or 4")
else:
    print("idk")

# s.lower() --> method inside data type

# don't need function prototypes if you define main(): & call main() in the end

# implement "do{}while" in py:
while True:
    n = int(input("n: "))
    if n > 0
    break

# scope: in py, n would exist outside the loop

# doble espacio entre fxones

# try except to avoid crashing:

try:
    n = int(input("n: "))
    if n > 0:
        return n
except ValueError:
    print("Not an integer")

# para printear en horizontal cambiás el parámetro end a "", default value es "\n"
# tmb podés concatenar cosas con ","

for i in range(3):
    print("?", end="")
print() # para dejar el cursor en newline

# sinónimo:
print("?" * 3)

# lista:
scores = [23, 34, 21]
# sinónimo:
scores = list()
average = sum(scores) / len(scores)

for i in range(3):
    score = int(input("score: "))
    scores.append(score)
    # sinónimo de append, hacer una lista[1] y concatenar:
    scores += [score]
    # no exite scores++;

from sys import argv
# len(argv) no incluye "python". $ python test.py => len(argv) = 1

for book in books[1:4]: # corchetes opcionales start 1: y end :4 values
    print(book)

# exit values:
import sys
sys.exit(0)
sys.exit(1)
# if you import a whole library, access: sys.argv, not only argv
# $ echo $? to see exit value

# dictionaries: key + value:
people = dict()
# sinónimo
people = {
    "Carter": "+54 11 6902 2719"
    "James": "+54 11 9210 3481"
}
name = input("name: ")
# people[name] = celular; indexás por el key.

# swap:
x, y = y, x # no eran inmutables tho...? sí, lo que hace es:

x = 1
y = 2
z = 3

print(f"x is {x}, y is {y}, z is {z}")

[x, y, z] = [z, y, x] # destructuring (js)

print(f"x is {x}, y is {y}, z is {z}")

# Saves names and numbers to a CSV file

import csv

# Get name and number
name = input("Name: ")
number = input("Number: ")

# Open CSV file
with open("phonebook.csv", "a") as file: # file = open ("phonebook.csv", "a"), file.close()

    # Print to file
    writer = csv.writer(file)
    writer.writerow([name, number])

# Para que no se confunda las columnas, print to file:
writer = csv.DictWriter(file, fieldnames=["name", "number"])
writer.writerow({"name": name, "number": number})

# some loops in py:

letters_only = True if input().isalpha() else False

for x in range (0, 100, 2): # vas saltando de a 2; desde 0 hasta 99
    print(x) # 0, 2, 4... 98.

list = [x for x in range(500)] # lista de 0 a 499
list.append(5) # agrega 5 al final
list.insert(4, 5) # agrega 5 en la posición 4 (0 indexed)
list[len(list):] = [1, 2, 3] # concatena nueva lista al final de la og


# tuples: ordered, immutable set of x
for prez, year in presidents:
    print("In {1}, {0} took office".format(prez, year))

# dictionaries:
pizzas = {
    "cheese": 9,
    "pepperoni": 10,
    "vegetable": 11,
    "buffalo chicken": 12
}

pizzas["bacon"] = 8 # add a new one / access value if key exists

# print keys:
for pie in pizzas:
    print(pie)

# print values (need to transform dict into list with .items())
for pie, price in pizzas.items():
    print(price)

for pie, price in pizzas.items():
print("A whole {} pizza costs ${}".format(pie, price))


for pie, price in pizzas.items():
    print("A whole {} pizza costs ${}".format(pie, price))

# Objects: object.method()

class Student():

    def __init__(self, name, id):
    self.name = name
    self.id = id

    def changeID(self, id):
    self.id = id

    def print(self):
    print("{} – {}".format(self.name, self.id))

text.strip()
words.split() # makes a list of words in text

book = dict()
book["title"] = "Corduroy"
book["author"] = "Don Freeman"
print(book["title"])
# "Corduroy"

# define one book:
book = {
    "title": "Goodnight Moon",
    "author": "Margaret Wise Brown"
}

# define several books (list):
[{"title": "Goodnight Moon", ...},
 {"title": "Corduroy", ...},
 {"title": "Curious George", ...}]

 # reader gives every row
 # dict reader gives every row as dict, first row as attributes. You can append to list