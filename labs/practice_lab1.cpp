#include <iostream>
#include <iomanip>
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

// a function to find and replace all occurrences of a substring in a string
void findAndReplace(string& story, const string& findStr, const string& replaceStr) {
    // find the first occurrence of the substring
    size_t pos = 0;
    // loop through the string to replace all the occurrences
    while ((pos = story.find(findStr, pos)) != string::npos) {
        story.replace(pos, findStr.length(), replaceStr);
        // move to the next occurrence
        pos += replaceStr.length();
    }
}

// a function to play the game
void playGame(){

    // declare story string
    string story = "Hey _VERB1_ _VERB1_,\nThe _NOUN2_ and the _NOUN3_,\nThe cow _VERB2_ over the _NOUN4_;\nThe _ADJ1_ _NOUN5_ _VERB3_\nTo see such sport,\nAnd the _NOUN6_ _VERB4_ away with the _NOUN7_.";

    // word input loop
    const int wordListSize = 11;

    // declare an array of strings to hold the words
    string words[wordListSize];

    // hints give the user an idea of what type of word to enter
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

    //  prompt for user input
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

    // declare the index variable to keep track of the current word
    int i = 0;
    // loop through the word list
    for (int i = 0; i < wordListSize; i++) {
        cout << "Enter a " << hints[i] << ": ";
        getline(cin, words[i]);


            // Convert to lowercase
        for (size_t j = 0; j < words[i].length(); j++) {
            words[i][j] = tolower(words[i][j]);
        }

            // Convert first letter to uppercase
        if (!words[i].empty()) {
            words[i][0] = toupper(words[i][0]);
        }

        findAndReplace(story, targets[i], words[i]);
    }

    cout << "\n Your MadLibs Story: \n" << story << endl;
}

// main function
int main(){

  // replay loop (the game state)
  char replay = 'y';
  // show the rules
  showRules();

  // play the game
  do {
    // play the game
    playGame();
    // prompt to replay(y/n)
    cout << "Do you want to play again? (y/n): ";
    cin >> replay;

    // Clear the input buffer starting a new game and before getting new words
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

  } while (replay == 'y' || replay == 'Y');
  
  cout << "Goodbye!\n";

  exit(0);

}

