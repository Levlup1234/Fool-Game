#include "game_state.hpp"
#include "card.hpp"
#include <vector>

void GameState::rem_field(std::vector<Card>& field)
{
    for (auto player : players) {
        player->remember_field(field);
    }
}

void GameState::one_turn()
{
    auto atk_player = players.at(atk_player_index);
    auto def_player = players.at(def_player_index);
    std::vector<Card> cards_on_field{};
    rem_field(cards_on_field);

    std::cout << "Now is turn of player " << atk_player->get_name() << std::endl;
    cards_on_field.push_back(atk_player->play_card(true));
    rem_field(cards_on_field);

    std::cout << atk_player->get_name() << " played " << cards_on_field.back() << std::endl;
    auto state = TurnStates::beat;

    while (state != TurnStates::end) {
        switch (state) {
        case TurnStates::take:
            for (auto card : cards_on_field) {
                def_player->take_card(card);
                state = TurnStates::end;
            }
            break;

        case TurnStates::end:
            std::cout << "Well, we should not be here\n";
            break;

        case TurnStates::beat: {
            Card card = def_player->play_card();
            if (card.is_empty()) {
                std::cout << "Player " << def_player->get_name() << " decided to take cards\n";
                state = TurnStates::take;
                break;
            }
            std::cout << def_player->get_name() << " played " << card;
            cards_on_field.push_back(card);
            rem_field(cards_on_field);

            state = TurnStates::add;
            for (auto player : players) {
                if (player->get_hand().size() == 0) {
                    std::cout << player->get_name() << " has no more cards\n";
                    state = TurnStates::end;
                    break;
                }
            }
            break;
        }

        case TurnStates::add:
            std::cout << "===================\ntable:\n";
            for (auto card : cards_on_field) {
                std::cout << card;
            }
            std::cout << "===================\n";

            std::cout << atk_player->get_name() << ", you can add cards if you want\n";
            {
                Card card = atk_player->play_card();
                if (card.is_empty()) {
                    std::cout << "Player " << atk_player->get_name() << " decided to pass\n";
                    // change atacking player here
                    std::cout << "Next turn\n";

                    state = TurnStates::end;
                    std::swap(def_player_index, atk_player_index);   //TODO: multiple players
                    break;
                }
                std::cout << "Player " << atk_player->get_name() << " played " << card;
                cards_on_field.push_back(card);
                rem_field(cards_on_field);
                state = TurnStates::beat;
            }
            break;
        }
    }
    take_cards();
    std::cout << "======================\n";
}

void GameState::take_cards()
{
    for (int i = 0; i < players.size(); ++i) {
        while (players.at(i)->get_hand().size() < default_hand_size) {
            if (m_deck.empty())
                return;
            players.at(i)->take_card(m_deck.take_card());
        }
    }
}

void GameState::start_game()
{
    while (!m_winner) {
        one_turn();
        for (auto& player : players) {
            if (player->get_hand().size() == 0) {
                if (m_winner) {
                    std::cout << "Tie\n";
                    return;
                }
                std::cout << player->get_name() << " won! Congrats!\n";
                m_winner = true;
            }
        }
    }
}