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

#include <iostream>
#include <gtkmm/button.h>
#include "sell.hpp"
#include "window.hpp"

Cafet::Sell::Sell(Cafet::Window& window) : m_window(window) {
	set_border_width(10);

	{
		Gtk::Button* button = Gtk::make_managed<Gtk::Button>("Formule");
		button->set_property("expand", true);
		button->signal_clicked().connect(sigc::mem_fun(*this, &Sell::on_button_formula_clicked));
		attach(*button, 0, 0, 1, 3);
	}

	{
		Gtk::Button* button = Gtk::make_managed<Gtk::Button>("Boisson");
		button->set_property("expand", true);
		button->signal_clicked().connect(sigc::mem_fun(*this, &Sell::on_button_drink_clicked));
		attach(*button, 1, 0, 1, 3);
	}

	{
		Gtk::Button* button = Gtk::make_managed<Gtk::Button>("Supplément");
		button->set_property("expand", true);
		button->signal_clicked().connect(sigc::mem_fun(*this, &Sell::on_button_addon_clicked));
		attach(*button, 2, 0, 1, 3);
	}

	{
		Gtk::Button* button = Gtk::make_managed<Gtk::Button>("Friandise");
		button->set_property("expand", true);
		button->signal_clicked().connect(sigc::mem_fun(*this, &Sell::on_button_food_clicked));
		attach(*button, 3, 0, 1, 2);
	}

	{
		Gtk::Button* button = Gtk::make_managed<Gtk::Button>("Annuler");
		button->set_property("expand", true);
		button->signal_clicked().connect(sigc::mem_fun(*this, &Sell::on_button_cancel_clicked));
		attach(*button, 3, 2);
	}

	show_all_children();
}


Cafet::Sell::~Sell() {}

void Cafet::Sell::on_button_formula_clicked() {
	m_window.sell_formula();
}

void Cafet::Sell::on_button_drink_clicked() {
	m_window.sell_drink();
}

void Cafet::Sell::on_button_addon_clicked() {
	m_window.sell_addon();
}

void Cafet::Sell::on_button_food_clicked() {
	m_window.sell_food();
}

void Cafet::Sell::on_button_cancel_clicked() {
	m_window.home();
}
