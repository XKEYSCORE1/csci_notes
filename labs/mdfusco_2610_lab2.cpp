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


void showRules(){ // show the rules
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
  cout << "- Rock breaks Scissors" << endl;
  return;
}




void playGame(int& playerScore, int& opponentScore)  {  
    // pass arguments by reference rather than value (to make them accessible externally)
  string choices[] = {"Rock","Paper","Scissors","Lizard","Spock"}; 
   // declare an array of choices 1-5

  int playerChoice = 0;
  int opponentChoice = 0;
   // initalize player and opponent choices to 0 (important for replayability)

  cout << "\n************************************************" << endl; // welcome text
  cout << "Welcome to Rock, Paper, Scissors, Lizard, Spock." << endl;
  cout << "************************************************" << endl; 

    for(int round=0; round<5; round++){ 
      // loop function to display the round and choices

        cout << "Round " << (round+1) << ": \n"; 
        // "Round (n+1):"

        for(int i=0; i<5; i++){ 
          // for i in [0, 5) -> loop to display choices
            cout << (i+1) << ". " << choices[i] << "\n"; 
            // adjust for 0-based index and print the adjusted number and the corresponding choice
        }
            cout << "Please enter your choice (1-5): " << endl;  
              // prompt the user for their choice
            cin >> playerChoice; 
              // read the user's choice
                if (playerChoice < 1 || playerChoice > 5) { // input validation (1<n<5)
                    cout << "Invalid choice. Round skipped.\n";
                    round--; // Decrement round to give player another chance if invalid
                    continue;
                }
            playerChoice--; 
              // Adjust for 0-based index

      
            opponentChoice = rand() % 5;    
            // declare and generate a random response for the opponent (0-4)

            cout << "You chose: " << choices[playerChoice] << endl; 
            // visually verify the user's choice
            cout << "Your opponent chose: " << choices[opponentChoice] << endl; 
            // reveal the opponent's choice

      
            // Array: Rock(0), Paper(1), Scissors(2), Lizard(3), Spock(4)

            switch(playerChoice){ 
                // evaluate the player's choice

                        case 0: 
                            // rock
                            if (opponentChoice == 2 || opponentChoice == 3){ 
                              // rock vs. scissors or lizard = Win
                                cout << "************" << endl;
                                cout << "You win!" << endl;
                                cout << "************" << endl;
                                playerScore++;
                            }
                            else if (opponentChoice == 1){ 
                              // rock vs. rock = Tie
                                cout << "Tie!" << endl;
                                cout << "************" << endl;
                            }
                            else {
                              // rock vs. paper or spock = Loss
                                cout << "************" << endl;
                                cout << "You lose!" << endl; 
                                cout << "************" << endl;
                                opponentScore++;
                            }
                            break;
                        case 1: 
                            // paper
                            if (opponentChoice == 3 || opponentChoice == 4){ 
                              // paper vs. lizard or spock = Win
                                cout << "************" << endl;
                                cout << "You win!" << endl; 
                                cout << "************" << endl;
                                playerScore++;
                            }
                            else if (opponentChoice == 2){ 
                                // paper vs. paper = Tie
                                cout << "************" << endl;
                                cout << "Tie!" << endl;
                                cout << "************" << endl;
                            }
                            else { // paper vs. rock or scissors = Loss
                                cout << "************" << endl;
                                cout << "You lose!" << endl; 
                                cout << "************" << endl;
                                opponentScore++;
                            }
                            break;
                        case 2: 
                            // scissors
                            if (opponentChoice == 0 || opponentChoice == 4){ 
                                // scissors vs. rock or spock = Win
                                cout << "************" << endl;
                                cout << "You win!" << endl;
                                cout << "************" << endl;
                                playerScore++;
                            }
                            else if (opponentChoice == 3){ 
                                // scissors vs. scissors = Tie
                                cout << "************" << endl;
                                cout << "Tie!" << endl;
                                cout << "************" << endl;
                            }
                            else { 
                                // scissors vs. paper or lizard = Loss
                                cout << "************" << endl;
                                cout << "You lose!" << endl; 
                                cout << "************" << endl;
                                opponentScore++;
                            }
                            break;
                        case 3: 
                            // lizard
                            if (opponentChoice == 0 || opponentChoice == 2){ 
                                // lizard vs. rock or scissors = Win
                                cout << "************" << endl;
                                cout << "You win!" << endl;
                                cout << "************" << endl;
                                playerScore++;
                            }
                            else if (opponentChoice == 4){ 
                                // lizard vs. lizard = Tie
                                cout << "************" << endl;
                                cout << "Tie!" << endl;
                                cout << "************" << endl;
                            }
                            else { 
                                // lizard vs. paper or spock = Loss
                                cout << "************" << endl;
                                cout << "You lose!" << endl; 
                                cout << "************" << endl;
                                opponentScore++;
                            }
                            break;
                        case 4: 
                            // spock
                            if (opponentChoice == 1 || opponentChoice == 3){ 
                                // spock vs. paper or lizard = Win
                                cout << "************" << endl;
                                cout << "You win!" << endl;
                                cout << "************" << endl;
                                playerScore++;
                            }
                            else if (opponentChoice == 4){ 
                                // spock vs. spock = Tie
                                cout << "************" << endl;
                                cout << "Tie!" << endl;
                                cout << "************" << endl;
                            }
                            else { 
                                // spock vs. rock or scissors = Loss
                                cout << "************" << endl;
                                cout << "You lose!" << endl; 
                                cout << "************" << endl;
                                opponentScore++;
                            }
                            break;
                        default: 
                            // invalid choice
                            cout << "************" << endl;
                            cout << "Invalid choice!" << endl;
                            cout << "************" << endl;
                            break;
                    }


            // display player scores
            cout << "*******************\n" << "Player score: " << playerScore  << endl;
            cout  << "Opponent score: " << opponentScore << "\n*******************\n" << endl;
      
        } // best of 5 game ends here.

} // playGame ends here.




void finalResults(int playerScore, int opponentScore){

         if (playerScore > opponentScore) { 
           // win case
            cout << "Winner Winner Chicken Dinner!\n";
        } else if (opponentScore > playerScore) { 
           // loose case
            cout << "You loose, better luck next time!\n";
        } else { 
           // tie case
            cout << "The game is a tie!\n";
        }

        cout << "\n***************Final Score**************:\n";
        cout << "Player: " << playerScore << "\n"; // display player's final score
        cout << "\n****************************************:\n";
        cout << "Opponent: " << opponentScore << "\n"; // display opponent's final score
        cout << "\n****************************************:\n";


} // finalResults ends here.




int main(){
  
  int seed = static_cast<unsigned>(time(0)); // seed the random number generator` with a non-negative
  
  srand(seed); // initialize the random number generator
    
    int playerScore=0;
    int opponentScore=0;
    // declare integers for the score

    char replay;
    // declare replay character

    do{ 
      // call the showRules() function and the playGame() + finalResults() functions with parameters

        playerScore = 0; // Reset player score
        opponentScore = 0; // Reset opponent score

        showRules(); 
          // Shows the rules of the game
        playGame(playerScore, opponentScore); 
          // Calls the game logic
        finalResults(playerScore, opponentScore); 
          // Displays the final results

        cout << "Play again? (y/n): "; // prompt to user play again
        cin >> replay; // store the user's input

    } while (replay== 'y' || replay == 'Y'); // loop the game

        cout << "Goodbye!\n" << endl; // bid farewell to the user
        return 0; // exit main 
  
} // main ends here.
