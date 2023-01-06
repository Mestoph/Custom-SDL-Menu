#include "MySDL.h"

MySDL::MySDL() {
    this->m_window = nullptr;
    this->m_renderer = nullptr;
    this->m_font = nullptr;
    this->m_titleFont = nullptr;
    this->m_texture = nullptr;
}

MySDL::~MySDL() {
    this->closeWindow();
    this->close();
}

// Initialisation de SDL, TTF et IMG.
bool MySDL::init() {
    Logger log;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0) {
        log.write("Erreur : Initialisation de SDL : ", SDL_GetError());

        return false;
    }

    if (TTF_Init() < 0) {
        log.write("Erreur : Initialisation de TTF : ", TTF_GetError());

        return false;
    }

    int flags = IMG_INIT_PNG | IMG_INIT_JPG;
    if ((IMG_Init(flags) & flags) != flags) {
        log.write("Erreur : Initialisation de IMG : ", IMG_GetError());

        return false;
    }

    return true;
}

// Fermeture des bibliothèques SDL, TTF et IMG.
void MySDL::close() {
    Logger log;

    log.write("Fermeture des bibliothèques SDL, TTF et IMG.");

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

// Création de la fenêtre, renderer et font.
bool MySDL::initWindow(ScreenSize& _screenSize) {
    Logger log;

    // Création de la fenêtre.
    this->m_window = SDL_CreateWindow("Custom Menu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _screenSize.width, _screenSize.height, SDL_WINDOW_SHOWN);
    if (!this->m_window) {
        log.write("Erreur : Création de la fenêtre : ", SDL_GetError());

        return false;
    }

    // Création du renderer
    this->m_renderer = SDL_CreateRenderer(this->m_window, -1, SDL_RENDERER_ACCELERATED);
    if (!this->m_renderer) {
        log.write("Erreur : Création du renderer : ", SDL_GetError());

        SDL_DestroyWindow(this->m_window);

        return false;
    }

    // Chargement de la police de caractères.
    this->m_font = TTF_OpenFont("arial.ttf", 20);
    if (!this->m_font) {
        log.write("Erreur : Chargement de la police de caractères : ", TTF_GetError());

        SDL_DestroyRenderer(this->m_renderer);
        SDL_DestroyWindow(this->m_window);

        return false;
    }

    this->m_titleFont = TTF_OpenFont("arial.ttf", 30);
    if (!this->m_titleFont) {
        log.write("Erreur : Chargement de la police de caractères : ", TTF_GetError());

        SDL_DestroyRenderer(this->m_renderer);
        SDL_DestroyWindow(this->m_window);
        TTF_CloseFont(this->m_font);

        return false;
    }

    return true;
}

// Liberation de la mémoire.
void MySDL::closeWindow() {
    Logger log;

    log.write("Liberation de la mémoire.");

    if (this->m_font) {
        TTF_CloseFont(this->m_font);
    }

    if (this->m_titleFont) {
        TTF_CloseFont(this->m_titleFont);
    }

    if (this->m_renderer) {
        SDL_DestroyRenderer(this->m_renderer);
    }

    if (this->m_window) {
        SDL_DestroyWindow(this->m_window);
    }
}

SDL_Renderer* MySDL::getRenderer() {
    return this->m_renderer;
}

TTF_Font* MySDL::getFont() {
    return this->m_font;
}

TTF_Font* MySDL::getTitleFont() {
    return this->m_titleFont;
}

SDL_Color MySDL::hex2SDLColor(const string _hexColor)
{
    return hex2SDLColor(_hexColor, SDL_Color{ 0, 0, 0 });
}

SDL_Color MySDL::hex2SDLColor(const string _hexColor, const SDL_Color _sdlColor) {
    Logger log;

    // Vérifiez que la chaîne de couleur hexadécimale est de la forme "#RRGGBB".
    if (_hexColor.length() != 7 || _hexColor[0] != '#') {
        log.write("Erreur : la couleur hexadécimale doit être de la forme #RRGGBB.");
        
        return _sdlColor;
    }

    // Convertissez la chaîne en entier.
    unsigned int color = 0;
    for (int i = 1; i < 7; ++i) {
        char c = _hexColor[i];

        if (c >= '0' && c <= '9') {
            color = (color << 4) | (c - '0');
        }
        else if (c >= 'A' && c <= 'F') {
            color = (color << 4) | (c - 'A' + 10);
        }
        else if (c >= 'a' && c <= 'f') {
            color = (color << 4) | (c - 'a' + 10);
        }
        else {
            log.write("Erreur : la couleur hexadécimale contient des caractères non valides.");

            return _sdlColor;
        }
    }

    // Créez et renvoyez une structure SDL_Color
    SDL_Color sdl_color;
    // sdl_color.a = (color >> 24) & 0xff;
    sdl_color.r = (color >> 16) & 0xff;
    sdl_color.g = (color >> 8) & 0xff;
    sdl_color.b = color & 0xff;

    return sdl_color;
}
