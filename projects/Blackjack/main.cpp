#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iterator> 
#include <map>
#include <utility>

using namespace std;


// struct to represent a card
struct Card{
	string value;
	string suit;
};

// struct to represent a deck of cards
struct Deck {
    int currentCard = 0;
    Card card[52];

    // Constructor to create and shuffle a deck
    Deck() 
    {
        const char suits[] = {'C', 'D', 'H', 'S'};
        const string cardValues[] = {"A", "K", "Q", "J", "T", "9", "8", "7", "6", "5", "4", "3", "2"};
        int count = 0;
        Card current;

        // Create the deck and replace suits
        for (int n = 0; n < 4; n++) 
        {
            for (int m = 0; m < 13; m++) 
            {
                current.suit = string(1, suits[n]);
                current.value = cardValues[m];
                card[count] = suitReplace(current);
                count++;
            }
        }

        // Shuffle the deck
        shuffleDeck();
    }

    // Function to shuffle the deck
    void shuffleDeck() 
    {

        for (int i = 0; i < 52; i++) 
        {
            int j = i + rand() % (52 - i);
            swap(card[i], card[j]);
        }

    }

    // Function to draw a card from the deck
    Card drawCard() 
    {
        if (currentCard < 52) 
        {
            return card[currentCard++];
        } else
        {
            return Card{"", ""};
        }
    }

    // Function to replace suit symbols in a card
    static Card suitReplace(Card c) 
    {
        if (c.suit == "S") c.suit = "♠";
        else if (c.suit == "H") c.suit = "♥";
        else if (c.suit == "C") c.suit = "♣";
        else if (c.suit == "D") c.suit = "♦";
        return c;
    }

    // Function to print the deck
    void printDeck() 
    {
        for (int i = 0; i < 52; i++) 
        {
            cout << card[i].value << card[i].suit;
            if (i != 51) cout << ", ";
        }
        cout << endl;
    }
};


// struct to represent a hand of cards
struct Hand 
{
    string owner;
    int numCards = 0;
    // max possible hand is A,A,A,A,2,2,2,2,3,3,3
    Card card[12];

    // function to create a hand
    static Hand createHand(string owner)
    {
        Hand h;
        h.owner = owner;
        return h;
    }

    // function to add a card to a hand
    void addCard(Card c)
    {
        // h.numCards is the last element in the Hand's Card array.
        // Don't attempt to add past element 11 (0-11 is 12 items).
        if (numCards < 11) 
        {
            card[numCards] = c;
            // the hand is one larger.
            numCards++;
            cout << "DEBUG: " << owner << "'s hand size: " << numCards << endl;
        }
    }

    // function to print a card
    string printCard(const Card& card) const 
    {
        return card.value + card.suit;
    }

};



// void printDealer( Hand h ){
//     string s;
//     std::cout << "\n" << h.owner << "'s hand:";
//     for(int i=0; i < h.numCards; i++){
//         if(i==0){
//             s += " ??";
//         }else{
//             s += ( " " + printCard(h.card[i]) );
//         }
//     }
// }



// Function to deal a card to a player
Hand& dealCard(Hand& h, Deck& d) 
{ 
    // Attempt to draw a card from the deck
    Card drawnCard = d.drawCard();

    // Check if the drawn card is valid (not empty)
    if (drawnCard.value != "" && drawnCard.suit != "") 
    {
        // DEBUG: Print the card being dealt
        cout << "Dealing card: " << drawnCard.value << drawnCard.suit << endl;
        h.addCard(drawnCard);
    } else 
    {
        // Handle the empty deck scenario
        cout << "Error: Deck is empty, no more cards to deal." << endl;
    }
    
    return h;

}




