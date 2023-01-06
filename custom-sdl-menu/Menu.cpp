#include "Menu.h"

Menu::Menu(string _title, SDL_Color _titleColor, SDL_Color _bgColor, SDL_Color _textColor, SDL_Color _selectedColor) {
	this->m_title = _title;
	this->m_titleColor = _titleColor;

	this->m_bgColor = _bgColor;
	this->m_tColor = _textColor;
	this->m_sColor = _selectedColor;

	this->m_buttons = {};
}

Menu::~Menu() {
	for (auto& button : this->m_buttons) {
		if (button->getSubMenu() != nullptr)
			delete button->getSubMenu();
	}

	this->m_buttons.clear();
}

const SDL_Color& Menu::getBgColor() const {
	return this->m_bgColor;
}

const SDL_Color& Menu::getTextColor() const {
	return this->m_tColor;
}

const SDL_Color& Menu::getSelectedColor() const {
	return this->m_sColor;
}

const SDL_Color& Menu::getTitleColor() const {
	return this->m_titleColor;
}

const string& Menu::getTitle() const {
	return this->m_title;
}

const vector<Button*>& Menu::getButtons() const {
	return this->m_buttons;
}

const void Menu::addButton(Button* _button) {
	if (_button == nullptr)
		return;

	this->m_buttons.push_back(_button);
}

