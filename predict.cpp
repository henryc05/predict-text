#include <iostream>
#include "backtracking.h"
#include "lexicon.h"
#include "set.h"
#include "SimpleTest.h"
using namespace std;

// keypad is a program-wide constant that stores the Map from digit char to
// its associated set of possible letters
static const Map<char, Set<char>> keypad = {
    {'2', {'a','b','c'} }, {'3', {'d','e','f'} }, {'4', {'g','h','i'} },
    {'5', {'j','k','l'} }, {'6', {'m','n','o'} }, {'7', {'p','q','r','s'} },
    {'8', {'t','u','v'} }, {'9', {'w','x','y','z'} } };

// this is a predictor helper function that takes in digits, suggestions, lex, and past word. This helper function
// follows a recursion search tree that accesses the string digits and recursively filters through each digit to predict
// and generate possible words from the digits that are inputted. The way this helper function does this is through mainly
// base cases where if a word prefix that is generated is not in the lex dictionary, it is automatically removed. Else,
// when the digits are looped through, add every suggestion into the suggestion set.
void predictor(string digits, Set<string>& suggestions, Lexicon& lex, string pastWord){
    if ( digits.length() == 0 && lex.contains(pastWord) ){ // when there is no more digit
        suggestions.add(pastWord);
        return;

    }

    if (!lex.containsPrefix(pastWord)){ // future
        return;
    }

    Set<char> letters = keypad.get(digits[0]);

    for (char letter : letters){
        predictor(digits.substr(1), suggestions, lex, pastWord + letter);
    }

}
// this is a void wrapper function that calls in predictor with more parameters.
void predict(string digits, Set<string>& suggestions, Lexicon& lex) {
    predictor(digits, suggestions, lex, "");
}


/* Test helper function to return shared copy of Lexicon. Use to
 * avoid (expensive) re-load of word list on each test case. */
static Lexicon& sharedLexicon() {
    static Lexicon lex("res/EnglishWords.txt");
    return lex;
}
