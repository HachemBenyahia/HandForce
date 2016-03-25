#include "Solver.h"

Solver* Solver::m_solver = 0;
Card* Solver::m_cards = 0;

Solver* Solver::GetSolver()
{
    if(!m_solver)
    {
        m_solver = new Solver;
        m_cards = new Card[52];

        m_cards[TWO_CLUBS] = Card("Clubs", "Two", "cards/two_clubs.bmp", 0);
        m_cards[THREE_CLUBS] = Card("Clubs", "Three", "cards/three_clubs.bmp", 1);
        m_cards[FOUR_CLUBS] = Card("Clubs", "Four", "cards/four_clubs.bmp", 2);
        m_cards[FIVE_CLUBS] = Card("Clubs", "Five", "cards/five_clubs.bmp", 3);
        m_cards[SIX_CLUBS] = Card("Clubs", "Six", "cards/six_clubs.bmp", 4);
        m_cards[SEVEN_CLUBS] = Card("Clubs", "Seven", "cards/seven_clubs.bmp", 5);
        m_cards[EIGHT_CLUBS] = Card("Clubs", "Eight", "cards/eight_clubs.bmp", 6);
        m_cards[NINE_CLUBS] = Card("Clubs", "Nine", "cards/nine_clubs.bmp", 7);
        m_cards[TEN_CLUBS] = Card("Clubs", "Ten", "cards/ten_clubs.bmp", 8);
        m_cards[JACK_CLUBS] = Card("Clubs", "Jack", "cards/jack_clubs.bmp", 9);
        m_cards[QUEEN_CLUBS] = Card("Clubs", "Queen", "cards/queen_clubs.bmp", 10);
        m_cards[KING_CLUBS] = Card("Clubs", "King", "cards/king_clubs.bmp", 11);
        m_cards[ACE_CLUBS] = Card("Clubs", "Ace", "cards/ace_clubs.bmp", 12);

        m_cards[TWO_DIAMONDS] = Card("Diamonds", "Two", "cards/two_diamonds.bmp", 0);
        m_cards[THREE_DIAMONDS] = Card("Diamonds", "Three", "cards/three_diamonds.bmp", 1);
        m_cards[FOUR_DIAMONDS] = Card("Diamonds", "Four", "cards/four_diamonds.bmp", 2);
        m_cards[FIVE_DIAMONDS] = Card("Diamonds", "Five", "cards/five_diamonds.bmp", 3);
        m_cards[SIX_DIAMONDS] = Card("Diamonds", "Six", "cards/six_diamonds.bmp", 4);
        m_cards[SEVEN_DIAMONDS] = Card("Diamonds", "Seven", "cards/seven_diamonds.bmp", 5);
        m_cards[EIGHT_DIAMONDS] = Card("Diamonds", "Eight", "cards/eight_diamonds.bmp", 6);
        m_cards[NINE_DIAMONDS] = Card("Diamonds", "Nine", "cards/nine_diamonds.bmp", 7);
        m_cards[TEN_DIAMONDS] = Card("Diamonds", "Ten", "cards/ten_diamonds.bmp", 8);
        m_cards[JACK_DIAMONDS] = Card("Diamonds", "Jack", "cards/jack_diamonds.bmp", 9);
        m_cards[QUEEN_DIAMONDS] = Card("Diamonds", "Queen", "cards/queen_diamonds.bmp", 10);
        m_cards[KING_DIAMONDS] = Card("Diamonds", "King", "cards/king_diamonds.bmp", 11);
        m_cards[ACE_DIAMONDS] = Card("Diamonds", "Ace", "cards/ace_diamonds.bmp", 12);

        m_cards[TWO_HEARTS] = Card("Hearts", "Two", "cards/two_hearts.bmp", 0);
        m_cards[THREE_HEARTS] = Card("Hearts", "Three", "cards/three_hearts.bmp", 1);
        m_cards[FOUR_HEARTS] = Card("Hearts", "Four", "cards/four_hearts.bmp", 2);
        m_cards[FIVE_HEARTS] = Card("Hearts", "Five", "cards/five_hearts.bmp", 3);
        m_cards[SIX_HEARTS] = Card("Hearts", "Six", "cards/six_hearts.bmp", 4);
        m_cards[SEVEN_HEARTS] = Card("Hearts", "Seven", "cards/seven_hearts.bmp", 5);
        m_cards[EIGHT_HEARTS] = Card("Hearts", "Eight", "cards/eight_hearts.bmp", 6);
        m_cards[NINE_HEARTS] = Card("Hearts", "Nine", "cards/nine_hearts.bmp", 7);
        m_cards[TEN_HEARTS] = Card("Hearts", "Ten", "cards/ten_hearts.bmp", 8);
        m_cards[JACK_HEARTS] = Card("Hearts", "Jack", "cards/jack_hearts.bmp", 9);
        m_cards[QUEEN_HEARTS] = Card("Hearts", "Queen", "cards/queen_hearts.bmp", 10);
        m_cards[KING_HEARTS] = Card("Hearts", "King", "cards/king_hearts.bmp", 11);
        m_cards[ACE_HEARTS] = Card("Hearts", "Ace", "cards/ace_hearts.bmp", 12);

        m_cards[TWO_SPADES] = Card("Spades", "Two", "cards/two_spades.bmp", 0);
        m_cards[THREE_SPADES] = Card("Spades", "Three", "cards/three_spades.bmp", 1);
        m_cards[FOUR_SPADES] = Card("Spades", "Four", "cards/four_spades.bmp", 2);
        m_cards[FIVE_SPADES] = Card("Spades", "Five", "cards/five_spades.bmp", 3);
        m_cards[SIX_SPADES] = Card("Spades", "Six", "cards/six_spades.bmp", 4);
        m_cards[SEVEN_SPADES] = Card("Spades", "Seven", "cards/seven_spades.bmp", 5);
        m_cards[EIGHT_SPADES] = Card("Spades", "Eight", "cards/eight_spades.bmp", 6);
        m_cards[NINE_SPADES] = Card("Spades", "Nine", "cards/nine_spades.bmp", 7);
        m_cards[TEN_SPADES] = Card("Spades", "Ten", "cards/ten_spades.bmp", 8);
        m_cards[JACK_SPADES] = Card("Spades", "Jack", "cards/jack_spades.bmp", 9);
        m_cards[QUEEN_SPADES] = Card("Spades", "Queen", "cards/queen_spades.bmp", 10);
        m_cards[KING_SPADES] = Card("Spades", "King", "cards/king_spades.bmp", 11);
        m_cards[ACE_SPADES] = Card("Spades", "Ace", "cards/ace_spades.bmp", 12);
    }

    return m_solver;
}

