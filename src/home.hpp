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

#pragma once


#include <gtkmm/grid.h>

namespace Cafet {

class Window;

class Home : public Gtk::Grid {
public:
	Home(Window& window);
	virtual ~Home();

protected:
	void on_button_customer_clicked();
	void on_button_shop_clicked();

	Window& m_window;
};

}
