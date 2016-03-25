#ifndef HAND
#define HAND

#include <iostream>
#include <vector>
#include <algorithm>
#include "Card.h"

class Hand
{
    private :
        std::vector<Card> m_hand;

        std::vector<Card> CardsByFamily(std::string family);
        std::vector<Card> CardsByName(const std::string& name) const;

        bool StraightBetween(std::vector<Card> cards, int start, int limit);
        std::vector<Card> Intersection(std::vector<Card> cardsA, std::vector<Card> cardsB);

        bool FindCard(Card card, std::vector<Card> cards);
        bool FindCardByName(std::string name, std::vector<Card> cards);
        int MinIndex(std::vector<int> numbers);
        static std::vector<std::string> GetNames();

    public :
        void Push(Card card) {m_hand.push_back(card);}
        void Clear() {m_hand.clear();}
        int GetSize();

        std::vector<Card> Flush();
        std::vector<Card> Straight();
        std::vector<Card> StraightFlush();
        std::vector<Card> RoyalFlush();
        std::vector<Card> FourOfAKind();
        std::vector<Card> ThreeOfAKind();
        std::vector<Card> FullHouse();
        std::vector<Card> OnePair();
        std::vector<Card> TwoPairs();
        std::vector<Card> HighCard();

        std::vector<Card> Sorted();

        std::vector<Card> GetCards() {return m_hand;};
};

std::ostream& operator<<(std::ostream& os, Hand& hand);

#endif
