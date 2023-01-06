#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>
#include <SDL.h>

#include "Button.h"

using namespace std;

class Button;

class Menu {
public:
	Menu(string _title, SDL_Color _titleColor, SDL_Color _bgColor, SDL_Color _textColor, SDL_Color _selectedColor);
	~Menu();

	const SDL_Color& getBgColor() const;
	const SDL_Color& getTextColor() const;
	const SDL_Color& getSelectedColor() const;
	const SDL_Color& getTitleColor() const;
	const string& getTitle() const;
	const vector<Button*>& getButtons() const;
	const void addButton(Button* _button);
private:
	SDL_Color m_bgColor;
	SDL_Color m_tColor;
	SDL_Color m_sColor;
	SDL_Color m_titleColor;
	string m_title;
	vector<Button*> m_buttons;
};

#endif
