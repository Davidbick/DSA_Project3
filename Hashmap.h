//
// Created by Vishal on 11/28/2024.
//
#include <unordered_map>
#include <string>
#include <iostream>
using namespace std;

#ifndef DSA_PROJECT3_HASHMAP_H
#define DSA_PROJECT3_HASHMAP_H

#endif //DSA_PROJECT3_HASHMAP_H

class Hashmap {
    private:
        unordered_map<string, unordered_map<string, unordered_map<string, unordered_map<string, unordered_map<string, unordered_map<string, string>>>>>> books;
        unordered_map<string, string> bookAuthors;
        unordered_map<string, string> bookDescription;
        unordered_map<string, string> bookCategory;
        unordered_map<string, string> bookPublisher;
        unordered_map<string, string> bookPublishDate;
        unordered_map<string, string> bookPrice;

    public:

};
