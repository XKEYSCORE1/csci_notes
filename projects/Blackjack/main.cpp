#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iterator>
#include <map>
#include <utility>

using namespace std;

//* ============== STRUCTS ============== *//

/**
 * Represents a single playing card.
 *
 * This struct encapsulates a card's suit and rank, essential components in card games.
 * Used throughout the game to represent individual cards in hands and decks.
 */
struct Card
{
    string rank; // rank of the card (A, K, Q, J, T, 9, 8, 7, 6, 5, 4, 3, 2)
    string suit; // suit of the card (C, D, H, S)
};

/**
 * Manages a standard 52-card playing deck.
 *
 * Supports operations for creating a deck with traditional suits and ranks, shuffling to ensure randomness,
 * drawing cards for gameplay, and printing the deck's current state for debugging or display.
 */
struct Deck
{

    int currentCard = 0; // index of the current card
    Card cards[52];      // Define the array for a standard deck of 52 cards

    Deck();                                  // Constructor to initialize the deck
    void shuffleDeck();                      // Shuffle the deck to randomize the card order
    Card drawCard();                         // Draw the top card from the deck
    void printDeck() const;                  // Print the deck of cards
    static Card convertCardToSymbol(Card c); // Convert suit characters to their corresponding symbols
};

/**
 * Represents a hand of cards for a player or the dealer in Blackjack.
 *
 * Stores a collection of 'Card' objects to represent a player's hand. Includes methods for adding cards to the hand,
 * printing the hand's contents, calculating the hand's score, and utility functions like printing a single card.
 */
struct Hand
{
    string owner;     // name of the hand's owner (e.g., player name or "Dealer")
    int numCards = 0; // number of cards in the hand
    Card card[12];    // max possible hand is A,A,A,A,2,2,2,2,3,3,3

    Hand();                                   // Default constructor for an empty hand
    Hand(const string &ownerName);            // Constructor to initialize a hand with a specified owner (parameters: ownerName)
    void printHand() const;                   // Print the cards in the hand
    void addCard(Card c);                     // Add a card to the hand
    string printCard(const Card &card) const; // Print a single card (Parameters: card reference)
    int evaluateScore(bool isDealer) const;   // Calculate the score of the hand (Parameters: isDealer)
};

/**
 * Tracks and displays the statistics of a Blackjack game session.
 *
 * Maintains the count of wins, losses, and ties for players and the dealer. Includes functionality to display these statistics
 * in a clear format, giving players insights into the game's progress and history.
 */
struct GameStats
{
    vector<int> playerWins;                                                            // number of wins for each player
    int dealerWins = 0;                                                                 // number of wins for the dealer
    vector<int> playerTies;                                                             // number of ties for each player
    GameStats(int numPlayers) : playerWins(numPlayers, 0), playerTies(numPlayers, 0) {} // Constructor to initialize the game statistics (Parameters: numPlayers)
    void printStats(int numPlayers) const;                                              // Print the game statistics
};

//* ============== FUNCTION DECLARATIONS ============== *//

/**
 * Draws a card from the deck and adds it to a player's hand.
 *
 * Ensures the drawn card is valid and updates the hand accordingly.
 * Used during the initial dealing of cards and when a player opts to 'hit'.
 *
 * @param hand Reference to the hand which will receive the card.
 * @param deck Reference to the deck from which the card will be drawn.
 * @return Updated hand after adding the drawn card.
 */
Hand drawFromDeck(Hand &hand, Deck &deck);

/**
 * Prepares the hands for each player and the dealer at the start of the game.
 *
 * Creates a separate hand for each player and an additional one for the dealer.
 * Essential for setting up the game and distributing initial cards.
 *
 * @param numPlayers The number of players participating in the game.
 * @return Vector containing the initialized hands for all players and the dealer.
 */
vector<Hand> initializeGameHands(int numPlayers);

/**
 * Distributes cards to all players and the dealer at the beginning of each round.
 *
 * Deals two cards to each hand, which is a crucial part of the game setup phase.
 * Uses the drawFromDeck function to ensure fair and random distribution of cards.
 *
 * @param hands Vector of hands representing each player and the dealer.
 * @param deck The deck from which the cards will be dealt.
 */