// Function to evaluate the score of a hand
int eval(Hand h, bool isDealer) 
{

    int score = 0;  // Score of the hand
    int aceCount = 0; // Count of Aces in the hand

    map<string, int> cardMap =  // Map of card values to their point values
    { 
        {"K", 10},
        {"Q", 10},
        {"J", 10},
        {"T", 10},
        {"9", 9},
        {"8", 8},
        {"7", 7},
        {"6", 6},
        {"5", 5},
        {"4", 4},
        {"3", 3},
        {"2", 2}
    };


    // Calculate initial score and count Aces
    for (int n = 0; n < h.numCards; n++) 
    {
                    // DEBUG: Print the card being evaluated and the current score
        cout << "Evaluating card: " << h.card[n].value << h.card[n].suit << " Current Score: " << score << endl;
        if (h.card[n].value == "A") 
        {
            aceCount++;
            score += 11;
        } else 
        {
            auto search = cardMap.find(h.card[n].value);
            if (search != cardMap.end()) 
            {
                score += search->second;
            } else 
            {
                std::cout << "ERROR: Invalid card value\n";
            }
        }
    }


    // Adjust for Aces for both dealer and player
    while (aceCount > 0 && score > 21) 
    {
        score -= 10; // Change an Ace from 11 to 1
        aceCount--;
    }

    // DEBUG: Print the final score
    cout << "Final score: " << score << endl;

    return score;
}



            
	// DEBUG: Print the cardVal map -- comment this out in your program 
    // cout << "\nThe map is:\n"; 
    // cout << "KEY\tVALUE\n";
    //     for (const auto& [key, value] : cardMap){
    //          cout << key << ":\t" << value << " points\n";
     //   }

//	printHand(h);


// function to print the deck
void printDeck(Deck d)
{
    for(int i=0; i<52; i++)
    {
        std::cout << d.card[i].value << d.card[i].suit;
        if(i!=51)
        { std::cout << ',';};
    }
 }



// Function to create hands for the dealer and players
void createHands(Hand& dealerHand, Hand& player1Hand) 
{
    dealerHand = Hand::createHand("Dealer");
    player1Hand = Hand::createHand("Player 1");
}



// Function to deal cards to the players and the dealer
void dealCards(Hand& dealerHand, Hand& player1Hand, Deck& deck) 
{
    player1Hand = dealCard(player1Hand, deck);
    dealerHand = dealCard(dealerHand, deck);
    player1Hand = dealCard(player1Hand, deck);
    dealerHand = dealCard(dealerHand, deck);
}




void printHand(Hand h)
{
    std::string s;
    std::cout << "\n" << h.owner << "'s hand:";
    for(int i=0; i < h.numCards; i++)
    {
        s += ( " " +h.printCard(h.card[i]) );
    }
    std::cout << s << endl;

}



void printDealerHand(const Hand& dealerHand, bool revealHoleCard)
{
    if (revealHoleCard == true) 
    {
        std::cout << "dealer cards: " << dealerHand.card[0].value + dealerHand.card[0].suit << " " << dealerHand.card[1].value + dealerHand.card[1].suit << endl;
    } else 
    {
        std::cout << "dealer cards: ?? " << dealerHand.card[1].value + dealerHand.card[1].suit << endl;
    }

}


// Function to print the hands of all players, and display the dealer's hole card if the revealHoleCard parameter is true
void printAllHands(const Hand& dealerHand, const Hand& player1Hand, bool revealHoleCard) 
{
    printHand(player1Hand);
    printDealerHand(dealerHand, revealHoleCard);
    
    // TODO: Additional printing logic for other players 
}



 // Check for Blackjack condition
void checkBlackjack(const Hand& dealerHand, const Hand& player1Hand) 
{
    int dealerScore = eval(dealerHand, true);
    int player1Score = eval(player1Hand, false);

    if (dealerScore == 21 && player1Score == 21) 
    {
        std::cout << "Push! Both the dealer and player 1 have Blackjack." << endl;
        return;
    }
    else if (dealerScore == 21) 
    {
        std::cout << "The dealer has Blackjack. Player 1 loses." << endl;
        return;
    }
    else if (player1Score == 21) 
    {
        std::cout << "Player 1 has Blackjack. Player 1 wins." << endl;
        
        return;
    }
}



// Function to prompt the player to hit or stand
bool hitOrStand(Hand& playerHand, Deck& deck) 
{

    std::cout << "Would you like to hit or stand? ";
    
    std::string hitOrStand_answer;
    std::cin >> hitOrStand_answer;

    if (hitOrStand_answer == "hit") 
    {
        playerHand = dealCard(playerHand, deck);
        return true;  // Player chooses to hit

    } else if (hitOrStand_answer == "stand") 
    {
        std::cout << "You chose to stand." << endl;
        return false;  // Player chooses to stand

    } else 
    {
        std::cout << "Invalid input. Please enter hit or stand." << endl;
        return true;  // Continue the turn by default

    }
}



