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

void showRules(){
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
	cout << "- Rock breaks Scissors" << endl;
	return;
}

bool done = false; // declare a boolean variable to control the game loop

void replay(){
    char replay; // declare a character variable to store the user's response
    cout << "Play again? (y/n)"; // prompt for (y/n) answer
    cin >> replay; // store the user's input in the variable replay

    if (replay == 'n'){ // if the user enters 'n', set done to true
        done = true; 
    }
    else if (replay == 'y'){ // if the user enters 'y', set done to false
        done = false;
    }
    else { // if the user enters anything else, prompt them to enter a valid response
        cout << "Please enter a valid response." << endl;
    }
}

int main(){

	bool done = false; // declare a boolean variable to control the game loop
	string choices[] = {"Rock","Paper","Scissors","Lizard","Spock"};
	int playerScore = 0;
	int playerChoice = 0;
	int opponentScore = 0;
	int opponentChoice = 0;



    if (done == false){ // if done is false, run the game
        cout << "\n************************************************" << endl;
	    cout << "Welcome to Rock, Paper, Scissors, Lizard, Spock." << endl;
	    cout << "************************************************" << endl;
    }
    else if (done == true){ // if done is true, end the game
        cout << "Goodbye!" << endl;
        return 0;
    }

    char *ctime(const time_t *timer); // get the current time
    srand(time(0)); // seed the random number generator
    
    int n = 0; // declare a counter variable
	while(n<=5){ // game loop (best of 5)

		
        playerScore = 0; // reset the scores when playing again

		showRules(); // show the rules
		
        
		while(n<=5){ // best out of 5 turn loop

			
            for (int i = 0; i < 5; i++){ //print the choices as a numbered list (1-5)
                cout << i+1 << ". " << choices[i] << endl;
            }
            
            cout << "Please enter your choice: " << endl; // prompt the user for their choice
            cin >> playerChoice; // store the user's input in the variable "playerChoice"
			cout << "You chose: " << playerChoice << endl; // visually confirm the choice

            opponentChoice = rand() % 5; // generate a random response for the opponent (0-4)
			cout << "Your opponent chose: " << opponentChoice << endl; // reveal the opponent's choice

            // rock beats scissors
            // rock beats lizard

            // paper beats rock
            // paper beats spock

            // sicssors beats paper
            // scissors beats lizard

            // lizard beats spock
            // lizard beats paper

            // spoock beats rock
            // spoock beats scissors

            switch(playerChoice){ // evaluate the player's choice
                case 1: // rock
                    if (opponentChoice == 2 || opponentChoice == 3){ // scissors or lizard
                        cout << "************" << endl;
                        cout << "You win!" << endl;
                        cout << "************" << endl;
                        playerScore++;
                    }
                    else if (opponentChoice == 1){ // rock
                        cout << "************" << endl;
                        cout << "Tie!" << endl;
                        cout << "************" << endl;
                    }
                    else {// paper or spock
                        cout << "************" << endl;
                        cout << "You lose!" << endl; 
                        cout << "************" << endl;
                        opponentScore++;
                    }
                    break;
                case 2: // paper
                    if (opponentChoice == 3 || opponentChoice == 4){ // lizard or spock
                        cout << "************" << endl;
                        cout << "You win!" << endl;
                        cout << "************" << endl;
                        playerScore++;
                    }
                    else if (opponentChoice == 2){ // paper
                        cout << "************" << endl;
                        cout << "Tie!" << endl;
                        cout << "************" << endl;
                    }
                    else { // rock or scissors
                        cout << "************" << endl;
                        cout << "You lose!" << endl; 
                        cout << "************" << endl;
                        opponentScore++;
                    }
                    break;
                case 3: // scissors
                    if (opponentChoice == 0 || opponentChoice == 4){ // rock or spock
                        cout << "************" << endl;
                        cout << "You win!" << endl;
                        cout << "************" << endl;
                        playerScore++;
                    }
                    else if (opponentChoice == 3){ // scissors
                        cout << "************" << endl;
                        cout << "Tie!" << endl;
                        cout << "************" << endl;
                    }
                    else { // paper or lizard
                        cout << "************" << endl;
                        cout << "You lose!" << endl; 
                        cout << "************" << endl;
                        opponentScore++;
                    }
                    break;
                case 4: // lizard
                    if (opponentChoice == 0 || opponentChoice == 2){ // rock or scissors
                        cout << "************" << endl;
                        cout << "You win!" << endl;
                        cout << "************" << endl;
                        playerScore++;
                    }
                    else if (opponentChoice == 4){ // lizard
                        cout << "************" << endl;
                        cout << "Tie!" << endl;
                        cout << "************" << endl;
                    }
                    else { // paper or spock
                        cout << "************" << endl;
                        cout << "You lose!" << endl; 
                        cout << "************" << endl;
                        opponentScore++;
                    }
                    break;
                case 5: // spock
                    if (opponentChoice == 1 || opponentChoice == 3){ // paper or lizard
                        cout << "************" << endl;
                        cout << "You win!" << endl;
                        cout << "************" << endl;
                        playerScore++;
                    }
                    else if (opponentChoice == 5){ // spock
                        cout << "************" << endl;
                        cout << "Tie!" << endl;
                        cout << "************" << endl;
                    }
                    else { // rock or scissors
                        cout << "************" << endl;
                        cout << "You lose!" << endl; 
                        cout << "************" << endl;
                        opponentScore++;
                    }
                    break;
                default: // invalid choice
                    cout << "************" << endl;
                    cout << "Invalid choice!" << endl;
                    cout << "************" << endl;
                    break;
            }

			cout << "Player score: " << playerScore << endl;
			cout << "Opponent score: " << opponentScore << endl;

		} // best of 5 game ends here.

		
		if (playerScore > opponentScore){ // Print out who won
            
            cout << "====================" << endl;
            cout << "You win!" << endl;
            cout << "====================" << endl;
        }
        else if (playerScore < opponentScore){
            cout << "====================" << endl;
            cout << "You lose!" << endl;
            ccout << "====================" << endl;
        }
        else {
            cout << "====================" << endl;
            cout << "Tie!" << endl;
            cout << "====================" << endl;
        }

	} // replay loop ends here.

	return 0;
}