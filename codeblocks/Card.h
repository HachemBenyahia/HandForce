#ifndef CARD
#define CARD

#include <iostream>
#include <string>

class Card
{
    private :
        std::string m_name, m_path, m_family;
        int m_number;

    public :
        Card(std::string family = "", std::string name = "", std::string path = "", int number = -1);
        bool SameRank(const Card& other);
        bool SameFamily(const Card& other);
        bool operator==(const Card& other);
        bool operator<(const Card& other);
        bool operator<=(const Card& other);
        bool operator>(const Card& other);
        bool operator>=(const Card& other);
        std::string GetPath() {return m_path;}
        std::string GetName() const {return m_name;}
        std::string GetFamily() {return m_family;}
        int GetNumber() const {return m_number;}
};

std::ostream& operator<<(std::ostream& os, Card& card);

#endif