void dealCards(vector<Hand> &hands, Deck &deck);

/**
 * Displays the dealer's hand, with an option to hide the first card.
 *
 * Useful for revealing the dealer's hand partially or completely, depending on
 * the game phase (e.g., hiding during initial deal, revealing at the end).
 *
 * @param dealerHand The hand of the dealer.
 * @param revealHoleCard Indicates whether to show the dealer's first card.
 */
void printDealerHand(const Hand &dealerHand, bool revealHoleCard);

/**
 * Prints the hands of all players and optionally the dealer's hand with the hole card revealed or hidden.
 *
 * @param hands A vector of 'Hand' objects representing each player's and the dealer's hand.
 * @param revealHoleCard Flag to indicate whether the dealer's hole card should be visible.
 */
void printAllResults(const vector<Hand> &hands, bool revealHoleCard);

/**
 * Determines if any player or the dealer has a Blackjack (a score of 21).
 *
 * @param hands Vector of 'Hand' objects representing each player's and the dealer's hand.
 * @param stats Reference to the GameStats object for updating statistics.
 * @param numPlayers Number of players in the game.
 * @return True if Blackjack is found in any hand; False otherwise.
 */
bool checkBlackjack(const vector<Hand> &hands, GameStats &stats, int numPlayers);

/**
 * Interactively prompts a player to hit (draw a card) or stand (end their turn).
 *
 * @param playerHand Reference to the player's hand making the decision.
 * @param dealerHand Reference to the dealer's hand, used to display dealer's up card.
 * @param deck Reference to the deck for drawing cards if the player hits.
 * @return True if player hits, False if player stands.
 */
bool hitOrStand(Hand &playerHand, const Hand &dealerHand, Deck &deck);

/**
 * Evaluates the hands to determine the winner of a round.
 *
 * Compares scores between each player's hand and the dealer's to determine round outcomes,
 * updating game statistics accordingly.
 *
 * @param hands Vector containing 'Hand' objects for all players and the dealer.
 * @param stats Reference to the GameStats object for updating statistics.
 * @return Always returns 0 as a signal of normal function completion.
 */
int determineWinner(vector<Hand> &hands, GameStats &stats);

/**
 * Orchestrates a single round of Blackjack, encompassing all gameplay aspects.
 *
 * Manages the setup of hands, dealing of cards, player decisions, dealer actions, and determining the round's winner.
 *
 * @param deck Reference to the Deck object used in the game.
 * @param numPlayers Number of players in the game.
 * @param stats Reference to the GameStats object for updating round statistics.
 */
void playRound(Deck &deck, int numPlayers, GameStats &stats);

//* ============== MAIN ============== *//
/**
 * The main entry point of the Blackjack game program.
 *
 * This function initializes the game, including setting up the deck and game statistics.
 * It handles the game loop, player interactions, and determines when the game ends.
 *
 * @return Exit status of the program (0 for successful execution).
 */
int main()
{
    // seed the random number generator, set the replay flag, and initialize the deck
    srand(time(0));
    bool playAgain = true; // Replay flag
    Deck deck;             // Deck struct containing 52 cards

    // Welcome message and prompt for number of players
    std::cout << "Welcome to Blackjack! How many players are there? (1-3): ";
    int numPlayers; // integer to store the number of players playing the game
    std::cin >> numPlayers;

    /**
     * @brief Create a GameStats object to track the game statistics.
     *
     * The GameStats object stores the number of wins, losses, and ties for each player and the dealer.
     * It is used to display the game's progress and outcomes to the players.
     *
     * @param numPlayers The number of players participating in the game (1-3).
     *
     * @return GameStats
     */
    GameStats stats(numPlayers);

    while (playAgain)
    { // Play a round
        playRound(deck, numPlayers, stats);

        // Replay option
        std::cout << "Would you like to play again? (yes/no) ";
        string playAgain_answer; // string to store the user's response to the play again prompt
        std::cin >> playAgain_answer;
        playAgain = (playAgain_answer == "yes" || playAgain_answer == "y");
    }
    return 0;
}

