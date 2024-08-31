#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>

// Custom hash function for std::pair
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2>& pair) const {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};

class DFA {
private:
    std::unordered_set<int> states; // Set of states
    std::unordered_set<char> alphabet; // Input alphabet
    std::unordered_map<std::pair<int, char>, int, pair_hash> transitionFunction; // Transition function
    int startState; // Start state
    std::unordered_set<int> acceptStates; // Set of accept states

public:
    DFA(const std::unordered_set<int>& states, const std::unordered_set<char>& alphabet, 
        const std::unordered_map<std::pair<int, char>, int, pair_hash>& transitionFunction, 
        int startState, const std::unordered_set<int>& acceptStates) 
        : states(states), alphabet(alphabet), transitionFunction(transitionFunction), 
          startState(startState), acceptStates(acceptStates) {}

    bool isAccepted(const std::string& input) {
        int currentState = startState;
        for (char symbol : input) {
            if (alphabet.find(symbol) == alphabet.end()) {
                std::cout << "Error: Symbol " << symbol << " not in DFA alphabet!" << std::endl;
                return false;
            }
            auto transition = std::make_pair(currentState, symbol);
            if (transitionFunction.find(transition) == transitionFunction.end()) {
                std::cout << "Error: No transition defined for state " << currentState << " on symbol " << symbol << std::endl;
                return false;
            }
            currentState = transitionFunction[transition];
        }
        return acceptStates.find(currentState) != acceptStates.end();
    }
};

int main() {
    // Define states
    std::unordered_set<int> states;
    states.insert(0);
    states.insert(1);
    states.insert(2);


    // Define alphabet
    std::unordered_set<char> alphabet;
    alphabet.insert('a');
    alphabet.insert('b');


    // Define transition function with the custom pair_hash
    std::unordered_map<std::pair<int, char>, int, pair_hash> transitionFunction;
    transitionFunction.insert(std::make_pair(std::make_pair(0, 'a'), 1));
    transitionFunction.insert(std::make_pair(std::make_pair(0, 'b'), 0));
    transitionFunction.insert(std::make_pair(std::make_pair(1, 'a'), 1));
    transitionFunction.insert(std::make_pair(std::make_pair(1, 'b'), 2));
    transitionFunction.insert(std::make_pair(std::make_pair(2, 'a'), 1));
    transitionFunction.insert(std::make_pair(std::make_pair(2, 'b'), 0));



    // Define start state
    int startState = 0;

    // Define accept states
    std::unordered_set<int> acceptStates;
    acceptStates.insert(2);

    // Create DFA
    DFA dfa(states, alphabet, transitionFunction, startState, acceptStates);

    // Test strings
    std::vector<std::string> testStrings;
    testStrings.push_back("ab");
    testStrings.push_back("aab");
    testStrings.push_back("abb");
    testStrings.push_back("aabba");
    testStrings.push_back("ba");


    for (const std::string& input : testStrings) {
        if (dfa.isAccepted(input)) {
            std::cout << "The string \"" << input << "\" is accepted by the DFA." << std::endl;
        } else {
            std::cout << "The string \"" << input << "\" is rejected by the DFA." << std::endl;
        }
    }

    return 0;
}
