#ifndef CARD_H
#define CARD_H

#include "common.hpp"
#include <ostream>
#include <string_view>
#include <iostream>
#include <algorithm>

// basic card
class Card
{
public:
    Card()
      : m_suit{""}
      , m_nominal{""}
    {}

    Card(std::string_view suit, std::string_view nominal)
      : m_suit{suit}
      , m_nominal{nominal}
    {}

    void print_name()
    {
        std::cout << m_nominal << " of " << m_suit << std::endl;
    }
    const std::string& get_suit() const
    {
        return m_suit;
    }

    const std::string& get_nominal() const
    {
        return m_nominal;
    }

    friend std::ostream& operator<<(std::ostream& out, const Card card);

    bool operator==(Card& card)
    {
        return m_nominal == card.m_nominal;
    }

    bool operator!=(Card& card)
    {
        return m_nominal != card.m_nominal;
    }

    bool operator>(Card& card)
    {
        return std::find(card_names.nom_vec.begin(), card_names.nom_vec.end(), m_nominal) >
               std::find(card_names.nom_vec.begin(), card_names.nom_vec.end(), card.m_nominal);
    }

    bool operator<(Card& card)
    {
        return std::find(card_names.nom_vec.begin(), card_names.nom_vec.end(), m_nominal) <
               std::find(card_names.nom_vec.begin(), card_names.nom_vec.end(), card.m_nominal);
    }

    bool is_empty()
    {
        return (m_nominal == "") and (m_suit == "");
    }

private:
    std::string m_suit;
    std::string m_nominal;
};

inline std::ostream& operator<<(std::ostream& out, const Card card)
{
    out << card.m_nominal << " of " << card.m_suit << std::endl;
    return out;
}

#endif