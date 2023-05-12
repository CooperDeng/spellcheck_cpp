#include<iostream>
#include "Node.h"

class Trie {
    private:

    Node* root;
    int counter;
    int e_counter;
    public:

    //constructor
    Trie();

    void insert(std::string word);
    void load(std::string word);
    void search(std::string word);
    void erase(std::string word);
    void print(std::string word, Node* traverse);
    void spellcheck(std::string word);
    void spellcheckprint(std::string word, Node* traverse, std::string base);
    void empty();
    void clear();
    void size();

    //for using the print function
    Node* getroot();
    
    //destructor
    ~Trie();
};

class illegal_exception {
    public:
    std::string error;
    illegal_exception();
};