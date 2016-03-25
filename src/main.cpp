#include "Image.h"
#include "Pixel.h"
#include "Card.h"
#include "Solver.h"
#include "Hand.h"
#include <ctime>
#include <sstream>

#include <cstdlib>
#include <SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>

#define WINDOW_WIDTH 808
#define WINDOW_HEIGHT 584

#define CARD_WIDTH 50
#define CARD_HEIGHT 36 // originally 70

#define TABLE_LEFT_GAP 271
#define TABLE_TOP_GAP 208

#define HAND_LEFT_GAP 354
#define HAND_TOP_GAP 368 // 367 for 6 players

#define TABLE_GAP 4

#define DELAY 500

std::string intToString(int i) {
     std::ostringstream oss;
     oss << i;
     return oss.str();
}

bool operator!=(const RECT& rectA, const RECT& rectB)
{
    if(rectA.bottom == rectB.bottom && rectA.left == rectB.left && rectA.right == rectB.right && rectA.top == rectB.top)
        return false;

    return true;
}

void WriteLine(const std::string& line, int y, SDL_Surface *screen)
{
    SDL_Color color = {255, 255, 255};
    int width, height;
    SDL_Rect rect;
    TTF_Font *font = TTF_OpenFont("fonts/times.ttf", 17);

    TTF_SizeText(font, line.c_str(), &width, &height);
    rect.x = ((screen->w - width) / 2);
    rect.y = y;

    SDL_Surface *text = TTF_RenderText_Blended(font, line.c_str(), color);
    SDL_BlitSurface(text, 0 ,screen, &rect);
    SDL_FreeSurface(text);

    TTF_CloseFont(font);
}

int main (int argc, char** argv)
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    atexit(SDL_Quit);

    SDL_Surface* screen = SDL_SetVideoMode((CARD_WIDTH + 10) * 7 - 10, 100, 24, SDL_HWSURFACE|SDL_DOUBLEBUF);

    SDL_WM_SetCaption("HandForce 1.0.0 - 2016 - Author : Hachem Benyahia", 0);
    SDL_Surface *icon = IMG_Load("icons/icon.png");
    SDL_WM_SetIcon(icon, 0);

    std::string lines[2];

    bool done = false;

    Solver *solver = Solver::GetSolver();

    RECT rect, rectTmp;
    HWND window, windowTmp;

    window = GetForegroundWindow();
    GetWindowRect(window, &rect);

    char title[256], titleTmp[256];
    GetWindowText(window, title, sizeof(title));
    int width, height;
    double previousTime = std::clock() - DELAY, currentTime;

    while(!done)
    {
        SDL_Event event;

        while(SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    done = true;
                break;
            }
        }

        currentTime = clock();
        window = GetForegroundWindow();
        GetWindowRect(window, &rect);

        if((currentTime - previousTime) > DELAY)
        {
            windowTmp = GetForegroundWindow();
            GetWindowRect(windowTmp, &rectTmp);
            GetWindowText(windowTmp, titleTmp, sizeof(titleTmp));

            window = windowTmp;
            rect = rectTmp;
            strcpy(title, titleTmp);

            width = rect.right - rect.left;
            height = rect.bottom - rect.top;

            wchar_t path[7][30];
            for(int k = 0 ; k < 7 ; k++)
                swprintf(path[k], L"tmp/card%d.bmp", k);

            solver->Screenshot(rect.left + HAND_LEFT_GAP, rect.top + HAND_TOP_GAP, CARD_WIDTH, CARD_HEIGHT, path[0]);

            solver->Screenshot(rect.left + HAND_LEFT_GAP + CARD_WIDTH - 2,
                               rect.top + HAND_TOP_GAP, CARD_WIDTH, CARD_HEIGHT, path[1]);

            solver->Screenshot(rect.left + TABLE_LEFT_GAP, rect.top + TABLE_TOP_GAP, CARD_WIDTH, CARD_HEIGHT, path[2]);

            solver->Screenshot(rect.left + TABLE_LEFT_GAP + CARD_WIDTH + TABLE_GAP,
                               rect.top + TABLE_TOP_GAP, CARD_WIDTH, CARD_HEIGHT, path[3]);

            solver->Screenshot(rect.left + TABLE_LEFT_GAP + 2 * (CARD_WIDTH + TABLE_GAP),
                               rect.top + TABLE_TOP_GAP, CARD_WIDTH, CARD_HEIGHT, path[4]);

            solver->Screenshot(rect.left + TABLE_LEFT_GAP + 3 * (CARD_WIDTH + TABLE_GAP),
                               rect.top + TABLE_TOP_GAP, CARD_WIDTH, CARD_HEIGHT, path[5]);

            solver->Screenshot(rect.left + TABLE_LEFT_GAP + 4 * (CARD_WIDTH + TABLE_GAP),
                               rect.top + TABLE_TOP_GAP, CARD_WIDTH, CARD_HEIGHT, path[6]);

            solver->Clear();
            std::cout << std::endl;
            for(int k = 0 ; k < 7 ; k++)
            {
                std::wstring ws(path[k]);
                std::string file(ws.begin(), ws.end());

                Image image(file);

                Card card = solver->FindCard(image);
                if(card.GetName() != "")
                {
                    std::cout << card << std::endl;
                    solver->Push(card);
                }

                if(width != WINDOW_WIDTH || height != WINDOW_HEIGHT)
                {
                    lines[0] = "Incorrect dimensions : window must be " + intToString(WINDOW_WIDTH) + " x " +
                    intToString(WINDOW_HEIGHT);

                    lines[1] = "Current dimensions : " + intToString(width) + " x " +
                    intToString(height);
                }
                else
                {
                    lines[0] = solver->HandForce();
                    lines[1] = "";
                }
            }

            previousTime = currentTime;
        }

        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

        for(int i = 0 ; i < 2 ; i++)
            WriteLine(lines[i], 20 * i + 30, screen);

        SDL_Flip(screen);
    }

    Solver::DestroySolver();

    SDL_FreeSurface(icon);

    TTF_Quit();
    SDL_Quit();

    return 0;
}

