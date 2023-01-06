
#include <vector>

#ifdef _WIN32
#include <process.h>
#else
#include <unistd.h>
#endif

#include <cstdlib>

#include "MySDL.h"
#include "json.hpp"
#include "Menu.h"

using namespace std;
using json = nlohmann::json;

Menu* m_mainMenu = nullptr;
Menu* m_currentMenu = nullptr; 
size_t m_currentIndex = 0;
bool m_isRunning = false;

inline SDL_Color checkColor(MySDL& _sdl, auto& _j, const string& _key, const string& _defaultColor) {
    if (_j == nullptr || _j.empty() || !_j.contains(_key))
        return _sdl.hex2SDLColor(_defaultColor);
    
    return _sdl.hex2SDLColor(_j[_key]);
}

void loadMenuData(MySDL& _sdl, auto& _j, Menu* _prevMenu, Button * _PrevButton) {
    if (_j.empty() || !_j.contains("menu"))
        return;

    // Récupérer les couleurs du menu.
    SDL_Color bg = checkColor(_sdl, _j["menu"], "bg_color", BG_COLOR);
    SDL_Color t = checkColor(_sdl, _j["menu"], "t_color", TEXT_COLOR);
    SDL_Color s = checkColor(_sdl, _j["menu"], "s_color", SEL_COLOR);

    // Récupérer le titre du menu.
    string title = _j["menu"]["title"]["text"];

    SDL_Color titleColor = _sdl.hex2SDLColor(TEXT_COLOR);
    if (_j["menu"]["title"].contains("color"))
        titleColor = checkColor(_sdl, _j["menu"]["title"], "color", TEXT_COLOR);

    Menu* menu = new Menu(title, titleColor, bg, t, s);

    if (m_mainMenu == nullptr) {
        m_mainMenu = menu;
        m_currentMenu = menu;
    }

    if (_PrevButton != nullptr)
        _PrevButton->setSubMenu(menu);

    int cpt = 0;
    // Récupérer les boutons du menu.
    for (const auto& button : _j["menu"]["buttons"]) {
        if (button.empty())
            continue;

        if (++cpt > MAX_ITEMS_PER_PAGE)
            break;

        // Récupérer les couleurs du bouton.
        SDL_Color t = checkColor(_sdl, button, "t_color", TEXT_COLOR);
        SDL_Color s = checkColor(_sdl, button, "s_color", SEL_COLOR);

        // Récupérer le texte du bouton et l'action associée.
        string text = button["text"];

        string action = "";
        if (button.contains("action"))
            action = button["action"];

        Button* b = new Button(text, bg, t, s, action, _prevMenu);
        menu->addButton(b);

        // Récupérer le sous-menu.
        if (button.contains("menu"))
            loadMenuData(_sdl, button, menu, b);
    }
}

void unloadMenuData() {
    if (m_mainMenu == nullptr)
        return;

    delete m_mainMenu;
}

bool startAction(string _action) {
    if (_action.empty())
        return false;

#ifdef _WIN32
    int status = system(_action.c_str());
#else
    int status = system(_action.c_str());
#endif

    return true;
}

void checkAction(Button* _button) {
    if (_button == nullptr)
        return;

    Menu* menu = _button->getSubMenu();

    if (menu != nullptr) {
        m_currentMenu = menu;
    }
    else {
        if (_button->getAction()._Equal("back") && _button->getPrevMenu() != nullptr)
            m_currentMenu = _button->getPrevMenu();
        else if (_button->getAction()._Equal("end"))
            m_isRunning = false;
        else
            startAction(_button->getAction());
    }
}

void checkSelection(vector<Button*> _buttons) {
    if (_buttons.empty())
        return;

    size_t size = _buttons.size();

    if (m_currentIndex < 0)
        m_currentIndex = 0;

    if (m_currentIndex > size - 1)
        m_currentIndex = size - 1;

    for (size_t i = 0; i < size; i++)
        _buttons[i]->setSelected(i == m_currentIndex);
}

