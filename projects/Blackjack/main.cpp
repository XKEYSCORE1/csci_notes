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
            if (i != 51)
                cout << ", ";
        }
        std::cout << endl;
    }

    // Function to draw a card from the deck
    Card drawCard()
    {
        if (currentCard < 52)
        {
            return card[currentCard++];
        }
        else
        {
            return Card{"", ""};
        }
    }

    // Function to replace suit symbols in a card
    static Card suitReplace(Card c)
    {
        if (c.suit == "S")
            c.suit = "♠";
        else if (c.suit == "H")
            c.suit = "♥";
        else if (c.suit == "C")
            c.suit = "♣";
        else if (c.suit == "D")
            c.suit = "♦";
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
    Hand(const string &ownerName) : owner(ownerName) {}

    // function to print a hand
    void toString() const
    {
        std::string s;
        std::cout << "\n"
                  << owner << "'s hand:";
        for (int i = 0; i < numCards; i++)
        {
            s += (" " + printCard(card[i]));
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
            // std::cout << "DEBUG: " << owner << "'s hand size: " << numCards << endl;
        }
    }

    // function to print a card
    string printCard(const Card &card) const
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
                {"K", 10}, {"Q", 10}, {"J", 10}, {"T", 10}, {"9", 9}, {"8", 8}, {"7", 7}, {"6", 6}, {"5", 5}, {"4", 4}, {"3", 3}, {"2", 2}};

        // for loop to iterate through the cards in the hand
        for (int i = 0; i < numCards; ++i)
        { // if the card is an Ace, add 11 to the score and increment the aceCount
            if (card[i].value == "A")
            {
                aceCount++;
                score += 11;
                // add the value of the card to the score
            }
            else
            {
                score += cardMap[card[i].value];
            }
        }
        // if the score is over 21, convert an Ace from 11 to 1
        while (aceCount > 0 && score > 21)
        {
            score -= 10; // Convert an Ace from 11 to 1
            aceCount--;
        }

        return score;
    }
};

// struct to represent the game stats
struct GameStats
{
    // Initialize the stats
    int playerWins = 0;
    int dealerWins = 0;
    int ties = 0;
    // Function to print the stats
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
        }
        else
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

// Global variable to store the game stats
GameStats stats;

// Function to draw a card from the deck and add it to a hand
Hand drawFromDeck(Hand &hand, Deck &deck)
{
    // Draw a card from the deck
    Card drawnCard = deck.drawCard();

    // Add the card to the hand if it is not empty
    if (drawnCard.value != "" && drawnCard.suit != "")
    {
        hand.addCard(drawnCard);
    }
    else
    {
        std::cout << "ERROR: No more cards to deal." << endl;
    }
    return hand;
}

// Function to create hands for the dealer and players
vector<Hand> createHands(int numPlayers)
{

    vector<Hand> hands;

    // Create hands for all players
    for (int i = 0; i < numPlayers; i++)
    {
        hands.push_back(Hand("Player " + to_string(i + 1)));
    }

    // Create a hand for the dealer
    hands.push_back(Hand("Dealer"));
    // Return the vector of hands created
    return hands;
}

// Function to deal cards to the players and the dealer
void dealCards(vector<Hand> &hands, Deck &deck)
{
    // Deal two rounds of cards
    for (int round = 0; round < 2; round++)
    {
        // Deal one card to each player
        for (Hand &hand : hands)
        {
            drawFromDeck(hand, deck); // Deal one card to each hand
        }
    }
}

// function to print the dealer's hand
void printDealerHand(const Hand &dealerHand, bool revealHoleCard)
{
    // Print the dealer's hand with the hole card revealed based on the revealHoleCard parameter
    if (revealHoleCard == true)
    {
        std::cout << "Dealer cards: " << dealerHand.card[0].value + dealerHand.card[0].suit << " " << dealerHand.card[1].value + dealerHand.card[1].suit << endl;
    }
    else
    {
        std::cout << "Dealer cards: ?? " << dealerHand.card[1].value + dealerHand.card[1].suit << endl;
    }
}

// Function to print the hands of all players, and display the dealer's hole card if the revealHoleCard parameter is true
void printAllHands(const vector<Hand> &hands, bool revealHoleCard)
{
    for (size_t i = 0; i < hands.size(); ++i)
    {
        if (hands[i].owner != "Dealer")
        {
            hands[i].toString();
        }
    }

    // Print the dealer's hand last, with hole card based on revealHoleCard
    printDealerHand(hands.back(), revealHoleCard);
}