//* ==================FUNCTION DEFINITIONS ================== *//

/*========DEFINE DECK STRUCT FUNCTIONS========*/

// Constructs a standard deck of 52 playing cards
// Initializes the deck with all suits and ranks, then shuffles it
Deck::Deck()
{
    const char suits[] = {'C', 'D', 'H', 'S'};
    const string cardRanks[] = {"A", "K", "Q", "J", "T", "9", "8", "7", "6", "5", "4", "3", "2"};
    int count = 0;
    Card current;
    // Loop 4 time to construct the 4 suites
    for (int n = 0; n < 4; n++)
    { // Loop 13  times (x4) for the 13 ranks in each of the 4 suites
        for (int m = 0; m < 13; m++)
        { // Convert the card suit and value to a string, replace the suit symbols with the unicode symbols, and add the card to the deck
            current.suit = string(1, suits[n]);
            current.rank = cardRanks[m];
            cards[count] = convertCardToSymbol(current);
            count++;
        }
    }
    shuffleDeck();
}

// Randomizes the order of cards in the deck
// Ensures a fair and unpredictable game each time
void Deck::shuffleDeck()
{
    // Shuffle the deck by swapping each card with a card at a random index
    for (int i = 0; i < 52; i++)
    {
        int j = i + rand() % (52 - i);
        swap(cards[i], cards[j]);
    }
}

// Draws the top card from the deck and updates the current card index
// Returns an empty card if the deck is depleted
Card Deck::drawCard()
{
    if (currentCard < 52)
    {
        return cards[currentCard++];
    }
    else
    {
        std::cout << "ERROR: No more cards to deal." << endl;
        return Card();
    }
}

// Prints the entire deck of cards in its current order
//  for debugging or visualizing the deck state
void Deck::printDeck() const
{
    for (int i = 0; i < 52; i++)
    {
        cout << cards[i].rank << cards[i].suit;
        if (i != 51)
            cout << ", ";
    }
    std::cout << endl;
}

// Converts suit characters to their corresponding symbols
Card Deck::convertCardToSymbol(Card c)
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

/* ========DEFINE HAND STRUCT FUNCTIONS======= */

// Creates an empty hand with an "Unknown" owner
Hand::Hand() : owner("Unknown"), numCards(0) {}

// Creates an empty hand for a specified owner
Hand::Hand(const string &ownerName) : owner(ownerName) {}

// Displays the cards in the hand of the specified player
void Hand::printHand() const
{
    std::cout << "\n" << owner << "'s hand:";

    for (int i = 0; i < numCards; i++)
    {
        // Print the card with a space before and after, and the score in parentheses (return bool isDealer if owner is dealer)
        std::cout << (" " + printCard(card[i])) << " ";
    }
    std::cout << " (Score: " << evaluateScore(owner == "Dealer") << ")" << std::endl;
}

// Adds a card to the hand if there is room
// Prevents adding more than the maximum number of cards
void Hand::addCard(Card c)
{
    // Don't attempt to add past element 11 (0-11 is 12 items).
    if (numCards < 11)
    {
        card[numCards] = c;
        // the hand is one larger.
        numCards++;
    }
}

// Returns a string representation of a card (rank and suit)
string Hand::printCard(const Card &card) const
{
    return card.rank + card.suit;
}

