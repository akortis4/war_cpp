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

        void check_hand_length() {
            if (player_hand.size() == 0) {
                no_cards = true;
            }
        }

        bool get_no_cards() {
            return no_cards;
        }

        void shuffle_cards() {
            auto rng = std::default_random_engine {};
            std::shuffle(std::begin(player_hand), std::end(player_hand), rng);
        }

        void add_won_card(Card card) {
            player_hand.push_back(card);
        }

        void remove_card() {
            player_hand.erase(player_hand.begin());
        }

        int get_hand_length() {
            int max_size{0};
            max_size = player_hand.size();
            return max_size;
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
        int battle_count{0};
        bool run{true};
    
    public:
        Game() {
            deck.deal_cards(player1, player2);
        }

        void run_game() {
            while (run) {
                player1.check_hand_length();
                player2.check_hand_length();
                if (player1.get_no_cards() || player2.get_no_cards()) {
                    display_winner();
                    run = false;
                    break;
                }
                if (battle_count > 25) {
                    if (battle_count % 5 == 0) {
                        player1.shuffle_cards();
                        player2.shuffle_cards();
                    }
                }
                battle();
                std::cout << "Player 1 hand size: " << player1.get_hand_length() << "\n";
                std::cout << "Player 2 hand size: " << player2.get_hand_length() << "\n";
                std::cin.ignore();
                ++battle_count;
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
            Card card1 = player1.get_card(0);
            Card card2 = player2.get_card(0);
            int battle_result = compare_card(card1, card2);
            if (battle_result == 1) {
                std::cout << "Player 1 wins : " << card1.card_face << " " << card1.card_suit << " beats " << card2.card_face << " " << card2.card_suit << "\n";
                player1.add_won_card(card1);
                player1.add_won_card(card2);
                player1.remove_card();
                player2.remove_card();
            } else if (battle_result == -1) {
                std::cout << "Player 2 wins : " << card2.card_face << " " << card2.card_suit << " beats " << card1.card_face << " " << card1.card_suit << "\n";
                player2.add_won_card(card1);
                player2.add_won_card(card2);
                player1.remove_card();
                player2.remove_card();
            } else if (battle_result == 0) {
                std::cout << "WAR!!!" << "\n";
                bool war{true};
                std::vector<Card> war_pile{card1, card2};
                while (war) {
                    int p1_max{player1.get_hand_length()};
                    int p2_max{player2.get_hand_length()};
                    Card war_card1;
                    Card war_card2;
                    int max_size = (p1_max < p2_max) ? p1_max : p2_max;
                    if (max_size == 1) {
                        if (p1_max == 1) {
                            war_card1 = card1;
                            player2.remove_card();
                            war_card2 = player2.get_card(0);
                            war_pile.push_back(war_card2);
                        }
                        if (p2_max == 1) {
                            war_card2 = card2;
                            player1.remove_card();
                            war_card1 = player1.get_card(0);
                            war_pile.push_back(war_card1);
                        }
                    } else if (max_size < 5) {
                        player1.remove_card();
                        player2.remove_card();
                        war_card1 = player1.get_card(max_size - 1);
                        war_card2 = player2.get_card(max_size - 1);
                        for (int i{0}; i < max_size; ++i) {
                            war_pile.push_back(player1.get_card(0));
                            war_pile.push_back(player2.get_card(0));
                            player1.remove_card();
                            player2.remove_card();
                        }
                    } else {
                        player1.remove_card();
                        player2.remove_card();
                        war_card1 = player1.get_card(3);
                        war_card2 = player2.get_card(3);
                        for (int i{0}; i < 4; ++i) {
                            war_pile.push_back(player1.get_card(0));
                            war_pile.push_back(player2.get_card(0));
                            player1.remove_card();
                            player2.remove_card();
                        }
                    }
                    int war_compare = compare_card(war_card1, war_card2);
                    if (war_compare == 1) {
                        std::cout << "Player 1 wins the war!!!" << "\n";
                        war = false;
                        if (p2_max == 1) {
                            player1.add_won_card(war_card2);
                            player2.remove_card();
                        } else {
                            for (Card card: war_pile) {
                                player1.add_won_card(card);
                            }
                        }
                        break;
                    } else if (war_compare == -1) {
                        std::cout << "Player 2 wins the war!!!" << "\n";
                        war = false;
                        if (p1_max == 1) {
                            player2.add_won_card(war_card2);
                            player1.remove_card();
                        } else {
                            for (Card card: war_pile) {
                                player2.add_won_card(card);
                            }
                        }
                        break;
                    } else if (war_compare == 0) {
                        continue;
                    } else {
                        std::cout << "Error in comparison!" << "\n";
                    }
                }
            } else {
                std::cout << "Error in comparison" << "\n";
            }
        }
};

int main() {
    Game game{};
    game.run_game();
    return 0;
}