/*
int main (int argc, char** argv)
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    atexit(SDL_Quit);

    SDL_Surface* screen = SDL_SetVideoMode((CARD_WIDTH + 10) * 7 - 10, 400, 24, SDL_HWSURFACE|SDL_DOUBLEBUF);

    SDL_WM_SetCaption("HandForce - 2016", 0);
    SDL_Surface *icon = IMG_Load("icons/icon.png");
    SDL_WM_SetIcon(icon, 0);

    std::string lines[2];

    SDL_Surface* cards[7];
    SDL_Rect cardsPositions[7];

    cardsPositions[0].x = 0;
    cardsPositions[0].y = 50;

    for(int i = 1 ; i < 7 ; i++)
    {
        cardsPositions[i].x = (CARD_WIDTH + 10) * i;
        cardsPositions[i].y = 50;
    }

    bool done = false;

    Solver *solver = Solver::GetSolver();

    RECT rect, rectTmp;
    HWND window, windowTmp;

    window = GetForegroundWindow();
    GetWindowRect(window, &rect);

    char title[256], titleTmp[256];
    GetWindowText(window, title, sizeof(title));

    int width, height;

    double previousTime = std::clock() - DELAY, currentTime;

    while(!done)
    {
        SDL_Event event;

        while(SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    done = true;
                break;

                case SDL_KEYDOWN:
                {
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        done = true;
                    break;
                }
            }
        }

        currentTime = clock();
        window = GetForegroundWindow();
        GetWindowRect(window, &rect);

        if((currentTime - previousTime) > DELAY)
        {
            windowTmp = GetForegroundWindow();
            GetWindowRect(windowTmp, &rectTmp);
            GetWindowText(windowTmp, titleTmp, sizeof(titleTmp));

            window = windowTmp;
            rect = rectTmp;
            strcpy(title, titleTmp);

            width = rect.right - rect.left;
            height = rect.bottom - rect.top;

            wchar_t path[7][30];
            for(int k = 0 ; k < 7 ; k++)
                swprintf(path[k], L"tmp/card%d.bmp", k);

            solver->Screenshot(rect.left + HAND_LEFT_GAP, rect.top + HAND_TOP_GAP, CARD_WIDTH, CARD_HEIGHT, path[0]);

            solver->Screenshot(rect.left + HAND_LEFT_GAP + CARD_WIDTH - 2,
                               rect.top + HAND_TOP_GAP, CARD_WIDTH, CARD_HEIGHT, path[1]);

            solver->Screenshot(rect.left + TABLE_LEFT_GAP, rect.top + TABLE_TOP_GAP, CARD_WIDTH, CARD_HEIGHT, path[2]);

            solver->Screenshot(rect.left + TABLE_LEFT_GAP + CARD_WIDTH + TABLE_GAP,
                               rect.top + TABLE_TOP_GAP, CARD_WIDTH, CARD_HEIGHT, path[3]);

            solver->Screenshot(rect.left + TABLE_LEFT_GAP + 2 * (CARD_WIDTH + TABLE_GAP),
                               rect.top + TABLE_TOP_GAP, CARD_WIDTH, CARD_HEIGHT, path[4]);

            solver->Screenshot(rect.left + TABLE_LEFT_GAP + 3 * (CARD_WIDTH + TABLE_GAP),
                               rect.top + TABLE_TOP_GAP, CARD_WIDTH, CARD_HEIGHT, path[5]);

            solver->Screenshot(rect.left + TABLE_LEFT_GAP + 4 * (CARD_WIDTH + TABLE_GAP),
                               rect.top + TABLE_TOP_GAP, CARD_WIDTH, CARD_HEIGHT, path[6]);

            solver->Clear();
            for(int k = 0 ; k < 7 ; k++)
            {
                SDL_FreeSurface(cards[k]);

                std::wstring ws(path[k]);
                std::string file(ws.begin(), ws.end());

                Image image(file);

                char path[7][30];
                sprintf(path[k], "cards/null_card%d.bmp", k);
                cards[k] = SDL_LoadBMP(path[k]);

                Card card = solver->FindCard(image);
                if(card.GetName() != "")
                {
                    solver->Push(card);
                    cards[k] = SDL_LoadBMP(card.GetPath().c_str());
                }

                if(width != WINDOW_WIDTH || height != WINDOW_HEIGHT)
                {
                    lines[0] = "Incorrect dimensions : window must be " + intToString(WINDOW_WIDTH) + " x " +
                    intToString(WINDOW_HEIGHT);

                    lines[1] = "Current dimensions : " + intToString(width) + " x " +
                    intToString(height);
                }
                else
                {
                    lines[0] = solver->HandForce();
                    lines[1] = "";
                }
            }

            previousTime = currentTime;
        }

        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

        WriteLine("Current cards :", 14, screen);

        for(int i = 0 ; i < 7 ; i++)
            SDL_BlitSurface(cards[i], 0, screen, &cardsPositions[i]);

        WriteLine("Current Hand : ", 100, screen);

        for(int i = 0 ; i < 2 ; i++)
            WriteLine(lines[i], 20 * i + 300, screen);

        SDL_Flip(screen);
    }

    Solver::DestroySolver();

    for(int i = 0 ; i < 7 ; i++)
        SDL_FreeSurface(cards[i]);

    SDL_FreeSurface(icon);

    TTF_Quit();
    SDL_Quit();

    return 0;
}
*/
