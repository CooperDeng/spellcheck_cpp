#include <iostream>
#include "Node.h"

Node::Node() {
    data = "";
    EOW = 0;
    for(int i=0; i <26; i++) {
        this->children[i] = NULL;
    }
 }

Node::Node(std::string input) {
    data = input;
    EOW = 0;
    for(int i=0; i <26; i++) {
        this->children[i] = NULL;
    }
}

bool Node::getEOW() {

    if (EOW == 0) {
        return false;
    }

    else {
        return true;
    }

}

Node::~Node(){
    for(int i=0; i<26; i++) {
        if (this->children[i] != NULL) {
            delete this->children[i];
        }
        this->children[i] = NULL;
    }

    
}