#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iterator>
#include <map>
#include <utility>
#include <vector>
#include<chrono>
#include<thread>

using namespace std;

//* ============== CONSTANTS ============== *//

const int MAX_PLAYER_COUNT = 3; // Maximum number of players in the game
const int MAX_HAND_SIZE = 12;	// Maximum number of cards in a hand

const int SUIT_COUNT = 4;			// Number of suits in a standard deck
const int RANK_COUNT = 13;			// Number of ranks in a standard deck
const int DECK_SIZE = 52;			// Number of cards in a standard deck
const int NUMBER_OF_DECKS = 6;		// Number of decks in the shoe
const int STARTING_CARDS = 2;		// Number of cards dealt at the start of the game
const int RESHUFFLE_THRESHOLD = 75; // Number of cards left in the deck to trigger a reshuffle

const int BLACKJACK = 21;		// Blackjack score threshold
const int FACE_CARD_VALUE = 10; // Value of face cards (K, Q, J)
const int ACE_HIGH = 11;		// Value of an Ace when high
const int ACE_LOW = 1;			// Value of an Ace when low

const int ACE_THRESHOLD = 21; // Threshold for changing Ace value
const int DEALER_STAND = 17;  // Dealer stand threshold

//* ============== STRUCTS ============== *//

/**
 * @brief a single playing card.
 *
 *@details This struct encapsulates a card's suit and rank, essential components in card games.
 * Used throughout the game to represent individual cards in hands and decks.
 */
struct Card
{
	string rank; // rank of the card (A, K, Q, J, T, 9, 8, 7, 6, 5, 4, 3, 2)
	string suit; // suit of the card (C, D, H, S)
};

/**
 * @brief Houses a collection of playing decks.
 *
 * @details Manages operations for initializing and shuffling decks, drawing cards for gameplay,
 * and displaying the shoe's current state. Represents the shoe used in Blackjack.
 */
struct Shoe
{

	int currentCard = 0;					 // index of the current card being drawn
	Card cards[DECK_SIZE * NUMBER_OF_DECKS]; // Define the array for 6 standard decks of 52 cards (312 cards - standard casino shoe)

	Shoe();									 // Constructor to initialize the shoe with 6 standard decks of 52 cards (312 cards)
	void initializeDecks();					 // Initialize the 6 decks of cards in the shoe
	void shuffleDecks();					 // Shuffle the  6 decks to randomize the card order
	Card drawCardFromShoe();				 // Draw the top card from the deck housed in the shoe
	void printShoe() const;					 // Print the deck of cards in the shoe
	static Card convertCardToSymbol(Card c); // Convert suit characters to their corresponding symbols
};

/**
 * @brief Represents a hand of cards for a player or the dealer.
 *
 *@details Manages a collection of 'Card' objects to represent a hand in Blackjack. Provides
 * functionality to add cards, calculate the hand's score, and display the hand's content.
 */
struct Hand
{
	string owner;			  // name of the hand's owner (e.g., player name or "Dealer")
	int numCards = 0;		  // number of cards in the hand
	Card card[MAX_HAND_SIZE]; // max possible hand is A,A,A,A,2,2,2,2,3,3,3

	Hand();												   // Default constructor for an empty hand
	Hand(const string &ownerName);						   // Constructor to initialize a hand with a specified owner (parameters: ownerName)
	void printHand() const;								   // Print the cards in the hand
	void addCardToHand(Card c);							   // Add a card to the hand
	string printCardInHand(const Card &card) const;		   // Print a single card (Parameters: card reference);
	int adjustScoreForAces(int score, int aceCount) const; // Adjust the score for Aces
	int evaluateHandScore() const;						   // Calculate the score of the hand
};

/**
 * @brief Manages game statistics.
 *
 * @details Maintains and displays the wins, losses, and ties for players and the dealer, providing a
 * comprehensive view of the game's progress.
 */
