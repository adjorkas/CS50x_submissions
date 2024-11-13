'''
This program fills a database with Python, and it should be run only ONCE.

(1) The .schema showing how the tables were made:

    CREATE TABLE students (
        id INTEGER,
        student_name TEXT,
        PRIMARY KEY(id)
    );

    CREATE TABLE houses (
        id INTEGER NOT NULL,
        house TEXT NOT NULL,
        head TEXT NOT NULL,
        PRIMARY KEY (id)
    );

    CREATE TABLE assignments (
        id INTEGER NOT NULL,
        student_id INTEGER NOT NULL,
        house_id INTEGER NOT NULL,
        PRIMARY KEY (id),
        FOREIGN KEY(student_id) REFERENCES students(id),
        FOREIGN KEY(house_id) REFERENCES houses(id)
    );

(2) Query to see the final result:

    SELECT students.student_name, houses.head, houses.house
        FROM assignments JOIN houses
        ON houses.id = assignments.house_id
        JOIN students
        ON assignments.student_id = students.id
        ORDER BY house;
'''

from cs50 import SQL
from csv import DictReader

houses_dictionary = {}

db = SQL("sqlite:///roster.db")

with open("students.csv", "r") as file:

    # Create DictReader
    reader = DictReader(file)

    # Iterate over .csv file
    for row in reader:
        # Populate houses dictionary, e.g.: houses["Slytherin"] = Severus Snape
        house = row["house"]
        head = row["head"]
        if house not in houses_dictionary:
            houses_dictionary[house] = head

    # Populate houses table in db
    for key in houses_dictionary.keys():
        db.execute("INSERT INTO houses (house, head) "
                   "VALUES (?, ?)", key, houses_dictionary[key])

    # Populate assignments table in db
    assignments_dict = db.execute("SELECT students.id AS student_id, "
                                  "houses.id AS house_id FROM students "
                                  "JOIN houses ON students.house = houses.house")
    for i in assignments_dict:
        db.execute("INSERT INTO assignments (student_id, house_id) "
                   "VALUES (?, ?)", i["student_id"], i["house_id"])

    # Delete house and head columns in students table
    db.execute("ALTER TABLE students DROP COLUMN house")
    db.execute("ALTER TABLE students DROP COLUMN head")
