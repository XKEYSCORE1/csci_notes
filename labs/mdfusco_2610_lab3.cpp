// Lab 3: Madlibs
// DUE: 2024-03-10 (March 10) 11:59pm
// rename to "username_lab3.cpp" and submit to
// james.dittrich+YSU@gmail.com
#include <iostream>
#include <iomanip>
#include <cctype>
#include <string>
using namespace std;

// a function to show the rules of the game
void showRules() {
    // welcome text
    cout << "\n************************************************" << endl;
    cout << "Welcome to MADLIBS" << endl;
    cout << "************************************************\n" << endl;

    // show the rules
    cout << "\nThe rules are simple:" << endl;
    cout << "Fill in the blanks with your own words to create a funny story!\n" << endl;

    return;
}

// a function to find and replace a substring in a string
    // Replaces every instance of 'findStr' with 'replaceStr' within 'story'.
        // Parameters are passed by reference, enabling direct modification of the original 'story' string in the calling function in PlayGame().
void findAndReplace(string& story, const string& findStr, const string& replaceStr) {

    // Initialize unsigned integer pos to store the position of each occurrence of findStr
    size_t pos = 0;

    // Continue to search and replace as long as findStr is found in story and not at the end of the string
        // "string::npos" is a constant representing the maximum value for pos
    while ((pos = story.find(findStr, pos)) != string::npos) { 

    // Replace findStr with replaceStr
        // string.replace(starting position, length, replacement string)
        story.replace(pos, findStr.length(), replaceStr); 

    //  increment the position by the length of the replacement string 
        pos += replaceStr.length();

    }
}


// a function to play the game
void playGame(){

    // declare story string
    string story = "Hey _VERB1_ _VERB1_,\nThe _NOUN2_ and the _NOUN3_,\nThe cow _VERB2_ over the _NOUN4_;\nThe _ADJ1_ _NOUN5_ _VERB3_\nTo see such sport,\nAnd the _NOUN6_ _VERB4_ away with the _NOUN7_.";

    // declare an integer for the size of the word list
    const int wordListSize = 11;

    // declare an array of strings to hold the words
    string words[wordListSize];

    // declare an array of strings to hold the hints
    string hints[wordListSize] = {
        "silly nonsense word (verb)", // [0]
        "animal (noun)", // [1]
        "thing (noun)", // [2]
        "(verb - past tense)", // [3]
        "place (noun)", // [4] 
        "(adjective)", // [5]
        "animal (noun)", // [6]
        "(verb - past tense)", // [7]
        "thing (noun)",  // [8]
        "(verb - past tense)", // [9]
        "thing (noun)" // [10]
    };

    // declare an array of strings to hold the targets
    string targets[wordListSize] = {
    "_VERB1_", // [0]
    "_NOUN2_", // [1]
    "_NOUN3_", // [2]
    "_VERB2_", // [3]
    "_NOUN4_", // [4]
    "_ADJ1_",  // [5]
    "_NOUN5_", // [6]
    "_VERB3_", // [7]
    "_NOUN6_", // [8]
    "_VERB4_", // [9]
    "_NOUN7_" // [10]
    };

    // declare the index variable to keep track of the current word substring
    int i = 0;

    // loop through the word list array, get the users input and replace the target word with the user's word
    for (int i = 0; i < wordListSize; i++) {
        cout << "Enter a " << hints[i] << ": "; // prompt the user for a word
        getline(cin, words[i]); // get the user's input


            // Convert each character in each substring to lowercase
                // for (each character in the substring (string length is a 0-based index, the character index (j) is less than the length of the substring, increment the character index), 
        for (size_t j = 0; j < words[i].length(); j++) { 

                        // i is the index of the word substring, j is the index of the character in the substring
            words[i][j] = tolower(words[i][j]); 
        }

            // Convert first letter of the substring to uppercase
                 // if the substring is not empty, convert the first letter to uppercase
        if (!words[i].empty()) { 

            // i is the index of the word substring, 0 is the index of the first character in the substring
            words[i][0] = toupper(words[i][0]); 
        }

            //call findAndReplace replace the target word with the user's word
                // parameters: story, targets[i], words[i]
                     // accepted by reference in the findAndReplace function
                        //  story -> string& story |  targets[i] -> const string& findStr |  words[i] -> const string& replaceStr, 
        findAndReplace(story, targets[i], words[i]);

    }
    // display the story
    cout << "\nYour MadLibs Story: \n" << story << endl;
}


// main function
int main(){

  // replay loop (the game state)
  char replay = 'y';
  // show the rules
  showRules();

  do { // do-while loop to play the game at least once
    // play the game
    playGame();
    // prompt to replay(y/n)
    cout << "Do you want to play again? (y/n): ";
    cin >> replay;

    // Clear the input buffer when starting a new game and before getting new user input
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

  } while (replay == 'y' || replay == 'Y');
  
  cout << "\nGoodbye!\n";
}