struct GameStats
{
	vector<int> playerWins;																// number of wins for each player
	vector<int>playerLosses; 															// number of losses for each player
	vector<int> playerTies;																// number of ties for each player
	vector<int> playerBlackjacks;														// number of Blackjacks for each player
	vector<int> playerBusts;															// number of busts for each player
	int dealerWins = 0;																	// number of wins for the dealer
	int dealerBlackjacks = 0;															// number of Blackjacks for the dealer
	int totalRounds = 1;																// total number of rounds played (initialized to 1)

	GameStats(int numPlayers) : 														// Constructor to initialize the game statistics (Parameters: numPlayers)
		playerWins(numPlayers, 0), playerLosses(numPlayers, 0),
		playerTies(numPlayers, 0), playerBusts(numPlayers, 0), 
		playerBlackjacks(numPlayers, 0) {} 

	void printStats(int numPlayers) const;												// Displays current game statistics
};

//* ============== FUNCTION DECLARATIONS ============== *//

/**
 * @brief Draws a card from the shoe and adds it to a player's hand.
 *
 * @details Ensures the drawn card is valid and updates the hand accordingly.
 * Used during the initial dealing of cards and when a player opts to 'hit'.
 *
 * @param hand Reference to the hand which will receive the card.
 * @param deck Reference to the shoe housing the deck from which the card will be drawn.
 * @return Updated hand after adding the drawn card.
 */
Hand drawFromShoe(Hand &hand, Shoe &deck);

/**
 * @brief Prepares the hands for each player and the dealer at the start of the game.
 *
 * @details Creates a separate hand for each player and an additional one for the dealer.
 * Essential for setting up the game and distributing initial cards.
 *
 * @param numPlayers The number of players participating in the game.
 * @return Vector containing the initialized hands for all players and the dealer.
 */
vector<Hand> initializeGameHands(int numPlayers);

/**
 * @brief Distributes cards to all players and the dealer at the beginning of each round.
 *
 * @details Deals two cards to each hand, which is an important part of the game setup phase.
 * Uses the drawFromShoe function to ensure fair and random distribution of cards.
 *
 * @param hands Vector of hands representing each player and the dealer.
 * @param deck The deck housed in the shoe from which the cards will be dealt.
 */
void dealCards(vector<Hand> &hands, Shoe &deck);

/**
 * @brief prints all hands, including the dealer's with an option to reveal the hole card.
 *
 * @details Displays the cards in each player's hand and the dealer's hand, with the option to reveal the dealer's hole card.
 * Used to show the current state of the game to the players and update them on the progress.
 *
 * @param hands Vector of 'Hand' objects representing each player's and the dealer's hand.
 * @param revealDealerHoleCard Flag to determine if the dealer's hole card should be revealed.
 */
void printHands(const vector<Hand> &hands, bool revealDealerHoleCard);

/**
 * @brief Checks for Blackjack (score of 21) for each player and the dealer.
 *
 * @details Evaluates each hand at the start of the round for a Blackjack. 
 *          Separately handles player and dealer Blackjacks.
 *          Updates game statistics and prints relevant game outcomes.
 *          Ends the round early if a dealer Blackjack is found.
 *
 * @param hands Vector of 'Hand' objects representing each player's and the dealer's hand.
 * @param stats Reference to the GameStats object for updating statistics.
 * @param numPlayers Number of players in the game.
 * @return True if any Blackjack is found; False otherwise.
 */
bool checkBlackjack(const vector<Hand> &hands, GameStats &stats, int numPlayers);

/**
 * @brief Interactively prompts a player to hit (draw a card) or stand (end their turn).
 *
 *@details Displays the player's hand, the dealer's up card, and the player's current score.
 * Accepts the player's decision and updates the hand accordingly.
 *
 * @param playerHand Reference to the player's hand making the decision.
 * @param dealerHand Reference to the dealer's hand, used to display dealer's up card.
 * @param deck Reference to the deck housed in the shoe for drawing cards if the player hits.
 * @return True if player hits, False if player stands.
 */
bool hitOrStand(Hand &playerHand, const Hand &dealerHand, Shoe &deck);

