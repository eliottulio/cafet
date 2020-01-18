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
#include <algorithm>
#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/grid.h>
#include "data_structures.hpp"
#include "sell_formula.hpp"
#include "window.hpp"

Cafet::Sell_formula::Sell_formula(Cafet::Window& window) : m_window(window) {
	set_border_width(10);

	{
		std::unordered_map<std::string, Drink> new_map_of_drinks;
		for (const auto& elem : map_of_drinks)
			if (elem.second.default_size.value_or(Drink_size('L', 0)).name == 'L')
				new_map_of_drinks.insert(std::make_pair(elem.first, elem.second));

		drink_selection = Gtk::Grid();

		int height = int(std::sqrt(new_map_of_drinks.size()));
		int width = int(double(new_map_of_drinks.size()) / height + 0.5);

		std::size_t i = 0;
		for (const auto& elem : new_map_of_drinks) {
			std::size_t x = i % width;
			std::size_t y = i / width;

			Gtk::Button* button = Gtk::make_managed<Gtk::Button>(elem.first);
			button->set_property("expand", true);
			button->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &Sell_formula::on_drink_button_clicked), elem.second));
			drink_selection.attach(*button, x, y);
			i++;
		}
		{
			Gtk::Button* button = Gtk::make_managed<Gtk::Button>("Annuler");
			button->set_property("expand", true);
			button->signal_clicked().connect(sigc::mem_fun(*this, &Sell_formula::on_drink_cancel_button_clicked));
			drink_selection.attach(*button, width - 1, height);
		}
	}

	{
		std::unordered_map<std::string, Food> new_map_of_foods;
		for (const auto& elem : map_of_foods)
			if (elem.second.price == 100)
				new_map_of_foods.insert(std::make_pair(elem.first, elem.second));

		food_selection = Gtk::Grid();

		int height = int(std::sqrt(new_map_of_foods.size()));
		int width = int(double(new_map_of_foods.size()) / height + 0.5);

		std::size_t i = 0;
		for (const auto& elem : new_map_of_foods) {
			std::size_t x = i % width;
			std::size_t y = i / width;

			Gtk::Button* button = Gtk::make_managed<Gtk::Button>(elem.first);
			button->set_property("expand", true);
			button->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &Sell_formula::on_food_button_clicked), elem.second));
			food_selection.attach(*button, x, y);
			i++;
		}
		{
			Gtk::Button* button = Gtk::make_managed<Gtk::Button>("Annuler");
			button->set_property("expand", true);
			button->signal_clicked().connect(sigc::mem_fun(*this, &Sell_formula::on_food_cancel_button_clicked));
			food_selection.attach(*button, width - 1, height);
		}
	}

	{
		confirmation = Gtk::Grid();

		{
			Gtk::Button* button = Gtk::make_managed<Gtk::Button>("Confirmer");
			button->set_property("expand", true);
			button->signal_clicked().connect(sigc::mem_fun(*this, &Sell_formula::on_confirm_confirm_button_clicked));
			confirmation.attach(*button, 0, 0);
		}
		{
			Gtk::Button* button = Gtk::make_managed<Gtk::Button>("Annuler");
			button->set_property("expand", true);
			button->signal_clicked().connect(sigc::mem_fun(*this, &Sell_formula::on_confirm_cancel_button_clicked));
			confirmation.attach(*button, 1, 0);
		}
	}

	add(drink_selection);
	show_all_children();
}


Cafet::Sell_formula::~Sell_formula() {}

void Cafet::Sell_formula::on_drink_button_clicked(const Cafet::Drink& drink) {
	current_drink = drink.name;
	std::cout << "Drink: " << drink.name << '\n';
	remove();
	add(food_selection);
	show_all_children();
}
void Cafet::Sell_formula::on_drink_cancel_button_clicked() {
	m_window.sell();
}

void Cafet::Sell_formula::on_food_button_clicked(const Cafet::Food& food) {
	std::cout << "Food: " << food.name << '\n';
	current_food = food.name;
	remove();
	add(confirmation);
	show_all_children();
	using std::to_string;
	((Gtk::Button*)confirmation.get_child_at(0, 0))->set_label("Confirm (" + *current_drink + ", " + food.name + " (2€))");
}
void Cafet::Sell_formula::on_food_cancel_button_clicked() {
	remove();
	add(drink_selection);
	show_all_children();
}

void Cafet::Sell_formula::on_confirm_confirm_button_clicked() {
	std::ofstream formulae_out("transactions/formulae.txt", std::fstream::ios_base::app);
	formulae_out << std::time(0) << "; " << *current_drink << "; " << *current_food << "; 2.0" << '\n';
	on_confirm_cancel_button_clicked();
	m_window.home();
}
void Cafet::Sell_formula::on_confirm_cancel_button_clicked() {
	remove();
	add(drink_selection);
	show_all_children();
}
