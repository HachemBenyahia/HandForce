#include "Hand.h"

std::vector<Card> Hand::CardsByFamily(std::string family)
{
    std::vector<Card> cards;

    for(std::vector<Card>::iterator it = m_hand.begin() ; it != m_hand.end() ; it++)
        if(it->GetFamily() == family)
            cards.push_back(*it);

    return cards;
}

std::vector<Card> Hand::CardsByName(const std::string& name) const
{
    std::vector<Card> cards;

    for(int i = 0 ; i < m_hand.size() ; i++)
        if(m_hand[i].GetName() == name)
            cards.push_back(m_hand[i]);

    return cards;
}

std::vector<Card> Hand::Flush()
{
    if(CardsByFamily("Clubs").size() >= 5)
        return CardsByFamily("Clubs");

    if(CardsByFamily("Diamonds").size() >= 5)
        return CardsByFamily("Diamonds");

    if(CardsByFamily("Hearts").size() >= 5)
        return CardsByFamily("Hearts");

    if(CardsByFamily("Spades").size() >= 5)
        return CardsByFamily("Spades");

    std::vector<Card> cards;

    return cards;
}

std::vector<Card> Hand::Straight()
{
    std::vector<Card> sortedHand = Sorted();
    std::vector<Card> cards;

    if(sortedHand.size() == 5)
        if(StraightBetween(sortedHand, 0, 5))
        {
            cards.push_back(sortedHand[0]);
            cards.push_back(sortedHand[1]);
            cards.push_back(sortedHand[2]);
            cards.push_back(sortedHand[3]);
            cards.push_back(sortedHand[4]);
        }

    if(sortedHand.size() == 6)
        if(StraightBetween(sortedHand, 1, 6))
            if(cards.size())
                cards.push_back(sortedHand[5]);
            else
            {
                cards.push_back(sortedHand[1]);
                cards.push_back(sortedHand[2]);
                cards.push_back(sortedHand[3]);
                cards.push_back(sortedHand[4]);
                cards.push_back(sortedHand[5]);
            }

    if(sortedHand.size() == 7)
        if(StraightBetween(sortedHand, 2, 7))
            if(cards.size())
            {
                cards.push_back(sortedHand[6]);
                if(!FindCard(sortedHand[5], cards))
                    cards.push_back(sortedHand[5]);
            }
            else
            {
                cards.push_back(sortedHand[2]);
                cards.push_back(sortedHand[3]);
                cards.push_back(sortedHand[4]);
                cards.push_back(sortedHand[5]);
                cards.push_back(sortedHand[6]);
            }

    return cards;
}

std::vector<Card> Hand::FourOfAKind()
{
    std::vector<std::string> names = Hand::GetNames();

    for(int i = 0 ; i < names.size() ; i++)
    {
        if(CardsByName(names[i]).size() >= 4)
            return CardsByName(names[i]);
    }

    std::vector<Card> cards;
    return cards;
}

std::vector<Card> Hand::ThreeOfAKind()
{
    std::vector<std::string> names = Hand::GetNames();

    for(int i = 0 ; i < names.size() ; i++)
        if(CardsByName(names[i]).size() >= 3)
            return CardsByName(names[i]);

    std::vector<Card> cards;
    return cards;
}

std::vector<Card> Hand::FullHouse()
{
    std::vector<std::string> names = Hand::GetNames();
    std::vector<Card> cards;
    std::vector<Card> onePair = OnePair();
    std::vector<Card> threeOfAKind = ThreeOfAKind();

    if(!onePair.size())
        return cards;

    if(!threeOfAKind.size())
        return cards;

    if(threeOfAKind[0].GetName() != onePair[0].GetName())
    {
        cards.reserve(threeOfAKind.size() + onePair.size());
        cards.insert(cards.end(), threeOfAKind.begin(), threeOfAKind.end());
        cards.insert(cards.end(), onePair.begin(), onePair.end());
    }

    return cards;
}