/**
 * @brief Evaluates and determines the winner of the round.
 *
 * @details Compares the scores of each player's hand with the dealer's hand.
 *          Updates game statistics based on the outcomes: win, loss, or tie.
 *          Handles the cases of player or dealer busts.
 *          Requires the number of players to accurately update statistics.
 *
 * @param hands Vector containing 'Hand' objects for all players and the dealer.
 * @param stats Reference to the GameStats object for updating statistics.
 * @param numPlayers Number of players in the game, used for statistics.
 * @return Always returns 0 as a signal of normal function completion.
 */
int determineWinner(vector<Hand> &hands, GameStats &stats, int numPlayers);

/**
 * @brief Collects all cards from the hands back to the shoe for the next round.
 * 
 * @details Resets the number of cards in each hand, shuffles the deck, and resets the current card index.
 * 		Used to prepare for the next round and ensure a fair game.
 *
 * @param hands Vector containing 'Hand' objects for all players and the dealer.
 * @param deck Reference to the deck housed in the shoe for collecting the cards.
 */
void collectCards(vector<Hand> &hands, Shoe &deck);

/**
 * @brief Manages a single round of Blackjack.
 *
 * @details Facilitates the entire process of a round including dealing cards, checking for Blackjack,
 *          player decisions (hit or stand), and finally determining the round's winner.
 *          Updates game statistics and handles the flow of the game based on Blackjack rules.
 *
 * @param deck Reference to the shoe containing the decks used in the game.
 * @param numPlayers Number of players in the game.
 * @param stats Reference to the GameStats object for tracking round statistics.
 */
void playRound(Shoe &deck, int numPlayers, GameStats &stats);

int getPlayerCount();

//* ============== MAIN ============== *//

/**
 * @brief Main function - Entry point of the Blackjack game.
 *
 * @details Initializes the game with a specified number of players,
 *          manages the play loop, and handles player interactions.
 *          Coordinates the overall flow of the game, including replay options.
 */
int main()
{
	// seed the random number generator, set the replay flag, and initialize the deck
	srand(time(0));
	bool playAgain = true; // Replay flag
	Shoe deck;			   // Fill the shoe with 6 decks of cards

	// Welcome message and prompt for number of players
	int numPlayers = getPlayerCount();

	/**
	 * @brief Create a GameStats object to track the game statistics.
	 *
	 * @details The GameStats object stores the number of wins, losses, and ties for each player and the dealer.
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


/*========DEFINE SHOE STRUCT FUNCTIONS========*/

// Constructs a shoe to house a standard deck of 52 playing cards
// Initializes the deck with all suits and ranks, then shuffles it
void Shoe::initializeDecks()
{
	const char suits[] = {'C', 'D', 'H', 'S'};
	const string cardRanks[] = {"A", "K", "Q", "J", "T", "9", "8", "7", "6", "5", "4", "3", "2"};
	int count = 0;

	for (int deck = 0; deck < NUMBER_OF_DECKS; ++deck)
	{
		for (int suit = 0; suit < SUIT_COUNT; ++suit)
		{
			for (int rank = 0; rank < RANK_COUNT; ++rank)
			{
				Card current = {cardRanks[rank], string(1, suits[suit])};
				cards[count++] = convertCardToSymbol(current);
			}
		}
	}
}

// Randomizes the order of cards in the deck
// Ensures a fair and unpredictable game each time
void Shoe::shuffleDecks()
{
	for (int i = 0; i < (DECK_SIZE * NUMBER_OF_DECKS); ++i)
	{
		int randomIndex = rand() % (DECK_SIZE * NUMBER_OF_DECKS);
		swap(cards[i], cards[randomIndex]);
	}
	std::cout << "\nShuffling the deck...\n" << endl;
}

Shoe::Shoe()
{
	initializeDecks();
	shuffleDecks();
}

// Draws the top card from the deck and updates the current card index
// shuffles at the reshuffle point
// handles case where the deck may be empty
// Returns the drawn card
Card Shoe::drawCardFromShoe()
{
	if (currentCard >= DECK_SIZE * NUMBER_OF_DECKS - RESHUFFLE_THRESHOLD)
	{ // Reshuffle point ->  return the next card
		shuffleDecks();
		currentCard = 0;
	}

	if (currentCard < (DECK_SIZE * NUMBER_OF_DECKS))
	{ // If there are still cards left to draw return the next card
		return cards[currentCard++];
	}
	else
	{ // If there are no cards left to draw, reshuffle the deck
		std::cout << "ERROR: No more cards to deal, reshuffling." << endl;
		shuffleDecks();
		currentCard = 0;
		return cards[currentCard++];
	}
}

// Prints the entire deck of cards in its current order
//  for debugging or visualizing the deck state
void Shoe::printShoe() const
{
	for (int i = 0; i < (DECK_SIZE * NUMBER_OF_DECKS); i++)
	{
		cout << cards[i].rank << cards[i].suit;
		if (i != (DECK_SIZE * NUMBER_OF_DECKS) - 1)
			cout << ", ";
	}
	std::cout << endl;
}

// Converts suit characters to their corresponding symbols
Card Shoe::convertCardToSymbol(Card c)
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
	std::cout << "\n"
			  << owner << "'s hand:";
	for (int i = 0; i < numCards; ++i)
	{
		std::cout << " " << card[i].rank << card[i].suit;
	}
	std::cout << " (Score: " << evaluateHandScore() << ")\n";
}

