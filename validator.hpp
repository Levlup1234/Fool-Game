#ifndef VALID_H
#define VALID_H

#include <iostream>

class Valid
{
public:
    int read_num_players()
    {
        int num;
        while (1) {
            std::cout << "Welcome! How many of you, people, want to play? " << std::endl;
            std::cin >> num;

            if (std::cin.fail()) {   // если ничего не извлекли
                std::cin.clear();
                std::cin.ignore(32767, '\n');
                std::cout << "Please, enter numbers\n";
                continue;
            }

            std::cin.ignore(32767, '\n');
            if (std::cin.gcount() > 1) {
                std::cout << "Please, enter just numbers\n";
                continue;
            }
            if (num <= 0) {
                std::cout << "Please, enter positive numbers\n";
                continue;
            }
            break;
        }
        if (num > 6) {
            std::cout << "Sorry, but only 6 people are allowed at most\n";
            num = 6;
        }
        if (num == 1) {
            std::cout << "You need at least two players, so we found you a new friend!\n";
            num = 2;
        }
        std::cout << "Here, table for " << num << std::endl;
        return num;
    }

    int read_index(int max)
    {
        int index;

        while (1) {
            std::cout << "Enter index of a card you want to play, or 0 to pass\n";
            std::cin >> index;
        
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(32767, '\n');
                std::cout << "Please, enter numbers\n";
                continue;
            }

            std::cin.ignore(32767, '\n');
            if (std::cin.gcount() > 1) {
                std::cout << "Please, enter only numbers\n";
                continue;
            }
            if (index < 0) {
                std::cout << "Please, enter non-negative numbers\n";
                continue;
            }
            if (index > max) {
                std::cout << "This is not a valid index, enter something smaller\n";
                continue;
            }
            break;
        }
        return index;
    };
};

#endif