std::vector<Card> Hand::TwoPairs()
{
    std::vector<Card> cards;

    if(OnePair().size() >= 4)
        return OnePair();

    return cards;
}

std::vector<Card> Hand::OnePair()
{
    std::vector<std::string> names = Hand::GetNames();

    std::vector<Card> cards;

    for(int i = 0 ; i < names.size() ; i++)
        if(CardsByName(names[i]).size() >= 2)
        {
            std::vector<Card> others = CardsByName(names[i]);
            std::vector<Card> tmp = cards;

            cards.reserve(tmp.size() + others.size());
            cards.insert(cards.end(), tmp.begin(), tmp.end());
            cards.insert(cards.end(), others.begin(), others.end());
        }

    return cards;
}

std::vector<Card> Hand::HighCard()
{
    std::vector<Card> sortedHand = Sorted();
    std::vector<Card> cards;

    if(sortedHand.size())
        cards.push_back(sortedHand[sortedHand.size() - 1]);

    return cards;
}

bool Hand::FindCard(Card card, std::vector<Card> cards)
{
    for(int i = 0 ; i < cards.size() ; i++)
        if(cards[i] == card)
            return true;

    return false;
}

bool Hand::StraightBetween(std::vector<Card> cards, int start, int limit)
{
    std::vector<int> numbers;
    for(int i = 0 ; i < cards.size() ; i++)
        numbers.push_back(cards[i].GetNumber());

    for(int i = start ; i < limit ; i++)
    {
        if(i == limit - 1)
            break;

        if(numbers[i + 1] - numbers[i] > 1)
            return false;
    }

    return true;
}

std::vector<Card> Hand::StraightFlush()
{
    std::vector<Card> cards;

    std::vector<Card> cardsFlush = Flush();

    if(!cardsFlush.size())
        return cards;

    std::vector<Card> cardsStraight = Straight();

    if(!cardsStraight.size())
        return cards;

    if(Intersection(cardsFlush, cardsStraight).size() >= 5)
        return Intersection(cardsFlush, cardsStraight);

    return cards;
}

std::vector<Card> Hand::RoyalFlush()
{
    std::vector<Card> cards;

    if(cards.size() && FindCardByName("Ace", cards) && FindCardByName("King", cards))
        return StraightFlush();
    else
        return cards;
}

bool Hand::FindCardByName(std::string name, std::vector<Card> cards)
{
    for(int i = 0 ; i < cards.size() ; i++)
        if(cards[i].GetName() == name)
            return true;

    return false;
}

int Hand::GetSize()
{
    return m_hand.size();
}

std::vector<Card> Hand::Sorted()
{
    std::vector<Card> handCopy = m_hand;
    std::sort(handCopy.begin(), handCopy.end());
    return handCopy;
}

std::vector<Card> Hand::Intersection(std::vector<Card> cardsA, std::vector<Card> cardsB)
{
    std::vector<Card> cards;

    for(int i = 0 ; i < cardsA.size() ; i++)
        for(int j = 0 ; j < cardsB.size() ; j++)
        {
            if(cardsA[i] == cardsB[j])
                cards.push_back(cardsA[i]);
        }

    return cards;
}

std::vector<std::string> Hand::GetNames()
{
    std::vector<std::string> names;

    names.push_back("Two");
    names.push_back("Three");
    names.push_back("Four");
    names.push_back("Five");
    names.push_back("Six");
    names.push_back("Seven");
    names.push_back("Eight");
    names.push_back("Nine");
    names.push_back("Ten");
    names.push_back("Jack");
    names.push_back("Queen");
    names.push_back("King");
    names.push_back("Ace");

    return names;
}

std::ostream& operator<<(std::ostream& os, Hand& hand)
{
    std::vector<Card> cards = hand.GetCards();

    for(int i = 0 ; i < cards.size() ; i++)
        os << cards[i] << std::endl;

    return os;
}
