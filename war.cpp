#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

struct Card {
    std::string card_face{};
    std::string card_suit{};
    int card_value{};
};

class PlayerHand {
    private:
        std::vector<Card> player_hand(26);
    
    public:
        PlayerHand() {
        }

        void receive_deal(Card card) {
            player_hand.push_back(card);
        }

        void print_hand() {
            for (Card card: player_hand) {
                std::cout << card.card_face << " " << card.card_suit << "\n";
            }
        }
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

        void deal_cards(PlayerHand player1, PlayerHand player2) {
            for (int i{0}; i < sizeof(deck) / sizeof(deck[0]); ++i) {
                if (i % 2 == 0) {
                    player1.receive_deal(deck[i]);
                } else {
                    player2.receive_deal(deck[i]);
                }
            }
        }

        void print_deck() {
            for (Card card: deck) {
                std::cout << card.card_face << " " << card.card_suit << "\n";
            }
        }
};



int main() {
    Deck deck{};
    PlayerHand player1{};
    PlayerHand player2{};
    deck.deal_cards(player1, player2);
    player1.print_hand();
    return 0;
}