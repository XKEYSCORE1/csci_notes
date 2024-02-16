/*
CSIS 2610 - Lab 2 DUE: 2/19/2023 5:10pm
author: Milan Fusco

please rename this sourcecode file like "jdittrich_2610_lab2.cpp" - using your email username
submit via email attachment to: james.dittrich+YSU@gmail.com
*/

#include <iostream> // basic i/o
#include <iomanip> // output formatting
#include <cstdlib> // rand() and srand()
#include <ctime> // system time
#include <string> // string handling
using namespace std;

void showRules() {

  // welcome text
  cout << "\n************************************************" << endl;
  cout << "Welcome to Rock, Paper, Scissors, Lizard, Spock." << endl;
  cout << "************************************************\n" << endl;

  // show the rules
  cout << "\nThe rules are simple:" << endl;
  cout << "- Scissors cut Paper" << endl;
  cout << "- Rock crushes Lizard" << endl;
  cout << "- Paper covers Rock" << endl;
  cout << "- Lizard poisons Spock" << endl;
  cout << "- Spock smashes Scissors" << endl;
  cout << "- Scissors decapitate Lizard" << endl;
  cout << "- Lizard eats Paper" << endl;
  cout << "- Paper disproves Spock" << endl;
  cout << "- Spock vaporizes Rock" << endl;
  cout << "- Rock breaks Scissors\n" << endl;
  return;
}



void playGame(int* playerScore, int* opponentScore) {
  // delegate game logic and user input handling to a separate function
    // declare the player and opponent scores as pointers 
      // so that they can be modified in the other functions (pass by reference)

  string choices[] = {"Rock", "Paper", "Scissors", "Lizard", "Spock"};
  // declare an array of choices 0-4

  int playerChoice = 0;
  int opponentChoice = 0;
  // initalize player and opponent choices to 0 (important for replayability)


  for (int round = 0; round < 5; round++) {
    // loop function to display the round and choices

    cout << "===========" << "Round "  << (round + 1) << ": " << "===========" << endl;
    // "Round (n+1):"

    cout << "Choose your weapon (1-5): " << "\n" << "*******************************" << endl;
    // prompt the user to choose their selection


    do {
      // loop to get and validate the user's input

      for (int i = 0; i < 5; i++) {
      // for i in [0, 5) -> loop to display choices

      cout << (i + 1) << ". " << choices[i] << endl;
      // adjust for 0-based index and print the adjusted number and the corresponding choice

    }
      cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
      cout << "Please enter your choice (1-5): " << endl;

      cin >> playerChoice;
      // store the user's input


      if (cin.fail()) { 
        // Check for non-numeric input

        cin.clear(); 
        // Clear error state

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        // Ignore bad input

        cout << "Invalid choice. Please enter a number between 1 and 5.\n";

      } else {
        // Valid input

        playerChoice--;
        // Adjust for 0-based index


        if (playerChoice < 0 || playerChoice > 4) { 
          // Check for out-of-range numeric input

          cout << "Invalid choice. Please enter a number between 1 and 5.\n";

        } else {

          break; 
          // Valid input

        }

      }

    } while (true);
      // loop until the user is forced to comply and valid input is entered



    opponentChoice = rand() % 5;
    // declare and generate a random response for the opponent (0-4)

    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl; // visually separate the user's choice from the rounds results

    cout << "\nYou chose: " << choices[playerChoice] << endl;
    // visually verify the user's choice

    cout << "Your opponent chose: " << choices[opponentChoice] << "\n " << endl;
    // reveal the opponent's choice

    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

  

    // Evaluate the player's choice and the opponent's choice 
    // Array: Rock(0), Paper(1), Scissors(2), Lizard(3), Spock(4)

    switch(playerChoice){ 
      // evaluate the player's choice

      case 0: 
        // rock

        if (opponentChoice == 2 || opponentChoice == 3){ 
          // rock vs. scissors or lizard = Win


          cout << "Rock beats Scissors or Lizard!" << endl;
          cout << "--------------------------------" << endl;
          cout << "You win!" << endl;
          cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;

          (*playerScore)++; // dereference the pointer and increment the value

        }

        else if (opponentChoice == 0){
          // rock vs. rock = Tie


          cout << "Rock ties with Rock!" << endl;
          cout << "--------------------------------" << endl;
          cout << "Tie!" << endl;
          cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;

        }
        else {
          // rock vs. paper or spock = Loss


          cout << "Rock loses to Paper or Spock!" << endl;
          cout << "--------------------------------" << endl;
          cout << "You lose!" << endl; 
          cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;

          (*opponentScore)++; // dereference the pointer and increment the value

        }

        break;

      case 1: 
        // paper

        if (opponentChoice == 3 || opponentChoice == 4){ 
          // paper vs. lizard or spock = Win


          cout << "Paper beats Lizard or Spock!" << endl;
          cout << "--------------------------------" << endl;
          cout << "You win!" << endl; 
          cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;

          (*playerScore)++; // dereference the pointer and increment the value

        }

        else if (opponentChoice == 1){ 
          // paper vs. paper = Tie


          cout << "Paper ties with Paper!" << endl;
          cout << "--------------------------------" << endl;
          cout << "Tie!" << endl;
          cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;

        }

        else { // paper vs. rock or scissors = Loss


          cout << "Paper loses to Rock or Scissors!" << endl;
          cout << "--------------------------------" << endl;
          cout << "You lose!" << endl; 
          cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;

          (*opponentScore)++;  // dereference the pointer and increment the value      

        }

        break;

      case 2: 
        // scissors

        if (opponentChoice == 0 || opponentChoice == 4){ 
          // scissors vs. rock or spock = Win


          cout << "Scissors beats Rock or Spock!" << endl;
          cout << "--------------------------------" << endl;
          cout << "You win!" << endl;
          cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;


          (*playerScore)++;  // dereference the pointer and increment the value

        }

        else if (opponentChoice == 2){ 
          // scissors vs. scissors = Tie


          cout << "Scissors ties with Scissors!" << endl;
          cout << "--------------------------------" << endl;
          cout << "Tie!" << endl;
          cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;


        }
        else { 
          // scissors vs. paper or lizard = Loss


          cout << "Scissors loses to Paper or Lizard!" << endl;
          cout << "--------------------------------" << endl;
          cout << "You lose!" << endl; 
          cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;


          (*opponentScore)++; // dereference the pointer and increment the value    
        }
        break;
      case 3: 
        // lizard
        if (opponentChoice == 0 || opponentChoice == 2){ 
          // lizard vs. rock or scissors = Win

          cout << "Lizard beats Rock or Scissors!" << endl;
          cout << "--------------------------------" << endl;
          cout << "You win!" << endl;
          cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;


          (*playerScore)++; // dereference the pointer and increment the value
        }
        else if (opponentChoice == 3){ 
          // lizard vs. lizard = Tie

          cout << "Lizard ties with Lizard!" << endl;
          cout << "--------------------------------" << endl;
          cout << "Tie!" << endl;
          cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;

        }
        else { 
          // lizard vs. paper or spock = Loss

          cout << "Lizard loses to Paper or Spock!" << endl;
          cout << "--------------------------------" << endl;
          cout << "You lose!" << endl; 
          cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;

          
          (*opponentScore)++; // dereference the pointer and increment the value  
        }

        break;

      case 4: 
        // spock

        if (opponentChoice == 1 || opponentChoice == 3){ 
          // spock vs. paper or lizard = Win

          cout << "Spock beats Paper or Lizard!" << endl;
          cout << "--------------------------------" << endl;
          cout << "You win!" << endl;
          cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;

          (*playerScore)++; // dereference the pointer and increment the value

          
        }

        else if (opponentChoice == 4){ 
          // spock vs. spock = Tie


          cout << "Spock ties with Spock!" << endl;
          cout << "--------------------------------" << endl;
          cout << "Tie!" << endl;
          cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;

          
        }

        else { 
          // spock vs. rock or scissors = Loss


          cout << "Spock loses to Rock or Scissors!" << endl;
          cout << "--------------------------------" << endl;
          cout << "You lose!" << endl; 
          cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;

          (*opponentScore)++;  // dereference the pointer and increment the value  

          
        }
        break;

      default: 
        // invalid choice


        cout << "Invalid choice!" << endl;
        cout << "--------------------------------" << endl;
        cout << "Please only use numbers 1-5" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;
        round--; // give user another chance to enter a valid choice

        break;

    }


    // display the round's score
    cout << "*********Round Score**********\n" << "Player score: " << *playerScore  << endl;

    cout  << "Opponent score: " << *opponentScore << "\n******************************\n" << endl;


    if (*playerScore >= 5 || *opponentScore >= 5) {  
			// dereference the pointer and check if a player has reached 5 points

      break; 
      // Exit the loop early if a player reaches 5 points

    } //

  } // best of 5 game ends here.

} // playGame ends here.





