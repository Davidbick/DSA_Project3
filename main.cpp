#include <iostream>
#include "Hashmap.h"
#include <unordered_map>
using namespace std;
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
int main() {
    Hashmap hashmap;
    string filename = "BooksDataset.csv";
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open the file " << filename << std::endl;
        return 1;
    }
    string line;
    int count = 1;
    while (getline(file, line)) {
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
        //break;
    }
    cout << "finish" << endl;
    file.close();
    return 0;
}
