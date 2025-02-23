#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "card.hpp"
#include "deck.hpp"
#include "player.hpp"
#include <ostream>
#include <string_view>
#include <vector>

// состояния хода
enum class TurnStates
{
    beat,
    add,
    take,
    end,
};

// основной игровой класс
class GameState
{
public:
    GameState(Deck deck, int num_players)
      : m_deck{deck}
      , m_winner{false}
    {
        ai_players.reserve(num_players - 1);
        players.reserve(num_players);
        std::cout << "Enter your name, player 1\n";
        std::string name;
        std::cin >> name;
        real_player = RealPlayer{name};
        for (int i = 1; i < num_players; ++i) {
            std::cout << "Enter your name, player " << i + 1 << std::endl;
            std::string name;
            std::cin >> name;
            AIPlayer player{name};
            ai_players.push_back(player);
        }
        players.push_back(&real_player);
        // players.insert(players.end(), ai_players.begin(), ai_players.end());
        for (auto i = 0; i < ai_players.size(); ++i) {
            players.push_back(&ai_players.at(i));
        }
        for (size_t i = 0; i < default_hand_size; ++i) {
            for (int i = 0; i < num_players; ++i) {
                auto card = m_deck.take_card();
                players.at(i)->take_card(card);
            }
        }
        if (num_players == 6) {
            trump = players.back()->get_hand().back().get_suit();
        } else {
            trump = m_deck.peek_card().get_suit();
        }
        for (auto player : players) {
            player->mem_trump(trump);
        }
        print_trump();
        atk_player_index = 0;
        def_player_index = atk_player_index + 1;
    };

    void print_trump()
    {
        std::cout << "Trump is " << trump << std::endl;
    }

    void start_game();

public:
    std::string_view trump;

private:
    void one_turn();
    void take_cards();
    void rem_field(std::vector<Card>& field);

    Deck m_deck;
    RealPlayer real_player;
    std::vector<AIPlayer> ai_players;
    std::vector<BasePlayer*> players;
    size_t atk_player_index;
    size_t def_player_index;
    TurnStates state;
    const int default_hand_size = 6;
    bool m_winner;
};

#endif