import csv
import sys
from itertools import islice


def main():
    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py .CSV .sequence")
        sys.exit(1)

    # Read database file into a variable
    database = []
    with open(sys.argv[1]) as CSV_file:
        reader = csv.DictReader(CSV_file)
        # print(reader.fieldnames)
        for row in reader:
            database.append(row)

    # Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as sequence_file:
        sequence = sequence_file.read()

    # Find longest match of each STR in DNA sequence
    max_str_reps = {}
    for key, value in database[1].items():
        if key != "name":
            max_str_reps[key] = str(longest_match(sequence, key))

    # Check database for matching profiles
    match = False
    match_name = ""
    for element in database:
        temporary_dict = element.copy()
        temporary_dict.pop("name")
        if temporary_dict == max_str_reps:
            match = True
            match_name = element["name"]
            break
        else:
            match = False

    match match:
        case True:
            print("{}".format(match_name))
        case False:
            print("No match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):
        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:
            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


if __name__ == "__main__":
    main()
