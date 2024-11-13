# Prints all favorites in CSV using csv.DictReader
'''
csv.reader gives lists of rows, row[1] is the second column
csv.DictReader gives dicts, so you can index by columns as row["column"]
'''

from csv import DictReader

# Open CSV file
with open("favorites.csv", "r") as file:

    # Create DictReader
    reader = DictReader(file)

    # Counts
    counts = {}

    # Iterate over CSV file, counting favorites
    for row in reader:
        favorite = row["language"]
        if favorite in counts:
            counts[favorite] += 1
        else:
            counts[favorite] = 1

# Print counts
for favorite in sorted(counts, key=lambda language: counts[language], reverse=True):
    print(f"{favorite}: {counts[favorite]}")

'''
CRUD IN SQL:
CREATE -- CREATE, INSERT
READ ---- SELECT
UPDATE
DELETE --- DELETE, DROP (entire tables)

CREATE TABLE table (column type, ...)
'''
