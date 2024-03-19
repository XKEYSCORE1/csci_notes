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

void shuffleDeck( Deck d ){
    srand(time(0));
    for (int i = 0; i < 52; i++) {
        int j = i + rand() % (52 - i);
        swap(d.card[i], d.card[j]);
    }
    return;
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


// TODO: replace the cards suits in the deck with the symbols
// METHOD 1 - use a function that swaps out the value of the card suit.
Card suitReplace(Card c){
	if (c.suit == "S"){
		c.suit = "â™ ";
	}else if (c.suit == "H"){
		c.suit = "â™¥";
	}
	else if (c.suit == "C"){
		c.suit = "â™£";
	}
	else if (c.suit == "D"){
		c.suit = "â™¦";
	}else{
		std::cout << "ERROR: invalid suit value in card: " << c.value << c.suit << endl;
	}
	return c;
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
	// for (const auto& [key, value] : cardMap){
	// 	cout << key << ":\t" << value << " points\n";
	// }

	printHand(h);

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


void printDeck(Deck d){
    for(int i=0; i<52; i++){
        std::cout << d.card[i].value << d.card[i].suit;
        if(i!=51){ std::cout << ',';
         };
    }
 }



void replaceCardSuits(Deck deck){
    for (int i = 0; i < 52; i++){
        deck.card[i] = suitReplace(deck.card[i]);
                    // cout << deck.card[i].value << deck.card[i].suit << endl;     
    }
}
//TODO: (optional) replace card letters with symbols
	// Method 2: don't do method 1 above, make the deck in create_deck using the suit symbols
	// Example:
	// string suitSymbols[] = {"â™£", "â™¦", "â™¥", "â™ "};
	// for (auto n : suitSymbols){ // the initializer may be an array
	// 	cout << n << endl;
	// }
	// cout << endl;

    // cout << "\nDEBUG: current card: " << deck.currentCard << endl;


// === MAIN === 
int main(){
// There are zero cards when you declare a new Hand.
// hand dealerHand, player1Hand;
    Hand dealerHand = createHand("Dealer");
    Hand player1Hand = createHand("Player 1");
// player2Hand, player3Hand;
    Deck deck = create_deck();
// iterate through the deck and replace the card letters with symbols
    for (int i = 0; i < 52; i++){
        deck.card[i] = suitReplace(deck.card[i]);
                 // cout << deck.card[i].value << deck.card[i].suit << endl;
    }
// swap the cards in the deck around to randomize the order.
    shuffleDeck(deck);
        // DEBUG:
        // cout << "Shuffled deck: ", printDeck() << endl;
        //  cout << "first item: " << deck[0] << endl;
// TODO: Deal cards out from the deck to make hand
    // The player gets dealt the first card.
    player1Hand = dealCard(player1Hand, deck);
    // increment the position (how many cards deep in the deck)
    deck.currentCard++;
	// cout << "DEBUG: back in main() from dealCard." << endl;
	// printHand(player1Hand);
	// cout << "DEBUG: Current number of cards dealt (deck list index): " << deck.currentCard << endl;

	dealerHand = dealCard(dealerHand, deck);
	// increment the position (how many cards deep in the deck)
	deck.currentCard++;
	// cout << "DEBUG: back in main() from dealCard." << endl;
	// printHand(dealerHand);
	// cout << "DEBUG: Current number of cards dealt (deck list index): " << deck.currentCard << endl;

	// The player gets dealt the first card.
	player1Hand = dealCard(player1Hand, deck);
	// increment the position (how many cards deep in the deck)
	deck.currentCard++;
	// cout << "DEBUG: back in main() from dealCard." << endl;
	// printHand(player1Hand);
	// cout << "DEBUG: Current number of cards dealt (deck list index): " << deck.currentCard << endl;

	dealerHand = dealCard(dealerHand, deck);
	// increment the position (how many cards deep in the deck)
	deck.currentCard++;
	// cout << "DEBUG: back in main() from dealCard." << endl;
	// printHand(dealerHand);
	// cout << "DEBUG: Current number of cards dealt (deck list index): " << deck.currentCard << endl;

	// TODO: print out hand of all players
    // print out the player's hand:
	printHand(player1Hand);
	// print out the dealer's hand, hiding the hole card:
	cout << "dealer cards: ?? " << dealerHand.card[1].value + dealerHand.card[1].suit << endl;
	// subsequent printing will require a function in the case that the dealer hits (on a hand < 16).	

	cout << "DEBUG In main(): " << player1Hand.owner << "'s hand value: " << eval(player1Hand) << endl;
	cout << "DEBUG In main(): " << dealerHand.owner << "'s hand value: " << eval(dealerHand) << endl;


	// TODO: Check for a Blackjack condition.  The game ends if any player (or the dealer) was dealt Blackjack.
	// If the Dealer has Blackjack and a Player doesn't, the game is over and every Player loses.
	// It's a PUSH (tie) if the Player has one as well, nobody "wins"
	// TODO: Prompt each player to Hit or Stand and deal out cards *appropriately*
	// -- if they have 21, don't let them hit.
	// TODO: The turn ends for each player if they bust (score > 21), and have no Aces (that they can elect to be a 1).
	// TODO: The dealer takes the last turn, and has an opportunity to hit repeatedly (on a hand <= 16, but must stand on a 17 or above).
	// TODO: Keep track of Player and Dealer wins, losses and ties
	// TODO: Put the entire game in a play again (game state loop) -- each hand is one round of a larger game. 


	return 0;
};