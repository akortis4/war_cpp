#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

struct Card {
    std::string card_face{};
    std::string card_suit{};
    int card_value{};
};

int compare_card(Card card1, Card card2) {
    int compare{};
    if (card1.card_value == card2.card_value) {
        compare = 0;
    } else if (card1.card_value < card2.card_value) {
        compare = -1;
    } else if (card1.card_value > card2.card_value) {
        compare = 1;
    } else {
        compare = -2;
    }
    return compare;
}

class PlayerHand {
    private:
        std::vector<Card> player_hand;
        int hand_position{0};
    
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

        int get_hand_size() {
            return std::size(player_hand);
        }

        Card get_card(int i) {
            return player_hand[i];
        }

        int get_position() {
            return hand_position;
        }

        void increment_position() {
            ++hand_position;
        }

        void reset_position() {
            hand_position = 0;
        }
};

class Deck {
    private:
        std::string card_faces[13]{"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
        std::string card_suits[4]{"Heats", "Diamonds", "Spades", "Clubs"};
        Card deck[52]{};

        void create_deck() {
            int counter{0};
            for (int i{0}; i < std::size(card_faces); ++i) {
                for (int j{0}; j < std::size(card_suits); ++j) {
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

        void deal_cards(PlayerHand& player1, PlayerHand& player2) {
            for (int i{0}; i < std::size(deck); ++i) {
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
    //need to iterate through each hand and compare next card
    //keep track of each position in the hand
    //maybe create a game class to stroe all this stuff in
    return 0;
}