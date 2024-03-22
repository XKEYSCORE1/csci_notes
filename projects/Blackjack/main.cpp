#include <iostream>
#include <iomanip>
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
        std::cout << endl;
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

    // Default constructor
    Hand() : owner("Unknown"), numCards(0) {}

    // Constructor to create a hand with a specified owner
    Hand(const string& ownerName) : owner(ownerName) {}

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
            //std::cout << "DEBUG: " << owner << "'s hand size: " << numCards << endl;
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

// struct to represent the game stats
struct GameStats
{
    int playerWins = 0;
    int dealerWins = 0;
    int ties = 0;

    void printStats() const
    {

        // Calculate the rounds played
        int totalRounds = playerWins + dealerWins + ties;
        double playerWinPercent, houseWinPercent, tiePercent;
         // Calculate the percentage of wins for each player
        if (totalRounds > 0)
        {
            playerWinPercent = (static_cast<double>(playerWins) / totalRounds) * 100;
            houseWinPercent = (static_cast<double>(dealerWins) / totalRounds) * 100;
            tiePercent = (static_cast<double>(ties) / totalRounds) * 100;
        // handle the case where no rounds have been played
        } else 
        {
            playerWinPercent = 0;
            houseWinPercent = 0;
            tiePercent = 0;
        }
    // Print the stats
    cout << fixed << setprecision(2);
    cout << "Player 1 Wins: " << playerWins << " (" << playerWinPercent << "%)" << endl;
    cout << "Dealer Wins: " << dealerWins << " (" << houseWinPercent << "%)" << endl;
    cout << "Ties: " << ties << " (" << tiePercent << "%)" << endl;

    }
};

GameStats stats;


// Function to draw a card from the deck and add it to a hand
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

// Function to deal a card to a hand
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

pair<Hand, Hand> createHands(){
    Hand dealerHand("Dealer");
    Hand player1Hand("Player 1");
    return make_pair(dealerHand, player1Hand);
}


// Function to deal cards to the players and the dealer
void dealCards(Hand& dealerHand, Hand& player1Hand, Deck& deck) 
{
    player1Hand = dealCard(player1Hand, deck);
    dealerHand = dealCard(dealerHand, deck);
    player1Hand = dealCard(player1Hand, deck);
    dealerHand = dealCard(dealerHand, deck);
}


// function to print the dealer's hand
void printDealerHand(const Hand& dealerHand, bool revealHoleCard)
{
    if (revealHoleCard == true) 
    {
        std::cout << "Dealer cards: " << dealerHand.card[0].value + dealerHand.card[0].suit << " " << dealerHand.card[1].value + dealerHand.card[1].suit << endl;
    } else 
    {
        std::cout << "Dealer cards: ?? " << dealerHand.card[1].value + dealerHand.card[1].suit << endl;
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

// Function to print the game statistics



// Function to play a round of Blackjack
void playRound(Deck& deck) 
{
    // Initialize the game
    deck.shuffleDeck();  // Shuffle the deck for a new round

    // Create hands for the dealer and player and deal the initial cards
    auto [dealerHand, player1Hand] = createHands(); 
    dealCards(dealerHand, player1Hand, deck);

    // prin the hands and check for blackjack
    printAllHands(dealerHand, player1Hand, false); 
    checkBlackjack(dealerHand, player1Hand); 

    // Player's turn
    bool playerTurn = true;

    // loop to allow the player to hit or stand, exit if the player busts or stands
    while (playerTurn && player1Hand.evaluateScore(false) < 21) 
    {
        playerTurn = hitOrStand(player1Hand, deck); // Hit or Stand
        player1Hand.toString();
    }

    // DEBUG: Print the player's hand and score
   // std::cout << "DEBUG: Player 1's Score: " << player1Hand.evaluateScore(false) << endl;

    // Dealer's turn (hit until score is 17 or higher)
    while (dealerHand.evaluateScore(true) < 17) 
    {
        dealerHand = dealCard(dealerHand, deck);
    }
    // Reveal dealer's hand
    printDealerHand(dealerHand, true); 
    dealerHand.toString();

    // DEBUG: Print the dealer's hand and score
   // std::cout << "DEBUG: Dealer's Score: " << dealerHand.evaluateScore(true) << endl;
    
    
    // Determine the winner of the round
    int winner = determineWinner(dealerHand, player1Hand);
    // Print the winner and update the game statistics
    if (winner == 1) 
    {
        std::cout << "Jackpot! Looks like luck is on your side!" << endl;
        stats.playerWins++;

    } else if (winner == -1) 
    {
        std::cout << "The house wins this round, but don't fold yet!!" << endl;
        stats.dealerWins++;
    }
    else 
    { 
        std::cout << "Both sides holding strong!" << endl;
        stats.ties++;
    }
    stats.printStats();

}



//* ======= MAIN ======= *//
 // TODO: Additional  logic for other players 


int main() 
{

    srand(time(0));
    bool playAgain = true;
    Deck deck;

   while(playAgain)
   {
    playRound(deck);

        //replay option
        std::cout << "Would you like to play again? (yes/no) ";
        std::string playAgain_answer;
        std::cin >> playAgain_answer;
        playAgain = (playAgain_answer == "yes" || playAgain_answer == "y");
   }

    return 0;


} // end main