// Calculates and returns the score of the hand
// Accounts for the variable value of Aces based on the total score
int Hand::evaluateScore(bool isDealer) const
{
    int score = 0;
    int aceCount = 0;

    // map to store the value of each card
    map<string, int> cardMap =
        {
            {"K", 10}, {"Q", 10}, {"J", 10}, {"T", 10}, {"9", 9}, {"8", 8}, {"7", 7}, {"6", 6}, {"5", 5}, {"4", 4}, {"3", 3}, {"2", 2}};

    /* Loop through the cards in the hand and if an Ace is found, increment the aceCount and add 11 to the score.
         If the score is over 21, convert an Ace from 11 to 1.
            If no aces are found,  add the value of the cards to the hand score */

    // for loop to iterate through the cards in the hand
    for (int i = 0; i < numCards; ++i)
    { // if the card is an Ace, add 11 to the score and increment the aceCount
        if (card[i].rank == "A")
        {
            aceCount++;
            score += 11;
            // add the value of the card to the score
        }
        else
        {
            score += cardMap[card[i].rank];
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

/* ========DEFINE GAMESTATS STRUCT VARIABLES AND FUNCTIONS======= */

// Prints the current game statistics including wins, losses, and ties
// Provides a summary of the game's progress
void GameStats::printStats(int numPlayers) const
{
    cout << fixed << setprecision(2);
    for (int i = 0; i < numPlayers; ++i)
    {
        std::cout << "Player " << (i + 1) << " Wins: " << playerWins[i] << " | Ties: " << playerTies[i] << endl;
    }
    std::cout << "Dealer Wins: " << dealerWins << endl;
}

/* ========DEFINE GAME FUNCTIONS======= */

// Draws a card from the deck and adds it to the given hand
// Handles cases where the deck may be empty
Hand drawFromDeck(Hand &hand, Deck &deck)
{
    // Draw a card from the deck
    Card drawnCard = deck.drawCard();

    // Add the card to the hand if it is not empty
    if (drawnCard.rank != "" && drawnCard.suit != "")
    {
        hand.addCard(drawnCard);
    }
    else
    {
        std::cout << "ERROR: No more cards to deal." << endl;
    }
    return hand;
}

// Initializes and returns hands for each player and the dealer
// Sets up the game for the specified number of players
vector<Hand> initializeGameHands(int numPlayers)
{
    vector<Hand> hands;

    // Create hands for all players
    for (int i = 0; i < numPlayers; i++)
    {
        hands.push_back(Hand("Player " + to_string(i + 1)));
    }

    // Create a hand for the dealer
    hands.push_back(Hand("Dealer"));

    return hands;
}

// Deals two cards to each player's hand and the dealer
// Called at the beginning of each round to distribute cards
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
// Prints the dealer's hand with an option to hide the first card
// Useful for adhering to game rules
void printDealerHand(const Hand &dealerHand, bool revealHoleCard)
{
    // Print the dealer's hand with the hole card revealed based on the revealHoleCard parameter
    if (revealHoleCard == true)
    {
        std::cout << "Dealer cards: " << dealerHand.card[0].rank + dealerHand.card[0].suit << " " << dealerHand.card[1].rank + dealerHand.card[1].suit << endl;
    }
    else
    {
        std::cout << "Dealer cards: ?? " << dealerHand.card[1].rank + dealerHand.card[1].suit << endl;
    }
}
// Prints all players' hands and the dealer's hand
// calls printDealerHand to print the dealer's hand and passes the revealHoleCard parameter
void printAllResults(const vector<Hand> &hands, bool revealHoleCard)
{
    for (size_t i = 0; i < hands.size(); ++i)
    {
        if (hands[i].owner != "Dealer")
        {
            hands[i].printHand();
            hands[i].evaluateScore(false);
        }
        else
        {
            // Print the dealer's hand last, with hole card based on revealHoleCard
            hands.back().printHand();
        }
    }
}

// Checks for Blackjack in any hand and handles special cases
// Returns true if any hand (player or dealer) has Blackjack
bool checkBlackjack(const vector<Hand> &hands, GameStats &stats, int numPlayers)
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
                printAllResults(hands, true);
                std::cout << "Push! Both " << hands[i].owner << " and dealer have Blackjack." << endl;
                stats.printStats(numPlayers);
            }
            else if (dealerBlackjack)
            {
                printAllResults(hands, true);
                std::cout << "The dealer has Blackjack. " << hands[i].owner << " loses." << endl;
                stats.printStats(numPlayers);
            }
            else
            {
                printAllResults(hands, true);
                std::cout << hands[i].owner << " has Blackjack. " << hands[i].owner << " wins." << endl;
                stats.printStats(numPlayers);
            }

            return true; // End the round immediately if Blackjack is found
        }
    }
    return false; // Continue the game if no Blackjack is found
}

