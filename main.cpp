#include <iostream>
#include "Hashmap.h"
#include "Trie.h"
#include <unordered_map>
#include <chrono>
using namespace std;
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

string toLowerCase(const string &str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

int main() {
    cout << "----------------------------------------------------" << endl
         << " Loading data... Please wait...                    " << endl
         << "----------------------------------------------------" << endl;
    Hashmap hashmap;
    Trie trie;
    string filename = "BooksDatasetClean.csv";
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open the file " << filename << endl;
        return 1;
    }
    string line;
    vector<Book> books;
    bool isHeader = true;
    bool quit = false;

    int count = 1;
    while (getline(file, line)) {
        if (isHeader) {
            isHeader = false; // Skip header row
            continue;
        }

        vector<string> row;
        stringstream ss(line);
        string data;
        bool quote = false;
        string s;
        while (getline(ss, data, ',')) {
            if (!quote) {
                if (!data.empty() && data[0] == '"') { ///if the string starts with a string
                    quote = true;
                    s = data.substr(1); ///take away quote
                }
                else if(data == ""){
                    //cout << "No data available." << endl;
                    row.push_back(" No data available.");
                }
                else {
                    data.erase(remove(data.begin(), data.end(), '"'), data.end()); ///removes any quotes
                    //cout << data << endl;
                    row.push_back(data);
                }
            }
            else {
                s += ',' + data;
                if (!data.empty() && data.back() == '"') {///if there is a string that ends in a quote
                    quote = false;
                    s.pop_back();
                    //cout << s << endl;
                    row.push_back(s);
                    s.clear();
                }
            }
        }

        while (row.size() < 8) {
            row.push_back(" No data available.");
        }


        // Add book to the list
        Book book;
        book.title = row[0];
        book.title = toLowerCase(row[0]); // Convert title to lowercase
        // Remove "By " from authors if present
        book.authors = row[1];
        if (book.authors.rfind("By ", 0) == 0) {
            book.authors = book.authors.substr(3);
        }
        book.description = row[2];
        book.category = row[3];
        book.category = book.category.substr(1);
        book.publisher = row[4];
        book.priceStarting = row[5];
        book.publishMonth = row[6];
        book.publishYear = row[7];

        books.push_back(book);
        hashmap.insert(book.title, book);
        trie.insert(book.title, book);
    }

    ///beginning of what the user sees
    cout << "----------------------------------------------------" << endl
         << " Welcome to the BookFinder!                    " << endl
         << "----------------------------------------------------" << endl
         << " We have 103,063 books stored in our Hashmap and   " << endl
         << " Trie Data Structures.                             " << endl
         << " You can learn more about our books by entering   " << endl
         << " the name of a book. Enter 'q' or 'Q' to quit.    " << endl
         << "----------------------------------------------------" << endl
         << endl;
    string input2;
    string input;
    while(!quit){
        bool display = true;
        cout << "----------------------------------------------------" << endl
             << " Enter a book title:                               " << endl
             << "----------------------------------------------------" << endl;
        getline(cin, input);

        cout << endl;
        if(input == "q" || input == "Q"){ ///quits the program whenever q or Q are entered
            break;
        }
        input = toLowerCase(input); ///Convert input to lowercase

        auto hashStart1 = chrono::high_resolution_clock::now(); ///timer starts for hashmap
        bool inMap = hashmap.contains(input); ///determines whether the title is in the hashmap
        if(!inMap) {
            auto hashEnd1 = chrono::high_resolution_clock::now(); ///timer ends when the book title entered is not found
            auto hashTime1 = chrono::duration_cast<chrono::microseconds>(hashEnd1 - hashStart1).count();
            cout << "----------------------------------------------------" << endl
                 << " Sorry, we don't have this book in our Hashmap. " << endl
                 << "----------------------------------------------------" << endl
                 << " Hashmap search time: " << hashTime1 << " microseconds." << endl
                 << "----------------------------------------------------" << endl
                 << endl;
        }
            auto trieStart1 = chrono::high_resolution_clock::now(); ///starts timer for the trie data structure
            bool inTrie = trie.contains(input); ///determines whether the title is in the trie
        if(!inTrie){
            auto trieEnd1 = chrono::high_resolution_clock::now(); ///timer ends when title isn't found in trie
            auto trieTime1 = chrono::duration_cast<chrono::microseconds>(trieEnd1-trieStart1).count();
            cout << "----------------------------------------------------" << endl
                 << " Sorry, we don't have this book in our Trie.    " << endl
                 << "----------------------------------------------------" << endl
                 << " Trie search time: " << trieTime1 << " microseconds." << endl
                 << "----------------------------------------------------" << endl
                 << endl;
        }
        else{ ///gives user different options
            basic_string<char> input2 = "";
            while(input2 != "r" && input2 != "R") {
                display = true;
                cout << "----------------------------------------------------" << endl
                     << " What information would you like about the book?   " << endl
                     << "----------------------------------------------------" << endl
                     << " a/A: Author(s)                                    " << endl
                     << " d/D: Description                                  " << endl
                     << " c/C: Category                                     " << endl
                     << " p/P: Publisher                                    " << endl
                     << " $: Price                                          " << endl
                     << " #: Publish month and year                         " << endl
                     << " e/E: Everything                                   " << endl
                     << " r/R: Reset search                                 " << endl
                     << "----------------------------------------------------" << endl;
                getline(cin, input2);
                cout << endl;
                auto hashStart2 = chrono::high_resolution_clock::now(); ///start a new timer so time isn't wasted
                Book hashBook = hashmap.get(input); ///retrieve book
                if (input2 == "q" || input2 == "Q") {
                    quit = true;
                    break;
                } else if (input2 == "r" || input2 == "R") {
                    cout << "----------------------------------------------------" << endl
                         << " Resetting search...                            " << endl
                         << "----------------------------------------------------" << endl
                         << endl;
                    break;
                }else if (input2 == "a" || input2 == "A") {
                    cout << "Author(s): " << hashBook.authors << endl;
                } else if (input2 == "d" || input2 == "D") {
                    cout << "Description: " << hashBook.description << endl;
                } else if (input2 == "c" || input2 == "C") {
                    cout << "Category: " << hashBook.category << endl;
                } else if (input2 == "p" || input2 == "P") {
                    cout << "Publisher: " << hashBook.publisher << endl;
                } else if (input2 == "$") {
                    cout << "Price: $" << hashBook.priceStarting << endl;
                } else if (input2 == "#") {
                    cout << "Publish month and year: " << hashBook.publishMonth << " " << hashBook.publishYear << endl;
                } else if (input2 == "e" || input2 == "E") {
                    cout << "Author(s): " << hashBook.authors << endl
                         << "Description: " << hashBook.description << endl
                         << "Category: " << hashBook.category << endl
                         << "Publisher: " << hashBook.publisher << endl
                         << "Price: $" << hashBook.priceStarting << endl
                         << "Publish month and year: " << hashBook.publishMonth << " " << hashBook.publishYear << endl;
                } else {
                    cout << "----------------------------------------------------" << endl
                         << " Invalid command. Please try again.            " << endl
                         << "----------------------------------------------------" << endl;
                    display = false;
                }
                auto hashEnd2 = chrono::high_resolution_clock::now();
                auto hashTime2 = chrono::duration_cast<chrono::microseconds>(hashEnd2 - hashStart2).count();
                if (display) {
                    cout << "----------------------------------------------------" << endl
                         << " Hashmap search time: " << hashTime2 << " microseconds.   " << endl
                         << "----------------------------------------------------" << endl
                         << endl;
                }

                auto trieStart2 = chrono::high_resolution_clock::now(); ///start new timer for trie
                Book trieBook = trie.search(input); ///retrieve book
                if (input2 == "q" || input2 == "Q") {
                    quit = true;
                    break;
                } else if (input2 == "a" || input2 == "A") {
                    cout << "Author(s): " << trieBook.authors << endl;
                } else if (input2 == "d" || input2 == "D") {
                    cout << "Description: " << trieBook.description << endl;
                } else if (input2 == "c" || input2 == "C") {
                    cout << "Category: " << trieBook.category << endl;
                } else if (input2 == "p" || input2 == "P") {
                    cout << "Publisher: " << trieBook.publisher << endl;
                } else if (input2 == "$") {
                    cout << "Price: $" << trieBook.priceStarting << endl;
                } else if (input2 == "#") {
                    cout << "Publish month and year: " << trieBook.publishMonth << " " << trieBook.publishYear << endl;
                } else if (input2 == "e" || input2 == "E") {
                    cout << "Author(s): " << trieBook.authors << endl
                         << "Description: " << trieBook.description << endl
                         << "Category: " << trieBook.category << endl
                         << "Publisher: " << trieBook.publisher << endl
                         << "Price: $" << trieBook.priceStarting << endl
                         << "Publish month and year: " << trieBook.publishMonth << " " << trieBook.publishYear << endl;
                }
                auto trieEnd2 = chrono::high_resolution_clock::now();
                auto trieTime2 = chrono::duration_cast<chrono::microseconds>(trieEnd2 - trieStart2).count();
                if (display) {
                    cout << "----------------------------------------------------" << endl
                         << " Trie search time: " << trieTime2 << " microseconds.      " << endl
                         << "----------------------------------------------------" << endl
                         << endl;
                }
            }
        }
    }
    cout << "\n--------------------------------------------------------" << endl;
    cout << "                Thank you for using BookFinder!         " << endl;
    cout << "                      Goodbye!                          " << endl;
    cout << "--------------------------------------------------------\n" << endl;
    file.close();
    return 0;
}
