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
        //break;
    }
    cout << "finish" << endl;
    for (int i = 100; i < 110; ++i) {
        cout << "Title: " << books[i].title << endl
             << "Authors: " << books[i].authors << endl
             << "Category: " << books[i].category << endl
             << "Price: " << books[i].priceStarting << endl
             << "Publish Date: " << books[i].publishMonth << " " << books[i].publishYear << endl
             << endl;
    }
    file.close();
    return 0;
}