void finalResults(int* playerScore, int* opponentScore){
	// dereference the pointers to be displayed

    if (*playerScore > *opponentScore) { 

      // win case
      cout << "Winner Winner Chicken Dinner!\n";
    } 

		else if (*opponentScore > *playerScore) { 
      // lose case
      cout << "You lose, better luck next time!\n";

    } else { 
      // tie case

      cout << "The game is a tie!\n";

    }

    cout << "\n***************Final Score**************:\n";
    cout << "Player: " << *playerScore; // display player's final score
    cout << "\n****************************************:\n";
    cout << "Opponent: " << *opponentScore; // display opponent's final score
    cout << "\n****************************************:\n";

    
  } // finalResults ends here.





int main(){

    int seed = static_cast<unsigned>(time(0)); 
    // seed the random number generator` with a non-negative
    // integer value (current system time)

    srand(seed); 
    // initialize the random number generator

      
    int playerScore=0;
    int opponentScore=0;
    // declare integers for the score

    char replay = '0'; // Declare the replay variable with a default value




    do { 
      // call the showRules() function and the playGame() + finalResults() functions with parameters

        playerScore = 0; // Reset player score
        opponentScore = 0; // Reset opponent score

        showRules(); 
          // Shows the rules of the game

        playGame(&playerScore, &opponentScore); 
          // Calls the game logic (passes playerScore and opponentScore by reference)

        finalResults(&playerScore, &opponentScore); 
          // Displays the final results (passes playerScore and opponentScore by reference)

        cout << "Play again? (y/n): "; // prompt to user play again
        


        do { 
          cin >> replay; 
          // store the user's input


          if (replay != 'y' && replay != 'Y' && replay != 'n' && replay != 'N') {
          // Input validation (while y/Y/n/N is not entered, prompt the user again)

            cout << "Invalid input. Please enter 'y' or 'n': "; 
          }


        } while (replay != 'y' && replay != 'Y' && replay != 'n' && replay != 'N');
          // loop the prompt until the user enters a valid input
    


    } while (replay == 'y' || replay == 'Y'); 
    // loop the game's main menu if the user wants to play again



    cout << "\nGoodbye!\n" << endl; 
    // bid farewell to the user

    return 0; 
    // exit main	

} // main ends here.  	