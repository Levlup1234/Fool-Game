#ifndef DECK_H
#define DECK_H

#include "card.hpp"
#include "common.hpp"
#include <algorithm>
#include <vector>
#include <random>

//колода
class Deck
{
public:
    Deck()
    {
        for (auto suit : card_names.suit_vec) {
            for (auto nominal : card_names.nom_vec) {
                list_of_cards.push_back(Card(suit, nominal));
            }
        }
        std::random_shuffle(list_of_cards.begin(), list_of_cards.end());   // Посмотреть другие ГСЧ
    };

    std::vector<Card>& get_deck()
    {
        return list_of_cards;
    }

    Card take_card()
    {
        auto t = list_of_cards.back();
        list_of_cards.pop_back();
        return t;
    }

    Card peek_card()
    {
        return list_of_cards.back();
    }

    bool empty()
    {
        if (list_of_cards.size() == 0)
            return true;
        return false;
    }

private:
    std::vector<Card> list_of_cards;
};

#endif