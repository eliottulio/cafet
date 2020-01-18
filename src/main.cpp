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
#include <gtkmm/application.h>
#include "window.hpp"
#include "data_structures.hpp"

int main(int argc, char** argv) {
	Cafet::init_cafet_info();

	auto app = Gtk::Application::create(argc, argv, "com.github.eliottulio");

	Cafet::Window window;

	return app->run(window);
}
