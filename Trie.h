//
// Created by Vishal on 12/3/2024.
//

#include <iostream>
#include <vector>
///#include "../Hashmap.h"
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
    Book books;
    bool end = false;
};

class Trie{
    private:
        Node* root;

    public:
        Trie(){
            root = new Node();
        }
///adds new book in trie based on given title
        void insert(const string& title, const Book& book){
            Node* curr = root;
            for(char c : title){ ///go through each letter
                if(!curr->child[c]){
                    curr->child[c] = new Node(); ///create new node if the letter if the letter has not been added
                }
                curr = curr->child[c];
            }
            curr->end = true; ///end of title
            curr->books = book; ///add book to this node
        }

///searches for the given book title
        Book search(const string& title){
            Node* curr = root;
            for(char c : title){
                if(!curr->child[c]){
                    return {}; ///return empty list if the book is not found
                }
                curr = curr->child[c];
            }
            if(curr->end){
                return curr->books; ///return the book
            }
            return {}; ///return empty list if book isn't found
        }

///determines whether a book is present or not
        bool contains(const string& title){
            Node* curr = root;
            for(char c : title){
                if(!curr->child[c]){
                    return false; ///return false if book isn't found
                }
                curr = curr->child[c];
            }
            if(curr->end){
                return true; ///return the book
            }
            return false; ///return false if book isn't found
        }

};



#endif //DSA_PROJECT3_TRIE_H


