#include <cstring>
#include "deck.hpp"


using namespace cards;

Deck::Deck() {
    #ifdef DYNAMIC_VARIANT
    cards_ = new Card[CARDS];
    #endif
    for (int i = 0; i < CARDS; ++i)
        cards_[i] = Card(i);
}

Deck::Deck(const Card& card) : Deck() {
    add(card);
}


Deck::Deck(const Deck& deck) : Deck() {
    len_ = deck.len_;
    for (int i = 0; i < CARDS; ++i) {
        cards_[i] = deck.cards_[i];
    }
}

#ifdef DYNAMIC_VARIANT
Deck::~Deck() {
    delete []cards_;
}
#else
Deck::~Deck() = default;
#endif

Deck& Deck::operator=(const Deck& deck) {
    if (this == &deck)
        return *this;
    len_ = deck.len_;
    for (int i = 0; i < CARDS; ++i) { // копируем все карты
        cards_[i] = deck.cards_[i];
    }
    return *this;
}

bool Deck::verify_state() const {
    bool present[CARDS];
    std::memset(present, 0, CARDS * sizeof(bool));

    if (len_ > CARDS)
        return false;
    for (int i = 0; i < CARDS; ++i) {
        uint8_t card = cards_[i].id();
        if (card >= CARDS)
            return false; // никогда не должно произойти
        if (present[card])
            return false;
        present[card] = true;
    }
    return true;
}

const Card& Deck::operator[](uint8_t i) const {
    if (i >= len_)
        throw std::out_of_range("Accessing card out of range");
    return cards_[i];
}

void Deck::add(const Card& card) {
    if (len_ == CARDS)
        throw std::runtime_error("Deck is full");

    for (int i = 0; i < CARDS; ++i) {
        if (cards_[i] == card) {
            if (i < len_) {
                throw std::runtime_error("Deck cannot have 2 equal cards");
            } else {
                std::swap(cards_[i], cards_[len_]);
                len_ += 1;
                return;
            }
        }
    }
    throw std::runtime_error("Deck's internal state was not maintained");
}

void Deck::remove(const Card& card) {
    if (len_ == 0)
        throw std::runtime_error("Deck is empty");

    for (int i = 0; i < len_; ++i) {
        if (cards_[i] == card) {
            len_ -= 1;
            std::swap(cards_[i], cards_[len_]);
            return;
        }
    }
    throw std::runtime_error("Deck has no such card");
}

void Deck::remove(uint8_t i) {
    if (len_ == 0)
        throw std::runtime_error("Deck is empty");
    if (i >= len_)
        throw std::out_of_range("Accessing card out of range");
    len_ -= 1;
    std::swap(cards_[i], cards_[len_]);
}

void Deck::sort() {
    std::sort(cards_, cards_ + len_);
}

void Deck::filter_suit(uint8_t suit) {
    for (int i = 0; i < len_; ++i) {
        if (cards_[i].suit() != suit) {
            remove(i);
            i -= 1;
        }
    }
}

uint8_t Deck::len() const {
    return len_;
}

std::ostream& cards::operator<<(std::ostream& os, const Deck& deck) {
    for (int i = 0; i < deck.len(); ++i) {
        os << deck[i].long_name() << " :: ";
    }
    os << std::endl;
    return os;
}

std::istream& cards::operator>>(std::istream& is, Deck& deck) {
    int n;
    is >> n;
    for (int i = 0; i < n; ++i) {
        int card;
        is >> card;
        deck.add(Card(card));
    }
    return is;
}

