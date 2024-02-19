#include <iostream>
using namespace std;

/**
 * The main function is the entry point of the program.
 * It implements a simple rock-paper-scissors game between two players.
 * The players make their choices and the program determines the winner based on the rules of the game.
 * The scores of the players are displayed after each round, and the game continues until one player reaches a score of 3.
 * Finally, the program announces the winner.
 *
 * @return 0 indicating successful execution of the program.
 */

int main() {

  int playerChoice = 0;
  int opponentChoice = 0;
  int player1Score, player2Score;
  player1Score = player2Score = 0;

  do {
    cout << "\n######### Rock, Scissors, Paper ##########";
    cout << "\n1. Rock\n2. Paper\n3. Scissors\n";
    cout << "\nPlayer 1, please enter your choice (1-3):";
    cin >> playerChoice;
    cout << "Player 2, please enter your choice (1-3):";
    cin >> opponentChoice;
    playerChoice--;
    opponentChoice--;
    cout << endl;
    // player1 chose rock:
    if (playerChoice == 0) {
      // opponent chose...
      if (opponentChoice == 0) { // rock.
        cout << "Rock and Rock, it's a tie!\n";
      } else if (opponentChoice == 1) { // paper.
        cout << "Paper covers Rock!\n";
        player2Score++;
      } else if (opponentChoice == 2) { // scissors.
        cout << "Rock smashes scissors!\n";
        player1Score++;
        // our PRNG is FUBAR
      } else {
        cout << "ERROR: something bad happened.\n";
        exit(-1);
      }
      // player1 chose Paper:
    } else if (playerChoice == 1) {
      // opponent chose...
      if (opponentChoice == 0) { // rock.
        cout << "Paper covers Rock!\n";
        player1Score++;
      } else if (opponentChoice == 1) { // paper.
        cout << "Paper and Paper, it's a tie!\n";
      } else if (opponentChoice == 2) { // scissors.
        cout << "Scissors cut Paper!\n";
        player2Score++;
        // our PRNG is FUBAR
      } else {
        cout << "ERROR: something bad happened.\n";
        exit(-1);
      }
      // player1 chose Scissors:
    } else if (playerChoice == 2) {
      // opponent chose...
      if (opponentChoice == 0) { // rock.
        cout << "Rock smashes scissors!\n";
        player2Score++;
      } else if (opponentChoice == 1) { // paper.
        cout << "Scissors cut Paper!\n";
        player1Score++;
      } else if (opponentChoice == 2) { // scissors.
        cout << "Scissors and Scissors, it's a tie!\n";
        // our PRNG is FUBAR
      } else {
        cout << "ERROR: something bad happened.\n";
        exit(-1);
      }
    } else {
      cout << "something bad happened.\n";
      exit(-1);
    }
    cout << "**************************\n";
    cout << "Player 1: " << player1Score << endl;
    cout << "Player 2: " << player2Score << endl;
    cout << "**************************\n";
  } while (player1Score <= 2 and player2Score <= 2);

  if (player1Score > player2Score) {
    cout << "Player 1 wins!\n";
  } else {
    cout << "Player 2 wins!\n";
  }
  return 0;
}