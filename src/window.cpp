// Copyright © 2019, Amelia Coutard
//
// This file is part of Cafet.
//
// Cafet is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Cafet is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Cafet.  If not, see <https://www.gnu.org/licenses/>.

#include "window.hpp"
#include "home.hpp"
#include "sell.hpp"
#include "sell_drink.hpp"
#include "sell_addon.hpp"
#include "sell_food.hpp"
#include "sell_formula.hpp"

Cafet::Window::Window() {

	Cafet::Home* home = Gtk::make_managed<Cafet::Home>(*this);
	m_stack.add(*home, "home");

	Cafet::Sell* sell = Gtk::make_managed<Cafet::Sell>(*this);
	m_stack.add(*sell, "sell");

	Cafet::Sell_drink* sell_drink = Gtk::make_managed<Cafet::Sell_drink>(*this);
	m_stack.add(*sell_drink, "sell drink");

	Cafet::Sell_addon* sell_addon = Gtk::make_managed<Cafet::Sell_addon>(*this);
	m_stack.add(*sell_addon, "sell addon");

	Cafet::Sell_food* sell_food = Gtk::make_managed<Cafet::Sell_food>(*this);
	m_stack.add(*sell_food, "sell food");

	Cafet::Sell_formula* sell_formula = Gtk::make_managed<Cafet::Sell_formula>(*this);
	m_stack.add(*sell_formula, "sell formula");


	m_stack.set_visible_child("home");
	add(m_stack);
	show_all_children();
}

Cafet::Window::~Window() {}

void Cafet::Window::home() {
	m_stack.set_visible_child("home");
}

void Cafet::Window::sell() {
	m_stack.set_visible_child("sell");
}

void Cafet::Window::sell_drink() {
	m_stack.set_visible_child("sell drink");
}

void Cafet::Window::sell_addon() {
	m_stack.set_visible_child("sell addon");
}

void Cafet::Window::sell_food() {
	m_stack.set_visible_child("sell food");
}

void Cafet::Window::sell_formula() {
	m_stack.set_visible_child("sell formula");
}
