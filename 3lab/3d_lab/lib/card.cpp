#include "card.hpp"
using namespace cards;

Card::Card() : card_(0) {}

Card::Card(uint8_t id) : card_(id) {
    if (id >= CARDS)
        throw std::invalid_argument("id ids range from 0 to 51");
}

Card::Card(uint8_t rank, uint8_t suit) : card_(rank + suit * RANKS) {
    if (rank >= RANKS)
        throw std::invalid_argument("card rank ranges from 0 to 12");
    if (suit >= SUITS)
        throw std::invalid_argument("card suit ranges from 0 to 3");
}

bool Card::operator==(const Card& other) const {
    return card_ == other.card_;
}

bool Card::operator==(const uint8_t other) const {
    return card_ == other;
}

std::strong_ordering Card::operator<=>(const uint8_t card) const {
    return card_ <=> card;
}

uint8_t Card::id() const {
    return card_;
}

uint8_t Card::suit() const {
    return card_ / RANKS;
}

char Card::suit_char() const {
    return SUIT_CHARS[suit()];
}

void Card::set_suit(uint8_t suit) {
    if (suit >= RANKS)
        throw std::invalid_argument("card suit ranges from 0 to 3");
    card_ = rank() + suit * RANKS;
}

uint8_t Card::rank() const {
    return card_ % RANKS;
}

char Card::rank_char() const {
    return RANK_CHARS[rank()];
}

void Card::set_rank(uint8_t rank) {
    if (rank >= RANKS)
        throw std::invalid_argument("card rank ranges from 0 to 12");
    card_ = rank + suit() * RANKS;
}

std::string Card::name() const {
    char res[3] = {};
    res[0] = rank_char();
    res[1] = suit_char();
    return res;
}

std::string Card::long_name() const {
    std::stringstream res;
    res << RANK_NAMES[rank()] << " of " << SUIT_NAMES[suit()];
    return res.str();
}