// Adds a card to the hand if there is room
// Prevents adding more than the maximum number of cards
void Hand::addCardToHand(Card c)
{
	// Don't attempt to add past element 11 (0-11 is 12 items).
	if (numCards < MAX_HAND_SIZE - 1	 // adjust for 0-based index
		&& c.rank != "" && c.suit != "") // Ensure the card is valid
	{
		card[numCards] = c; // Add the card to the hand
		// the hand is one larger.
		numCards++;
	}
}

// Returns a string representation of a card (rank and suit)
string Hand::printCardInHand(const Card &card) const
{
	return card.rank + card.suit;
}

// Adjusts the score of the hand considering the Aces
int Hand::adjustScoreForAces(int score, int aceCount) const
{
	while (score > ACE_THRESHOLD && aceCount > 0)
	{
		score -= ACE_HIGH - ACE_LOW; // Convert an Ace from 11 to 1
		aceCount--;
	}
	return score;
}

// Calculates and returns the score of the hand
// Accounts for the variable value of Aces based on the total score
int Hand::evaluateHandScore() const
{
	int score = 0;
	int aceCount = 0;

/// @brief Map to store the values of each card rank
	map<string, int> cardValues = 
	{
		{"A", ACE_HIGH}, {"K", FACE_CARD_VALUE}, {"Q", FACE_CARD_VALUE}, {"J", FACE_CARD_VALUE}, {"T", 10}, {"9", 9}, {"8", 8}, {"7", 7}, {"6", 6}, {"5", 5}, {"4", 4}, {"3", 3}, {"2", 2}
	};

	for (const auto &card : this->card)
	{
		score += cardValues[card.rank];
		if (card.rank == "A")
		{
			aceCount++;
		}
	}

	return adjustScoreForAces(score, aceCount);
}

/* ========DEFINE GAMESTATS STRUCT VARIABLES AND FUNCTIONS======= */

// Prints the current game statistics including wins, losses, and ties
// Provides a summary of the game's progress
void GameStats::printStats(int numPlayers) const {
    std::cout << fixed << setprecision(2);
// calculate win, loss, and tie percentages
    for (int i = 0; i < numPlayers; ++i) {
        double winPercent = totalRounds > 0 ? (static_cast<double>(playerWins[i]) / totalRounds) * 100 : 0;
        double lossPercent = totalRounds > 0 ? (static_cast<double>(playerLosses[i]) / totalRounds) * 100 : 0;
        double tiePercent = totalRounds > 0 ? (static_cast<double>(playerTies[i]) / totalRounds) * 100 : 0;
// print player statistics
        std::cout << "Player " << (i + 1) << " - Wins: " << playerWins[i] << " (" << winPercent << "%), "
                  << "Losses: " << playerLosses[i] << " (" << lossPercent << "%), "
                  << "Ties: " << playerTies[i] << " (" << tiePercent << "%), "
                  << "Blackjacks: " << playerBlackjacks[i] << ", "
                  << "Busts: " << playerBusts[i] << std::endl;
    }
// calculate dealer win percentage
    double dealerWinPercent = totalRounds > 0 ? (static_cast<double>(dealerWins) / totalRounds) * 100 : 0;
    std::cout << "Dealer - Wins: " << dealerWins << " (" << dealerWinPercent << "%), "
              << "Blackjacks: " << dealerBlackjacks << std::endl;
}

