#include "deck.hpp"
#include "game_state.hpp"
#include "validator.hpp"

int main()
{
    Deck gaming_deck;
    Valid val;
    int n = val.read_num_players();
    GameState game(gaming_deck, n);
    game.start_game();
}