void Solver::DestroySolver()
{
    if(m_solver)
    {
        delete m_solver;
        delete[] m_cards;
    }

    m_cards = 0;
    m_solver = 0;
}

Card* Solver::GetCards()
{
    return m_cards;
}

Card Solver::FindCard(const Image& image)
{
    for(int i = TWO_CLUBS ; i <= ACE_SPADES ; i++)
    {
        Image other(m_cards[i].GetPath());

        if(image.Compare(other))
            return m_cards[i];
    }

    return Card();
}

std::string Solver::HandForce()
{
    std::vector<Card> cards;

    cards = m_current.RoyalFlush();
    if(cards.size())
        return "Royal Flush";

    cards = m_current.StraightFlush();
    if(cards.size())
    {
        std::sort(cards.begin(), cards.end());
        return "Straight flush " + cards[cards.size() - 1].GetName() + " high";
    }

    cards = m_current.FourOfAKind();
    if(cards.size())
    {
        std::string first = cards[0].GetName();

        if(first == "Six")
            first = "Sixes";
        else
            first += "s";

        return "Four of a kind " + first;
    }

    cards = m_current.FullHouse();
    if(cards.size())
    {
        std::sort(cards.begin(), cards.end());
        std::string first = cards[cards.size() - 1].GetName();
        std::string second = cards[cards.size() - 4].GetName();

        if(first == "Six")
            first += "Sixes";
        else
            first += "s";

        if(second == "Six")
            second = "Sixes";
        else
            second += "s";

        return "FullHouse " + first + " and " + second;
    }

    cards = m_current.Flush();
    if(cards.size())
    {
        std::sort(cards.begin(), cards.end());
        return "Flush " + cards[cards.size() - 1].GetName() + " high";
    }

    cards = m_current.Straight();
    if(cards.size())
    {
        std::sort(cards.begin(), cards.end());
        return "Straight " + cards[cards.size() - 1].GetName() + " high";
    }

    cards = m_current.ThreeOfAKind();
    if(cards.size())
    {
        std::string first = cards[0].GetName();

        if(first == "Six")
            first = "Sixes";
        else
            first += "s";

        return "Three of a kind, " + first;
    }

    cards = m_current.TwoPairs();
    if(cards.size())
    {
        std::sort(cards.begin(), cards.end());
        std::string first = cards[cards.size() - 1].GetName();
        std::string second = cards[cards.size() - 3].GetName();
        if(first == "Six")
            first = "Sixes";
        else
            first += "s";

        if(second == "Six")
            second = "Sixes";
        else
            second += "s";

        return "Two pairs, " + first + " and " + second;
    }

    cards = m_current.OnePair();
    if(cards.size())
    {
        std::sort(cards.begin(), cards.end());
        std::string first = cards[cards.size() - 1].GetName();

        if(first == "Six")
            first = "Sixes";
        else
            first += "s";

        return "One pair of " + first;
    }

    cards = m_current.HighCard();
    if(cards.size())
        return "High card " + m_current.HighCard()[0].GetName();

    return "";
}

void Solver::GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
    UINT num, size;

    Gdiplus::GetImageEncodersSize(&num, &size);
    Gdiplus::ImageCodecInfo* pImageCodecInfo = new Gdiplus::ImageCodecInfo[size];
    GetImageEncoders(num, size, pImageCodecInfo);

    for(int i = 0 ; i < num ; i++)
        if(!wcscmp(pImageCodecInfo[i].MimeType, format))
        {
            *pClsid = pImageCodecInfo[i].Clsid;
            delete pImageCodecInfo;
        }
}

void Solver::BitmapToJpg(HBITMAP hbmpImage, wchar_t* path)
{
    CLSID pngClsid;
    GetEncoderClsid(L"image/bmp", &pngClsid);

    Gdiplus::Bitmap *p_bmp = Gdiplus::Bitmap::FromHBITMAP(hbmpImage, 0);
    p_bmp->Save(path, &pngClsid, 0);

    delete p_bmp;
}

void Solver::Screenshot(int x, int y, int width, int height, wchar_t* path)
{
    Gdiplus::GdiplusStartupInput input;
    ULONG_PTR token;
    GdiplusStartup(&token, &input, 0);

    HDC hdcBase = CreateCompatibleDC(0);

    HDC hdcCurrent = ::GetDC(0);
    HBITMAP bmp = CreateCompatibleBitmap(hdcCurrent, width, height);
    SelectObject(hdcBase, bmp);
    BitBlt(hdcBase, 0, 0, width, height, hdcCurrent, x, y, SRCCOPY);

    DeleteDC(hdcCurrent);
    DeleteDC(hdcBase);

    BitmapToJpg(bmp, path);
    DeleteObject(bmp);
}
