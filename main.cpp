#include <iostream>
#include "../Hashmap.h"
#include <unordered_map>
using namespace std;
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>


int main() {
    Hashmap hashmap;
    string filename = "BooksDatasetClean.csv";
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open the file " << filename << std::endl;
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
                    row.push_back("No data available.");
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
            row.push_back("No data available.");
        }

        // Add book to the list
        Book book;
        book.title = row[0];

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
    }
    cout << "Welcome to the BookFinder!" << endl
         << "We have 103,063 books stored in our Hashmap and Trie Data Structures." << endl
         << "You can learn more about our books by entering the name of a book. Enter 'q' or 'Q' to quit." << endl
         << endl;
    string input2;
    while(!quit){
        string input;
        cout << "Enter a book title:" << endl;
        getline(cin, input);
        cout << endl;
        if(input == "q" || input == "Q"){
            quit = true;
            break;
        }
        bool inMap = hashmap.contains(input);
        if(!inMap){
            cout << "Sorry, we don't have this book in our inventory." << endl;
            cout << endl;
        }
        else{
            Book b = hashmap.get(input);
            cout << "If you want to know the author(s) of the book, enter 'a' or 'A'." << endl
                 << "If you want a description of the book, enter 'd' or 'D'." << endl
                 << "If you want the category of the book, enter 'c' or 'C'." << endl
                 << "If you want the publisher of the book, enter 'p' or 'P'." << endl
                 << "If you want the price of the book, enter '$'." << endl
                 << "If you want the publish month and year of the book, enter '#'." << endl
                 << "If you want everything, enter 'e' or 'E'." << endl;
            getline(cin, input);
            cout << endl;
            if(input == "q" || input == "Q"){
                quit = true;
                break;
            }
            else if(input == "a" || input == "A"){
                cout << "Author(s): " << b.authors << endl;
            }
            else if(input == "d" || input == "D"){
                cout << "Description: " << b.description << endl;
            }
            else if(input == "c" || input == "C"){
                cout << "Category: " << b.category << endl;
            }
            else if(input == "p" || input == "P"){
                cout << "Publisher: " << b.publisher << endl;
            }
            else if(input == "$"){
                cout << "Price: $" << b.priceStarting << endl;
            }
            else if(input == "#"){
                cout << "Publish month and year: " << b.publishMonth << " " << b.publishYear << endl;
            }
            else if(input == "e" || input == "E"){
                cout << "Author(s): " << b.authors << endl
                     << "Description: " << b.description << endl
                     << "Category: " << b.category << endl
                     << "Publisher: " << b.publisher << endl
                     << "Price: $" << b.priceStarting << endl
                     << "Publish month and year: " << b.publishMonth << " " << b.publishYear << endl;
            }
            cout << endl;
        }
    }

    /*for (int i = 100; i < 110; i++) {
        cout << "Title: " << books[i].title << endl
             << "Authors: " << books[i].authors << endl
             << "Category: " << books[i].category << endl
             << "Price: " << books[i].priceStarting << endl
             << "Publish Date: " << books[i].publishMonth << " " << books[i].publishYear << endl
             << endl;
    }*/

    file.close();
    return 0;
}
