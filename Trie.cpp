#include<iostream>
#include"Trie.h"

//illegal exception
illegal_exception::illegal_exception() {
    error = "illegal argument\n";
}

//constructor
Trie::Trie() {
    Node * tempptr = new Node();
    root = tempptr;
    tempptr = NULL;

    //just to be more explicit
    for (int i = 0; i<26; i++){
        root->children[i] = NULL;
    }

    counter = 0;
    e_counter = 0;
}

// This function is inspired by code from 
// www.geeksforgeeks.org/trie-insert-and-search/
void Trie::insert(std::string word) {

    //traversing node through tree to find a place for insert
    Node *traverse = root;

    for (int i = 0; i<word.length(); i++) {

        //practically the "index of the character"
        //should be in range of [0,26]
        int index_char = word[i] - 'a';

        //try throw and catch
        //if the character is legal or not
        try {
            if (index_char < 0 || index_char > 26) {
                throw illegal_exception();
            }
        }
        catch(illegal_exception exception) {
            std::cout <<exception.error;
            return;
        }

        //test if the node is empty
        //if it is, we create a new node
        if (traverse->children[index_char]==NULL){
            Node *newNode = new Node();
            traverse->children[index_char] = newNode;
            newNode = NULL;
        }

        //looping into the next node
        traverse = traverse->children[index_char];
    }

    //if this is a end of word
    if (traverse->getEOW()) {
        std::cout << "failure\n";
        traverse = NULL;
        return;
    }

    //we dont really need else here, but i'm putting it here just to
    //be more explicit
    else {
        counter++;
        traverse->EOW=1;
        traverse=NULL;
        std::cout <<"success\n";
        return;
    }
}

// This function is inspired by code from 
// www.geeksforgeeks.org/trie-insert-and-search/
void Trie::load(std::string word){
    //load is 99% the same thing as insert, we just modify its
    //actions when it comes to outputting stuff
    //traversing node through tree to find a place for insert
    Node *traverse = root;

    for (int i = 0; i<word.length(); i++) {

        //practically the "index of the character"
        //should be in range of [0,26]
        int index_char = word[i] - 'a';

        //try throw and catch
        //if the character is legal or not
        try {
            if (index_char < 0 || index_char > 26) {
                throw illegal_exception();
            }
        }
        catch(illegal_exception exception) {
            std::cout <<exception.error;
            return;
        }

        //test if the node is empty
        //if it is, we create a new node
        if (traverse->children[index_char]==NULL){
            Node *newNode = new Node();
            traverse->children[index_char] = newNode;
            newNode = NULL;
        }

        //looping into the next node
        traverse = traverse->children[index_char];
    }

    //if this is a end of word
    //load does not display output
    if (traverse->getEOW()) {
        traverse = NULL;
        return;
    }

    //we dont really need else here, but i'm putting it here just to
    //be more explicit
    else {
        counter++;
        traverse->EOW=1;
        traverse=NULL;
        return;
    }
}

// This function is inspired by code from 
// www.geeksforgeeks.org/trie-insert-and-search/
void Trie::search(std::string word) {
    //we use the same looping algotithm as in insert
    //after reaching the end, we check if it's the EOW
    //if we reach the end while looking for it, then the word 
    //is definitely not in the trie
    Node *traverse = root;

    for (int i = 0; i<word.length(); i++) {

        //practically the "index of the character"
        //should be in range of [0,26]
        int index_char = word[i] - 'a';

        //bruh
        //trying to find empty/EOW at i = word.length()-1
        if (traverse->children[index_char] == NULL) {
            std::cout << "not found" << std::endl;
            return;
        }
        traverse = traverse->children[index_char];
    }

    //right now i = word.length()-1
    //look for EOW 
    if (traverse->getEOW()) {
        std::cout << "found word" << "\n";
        return;
    }

    else {
        std::cout << "not found\n";
        return;
    }
}

void Trie::erase(std::string word) {
    //we're trying to find the EOW and erase it
    //we're still using the same loop from insert
    //traversing node through tree to find EOW or empty
    Node *traverse = root;

    for (int i = 0; i<word.length(); i++) {

        //practically the "index of the character"
        //should be in range of [0,26]
        int index_char = word[i] - 'a';

        //test if the node is empty
        //if it is, we output error
        if (traverse->children[index_char]==NULL){
            std::cout <<"failure\n";
            traverse = NULL;
            return;
        }   

        //looping into the next node
        traverse = traverse->children[index_char];
    }

    //if this is a EOW
    //we set the EOW back to 0
    if (traverse->getEOW()) {
        traverse->EOW = 0;
        std::cout << "success\n";
        traverse = NULL;
        counter--;
        return;
    }

    //we dont really need else here, but i'm putting it here just to
    //be more explicit
    else {
        std::cout << "failure\n";
        traverse = NULL;
        return;
    }
} 

Node* Trie::getroot(){
    return this->root;
}

//recursion, call upon itself with a new set of input
//this function is inspired by the code provided at:
//https://stackoverflow.com/questions/13685687/how-to-print-all-words-in-a-trie
//by user Yakk - Adam Nevraumont
void Trie::print(std::string word, Node* traverse) {
    //only prints out word with it's the EOW
    if (traverse -> getEOW()) {
        std::cout << word << " ";
        e_counter ++;
        if (e_counter == counter){
            e_counter = 0;
            std::cout << std::endl;
        }
    }

    //looping through to find the next available word to print
    for (int i=0; i<26; i++){
        Node* temp = traverse->children[i];
        if (temp != NULL) {
            word.push_back('a' + i);
            print(word,temp);
            word.pop_back();
        }
    }    
}

void Trie::spellcheck(std::string word) {
    spellcheckprint("",root,word);
}

void Trie::spellcheckprint(std::string word, Node* traverse, std::string base){
    //only prints out word with it's the EOW and based off the base
    if (traverse -> getEOW() && word.substr(0,base.length())== base) {
        std::cout << word << " ";
        e_counter ++;
        if (e_counter == counter){
            e_counter = 0;
            std::cout << std::endl;
        }
    }

    //e_counter is still going up within spellcheck even though it's not printing
    else if (traverse->getEOW()){
        e_counter ++;
        if (e_counter == counter){
            e_counter = 0;
            std::cout << std::endl;
        }
    }


    //looping through to find the next available word to print
    for (int i=0; i<26; i++){
        Node* temp = traverse->children[i];
        if (temp != NULL) {
            word.push_back('a' + i);
            spellcheckprint(word,temp,base);
            word.pop_back();
        }
    }    
}

void Trie::empty() {
    if (counter == 0) {
        std::cout << "empty 1\n";
        return;
    }

    else {
        std::cout << "empty 0\n";
        return;
    }
}

void Trie::clear() {

    //clearing everything from the root
    for (int i = 0; i < 26; i++) {
        if (root->children[i] != NULL) {
            delete root->children[i];
        }
        root->children[i] = NULL;
    }
    counter = 0;

    std::cout << "success" << "\n";
    return;
}

void Trie::size() {
    std::cout << "number of words is: " << counter << std::endl;
    return;
}

//destructor
Trie::~Trie() {
// i commented it out because valgrind suggests "invalid read of size 8"
/*
    for (int i = 0; i<26; i++){
        if (root->children[i] != NULL) {
            Node * tempptr = root->children[i];
            delete tempptr;
            tempptr = NULL;
        }
        root->children[i] = NULL;
    }
*/
    Node *tempptr = root; 
    root = NULL;
    delete tempptr;
    tempptr = NULL;
}