/* ========DEFINE GAME FUNCTIONS======= */

// Prompts the user to enter the number of players
// Returns the number of players in the game
int getPlayerCount()
{
	int numPlayers;
	while (true)
	{
		std::cout << "Welcome to Blackjack! How many players are there? (1-" << MAX_PLAYER_COUNT << "): ";
		std::cin >> numPlayers;

		if (numPlayers >= 1 && numPlayers <= MAX_PLAYER_COUNT)
			return numPlayers; // Valid input, return the number

		std::cout << "Invalid number of players. Please enter a number between 1 and " << MAX_PLAYER_COUNT << "." << std::endl;
	}
}

// Draws a card from the deck and adds it to the given hand
// Handles cases where the deck may be empty
Hand drawFromShoe(Hand &hand, Shoe &deck)
{
	// Draw a card from the deck
	Card drawnCard = deck.drawCardFromShoe();

	// Add the card to the hand if it is not empty
	if (drawnCard.rank != "" && drawnCard.suit != "")
	{
		hand.addCardToHand(drawnCard);
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
void dealCards(vector<Hand> &hands, Shoe &deck)
{
	// Deal two rounds of cards
	for (int round = 0; round < STARTING_CARDS; round++)
	{
		// Deal one card to each player
		for (Hand &hand : hands)
		{
			drawFromShoe(hand, deck); // Deal one card to each hand
			std::cout << hand.owner << " was dealt a card." << "(Cards in hand: " << (hands.size()/2) << ")" << endl;
		}
	}
}

// Prints all hands, including the dealer's with an option to reveal the hole card
// Displays the current state of the game to the players
void printHands(const vector<Hand> &hands, bool revealDealerHoleCard)
{
	for (const auto &hand : hands)
	{
		if (hand.owner == "Dealer")
		{
			if (revealDealerHoleCard)
			{
				// Print dealer's entire hand with the hole card revealed
				hand.printHand();
			}
			else
			{
				// Print dealer's hand with the hole card hidden
				std::cout << "Dealer's hand: ?? " << hand.card[1].rank + hand.card[1].suit;
				std::cout << " (Score: XX )" << std::endl;
			}
		}
		else
		{
			// Print player's hand and evaluate the score
			hand.printHand();
			std::cout << " (Score: " << hand.evaluateHandScore() << ")" << std::endl;
		}
	}
}

// Checks for Blackjack in any hand and handles special cases
// Returns true if any hand (player or dealer) has Blackjack
bool checkBlackjack(const vector<Hand> &hands, GameStats &stats, int numPlayers) {
    bool dealerBlackjack = hands.back().evaluateHandScore() == BLACKJACK;
    bool anyBlackjack = dealerBlackjack;

    for (size_t i = 0; i < hands.size() - 1; ++i) {
        int playerScore = hands[i].evaluateHandScore();
        if (playerScore == BLACKJACK) {
            anyBlackjack = true; // set flag if any player has Blackjack
            if (!dealerBlackjack) {
                stats.playerWins[i]++;
                std::cout << hands[i].owner << " has Blackjack and wins!" << std::endl;
            } else {
                stats.playerTies[i]++;
                std::cout << "Push! Both " << hands[i].owner << " and dealer have Blackjack." << endl;
            }
        } else if (dealerBlackjack) {
            stats.dealerWins++;
            std::cout << hands[i].owner << " loses to dealer's Blackjack." << endl;
        }
    }
    if (dealerBlackjack) {
        stats.printStats(numPlayers);
        return true; // return early if dealer has Blackjack
    }
    return anyBlackjack;
}


// Interactively asks a player to hit or stand
// Returns the player's decision as a string ("hit" or "stand")
string getUserDecision(const Hand &playerHand)
{
	string decision; // string to store the player's decision
	do
	{
		std::cout << playerHand.owner << ": Would you like to hit or stand? ";
		std::cin >> decision;
		if (decision == "hit" || decision == "stand")
			break;
		std::cout << "Invalid input. Please enter 'hit' or 'stand'." << std::endl;
	} while (true);
	return decision;
}

// Interactively asks a player to hit or stand
// Updates the hand based on the player's decision
bool hitOrStand(Hand &playerHand, const Hand &dealerHand, Shoe &deck)
{
	while (true)
	{
		playerHand.printHand();
		std::cout << "Dealer's up card: " << dealerHand.card[1].rank + dealerHand.card[1].suit << std::endl;
		std::cout << playerHand.owner << ": Would you like to hit or stand? ";

		string decision;
		std::cin >> decision;

		if (decision == "hit")
		{
			playerHand.addCardToHand(deck.drawCardFromShoe());
			if (playerHand.evaluateHandScore() > BLACKJACK)
			{
				playerHand.printHand();
				std::cout << "You busted! Better luck next time!" << endl;
				return false; // Player busts
			}
		}
		else if (decision == "stand")
		{
			return false; // Player chooses to stand
		}
		else
		{
			std::cout << "Invalid input. Please enter 'hit' or 'stand'." << std::endl;
		}
	}
}

/* =========== GAME LOGIC ===========*/

// Compares scores and determines the winner of the round
// Updates the game statistics based on the outcomes
int determineWinner(vector<Hand> &hands, GameStats &stats, int numPlayers) {
    auto &dealerHand = hands.back();
    int dealerScore = dealerHand.evaluateHandScore();
    bool dealerBusted = dealerScore > BLACKJACK;

    // Check if dealer has blackjack
    if (dealerScore == BLACKJACK && dealerHand.numCards == 2) {
        stats.dealerBlackjacks++;
    }

    for (size_t i = 0; i < hands.size() - 1; ++i) {
        int playerScore = hands[i].evaluateHandScore();
        bool playerBusted = playerScore > BLACKJACK;

        if (playerBusted) {
            stats.playerLosses[i]++;
            stats.playerBusts[i]++;
            std::cout << hands[i].owner << " busted!" << endl;
        } else if (playerScore == BLACKJACK && hands[i].numCards == 2) {
            stats.playerBlackjacks[i]++;
        } else if (dealerBusted || playerScore > dealerScore) {
            stats.playerWins[i]++;
            std::cout << hands[i].owner << " wins!" << endl;
        } else if (playerScore == dealerScore) {
            stats.playerTies[i]++;
            std::cout << "Push! It's a tie for " << hands[i].owner << "." << endl;
        } else {
            stats.playerLosses[i]++;
            std::cout << hands[i].owner << " loses." << endl;
        }
    }

    if (dealerBusted) {
        for (auto &player : stats.playerWins) {
            player++;
        }
    }

    stats.totalRounds++;
    stats.printStats(numPlayers);
    return 0;
}

void collectCards(vector<Hand> &hands, Shoe &deck)
{
	std::cout << "Collecting cards back to the shoe..." << std::endl;

	for (Hand &hand : hands)
	{
		hand.numCards = 0; // reset the number of cards in the hand
	}
	deck.currentCard = 0; // reset the current card index
	deck.shuffleDecks();	// shuffle the deck
}

// Manages the flow of a single round of Blackjack
// Calls functions for dealing cards, player decisions, and evaluating outcomes
void playRound(Shoe &deck, int numPlayers, GameStats &stats)
{
	vector<Hand> hands = initializeGameHands(numPlayers);
	dealCards(hands, deck);

	if (!checkBlackjack(hands, stats, numPlayers))
	{
		for (auto &hand : hands)
		{
			if (hand.owner != "Dealer")
			{
				while (hitOrStand(hand, hands.back(), deck));
			}
		}

		auto &dealerHand = hands.back();
		while (dealerHand.evaluateHandScore() < DEALER_STAND)
		{
			dealerHand.addCardToHand(deck.drawCardFromShoe());
		}

		printHands(hands, true);
		determineWinner(hands, stats, numPlayers);
		collectCards(hands, deck);
	}
}
