#ifndef MySDL_H
#define MySDL_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "Logger.h"
#include "screensize.h"

class MySDL
{
public:
    MySDL();
    ~MySDL();
    bool init();
    bool initWindow(ScreenSize& _screenSize);
    SDL_Renderer* getRenderer();
    TTF_Font* getFont();
    TTF_Font* getTitleFont();
    static SDL_Color hex2SDLColor(const string _hexColor);
    static SDL_Color hex2SDLColor(const string _hexColor, const SDL_Color _sdlColor);

private:
    void close();
    void closeWindow();

    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    TTF_Font* m_font;
    TTF_Font* m_titleFont;
    SDL_Texture* m_texture;
};

#endif