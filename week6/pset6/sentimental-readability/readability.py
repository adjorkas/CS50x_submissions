# Readability!

text = input("Text: ")

letter_num = 0
word_num = 1
sentence_num = 0

for char in text:
    if char.isalpha():
        letter_num += 1
    if char.isspace():
        word_num += 1
    if char == "!" or char == "?" or char == ".":
        sentence_num += 1

L = 100 * letter_num / word_num
S = 100 * sentence_num / word_num
index = round(0.0588 * L - 0.296 * S - 15.8)

if index < 1:
    print("Before Grade 1")
elif index > 15:
    print("Grade 16+")
else:
    print(f"Grade {index}")
