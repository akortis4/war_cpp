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
        std::vector<Card> won_pile;
        bool no_cards{false};
    
    public:
        PlayerHand() {
        }

        void receive_deal(Card card) {
            player_hand.push_back(card);
        }

        Card get_card(int i) {
            return player_hand.at(i);
        }

        void out_of_cards() {
            if (player_hand.size() == 0 && won_pile.size() == 0) {
                no_cards = true;
            }
        }

        bool get_no_cards() {
            return no_cards;
        }

        void shuffle_cards() {
            if (player_hand.size() == 0 && won_pile.size() > 0) {
                auto rng = std::default_random_engine {};
                std::shuffle(std::begin(won_pile), std::end(won_pile), rng);
                player_hand.resize(won_pile.size());
                player_hand.swap(won_pile);
                won_pile.resize(0);
            }
        }

        void add_won_card(Card card) {
            won_pile.push_back(card);
        }

        void remove_card() {
            player_hand.erase(player_hand.begin());
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
};

class Game {
    private:
        Deck deck{};
        PlayerHand player1{};
        PlayerHand player2{};
        bool run{true};
    
    public:
        Game() {
            deck.deal_cards(player1, player2);
        }

        void run_game() {
            while (run) {
                player1.out_of_cards();
                player2.out_of_cards();
                if (player1.get_no_cards() || player2.get_no_cards()) {
                    run = false;
                    display_winner();
                    break;
                }
            player1.shuffle_cards();
            player2.shuffle_cards();
            battle();
            std::cin.ignore();
            }
        }

        void display_winner() {
            if (player1.get_no_cards()) {
                std::cout << "Sorry you lost. Player 2 is the Winner!" << "\n";
            } else {
                std::cout << "Congratulations! You are the winner!" << "\n";
            }
        }

        void battle() {
            Card p1_card{player1.get_card(0)};
            Card p2_card{player2.get_card(0)};
            int result = compare_card(p1_card, p2_card);
            std::vector<Card> winning_pile{p1_card, p2_card};           
            if (result == -1) {
                std::cout << "Player 2 Wins: " << p2_card.card_face << " " << p2_card.card_suit << " beats " << p1_card.card_face << " " << p1_card.card_suit << ".\n";
                for (int i{0}; i < winning_pile.size(); ++i) {
                    player2.add_won_card(winning_pile.at(i));
                }
                player1.remove_card();
                player2.remove_card();
            } else if (result == 1) {
                std::cout << "Player 1 Wins: " << p1_card.card_face << " " << p1_card.card_suit << " beats " << p2_card.card_face << " " << p2_card.card_suit << ".\n";
                for (int i{0}; i < winning_pile.size(); ++i) {
                    player1.add_won_card(winning_pile.at(i));
                }
                player1.remove_card();
                player2.remove_card();
            } else if (result == 0) {
                std::cout << "War!!!\n";
                std::vector<Card> war_pile;
                bool war{true};
                while (war) {
                    
                }
                //need to draw 3 cards or max if hand and won_pile sum to < 3
                //if hand < 3 check won pile and suffle add to end of hand
                //compare 4th card, if same war again
                //store all cards in war vector to add to winning hand
            } else {
                std::cout << "Error in comparison." << "\n";
            }
        }
};

int main() {
    Game game{};
    game.run_game();
    return 0;
}