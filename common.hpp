#ifndef COMMON_H
#define COMMON_H

#include <vector>
#include <string_view>
static struct
{
    const std::vector<std::string_view> suit_vec{"Diamonds", "Hearts", "Spades", "Clubs"};
    const std::vector<std::string_view> nom_vec{"Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"};
} card_names;

#endif