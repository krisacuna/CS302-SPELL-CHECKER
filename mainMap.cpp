/*
Name: KRISTOPHER ACUNA, 5005035589, 1004, AST5
Description: First time working with a hash map
Input: .txt files, also a .txt file of a dictionary with 60,000 words
Output: shows us possible Mispelled words, and applicable suggested words
from the dictionary.
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
// function declaration
vector<string> findClosestWords(const string &inputtedWords);
//-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=--
int main() {
  // not the global declarations, but these are found in the main
  unordered_map<string, int> listOfWords;
  vector<string> wordsToCheck;
  string inputWord;
  unordered_map<string, int> foundWordTwice;
  // enter the filename we want
  cout << "\nEnter filename: ";
  string fileName;
  cin >> fileName;
  // we must set the first infile into usa.txt
  ifstream firstInfile("usa.txt");
  ifstream secondInfile(fileName);
  // open it and place the 60,000 words from usa.txt into a unoredered_map
  // of list of words
  if (firstInfile.is_open()) {
    string wordStrings;
    while (firstInfile >> wordStrings) {
      // go ahead and change the strings to all uppercase
      transform(wordStrings.begin(), wordStrings.end(), wordStrings.begin(),
                ::toupper);
      listOfWords[wordStrings] = true;
    }
  }
  // -= -= -= -= -= -= -= -= -= -= -= -= -= -= -= -= -= -= -=
  // grabs the second infile
  // in which we take the other .txt file and compare it against the
  // already undordered map.
  if (secondInfile.is_open()) {
    while (secondInfile >> inputWord) {
      bool word_already_in_vector = false;
      // use toupper to make the string uppercase
      for (auto &charWord : inputWord) {
        charWord = toupper(charWord);
      }
      if (foundWordTwice.find(inputWord) == foundWordTwice.end()) {
        foundWordTwice[inputWord] = true;
      }
      // for loop that runs through the wordsToCheck
      // and checks the bool to see if we should push.back this into the map
      for (const auto &w : wordsToCheck) {
        if (w == inputWord) {
          // sets to true
          word_already_in_vector = true;
          break;
        }
      }
      // if word is not in already in vector, we will push.back this
      if (!word_already_in_vector) {
        wordsToCheck.push_back(inputWord);
      }
    }
  }
  // -= -= -= -= -= -= -= -= -= -= -= -= -= -= -= -= -= -= -=

  cout << "\n";
  // Create an iterator to go from the beginning to the end in this
  // while loop. while incremeting the iterator.
  auto it = wordsToCheck.begin();
  while (it != wordsToCheck.end()) {
    const auto &word = *it;
    ++it;
    // checks to see if the following word is found
    if (listOfWords.count(word) == 0) {
      vector<string> possibleWordSuggestion;
      cout << word << " is misspelled";
      cout << endl << endl;
      // -= -= -= -= -= -= -= -= -= -= -= -= -= -= -= -= -= -= -=
      // this is where we call find the cloest words which is
      // my only function for this program
      for (size_t i = 0; i < findClosestWords(word).size(); ++i) {
        auto &possibleWord = findClosestWords(word)[i];
        // complete a push back if it goes into this if statement
        if (listOfWords.count(possibleWord)) {
          possibleWordSuggestion.push_back(possibleWord);
        }
      }
      // have I found an empty vector? therefore I have no suggestions
      if (possibleWordSuggestion.size() == 0) {
        cout << "No suggestions";
        cout << endl;
      } else if (possibleWordSuggestion.size() > 0) {
        cout << "Suggested words";
        cout << endl;
        // otherwise print the suggested words
        // -= -= -= -= -= -= -= -= -= -= -= -= -= -= -= -= -= -= -=
        // call the sort function! this is how I take possible words
        // and sort them
        sort(possibleWordSuggestion.begin(), possibleWordSuggestion.end());
        // our iterator will go through in a for loop and cout and possible
        // words.
        for (auto it = possibleWordSuggestion.begin();
             it != possibleWordSuggestion.end(); ++it) {
          cout << *it << "\n";
        }
      }
      cout << "\n";
    }
  }
  // end of code
  return 0;
}
//-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-

/*
FUNCTION_IDENTIFIER: vector<string> findClosestWords(const string
&inputtedWords) parameters: const string &inputtedWords return value: findWord
description: Returns findWord which is a vector of strings. Found out the
suggested words that had different letters at that same position that was also a
word.
*/

vector<string> findClosestWords(const string &inputtedWords) {
  // Declarations within the function
  vector<string> findWord;
  // our unordered map of FoundWord, which is a string and int value
  unordered_map<string, int> foundWord;
  // Nested for loop
  // which goes through the inputtedWords list length
  for (int i = 0; i <= inputtedWords.length(); ++i) {
    // Second part of the for loop allows us to run from ASCII 'A' -> 'Z'
    for (char currentChar = 'A'; currentChar <= 'Z'; ++currentChar) {
      string firstW = inputtedWords;
      string secondW = inputtedWords;
      // this second word allows the char to be inserted at the
      // specific location.
      secondW = secondW.substr(0, i) + currentChar + secondW.substr(i);
      if (foundWord.count(secondW) == 0) {
        // inserts this at the end of the find word vector
        findWord.insert(findWord.end(), secondW);
      }
      // this is where we check the current char and its length so that
      // we can replace at the specific location.
      if (i < inputtedWords.length() && currentChar != inputtedWords[i]) {
        firstW.replace(i, 1, 1, currentChar);
        // inserts this at the end of the find word vector
        findWord.insert(findWord.end(), firstW);
      }
    }
  }
  // allows us to sort the findWord vector
  sort(findWord.begin(), findWord.end());
  return findWord;
}