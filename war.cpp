#include <iostream>
#include <string>
#include <algorithm>
#include <random>

struct Card {
    std::string card_face{};
    std::string card_suit{};
    int card_value{};
};

class Deck {
    private:
        std::string card_faces[13]{"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
        std::string card_suits[4]{"Heats", "Diamonds", "Spades", "Clubs"};
        Card deck[52]{};

        void create_deck() {
            int counter{0};
            for (int i{0}; i < sizeof(card_faces) / sizeof(card_faces[0]); ++i) {
                for (int j{0}; j < sizeof(card_suits) / sizeof(card_suits[0]); ++j) {
                    Card new_card {card_faces[i], card_suits[j], i};
                    deck[counter] = new_card;
                    ++counter;
                }
            }
        }

        void shuffle_deck() {
            std::random_shuffle(std::begin(deck), std::end(deck));
            std::random_shuffle(std::begin(deck), std::end(deck));
        }

    public:
        Deck() {
            create_deck();
            shuffle_deck();
        }

        Card* get_deck() {
            return deck;
        }
};

int main() {
    Deck deck{};


    return 0;
}