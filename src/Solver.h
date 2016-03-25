#ifndef SOLVER
#define SOLVER

#include "Card.h"
#include "Image.h"
#include <vector>
#include "Hand.h"
#include <windows.h>
#include <gdiplus.h>

enum
{
    TWO_CLUBS,
    THREE_CLUBS,
    FOUR_CLUBS,
    FIVE_CLUBS,
    SIX_CLUBS,
    SEVEN_CLUBS,
    EIGHT_CLUBS,
    NINE_CLUBS,
    TEN_CLUBS,
    JACK_CLUBS,
    QUEEN_CLUBS,
    KING_CLUBS,
    ACE_CLUBS,

    TWO_DIAMONDS,
    THREE_DIAMONDS,
    FOUR_DIAMONDS,
    FIVE_DIAMONDS,
    SIX_DIAMONDS,
    SEVEN_DIAMONDS,
    EIGHT_DIAMONDS,
    NINE_DIAMONDS,
    TEN_DIAMONDS,
    JACK_DIAMONDS,
    QUEEN_DIAMONDS,
    KING_DIAMONDS,
    ACE_DIAMONDS,

    TWO_HEARTS,
    THREE_HEARTS,
    FOUR_HEARTS,
    FIVE_HEARTS,
    SIX_HEARTS,
    SEVEN_HEARTS,
    EIGHT_HEARTS,
    NINE_HEARTS,
    TEN_HEARTS,
    JACK_HEARTS,
    QUEEN_HEARTS,
    KING_HEARTS,
    ACE_HEARTS,

    TWO_SPADES,
    THREE_SPADES,
    FOUR_SPADES,
    FIVE_SPADES,
    SIX_SPADES,
    SEVEN_SPADES,
    EIGHT_SPADES,
    NINE_SPADES,
    TEN_SPADES,
    JACK_SPADES,
    QUEEN_SPADES,
    KING_SPADES,
    ACE_SPADES
};

class Solver
{
    private :
        static Solver* m_solver;
        static Card* m_cards;
        Hand m_current;
        void GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
        void BitmapToJpg(HBITMAP hbmpImage, wchar_t* path);

    public :
        static Solver* GetSolver();
        static void DestroySolver();
        Card* GetCards();
        Card FindCard(const Image& image);
        void Push(Card card) {m_current.Push(card);}
        std::string HandForce();
        Hand GetCurrentHand() {return m_current;};
        void Screenshot(int x = 0, int y = 0, int width = GetSystemMetrics(SM_CXSCREEN),
                        int height = GetSystemMetrics(SM_CYSCREEN), wchar_t* path = L"screen.bmp");
        void Clear() {m_current.Clear();}
};

#endif
