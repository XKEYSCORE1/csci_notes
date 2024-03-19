#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iterator> 
#include <map>
#include <utility>

using namespace std;


struct Card{
	string value;
	string suit;
};

string printCard(Card c){
	return (c.value + c.suit);
}


struct Deck{
	int currentCard = 0;
	Card card[52];
};

void shuffleDeck( Deck& d ){
    srand(time(0));
    for (int i = 0; i < 52; i++) {
        int j = i + rand() % (52 - i);
        swap(d.card[i], d.card[j]);
    }
}

Deck create_deck(){
	const int NUMCARDS = 52;
	const int CARDSIZE = 2;
	Deck deck;
	char suits[]= {'C','D','H','S'};
	char cardValues[]= {'A','K','Q','J','T','9','8','7','6','5','4','3','2'};
	int count = 0;
	Card current;
	// for each suit
	for(int n=0; n<4; n++){
		// for each of the unique card calues
		for(int m=0; m<13; m++){
			current.suit = suits[n];
			current.value = cardValues[m];
			deck.card[count] = current;
			count++;
		}
	}
	if(count==52){
		std::cout << "deck size OK..." << endl;
	}else{
		std::cout << "deck size: " << count << ", ERROR...exiting." << endl;
		exit(-1);
	}
	return deck;	
}

// function to replace the card suits in the deck
Card suitReplace(Card c){
    if (c.suit == "S"){
        c.suit = "♠";
    }
    else if (c.suit == "H"){
        c.suit = "♥";
    }
    else if (c.suit == "C"){
        c.suit = "♣";
    }
    else if (c.suit == "D"){
        c.suit = "♦";
    }
    else if (c.suit == "♠"){
        // do nothing
    }
    else if (c.suit == "♥"){
        // do nothing
    }
    else if (c.suit == "♣"){
        // do nothing
    }
    else if (c.suit == "♦"){
        // do nothing
    }
    else {
        std::cout << "ERROR: invalid suit value in card: " << c.value << c.suit << endl;
    }
    return c;
}

// function to replace the card suits in the deck
void replaceCardSuits(Deck& deck){
    for (int i = 0; i < 52; i++){
        deck.card[i] = suitReplace(deck.card[i]);
        cout << deck.card[i].value << deck.card[i].suit << endl;     
    }
}

struct Hand{
	string owner;
	int numCards = 0;
	// max possible hand is A,A,A,A,2,2,2,2,3,3,3
	Card card[12];
};


Hand createHand(string owner){
	Hand h;
	h.owner = owner;
	return h;
}


void printHand( Hand h ){
	string s;
	std::cout << "\n" << h.owner << "'s hand:";
	for(int i=0; i < h.numCards; i++){
		s += ( " " + printCard(h.card[i]) );
	}
	std::cout << s << endl;
}

void printDealer( Hand h ){
    string s;
    std::cout << "\n" << h.owner << "'s hand:";
    for(int i=0; i < h.numCards; i++){
        if(i==0){
            s += " ??";
        }else{
            s += ( " " + printCard(h.card[i]) );
        }
    }
}

Hand addCard(Hand h, Card c){
	// h.numCards is the last element in the Hand's Card array.
	// Don't attempt to add past element 11 (0-11 is 12 items).
	if(h.numCards < 11){
		h.card[h.numCards] = c;
		// the hand is one larger.
		h.numCards++;
		// cout << "DEBUG: " << h.owner << "'s hand size: " << h.numCards << endl;
	}
	return h;
}


Hand dealCard(Hand h, Deck d){
	int i = d.currentCard;
	// cout << h.owner << "'s hand pre-deal: ";
	// printHand(h);
	// cout << "DEBUG: About to deal: " << d.card[i].value << d.card[i].suit << endl;
	h = addCard(h, d.card[d.currentCard]);

	// cout << "DEBUG: Current hand:";
	// printHand(h);
	// cout << "DEBUG: Next deck card: " << d.card[i+1].value << d.card[i+1].suit << endl;
	return h;
}




// TODO: Evaluate the hand, including Aces being worth 11 or 1 (if necessary)
// You will have to modify this code to get variable aces to work.
int eval( Hand h ){
	int score = 0;

	map <string, int> cardMap = {
		{"A",11},
		{"K",10},
		{"Q",10},
		{"J",10},
		{"T",10},
		{"9",9},
		{"8",8},
		{"7",7},
		{"6",6},
		{"5",5},
		{"4",4},
		{"3",3},
		{"2",2}
	};

    if (h.numCards == 2){
        if (h.card[0].value == "A" || h.card[1].value == "A"){ // if the hand has an Ace
            // if the hand has two Aces -> Blackjack!
            if (h.card[0].value == "A" && h.card[1].value == "A"){ 
                std::cout << "Blackjack!" << endl;
                return 21;
            }

            else if (h.card[0].value == "A" || h.card[1].value == "A"){ // if the hand has one Ace
            // if the hand has an Ace and a 10 or face card -> Blackjack! 
                if (h.card[0].value == "K" || h.card[1].value == "K" || h.card[0].value == "Q" || h.card[1].value == "Q" || h.card[0].value == "J" || h.card[1].value == "J" || h.card[0].value == "T" || h.card[1].value == "T"){
                    std::cout << "Blackjack!" << endl;
                    return 21;
                }
            // if the hand has an Ace, but no 10 or face card 
                //  -> ask the player if they want the Ace to be worth 1 or 11
                else{
                    std::cout << "You have an Ace! Would you like it to be worth 1 or 11?" << endl;
                    int aceValue;
                    cin >> aceValue;
                    if (aceValue == 1){
                        cardMap["A"] = 1;
                    }
                    else if (aceValue == 11){
                        cardMap["A"] = 11;
                    }
                    // input validation
                    else{
                        std::cout << "Invalid input. Please enter 1 or 11." << endl;
                    }
                }
            }
        }
    }

            
	// DEBUG: Print the cardVal map -- comment this out in your program 
    // cout << "\nThe map is:\n"; 
    // cout << "KEY\tVALUE\n";
    //     for (const auto& [key, value] : cardMap){
    //          cout << key << ":\t" << value << " points\n";
     //   }

//	printHand(h);

	// for each card in the hand, add the score:
	for(int n=0; n < h.numCards; n++){
		// cout << "DEBUG: Looking for " << h.card[n].value << endl;
		auto search = cardMap.find(h.card[n].value);
		if (search != cardMap.end()) {
			// cout << "Found key: " << search->first << ", value: " << search->second << '\n';
			score += static_cast<int>(search->second);
		} else {
			std::cout << "ERROR: key not found\n"; // this should never happen
		}
	}
	// cout << "Total hand score is: " << score << endl;
	return score;
};

