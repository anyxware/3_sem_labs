#include <stdio.h>
#include <iostream>
#include <windows.h> /
#include <conio.h>  
//--------------------------------Color-----------------------------------///
enum ConsoleColor
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

void SetColor(int text, int background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

void SetColor(int text, ConsoleColor background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

// kerchief

#include <iostream>
#include "../prjct/deck.hpp"
#define STATIC_VARIANT

using namespace cards;

//♥♦♣♠

void printCard(const Card& card) {
	if (card.suit_char() == 'C' || card.suit_char() == 'S')
		SetColor(Black, White);
	else
		SetColor(Red, White);

	char suit;
	switch (card.suit_char()) {
	case 'C': printf("%c", 5); break;
	case 'S': printf("%c", 6); break;
	case 'D': printf("%c", 4); break;
	case 'H': printf("%c", 3); break;
	}

	std::cout << " " << card.rank_char();
	SetColor(Black, Black);
	std::cout << "|";
	SetColor(LightGray, Black);
}

void printDecks(const Deck& freeDeck, Deck homeDecks[4], Deck deskDecks[7], int visibleCard[7]) {
	

	//print free deck
	std::cout << std::endl;
	{
		int lastIndex = freeDeck.len() - 1;
		if (lastIndex != -1) {
			Card card = freeDeck[lastIndex];
			printCard(card);
		}
		std::cout << std::endl << std::endl;
	}
	//print home decks
	{
		for (int i = 0; i < 4; i++) {
			int lastIndex = homeDecks[i].len() - 1;
			if (lastIndex != -1) {
				Card card = homeDecks[i][lastIndex];
				printCard(card);
			}
		}
		std::cout << std::endl << std::endl;
	}
	//print desk decks
	{
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < deskDecks[i].len() - visibleCard[i]; j++) {
				SetColor(Black, LightBlue);
				std::cout << " |";
				SetColor(LightGray, Black);
			}
			for (int j = visibleCard[i] - 1; j >= 0; j--) {
				int lastIndex = deskDecks[i].len() - 1 - j;
				Card card = deskDecks[i][lastIndex];
				printCard(card);
			}
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
}

int deltaRank(char rank1, char rank2) {
	const char ranks[] = "A23456789TJQK";
	int index1, index2;
	for (int i = 0; i < 14; i++) {
		if (rank1 == ranks[i]) index1 = i;
		if (rank2 == ranks[i]) index2 = i;
	}

	return index2 - index1;
}

bool isEqualSuit(char suit1, char suit2) {
	return suit1 == suit2;
}

bool isDifferentColor(Card card1, Card card2) {
	return (card1.suit_char() == 'D' || card1.suit_char() == 'H')
		&& (card2.suit_char() == 'C' || card2.suit_char() == 'S')
		||
		(card1.suit_char() == 'C' || card1.suit_char() == 'S')
		&& (card2.suit_char() == 'D' || card2.suit_char() == 'H');
}

bool timeToBreak() {
	char c;
	std::cout << "[q] ";
	scanf_s("%c", &c);
	return c == 'q';
}

std::pair<int, int> findCardToMoveToHome(Deck homeDeck[4], Deck deskDeck[7], const Deck& freeDeck) {

	// find possible card in desk and free decks

	Deck curDeck;

	for(int i = 0; i < 8; i++) {

		i < 7 ? curDeck = deskDeck[i] : curDeck = freeDeck;

		int lastIndex = curDeck.len() - 1;
		if (lastIndex == -1) continue;
		Card card = curDeck[lastIndex];
		if (deltaRank(card.rank_char(), 'A') == 0) { 
			for (int j = 0; j < 4; j++) {
				if (homeDeck[j].len() == 0) return std::make_pair(i, j);
			}
		}
		else {
			for (int j = 0; j < 4; j++) {
				int lastHomeIndex = homeDeck[j].len() - 1;
				if (lastHomeIndex == -1) continue;
				if (isEqualSuit(homeDeck[j][lastHomeIndex].suit_char(), card.suit_char())
					&& deltaRank(homeDeck[j][lastHomeIndex].rank_char(), card.rank_char()) == 1) {
					return std::make_pair(i, j);
				}
			}
		}
	}

	return std::make_pair(-1, -1);
}

void moveLastCard(Deck& srcDeck, Deck& dstDeck) {
	int lastIndex = srcDeck.len() - 1;
	Card card = srcDeck[lastIndex];
	srcDeck.remove(lastIndex);
	dstDeck.add(card);
}

int mostNumberOfInvisibleCards(Deck deskDecks[7], int visibleCards[7], bool checked[7]) {
	int max = 0;
	int index = -1; // if all desk decks aren't including any cards
	for (int i = 0; i < 7; i++) {
		int numberOfInvisibleCards = deskDecks[i].len() - visibleCards[i];

		if (deskDecks[i].len() == visibleCards[i] && deskDecks[i].len() != 0 && index == -1) index = i; // if desk isn't including invisible cards, only visible visible 

		if (numberOfInvisibleCards > max && !checked[i]) {
			max = numberOfInvisibleCards;
			index = i;
		}
	}
	return index;
}

int findSetInDeck(const Deck& deck, int numOfVisisbleCards) {
	int counter = 1;
	for (int i = 0; i < numOfVisisbleCards - 1; i++) {
		int lastIndex = deck.len() - 1 - i;
		Card card1 = deck[lastIndex];
		Card card2 = deck[lastIndex - 1];
		if (deltaRank(card1.rank_char(), card2.rank_char()) == 1 && isDifferentColor(card1, card2)) {
			counter++;
		}
	}
	return counter;
}

int findSuitablePlace(const Card& topCard, Deck deskDecks[7], int srcIndex, int setSize) {
	for (int i = 0; i < 7; i++) {
		if (i == srcIndex) continue;

		int lastIndex = deskDecks[i].len() - 1;
		if(lastIndex == -1 && isEqualSuit(topCard.rank_char(), 'K')
			&& setSize != deskDecks[srcIndex].len()) {
			return i;
		}
		else if (lastIndex == -1) {
			continue;
		}

		Card card = deskDecks[i][lastIndex];

		if (isDifferentColor(topCard, card) && deltaRank(topCard.rank_char(), card.rank_char()) == 1) {
			return i;
		}
	}
	return -1;
}

int findSuitablePlaceForFreeCard(const Card& freeCard, Deck deskDecks[7]) {
	for (int i = 0; i < 7; i++) {

		int lastIndex = deskDecks[i].len() - 1;
		if (lastIndex == -1 && isEqualSuit(freeCard.rank_char(), 'K')) {
			return i;
		}
		else if (lastIndex == -1) {
			continue;
		}

		Card card = deskDecks[i][lastIndex];

		if (isDifferentColor(freeCard, card) && deltaRank(freeCard.rank_char(), card.rank_char()) == 1) {
			return i;
		}
	}
	return -1;
}

void moveSet(Deck& srcDeck, Deck& dstDeck, int setSize) {
	for (int i = setSize; i > 0; i--) {
		int curIndex = srcDeck.len() - i;
		Card card = srcDeck[curIndex];
		srcDeck.remove(curIndex);
		dstDeck.add(card);
	}
}

void remix(Deck& mainDeck, Deck& freeDeck) {
	int lastIndex = freeDeck.len() - 1;
	for (int i = 0; i < freeDeck.len(); i++) {
		Card card = freeDeck[lastIndex - i];
		freeDeck.remove(lastIndex - i);
		mainDeck.add(card);
	}
}

int main()
{
	// set field
	std::default_random_engine generator(2);
	randint dist(0, CARDS);
	dist(generator);

	Deck mainDeck(52, generator);
	int lastCardIndex = 51;
	Deck freeDeck;
	Deck homeDecks[4];
	Deck deskDecks[7];
	int visibleCards[7];
	for (int& e : visibleCards) e = 1;
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < i + 1; j++) {
			Card card = mainDeck[lastCardIndex--];
			mainDeck.remove(card);
			deskDecks[i].add(card);
		}
	}
	// _set field 

	// game
	// move only one card in a step
	int k = 1;
	bool isFirstStep = true;
	int prevMainDeckLen = 0; // need to detect cycle

	while (k) {
		if (isFirstStep) {
			std::cout << "Start\n";
			isFirstStep = false;
		}
		else {
			if (timeToBreak()) break;
		}

		printDecks(freeDeck, homeDecks, deskDecks, visibleCards);

		// first point: find card which can be moved to home

		std::pair toHomeIndexes = findCardToMoveToHome(homeDecks, deskDecks, freeDeck); // i,j - from desk to home, -1,j - from free to home, -1,-1 - haven't found
		if (toHomeIndexes.first < 7 && toHomeIndexes.first != -1) {
			moveLastCard(deskDecks[toHomeIndexes.first], homeDecks[toHomeIndexes.second]);
			if (deskDecks[toHomeIndexes.first].len() == 0) {
				visibleCards[toHomeIndexes.first] = 0;
			}
			continue;
		}
		else if(toHomeIndexes.first == 7){
			moveLastCard(freeDeck, homeDecks[toHomeIndexes.second]);
			continue;
		}

		// second point: try to move card between desk decks

		bool checked[7];
		for (int i = 0; i < 7; i++) { checked[i] = false; }

		bool continueAfterMove = false;

		for (int i = 0; i < 7; i++) {
			int srcIndex = mostNumberOfInvisibleCards(deskDecks, visibleCards, checked);
			checked[srcIndex] = true;
			if (srcIndex == -1) continue;
			int setSize = visibleCards[srcIndex];
			
			int topCardIndex = deskDecks[srcIndex].len() - setSize;
			Card topCard = deskDecks[srcIndex][topCardIndex];

			int dstIndex = findSuitablePlace(topCard, deskDecks, srcIndex, setSize);
			if (dstIndex == -1) continue;

			moveSet(deskDecks[srcIndex], deskDecks[dstIndex], setSize);
			visibleCards[srcIndex] -= setSize;
			if (deskDecks[srcIndex].len() != 0 && visibleCards[srcIndex] == 0) {
				visibleCards[srcIndex]++;// if zero
			}
			visibleCards[dstIndex] += setSize;

			continueAfterMove = true;
			break;
		}

		if (continueAfterMove) continue;

		// third point: try to move card from free deck to desk deck

		int lastFreeIndex;
		lastFreeIndex = freeDeck.len() - 1;
		if (lastFreeIndex != -1) {
			Card freeCard = freeDeck[lastFreeIndex];
			int dstIndex = findSuitablePlaceForFreeCard(freeCard, deskDecks);
			if (dstIndex != -1) {
				moveLastCard(freeDeck, deskDecks[dstIndex]);
				visibleCards[dstIndex] += 1;
				continue;
			}
		}

		// forth point: open card from main deck, or remix it if empty

		int lastMainIndex = mainDeck.len() - 1;
		if (lastMainIndex == -1) {
			remix(mainDeck, freeDeck);
			if (prevMainDeckLen == mainDeck.len()) {
				break; // no steps have done
			}
			prevMainDeckLen = mainDeck.len();
		}
		else {
			moveLastCard(mainDeck, freeDeck);
		}
	}


	// _game

}