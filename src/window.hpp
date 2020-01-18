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

#include <gtkmm/window.h>
#include <gtkmm/stack.h>

#pragma once

namespace Cafet {

class Window : public Gtk::Window {
public:
	Window();
	virtual ~Window();

	void home();
	void sell();
	void sell_drink();
	void sell_addon();
	void sell_food();
	void sell_formula();

protected:
	Gtk::Stack m_stack;
};

}
