#pragma once

#include <random>
#include <functional>
#include "card.hpp"

namespace cards {
    using randint = std::uniform_int_distribution<int>;

    class Deck {
        uint8_t len_ = 0;

        // в массиве всегда хранятся все карты для оптимизаций
        // в начале хранится колода длиной len_, а за ней все остальные карты
        #ifdef DYNAMIC_VARIANT
        Card* cards_;
        #else
        Card cards_[CARDS];
        #endif
    public:
        Deck();
        explicit Deck(const Card &card); // инициализация 1 картой
        Deck(const Deck &deck);
        Deck& operator=(const Deck& deck);
        ~Deck();

        template <class URNG>
        Deck(uint8_t cards_count, URNG& generator) : Deck() {
            // случайная генерация карт
            if (cards_count > CARDS)
                throw std::invalid_argument("Deck can have no more than 52 cards");

            len_ = cards_count;
            // просто перемешать все карты
            std::shuffle(cards_, cards_ + CARDS, generator);
        }

        uint8_t len() const;
        const Card& operator[](uint8_t i) const;

        bool verify_state() const; // проверка состояний; для тестирования

        void add(const Card& card); // добавить карту
        void remove(const Card& card); // убрать карту
        void remove(uint8_t i); // убрать карту по индексу

        template <class URNG>
        void add_random_card(URNG& urng) { // добавить случайную карту
            if (len_ == CARDS)
                throw std::runtime_error("Deck is full");

            // просто выбрать любую карту из тех, что не в колоде
            uint8_t i = randint(len_, CARDS - 1)(urng);
            // и поместить её в конец колоды
            std::swap(cards_[i], cards_[len_]);
            len_ += 1;
        }

        void sort(); // сортировка сначала по масти, а затем по рангу
        void filter_suit(uint8_t suit); // убрать все карты другой масти
    };

    std::istream& operator>>(std::istream& is, Deck& deck);
    std::ostream& operator<<(std::ostream& os, const Deck& deck);
}
