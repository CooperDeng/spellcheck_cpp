#include <iostream>

class Node {
    public:

    std::string data;
    int EOW;
    Node *children[26];

    Node();

    Node(std::string input);

    bool getEOW();

    ~Node();

};