// function to print the deck
void printDeck(Deck d){
    for(int i=0; i<52; i++){
        std::cout << d.card[i].value << d.card[i].suit;
        if(i!=51){ std::cout << ',';
         };
    }
 }



// Function to create hands for the dealer and players
void createHands(Hand& dealerHand, Hand& player1Hand) {
    dealerHand = createHand("Dealer");
    player1Hand = createHand("Player 1");
}

// Function to create and shuffle the deck
Deck createAndShuffleDeck() {
    Deck deck = create_deck();
    replaceCardSuits(deck); // replace the card suits in the deck before shuffling

    shuffleDeck(deck);
    return deck;
}

// Function to deal cards to the players and the dealer
void dealCards(Hand& dealerHand, Hand& player1Hand, Deck& deck) {
    player1Hand = dealCard(player1Hand, deck);
    deck.currentCard++;
    dealerHand = dealCard(dealerHand, deck);
    deck.currentCard++;
    player1Hand = dealCard(player1Hand, deck);
    deck.currentCard++;
    dealerHand = dealCard(dealerHand, deck);
    deck.currentCard++;
}

// Function to print the hands of all players
void printAllHands(const Hand& dealerHand, const Hand& player1Hand) {
    printHand(player1Hand);
    cout << "dealer cards: ?? " << dealerHand.card[1].value + dealerHand.card[1].suit << endl;
    // Additional printing logic for other players if needed
}


// === MAIN === 
int main() {
    // Game state loop
    bool playAgain = true;
    do {
        Deck deck;
        deck = createAndShuffleDeck();
        Hand dealerHand;
        Hand player1Hand;
        createHands(dealerHand, player1Hand);
        dealCards(dealerHand, player1Hand, deck);

        // Print initial hands
        printAllHands(dealerHand, player1Hand);

        // Check for Blackjack condition
        if (eval(player1Hand) == 21 && eval(dealerHand) != 21) {
            cout << "Player 1 wins with Blackjack!" << endl;
        } else if (eval(dealerHand) == 21 && eval(player1Hand) != 21) {
            cout << "Dealer wins with Blackjack!" << endl;
        } else if (eval(dealerHand) == 21 && eval(player1Hand) == 21) {
            cout << "It's a tie with Blackjack!" << endl;
        } else {
            // Player's turn
            string choice;
            while (choice != "stand" && eval(player1Hand) < 21) {
                cout << "Player 1, do you want to hit or stand? ";
                cin >> choice;
                if (choice == "hit") {
                    player1Hand = dealCard(player1Hand, deck);
                    deck.currentCard++;
                    printAllHands(dealerHand, player1Hand);
                }
            }

            // Dealer's turn
            while (eval(dealerHand) <= 16) {
                dealerHand = dealCard(dealerHand, deck);
                deck.currentCard++;
            }

            // Print final hands
            printAllHands(dealerHand, player1Hand);

            // Evaluate hands and determine the winner
            int player1Score = eval(player1Hand);
            int dealerScore = eval(dealerHand);
            if (player1Score > 21) {
                cout << "Player 1 busts! Dealer wins." << endl;
            } else if (dealerScore > 21) {
                cout << "Dealer busts! Player 1 wins." << endl;
            } else if (player1Score > dealerScore) {
                cout << "Player 1 wins!" << endl;
            } else if (player1Score < dealerScore) {
                cout << "Dealer wins!" << endl;
            } else {
                cout << "It's a tie!" << endl;
            }
        }

        // Ask if the player wants to play again
        cout << "Do you want to play again? (yes/no) ";
        string playAgainChoice;
        cin >> playAgainChoice;
        if (playAgainChoice == "no" || playAgainChoice == "n"|| playAgainChoice == "No" || playAgainChoice == "NO" || playAgainChoice == "N") {
            playAgain = false;
        }
        else if (playAgainChoice == "yes" || playAgainChoice == "y"|| playAgainChoice == "Yes" || playAgainChoice == "YES" || playAgainChoice == "Y") {
            playAgain = true;
        }
        else {
            cout << "Invalid input. Please enter yes or no." << endl;
            playAgain = false;
        }
    } while (playAgain==true);

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
