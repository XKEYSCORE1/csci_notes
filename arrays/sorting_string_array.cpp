#include <iomanip>  // output formatting
#include <iostream> // basic i/o
#include <string>   // string handling
using namespace std;

#define WORD_LIMIT 10

bool isSorted(string wordList[], int itemCount) {
	bool sorted = true;
	for (int i = 0; i < itemCount; i++) {
		// if the next item exists
		if (i + 1 < itemCount) {
			if (wordList[i] > wordList[i + 1]) {
				return false;
			}
		}
	}
	return sorted;
}

void printWordList(string wordList[]) {
	for (unsigned count = 0; count < WORD_LIMIT; count++) {
		cout << count + 1 << ". " << wordList[count] << endl;
	}
	return;
}

int main() {

	string wordList[WORD_LIMIT];
	string temp;
	char response;
	unsigned itemCount = 0;
	bool atEnd = false;
	int swapcount = 0;

	cout << "Welcome to the word list program.\nPlease enter a word: ";
	cin >> wordList[itemCount];
	itemCount++;
	cout << itemCount << " item in the list.\n";
	cout << "Enter another word? (y/n): ";
	cin >> response;
	while (response != 'n' && itemCount < WORD_LIMIT) {
		cout << "Please enter a word: ";
		cin >> wordList[itemCount];
		itemCount++;
		cout << itemCount << " items in the list.\n";
		if(itemCount == WORD_LIMIT){
			cout << "Sorry, you reached the word limit of " << WORD_LIMIT << endl;
			break;
		}
		cout << "Enter another word? (y/n): ";
		cin >> response;
	}
	
	// wordList[itemCount] = "dog";
	// itemCount++;
	// wordList[itemCount] = "cat";
	// itemCount++;
	// wordList[itemCount] = "Hello";
	// itemCount++;
	// wordList[itemCount] = "World";
	// itemCount++;

	// removing the last item:
	// wordList[itemCount-1] = "";
	// itemCount--;

	cout << "\nOk, here's your word list:\n";
	printWordList(wordList);
	
	int count = 0;
	while (not isSorted(wordList, itemCount)) {
		cout << "Current item: " << wordList[count] << endl;
		if (count >= itemCount-1) {
			// DEBUG:
			cout << "count: " << count << ".  I'm at the end.\n";
			printWordList(wordList);
			count = 0; //reset to index 0
		}

		if (wordList[count] > wordList[count + 1]) {
			cout << "swapping: " << wordList[count + 1] << " for " << wordList[count] << endl;
			temp = wordList[count];
			wordList[count] = wordList[count + 1];
			wordList[count + 1] = temp;
			swapcount++;
			cout << "swaps: " << swapcount << endl;
		}
		count++;
	}

	for (unsigned count = 0; count < 10; count++) {
		cout << count + 1 << ". " << wordList[count] << endl;
	}

	cout << "\nSwapped array locations " << swapcount << " times.\n";
	return 0;
}