// Interactively asks a player to hit or stand
// Returns the player's decision as a string ("hit" or "stand")
string getUserDecision(const Hand& playerHand) {
    string decision; // string to store the player's decision
    do {
        std::cout << playerHand.owner << ": Would you like to hit or stand? ";
        std::cin >> decision;
        if (decision == "hit" || decision == "stand") break;
        std::cout << "Invalid input. Please enter 'hit' or 'stand'." << std::endl;
    } while (true);
    return decision;
}

// Interactively asks a player to hit or stand
// Updates the hand based on the player's decision
bool hitOrStand(Hand &playerHand, const Hand &dealerHand, Deck &deck) {
    playerHand.printHand();
    std::cout << "Dealer's hand: ?? " << dealerHand.card[1].rank + dealerHand.card[1].suit << std::endl;
    std::cout << "Your score is: " << playerHand.evaluateScore(false) << std::endl;

    string decision = getUserDecision(playerHand);
    if (decision == "hit") 
    {
        playerHand.addCard(deck.drawCard());
        return true; // Player chooses to hit
    } else 
    {
        std::cout << "You chose to stand." << std::endl;
        return false; // Player chooses to stand
    }
}

// Compares scores and determines the winner of the round
// Updates the game statistics based on the outcomes
int determineWinner(vector<Hand> &hands, GameStats &stats)
{
    auto &dealerHand = hands.back(); // Reference to the dealer's hand
    int dealerScore = dealerHand.evaluateScore(true);
    bool dealerBusted = dealerScore > 21;
    bool anyPlayerWins = false;

    for (size_t i = 0; i < hands.size() - 1; ++i)
    {
        int playerScore = hands[i].evaluateScore(false);
        bool playerBusted = playerScore > 21;

        if (playerBusted || (!dealerBusted && dealerScore > playerScore))
        {
            std::cout << "The dealer wins against " << hands[i].owner << "." << endl;
        }
        else if (dealerBusted || playerScore > dealerScore)
        {
            std::cout << hands[i].owner << " wins." << endl;
            stats.playerWins[i]++;
            anyPlayerWins = true;
        }
        else
        {
            std::cout << "Push! It's a tie for " << hands[i].owner << "." << endl;
            stats.playerTies[i]++;
        }
    }

    if (!anyPlayerWins && !dealerBusted)
    {
        stats.dealerWins = 1; // Dealer wins the round if no player wins and dealer doesn't bust
    }
    else
    {
        stats.dealerWins = 0; // Dealer does not win if any player wins or dealer busts
    }
    return 0;
}

// Manages the flow of a single round of Blackjack
// Calls functions for dealing cards, player decisions, and evaluating outcomes
void playRound(Deck &deck, int numPlayers, GameStats &stats)
{
    // Create hands for all players and the dealer
    vector<Hand> hands = initializeGameHands(numPlayers);

    // Deal the initial two cards
    dealCards(hands, deck);

    // Check for Blackjack condition
    if (!checkBlackjack(hands, stats, numPlayers))
    {
        // Player turns
        for (size_t i = 0; i < hands.size() - 1; ++i) // Loop through each player's turn
        {
            bool playerTurn = true; // Flag to track if the player's turn is ongoing

            while (playerTurn && hands[i].evaluateScore(false) <= 21) // Continue the turn if the player hasn't busted
            {
                playerTurn = hitOrStand(hands[i], hands.back(), deck); // Prompt the player to hit or stand
            }
        }

        // Dealer's turn

        auto &dealerHand = hands.back(); // Reference to the dealer's hand

        while (dealerHand.evaluateScore(true) < 17) // Dealer hits if the score is less than 17
        {
            dealerHand = drawFromDeck(dealerHand, deck);
        }
        // Reveal the dealer's hole card
        printAllResults(hands, true);

        // Determine and print the winner
        determineWinner(hands, stats);

        // Print the game stats
        stats.printStats(numPlayers);
    }
}

