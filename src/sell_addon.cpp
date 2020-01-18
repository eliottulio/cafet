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
#include <cmath>
#include <ctime>
#include <fstream>
#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/grid.h>
#include "data_structures.hpp"
#include "sell_addon.hpp"
#include "window.hpp"

Cafet::Sell_addon::Sell_addon(Cafet::Window& window) : m_window(window) {
	set_border_width(10);

	{
		addon_selection = Gtk::Grid();

		int height = int(std::sqrt(map_of_addons.size()));
		int width = int(double(map_of_addons.size()) / height + 0.5);

		std::size_t i = 0;
		for (const auto& elem : map_of_addons) {
			std::size_t x = i % width;
			std::size_t y = i / width;

			Gtk::Button* button = Gtk::make_managed<Gtk::Button>(elem.first);
			button->set_property("expand", true);
			button->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &Sell_addon::on_addon_button_clicked), elem.second));
			addon_selection.attach(*button, x, y);
			i++;
		}
		{
			Gtk::Button* button = Gtk::make_managed<Gtk::Button>("Annuler");
			button->set_property("expand", true);
			button->signal_clicked().connect(sigc::mem_fun(*this, &Sell_addon::on_addon_cancel_button_clicked));
			addon_selection.attach(*button, width - 1, height);
		}
	}

	{
		confirmation = Gtk::Grid();

		{
			Gtk::Button* button = Gtk::make_managed<Gtk::Button>("Confirmer");
			button->set_property("expand", true);
			button->signal_clicked().connect(sigc::mem_fun(*this, &Sell_addon::on_confirm_confirm_button_clicked));
			confirmation.attach(*button, 0, 0);
		}
		{
			Gtk::Button* button = Gtk::make_managed<Gtk::Button>("Annuler");
			button->set_property("expand", true);
			button->signal_clicked().connect(sigc::mem_fun(*this, &Sell_addon::on_confirm_cancel_button_clicked));
			confirmation.attach(*button, 1, 0);
		}
	}

	add(addon_selection);
	show_all_children();
}


Cafet::Sell_addon::~Sell_addon() {}

void Cafet::Sell_addon::on_addon_button_clicked(const Cafet::Addon& addon) {
	current_addon = addon.name;
	std::cout << "Addon: " << addon.name << '\n';
	remove();
	add(confirmation);
	show_all_children();

	std::size_t addon_price = addon.price;
	using std::to_string;
	((Gtk::Button*)confirmation.get_child_at(0, 0))->set_label("Confirm (" + *current_addon + " ("
																														+ to_string(addon_price / 100) + '.' + to_string(addon_price % 100) + "€))");
}
void Cafet::Sell_addon::on_addon_cancel_button_clicked() {
	m_window.sell();
}

void Cafet::Sell_addon::on_confirm_confirm_button_clicked() {
	std::ofstream drinks_out("transactions/addons.txt", std::fstream::ios_base::app);
	std::size_t price = map_of_addons.at(*current_addon).price;
	drinks_out << std::time(0) << "; " << *current_addon << "; " << price / 100 << '.' << price % 100 << '\n';
	on_confirm_cancel_button_clicked();
	m_window.home();
}
void Cafet::Sell_addon::on_confirm_cancel_button_clicked() {
	remove();
	add(addon_selection);
	show_all_children();
}
