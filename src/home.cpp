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
#include <gtkmm/frame.h>
#include <gtkmm/button.h>
#include "home.hpp"
#include "window.hpp"

Cafet::Home::Home(Cafet::Window& window) : m_window(window) {
	set_border_width(10);

	{
		Gtk::Frame* frame = Gtk::make_managed<Gtk::Frame>("Historique des trans-actions");
		frame->set_property("expand", true);
		attach(*frame, 0, 0, 2, 2);
	}

	{
		Gtk::Button* button = Gtk::make_managed<Gtk::Button>("Vente d'une consommation");
		button->set_property("expand", true);
		button->signal_clicked().connect(sigc::mem_fun(*this, &Home::on_button_customer_clicked));
		attach(*button, 2, 0);
	}

	{
		Gtk::Button* button = Gtk::make_managed<Gtk::Button>("Achat au magasin");
		button->set_property("expand", true);
		button->signal_clicked().connect(sigc::mem_fun(*this, &Home::on_button_shop_clicked));
		attach(*button, 2, 1);
	}

	show_all_children();
}


Cafet::Home::~Home() {}

void Cafet::Home::on_button_customer_clicked() {
	m_window.sell();
}

void Cafet::Home::on_button_shop_clicked() {
	std::cout << "Shop placeholder.\n";
}
