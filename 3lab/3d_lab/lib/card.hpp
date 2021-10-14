#pragma once

#include <stdexcept>
#include <compare>
#include <sstream>


namespace cards {
	using std::string;

	inline const int SUITS = 4;
	inline const char SUIT_CHARS[] = "CSDH";
	inline const char* SUIT_NAMES[] = {"Clubs", "Spades", "Diamonds", "Hearts"};
	inline const int RANKS = 13;
	inline const char RANK_CHARS[] = "23456789TJQKA";
	inline const char* RANK_NAMES[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
	inline const int CARDS = 52;

	class Card {
		uint8_t card_;
	public:
		Card();
		explicit Card(uint8_t id);
		Card(const Card &card) = default;
		explicit Card(uint8_t rank, uint8_t suit);
		Card& operator=(const Card& other) = default;

		bool operator==(const Card &other) const;
		bool operator==(uint8_t other) const;
		// операторы сравнения по-умолчанию
		std::strong_ordering operator<=>(const Card&) const = default;
		std::strong_ordering operator<=>(uint8_t card) const;

		uint8_t id() const;

		uint8_t suit() const;
		char suit_char() const;
		void set_suit(uint8_t suit);

		uint8_t rank() const;
		char rank_char() const;
		void set_rank(uint8_t rank);

		string name() const;
		string long_name() const;
	};
}
