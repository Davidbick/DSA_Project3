//
// Created by Vishal on 12/3/2024.
//

#include <iostream>
#include <vector>
#include "../Hashmap.h"
#include <string>
#include <utility>
#include <functional>
#include <stdexcept>
#include <unordered_map>
using namespace std;

#ifndef DSA_PROJECT3_TRIE_H
#define DSA_PROJECT3_TRIE_H

struct Node{
    unordered_map<char, Node*> child;
    vector<Book> books;
    bool end = false;
};

class Trie{
    private:
        Node* root;

    public:
        Trie(){
            root = new Node();
        }


};



#endif //DSA_PROJECT3_TRIE_H


