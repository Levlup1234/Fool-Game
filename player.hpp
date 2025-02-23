#ifndef PLAYER_H
#define PLAYER_H

#include "card.hpp"
#include "validator.hpp"
#include <algorithm>
#include <string>
#include <string_view>
#include <vector>

// игрок

class BasePlayer
{
public:
    virtual Card play_card(bool first = false) = 0;
    virtual std::string get_name() = 0;
    virtual std::vector<Card> get_hand() = 0;

    void remember_field(std::vector<Card>& field)
    {
        m_field = field;
    }

    void take_card(Card card)
    {
        m_hand.push_back(card);
    }

    void mem_trump(std::string_view trump)
    {
        m_trump = trump;
    }

    bool check_card_valid(Card& card)
    {
        if (m_field.size() == 0) {
            return true;
        }
        if (m_field.size() % 2 == 0) {
            // we're adding cards
            for (auto c : m_field) {
                if (c.get_nominal() == card.get_nominal()) {
                    return true;
                }
            }
        } else {
            // you're defending
            if (card.get_suit() == m_field.back().get_suit()) {
                if (card > m_field.back()) {
                    return true;
                }
            }
            if (card.get_suit() == m_trump) {
                if (m_field.back().get_suit() != m_trump) {
                    return true;
                } else {
                    if (card > m_field.back()) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    std::string m_trump;
    std::vector<Card> m_hand;
    std::vector<Card> m_field;
};

class RealPlayer : public BasePlayer
{
public:
    RealPlayer()
      : m_name{""} {};

    RealPlayer(std::string name)
      : m_name{name} {};

    virtual Card play_card(bool first = false) override
    {
        std::cout << "Your hand is: " << std::endl;
        print_hand();
        int index = val.read_index(m_hand.size());
        if (first) {
            while (!index) {
                std::cout << "Sorry, you must play a card at yout first turn\n";
                index = val.read_index(m_hand.size());
            }
        }
        if (!index) {
            return Card{};
        }
        --index;
        auto card = m_hand.at(index);
        while (!check_card_valid(card)) {
            std::cout << "You cannot play this card\n";
            index = val.read_index(m_hand.size());
            card = m_hand.at(index);
        }
        m_hand.erase(m_hand.begin() + index);
        return card;
    }

    bool take_or_play()
    {
        std::cout << "\nYour hand is: \n";
        print_hand();
        std::cout << "Do you want to take cards?\n1: yes\n2: no, i can beat it!\n";
        int flag;
        std::cin >> flag;
        return flag == 2 ? true : false;
    }

    void print_hand()
    {
        int i = 1;
        for (auto card : m_hand) {
            std::cout << i << " " << card;
            ++i;
        }
    }

    virtual std::vector<Card> get_hand() override
    {
        return m_hand;
    }

    virtual std::string get_name() override
    {
        return m_name;
    }

private:
    std::string m_name;
    Valid val;
};

class AIPlayer : public BasePlayer
{
public:
    AIPlayer()
      : m_name{""} {};

    AIPlayer(std::string name)
      : m_name{name} {};

    virtual Card play_card(bool) override
    {
        ai_sort_hand();
        int index = ai_choose_card();
        if (index < 0) {
            return Card{};
        }
        auto card = m_hand.at(index);
        m_hand.erase(m_hand.begin() + index);
        return card;
    };

    std::vector<Card> get_hand() override
    {
        return m_hand;
    }

    std::string get_name() override
    {
        return m_name;
    }

private:
    void ai_sort_hand()
    {
        std::sort(m_hand.begin(), m_hand.end());
        // for (auto card : m_hand) {
        //     std::cout << card;
        // }
        // std::cout << std::endl;
    }

    int ai_choose_card()
    {
        for (int i = 0; i < m_hand.size(); ++i) {
            if (check_card_valid(m_hand.at(i))) {
                //выбирает наименьшую не козырную карту
                if (m_hand.at(i).get_suit() != m_trump) {
                    return i;
                }
            }
        }
        // не подкидывает козыри ;) (TODO: возможно подкидывает с каким-то шансом)
        if (m_field.size() % 2 == 0) {
            return -1;
        }
        // значит бьёмся козырями
        for (int i = 0; i < m_hand.size(); ++i) {
            if (check_card_valid(m_hand.at(i))) {
                return i;
            }
        }
        return -1;
    }

    std::string m_name;
};

#endif