// Check for Blackjack condition for multiple players
bool checkBlackjack(const vector<Hand> &hands)
{
    bool dealerBlackjack = hands.back().evaluateScore(true) == 21;

    for (size_t i = 0; i < hands.size() - 1; ++i)
    {
        int playerScore = hands[i].evaluateScore(false);
        if (playerScore == 21 || dealerBlackjack)
        {
            // Print outcome based on who got Blackjack
            if (playerScore == 21 && dealerBlackjack)
            {
                cout << "Push! Both " << hands[i].owner << " and dealer have Blackjack." << endl;
            }
            else if (dealerBlackjack)
            {
                cout << "The dealer has Blackjack. " << hands[i].owner << " loses." << endl;
            }
            else
            {
                cout << hands[i].owner << " has Blackjack. " << hands[i].owner << " wins." << endl;
            }

            return true; // End the round immediately if Blackjack is found
        }
    }

    return false; // Continue the game if no Blackjack is found
}

// Function to prompt the player to hit or stand
bool hitOrStand(Hand &playerHand, Deck &deck)
{

    std::cout << playerHand.owner << ":  Would you like to hit or stand? ";

    std::string hitOrStand_answer;
    std::cin >> hitOrStand_answer;

    if (hitOrStand_answer == "hit")
    {
        playerHand = drawFromDeck(playerHand, deck);
        return true; // Player chooses to hit
    }
    else if (hitOrStand_answer == "stand")
    {
        std::cout << "You chose to stand." << endl;
        return false; // Player chooses to stand
    }
    else
    {
        std::cout << "Invalid input. Please enter hit or stand." << endl;
        return true; // Continue the turn by default
    }
}

// Function to determine the winner of the round
int determineWinner(vector<Hand> &hands, GameStats &stats)
{
    auto &dealerHand = hands.back();
    int dealerScore = dealerHand.evaluateScore(true);
    bool dealerBusted = dealerScore > 21;

    for (size_t i = 0; i < hands.size() - 1; ++i)
    {
        int playerScore = hands[i].evaluateScore(false);
        // Rest of the scoring logic goes here...
        bool playerBusted = playerScore > 21;

        if (playerBusted)
        {
            cout << hands[i].owner << " busts. The dealer wins." << endl;
            stats.dealerWins++;
        }
        else if (dealerBusted || playerScore > dealerScore)
        {
            cout << hands[i].owner << " wins." << endl;
            stats.playerWins++;
        }
        else if (playerScore == dealerScore)
        {
            cout << "Push! It's a tie for " << hands[i].owner << "." << endl;
            stats.ties++;
        }
        else
        {
            cout << "The dealer wins against " << hands[i].owner << "." << endl;
            stats.dealerWins++;
        }
    }
    return 0;
}

// Function to play a round of Blackjack
void playRound(Deck &deck, int numPlayers, GameStats &stats)
{
    // Create hands for all players and the dealer
    vector<Hand> hands = createHands(numPlayers);
    // Deal the initial two cards
    dealCards(hands, deck);
    // Check for Blackjack condition
    if (!checkBlackjack(hands))
    {
        // Player turns
        for (size_t i = 0; i < hands.size() - 1; ++i)
        {
            bool playerTurn = true;
            while (playerTurn && hands[i].evaluateScore(false) <= 21)
            {
                printAllHands(hands, false);
                playerTurn = hitOrStand(hands[i], deck);
            }
        }

        // Dealer's turn
        auto &dealerHand = hands.back();
        while (dealerHand.evaluateScore(true) < 17)
        {
            dealerHand.addCard(deck.drawCard());
        }
    }
    printAllHands(hands, true); // Reveal the dealer's hole card

    // Determine and print the winner
    determineWinner(hands, stats);
    stats.printStats();

    // Reveal all hands at the end of the round
}

//* ======= MAIN ======= *//

int main()
{
    srand(time(0));
    bool playAgain = true;
    Deck deck;
    // Welcome message and prompt for number of players
    cout << "Welcome to Blackjack! How many players are there? (1-3): ";
    int numPlayers;
    cin >> numPlayers;
    // Initialize game statistics
    GameStats stats;
    // Play a round
    while (playAgain)
    {
        playRound(deck, numPlayers, stats);
        // Replay option
        cout << "Would you like to play again? (yes/no) ";
        string playAgain_answer;
        cin >> playAgain_answer;
        playAgain = (playAgain_answer == "yes" || playAgain_answer == "y");
    }

    return 0;
}