int main(int argc, char* argv[]) {
    Logger log;

    // Lecture des dimensions de l'écran.
    ScreenSize screenSize = getScreenSize();
    screenSize.height = 480;
    screenSize.width = 640;

    // Initialisation de SDL, TTF et IMG.
    MySDL sdl;
    if (!sdl.init()) {
        return 1;
    }

    if (!sdl.initWindow(screenSize)) {
        return 2;
    }

    // Charger le fichier JSON.
    ifstream input_file(MENU_FILENAME);
    if (!input_file.is_open()) {
        log.write("Erreur : Impossible d'ouvrir le fichier", MENU_FILENAME);

        return 3;
    }

    json j;

    try {
        input_file >> j;

        loadMenuData(sdl, j, nullptr, nullptr);

        input_file.close();
    }
    catch (nlohmann::json::other_error& e) {
        log.write("Erreur :", e.what());

        return 4;
    }
    catch (nlohmann::json::out_of_range& e) {
        log.write("Erreur :", e.what());

        return 4;
    }
    catch (nlohmann::json::type_error& e) {
        log.write("Erreur :", e.what());

        return 4;
    }
    catch (nlohmann::json::invalid_iterator& e) {
        log.write("Erreur :", e.what());

        return 4;
    }
    catch (nlohmann::json::parse_error& e) {
        log.write("Erreur :", e.what());

        return 4;
    }
    catch (nlohmann::json::exception& e) {
        log.write("Erreur :", e.what());

        return 4;
    }
    catch (...) {
        log.write("Erreur : ?");

        return 4;
    }

    // Charger l'image PNG
    SDL_Texture* background = nullptr;
    if (j.contains("menu") && j["menu"].contains("bg_image")) {
        string file = j["menu"]["bg_image"];
        SDL_Surface* surface = IMG_Load(file.c_str());
        if (surface == nullptr)
            log.write("Erreur : Création de l'arrière-plan : ", SDL_GetError());
        else {
            background = SDL_CreateTextureFromSurface(sdl.getRenderer(), surface);
            SDL_FreeSurface(surface);
        }
    }

    // Boucle principale du programme.
    m_isRunning = true;
    while (m_isRunning) {
        // Gestion des évènements
        SDL_Event e;
        while (SDL_PollEvent(&e)) {

            Button* button = nullptr;
            Menu* menu = nullptr;
            vector<Button*> buttons = m_currentMenu->getButtons();

            switch (e.type) {
            case SDL_QUIT:

                m_isRunning = false;

                break;

                // Gestion de la position de la souris.
            case SDL_MOUSEMOTION:

                int x, y;
                SDL_GetMouseState(&x, &y);

                for (const auto& button : m_currentMenu->getButtons()) {
                    SDL_Rect r = button->getRect();

                    if (x >= r.x && x <= r.x + r.w && y >= r.y && y <= r.y + r.h) {
                        button->setSelected(true);
                    }
                    else {
                        button->setSelected(false);
                    }
                }

                break;

                // Gestion des événements de la souris.
            case SDL_MOUSEBUTTONDOWN:

                // Vérificatie si l'utilisateur a cliqué sur un bouton gauche
                if (e.button.button == SDL_BUTTON_LEFT) {
                    int x, y;
                    SDL_GetMouseState(&x, &y);

                    for (const auto& button : m_currentMenu->getButtons()) {
                        SDL_Rect r = button->getRect();

                        if (x >= r.x && x <= r.x + r.w && y >= r.y && y <= r.y + r.h) {
                            
                            checkAction(button);

                            break;
                        }
                    }
                }

                break;

                // Gestion des événements du joystick.
            case SDL_JOYAXISMOTION:

                if (e.jaxis.axis == 1) {
                    if (e.jaxis.value < 0)
                        m_currentIndex--;
                    else if (e.jaxis.value > 0)
                        m_currentIndex++;

                    checkSelection(buttons);
                }

                break;

            case SDL_JOYBUTTONDOWN:

                checkAction(buttons[m_currentIndex]);

                break;

                // Gestion des événements du clavier.
            case SDL_KEYDOWN:

                switch (e.key.keysym.sym) {
                case SDLK_q:
                    m_isRunning = false;

                    break;

                case SDLK_UP:

                    m_currentIndex--;

                    checkSelection(buttons);

                    break;

                case SDLK_DOWN:

                    m_currentIndex++;

                    checkSelection(buttons);

                    break;

                case SDLK_KP_ENTER:
                case SDLK_RETURN:

                    checkAction(buttons[m_currentIndex]);

                    break;
                }

                break;
            }

        }

        // Nettoyage de l'écran.
        SDL_Color bg = m_currentMenu->getBgColor();
        SDL_SetRenderDrawColor(sdl.getRenderer(), bg.r, bg.g, bg.b, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(sdl.getRenderer());

        // Dessiner l'image en arrière-plan.
        if (background != nullptr)
            SDL_RenderCopy(sdl.getRenderer(), background, NULL, NULL);

        // Affichage du titre.
        SDL_Surface* surface = TTF_RenderUTF8_Blended(sdl.getTitleFont(), m_currentMenu->getTitle().c_str(), m_currentMenu->getTitleColor());
        SDL_Texture* texture = SDL_CreateTextureFromSurface(sdl.getRenderer(), surface);

        int y = (screenSize.height - ((surface->h + 10) * ((int)m_currentMenu->getButtons().size() + 1))) / 2;

        SDL_Rect rect;
        rect.x = (screenSize.width - surface->w) / 2;
        rect.y = y;
        rect.w = surface->w;
        rect.h = surface->h;

        y += (surface->h + 10);

        SDL_RenderCopy(sdl.getRenderer(), texture, NULL, &rect);
        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface);

        // Affichage des boutons du menu
        for (const auto& button : m_currentMenu->getButtons()) {

            SDL_Surface* surface = TTF_RenderUTF8_Blended(sdl.getFont(), button->getText().c_str(), button->isSelected() ? button->getSelectedColor() : button->getTextColor());
            SDL_Texture* texture = SDL_CreateTextureFromSurface(sdl.getRenderer(), surface);

            SDL_Rect rect;
            rect.x = (screenSize.width - surface->w) / 2;
            rect.y = y;
            rect.w = surface->w;
            rect.h = surface->h;

            button->setRect(rect);

            y += (surface->h + 10);

            SDL_RenderCopy(sdl.getRenderer(), texture, NULL, &rect);
            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface);
        }

        // Mise à jour de l'écran
        SDL_RenderPresent(sdl.getRenderer());
    }

    if (background != nullptr)
        SDL_DestroyTexture(background);

    unloadMenuData();

    return 0;
}
