#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include <SDL.h>

#include "Menu.h"

using namespace std;

class Menu;

class Button {
public:
	Button(string _text, SDL_Color _bgColor, SDL_Color _textColor, SDL_Color _selectedColor, string _action, Menu* _prevMenu);
	~Button();

	const SDL_Color& getBgColor() const;
	const SDL_Color& getTextColor() const;
	const SDL_Color& getSelectedColor() const;
	const string& getText() const;
	const string& getAction() const;
	Menu* getSubMenu() const;
	Menu* getPrevMenu() const;
	const void setSubMenu(Menu* _subMenu);
	const SDL_Rect getRect() const;
	const void setRect(SDL_Rect _rect);
	const bool isSelected() const;
	const void setSelected(bool _selected);
private:
	SDL_Color m_bgColor;
	SDL_Color m_tColor;
	SDL_Color m_sColor;
	SDL_Rect m_rect;
	string m_text;
	string m_action;
	Menu* m_prevMenu;
	Menu* m_subMenu;
	bool m_selected;
};

#endif
