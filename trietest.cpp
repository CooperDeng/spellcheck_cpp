 #include <iostream>
 #include <fstream>
 #include "Trie.h"
 
int main() {

    Trie tree;

    

    while(true) {
        
        // looking for commands
        std::string user_input;
        std::getline(std::cin, user_input);
        int found = user_input.find(" ");
        std::string input_c = user_input.substr(0, found);
        std::string rest = user_input.substr(found+1);

        if (input_c == "i") {
            tree.insert(rest);
        }

        if (input_c == "load") {
            
            std::ifstream fin("corpus.txt");
            std::string loadword;
            while (fin >> loadword) {
                tree.load(loadword);
            }

            std::cout <<"success\n";
        }

        if (input_c == "s") {
            tree.search(rest);
        }

        if (input_c == "e") {
            tree.erase(rest);
        }

        //for test purposes only
        if (user_input == "empty") {
            tree.empty();
        }

        if (user_input == "size"){
            tree.size();
        }   
        
        if (user_input == "clear"){
            tree.clear();
        }

        if (user_input == "exit"){
            break;
        }

        if (user_input == "p"){
            tree.print("",tree.getroot());
        }

        if (input_c == "spellcheck"){
            tree.spellcheck(rest);
        }
    }
    
    tree.~Trie();

    return 0;
}