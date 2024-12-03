#include <iostream>
#include "../Hashmap.h"
#include "../Trie.h"
#include <unordered_map>
#include <chrono>
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
    string input;
    while(!quit){
        //string input;
        cout << "Enter a book title:" << endl;
        getline(cin, input);
        cout << endl;
        if(input == "q" || input == "Q"){
            //quit = true;
            break;
        }
        auto s = chrono::steady_clock::now();
        bool inMap = hashmap.contains(input);
        if(!inMap){
            cout << "Sorry, we don't have this book in our inventory." << endl;
            cout << endl;
            auto e = chrono::steady_clock::now();
            auto time = chrono::duration_cast<chrono::microseconds>(e-s).count();
            cout << "Search time: " << time << " microseconds." << endl;
            cout << endl;
        }
        else{
            cout << "If you want to know the author(s) of the book, enter 'a' or 'A'." << endl
                 << "If you want a description of the book, enter 'd' or 'D'." << endl
                 << "If you want the category of the book, enter 'c' or 'C'." << endl
                 << "If you want the publisher of the book, enter 'p' or 'P'." << endl
                 << "If you want the price of the book, enter '$'." << endl
                 << "If you want the publish month and year of the book, enter '#'." << endl
                 << "If you want everything, enter 'e' or 'E'." << endl;
            getline(cin, input2);
            cout << endl;
            auto start = chrono::high_resolution_clock::now();
            Book b = hashmap.get(input);
            if(input2 == "q" || input2 == "Q"){
                //quit = true;
                break;
            }
            else if(input2 == "a" || input2 == "A"){
                cout << "Author(s): " << b.authors << endl;
            }
            else if(input2 == "d" || input2 == "D"){
                cout << "Description: " << b.description << endl;
            }
            else if(input2 == "c" || input2 == "C"){
                cout << "Category: " << b.category << endl;
            }
            else if(input2 == "p" || input2 == "P"){
                cout << "Publisher: " << b.publisher << endl;
            }
            else if(input2 == "$"){
                cout << "Price: $" << b.priceStarting << endl;
            }
            else if(input2 == "#"){
                cout << "Publish month and year: " << b.publishMonth << " " << b.publishYear << endl;
            }
            else if(input2 == "e" || input2 == "E"){
                cout << "Author(s): " << b.authors << endl
                     << "Description: " << b.description << endl
                     << "Category: " << b.category << endl
                     << "Publisher: " << b.publisher << endl
                     << "Price: $" << b.priceStarting << endl
                     << "Publish month and year: " << b.publishMonth << " " << b.publishYear << endl;
            }
            else{
                cout << "That is not a valid command. Please try again." << endl;
            }
            cout << endl;
            auto end = chrono::high_resolution_clock::now();
            auto time = chrono::duration_cast<chrono::microseconds>(end-start).count();
            cout << "Search time: " << time << " microseconds." << endl;
            cout << endl;
        }
    }

    file.close();
    return 0;
}
