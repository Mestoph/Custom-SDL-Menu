#include "Button.h"

Button::Button(string _text, SDL_Color _bgColor, SDL_Color _textColor, SDL_Color _selectedColor, string _action, Menu* _prevMenu) {
	this->m_text = _text;
	this->m_action = _action;

	this->m_bgColor = _bgColor;
	this->m_tColor = _textColor;
	this->m_sColor = _selectedColor;

	this->m_prevMenu = _prevMenu;
	this->m_subMenu = nullptr;

	this->m_selected = false;
}

Button::~Button() {
	if (this->m_subMenu != nullptr)
		delete this->m_subMenu;
}

const SDL_Color& Button::getBgColor() const {
	return this->m_bgColor;
}

const SDL_Color& Button::getTextColor() const {
	return this->m_tColor;
}

const SDL_Color& Button::getSelectedColor() const {
	return this->m_sColor;
}

const string& Button::getText() const {
	return this->m_text;
}

const string& Button::getAction() const {
	return this->m_action;
}

Menu* Button::getPrevMenu() const {
	return this->m_prevMenu;
}

Menu *Button::getSubMenu() const {
	return this->m_subMenu;
}

const void Button::setSubMenu(Menu* _subMenu) {
	if (_subMenu == nullptr)
		return;

	this->m_subMenu = _subMenu;
}

const SDL_Rect Button::getRect() const {
	return this->m_rect;
}

const void Button::setRect(SDL_Rect _rect) {
	this->m_rect = _rect;
}

const bool Button::isSelected() const {
	return this->m_selected;
}

const void Button::setSelected(bool _selected) {
	this->m_selected = _selected;
}