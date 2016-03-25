#include "Card.h"

Card::Card(std::string family, std::string name, std::string path, int number) :
m_family(family), m_name(name), m_path(path), m_number(number)
{
}

bool Card::SameRank(const Card& other)
{
    return this->m_name == other.m_name;
}

bool Card::SameFamily(const Card& other)
{
    return this->m_family == other.m_family;
}

bool Card::operator==(const Card& other)
{
    return SameFamily(other) && SameRank(other);
}

bool Card::operator<(const Card& other)
{
    return m_number < other.GetNumber();
}

bool Card::operator<=(const Card& other)
{
    return m_number <= other.GetNumber();
}

bool Card::operator>(const Card& other)
{
    return m_number > other.GetNumber();
}

bool Card::operator>=(const Card& other)
{
    return m_number >= other.GetNumber();
}

std::ostream& operator<<(std::ostream& os, Card& card)
{
    os << card.GetName() << " of " << card.GetFamily();

    return os;
}
