#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>

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
        std::vector<Card> won_cards;
        bool out_of_cards{false};
    
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

        Card get_card(int i) {
            return player_hand[i];
        }

        void add_won_cards(Card card1, Card card2) {
            won_cards.push_back(card1);
            won_cards.push_back(card2);
        }

        void remove_card() {
            player_hand.erase(player_hand.begin());
        }

        void card_check() {
            if (player_hand.size() == 0 && won_cards.size() == 0) {
                out_of_cards = true;
            }
        }
};

class Deck {
    private:
        std::string card_faces[13]{"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
        std::string card_suits[4]{"Hearts", "Diamonds", "Spades", "Clubs"};
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
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::shuffle(std::begin(deck), std::end(deck), std::default_random_engine(seed));
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

class Game {
    private:
        Deck deck{};
        PlayerHand player1{};
        PlayerHand player2{};
        bool run{false};
    
    public:
        Game() {
            deck.deal_cards(player1, player2);
        }

        void run_game() {
            run = true;
            while (run) {
                Card player1_card = player1.get_card(0);
                Card player2_card = player2.get_card(0);
                int hand_compare {compare_card(player1_card, player2_card)};
                compare(hand_compare, player1_card, player2_card);
                std::cin.ignore();
            }
        }

        void compare(int hand_compare, Card player1_card, Card player2_card) {
            if (hand_compare == -1) {
                std::cout << "Player 2 Wins: " << player2_card.card_face << " " << player2_card.card_suit << " Beats " << player1_card.card_face << " " << player1_card.card_suit << "\n";
                player2.add_won_cards(player2_card, player1_card);
                player1.remove_card();
                player2.remove_card();
            } else if (hand_compare == 1) {
                std::cout << "Player 1 Wins: " << player1_card.card_face << " " << player1_card.card_suit << " Beats " << player2_card.card_face << " " << player2_card.card_suit << "\n";
                player1.add_won_cards(player1_card, player2_card);
                player1.remove_card();
                player2.remove_card();
            } else if (hand_compare == 0) {
                std::cout << "WAR!!!"<< "\n";
            } else {
                std::cout << "ERROR in comparison" << "\n";
            }
            player1.card_check();
            player2.card_check();
        }
};

int main() {
    Game game{};
    game.run_game();
    //need to iterate through each hand and compare next card
    //keep track of each position in the hand
    //maybe create a game class to stroe all this stuff in
    return 0;
}