# BookFinder

BookFinder is a command-line application designed to efficiently search and retrieve information about books from Wonderbk using two data structures: a **Hashmap** and a **Trie**. This project demonstrates fast data retrieval and showcases the performance differences between the two data structures.

---

## Features

- Reads and processes a dataset of over 103,000 books from a CSV file.
- Stores book information in both a **Hashmap** and a **Trie** for comparison.
- Allows users to search for books by title.
- Displays detailed information about a book, including:
    - Author(s)
    - Description
    - Category
    - Publisher
    - Price
    - Publish Month and Year
- Measures and displays the time taken for searches in both the Hashmap and Trie.
- User-friendly interface with options to reset or quit the search.

---

## Prerequisites

To run this project, ensure you have the following:

- A C++ compiler
- A dataset file named `BooksDatasetClean.csv` in the same directory as the program.

---

## Usage
Run the program, and you will see a prompt asking you to input a book title.

Example:
   ```text
   Enter a book title:
   ```
You can enter a title of a book:
```text
   The Great Gatsby
   ```
Now you will be prompted to enter a command assuming the book is in our library:

```text
If you want to know the author(s) of the book, enter 'a' or 'A'.
If you want a description of the book, enter 'd' or 'D'.
If you want to know the category of the book, enter 'c' or 'C'.
If you want to know the publisher of the book, enter 'p' or 'P'.
If you want to know the price of the book, enter '$'.
If you want to know the publish month and year of the book, enter 'm' or 'M'.
If you want to reset the program, enter 'r' or 'R'.
If you want to quit the program, enter 'q' or 'Q'.

Enter a command:
a
```

The code will give you the answer and the time taken for both structures to find it:
```text
Author(s): Fitzgerald, F. Scott
Hashmap search time: 744 microseconds.

Author(s): Fitzgerald, F. Scott
Trie search time: 3275 microseconds.
```

You can choose to reset the book search by inputting "r" or quit the code by inputting "q"

If you have trouble reading the csv file, use the command line:
```text
g++ -o main.exe main.cpp
```
Then run 'main.exe'