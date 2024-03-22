#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iterator> 
#include <map>
#include <utility>

using namespace std;


// struct to represent a card
struct Card
{
	string value;
	string suit;
};

// struct to represent a deck of cards
struct Deck 
{
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

};


// struct to represent a hand of cards
struct Hand 
{
    string owner;
    int numCards = 0;
    // max possible hand is A,A,A,A,2,2,2,2,3,3,3
    Card card[12];

// function to print a hand
    void toString()
    {
        std::string s;
        std::cout << "\n" << owner << "'s hand:";
        for(int i=0; i < numCards; i++)
        {
            s += ( " " +printCard(card[i]) );
        }
    std::cout << s << endl;
    }

    // function to create a hand
    static Hand createHand(string owner)
    {
        Hand h;
        h.owner = owner;
        return h;
    };


    // function to add a card to a hand
    void addCard(Card c)
    {
        // Don't attempt to add past element 11 (0-11 is 12 items).
        if (numCards < 11) 
        {
            card[numCards] = c;
            // the hand is one larger.
            numCards++;

            // DEBUG: Print the hand size
            cout << "DEBUG: " << owner << "'s hand size: " << numCards << endl;
        }
    }

    // function to print a card
    string printCard(const Card& card) const 
    {
        return card.value + card.suit;
    }


    // function to evaluate the score of a hand
    int evaluateScore(bool isDealer) const 
    {
        int score = 0;
        int aceCount = 0;

    // map to store the value of each card
        map<string, int> cardMap = 
        {
            {"K", 10}, {"Q", 10}, {"J", 10}, {"T", 10},
            {"9", 9}, {"8", 8}, {"7", 7}, {"6", 6},
            {"5", 5}, {"4", 4}, {"3", 3}, {"2", 2}
        };

    // for loop to iterate through the cards in the hand
        for (int i = 0; i < numCards; ++i) 
        {   // if the card is an Ace, add 11 to the score and increment the aceCount
            if (card[i].value == "A") 
            {
                aceCount++;
                score += 11;
                        //add the value of the card to the score
            } else {
                score += cardMap[card[i].value];
            }
        }
    // if the score is over 21, convert an Ace from 11 to 1
        while (aceCount > 0 && score > 21) 
        {
            score -= 10;  // Convert an Ace from 11 to 1
            aceCount--;
        }

        return score;
    }

};

void drawFromDeck(Hand& h, Deck& deck) 
{
    Card drawnCard = deck.drawCard(); 
    
    if (drawnCard.value != "" && drawnCard.suit != "") 
    {
        h.addCard(drawnCard);
    } else 
    {
        std::cout << "ERROR: No more cards to deal." << endl;
    }
}

Hand dealCard(Hand& hand, Deck& deck) 
    {
        drawFromDeck(hand, deck);
        return hand;
    }

            
	// DEBUG: Print the cardVal map -- comment this out in your program 
    // cout << "\nThe map is:\n"; 
    // cout << "KEY\tVALUE\n";
    //     for (const auto& [key, value] : cardMap){
    //          cout << key << ":\t" << value << " points\n";
     //   }

    //	toString(h);

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
    Hand h = player1Hand;
    h.toString();
    printDealerHand(dealerHand, revealHoleCard);

}



 // Check for Blackjack condition
void checkBlackjack(const Hand& dealerHand, const Hand& player1Hand) 
{
    int dealerScore = dealerHand.evaluateScore(true);
    int player1Score = player1Hand.evaluateScore(false);

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
    int dealerScore = dealerHand.evaluateScore(true);
    int player1Score = player1Hand.evaluateScore(false);

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
void playRound(Deck& deck, Hand& dealerHand, Hand& player1Hand) 
{
    deck.shuffleDeck();  // Shuffle the deck for a new round
    dealerHand = Hand::createHand("Dealer");
    player1Hand = Hand::createHand("Player 1");
    dealCards(dealerHand, player1Hand, deck);  // Initial card dealing

    printAllHands(dealerHand, player1Hand, false); // Print initial hands
    checkBlackjack(dealerHand, player1Hand); // Check for Blackjack

    // Player's turn
    bool playerTurn = true;
    while (playerTurn && player1Hand.evaluateScore(false) < 21) 
    {
        playerTurn = hitOrStand(player1Hand, deck); // Hit or Stand
        player1Hand.toString();
    }

    // DEBUG: Print the player's hand and score
    cout << "DEBUG: Player 1's Score: " << player1Hand.evaluateScore(false) << endl;


    // Dealer's turn
    while (dealerHand.evaluateScore(true) < 17) 
    {
        dealerHand = dealCard(dealerHand, deck);
    }
    printDealerHand(dealerHand, true); // Reveal dealer's hand

    // DEBUG: Print the dealer's hand and score
    cout << "DEBUG: Dealer's Score: " << dealerHand.evaluateScore(true) << endl;
    dealerHand.toString();
    

    int winner = determineWinner(dealerHand, player1Hand);

    if (winner == 1) cout << "Jackpot! Looks like luck is on your side!" << endl;
    else if (winner == -1) cout << "The house wins this round, but don't fold yet!!" << endl;
    else cout << "Both sides holding strong!" << endl;
}



//* ======= MAIN ======= *//



int main() 
{

    srand(time(0));
    bool playAgain = true;
    Deck deck;

   while(playAgain)
   {
        Hand dealerHand, player1Hand;
        playRound(deck, dealerHand, player1Hand);

        //replay option
        std::cout << "Would you like to play again? (yes/no) ";
        std::string playAgain_answer;
        std::cin >> playAgain_answer;
        playAgain = (playAgain_answer == "yes" || playAgain_answer == "y");
   }

    return 0;

} // end main

	// TODO: Keep track of Player and Dealer wins, losses and ties
    // TODO: Additional  logic for other players 