// Function to determine the winner of the round
int determineWinner(const Hand& dealerHand, const Hand& player1Hand) 
{
    int dealerScore = eval(dealerHand, true);
    int player1Score = eval(player1Hand, false);

    if (dealerScore > 21) 
    {
        std::cout << "The dealer busts. Player 1 wins." << endl;
        return 1;
    }
    else if (player1Score > 21) 
    {
        std::cout << "Player 1 busts. The dealer wins." << endl;
        return -1;
    }
    else if (dealerScore > player1Score) 
    {
        std::cout << "The dealer wins." << endl;
        return -1;
    }
    else if (player1Score > dealerScore) 
    {
        std::cout << "Player 1 wins." << endl;
        return 1;
    }
    else 
    {
        std::cout << "Push! It's a tie." << endl;
        return 0;
    }

}



// Function to play a round of Blackjack
void playGame(Hand& dealerHand, Hand& player1Hand, Deck& deck) 
{
    deck.shuffleDeck();
    bool revealHoleCard = false;
    dealCards(dealerHand, player1Hand, deck);

    // Print initial hands
    printAllHands(dealerHand, player1Hand, false);
}



//* ======= MAIN ======= *//



int main() 
{

    srand(time(0));

    // Game state loop
    bool playAgain = true;

    Hand dealerHand = Hand::createHand("Dealer");
    Hand player1Hand = Hand::createHand("Player 1");

    Deck deck;

    do {
        playGame(dealerHand, player1Hand, deck); // call game logic and play a round of Blackjack
        checkBlackjack(dealerHand, player1Hand); // check for initial Blackjack condition

        bool playerTurn = true; // flag to indicate if it is the player's turn
        
        while(playerTurn && eval(player1Hand, false) < 21) // if it is the player's turn and their hand is less than 21, 
        {
            playerTurn = hitOrStand(player1Hand, deck); // prompt player to hit or stand, deal cards, and increment the deck
            printAllHands(dealerHand, player1Hand, false); // print the hands of all players
        
        }

        while(eval(dealerHand, true) < 17)  // if less than 17, deal cards to the dealer and increment the deck
        {
            dealerHand = dealCard(dealerHand, deck);
            deck.currentCard++;
        }

        printAllHands(dealerHand, player1Hand, true);
        determineWinner(dealerHand, player1Hand);


        std::cout << "Game over." << endl;

        // Ask if the player wants to play again
        std::cout << "Do you want to play again? (yes/no) ";
        std::string playAgainChoice;
        std::cin >> playAgainChoice;
        
        if(playAgainChoice == "no" || playAgainChoice == "n" || playAgainChoice == "No" || playAgainChoice == "NO" || playAgainChoice == "N") 
        {
            playAgain = false;
        }
        else if (playAgainChoice == "yes" || playAgainChoice == "y" || playAgainChoice == "Yes" || playAgainChoice == "YES" || playAgainChoice == "Y") 
        {
            playAgain = true;
        }
        else 
        {
            cout << "Invalid input. Please enter yes or no." << endl;
            playAgain = false;
        }
    } while (playAgain);

    return 0;
}




	// TODO: print out hand of all players
	// TODO: Check for a Blackjack condition.  The game ends if any player (or the dealer) was dealt Blackjack.
	// If the Dealer has Blackjack and a Player doesn't, the game is over and every Player loses.
	// It's a PUSH (tie) if the Player has one as well, nobody "wins"
	// TODO: Prompt each player to Hit or Stand and deal out cards *appropriately*
	// -- if they have 21, don't let them hit.
	// TODO: The turn ends for each player if they bust (score > 21), and have no Aces (that they can elect to be a 1).
	// TODO: The dealer takes the last turn, and has an opportunity to hit repeatedly (on a hand <= 16, but must stand on a 17 or above).
	// TODO: Keep track of Player and Dealer wins, losses and ties
	// TODO: Put the entire game in a play again (game state loop) -- each hand is one round of a larger game. 
