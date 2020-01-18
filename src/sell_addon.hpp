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

#include <gtkmm/frame.h>
#include <string_view>
#include "data_structures.hpp"

namespace Cafet {

class Window;

class Sell_addon : public Gtk::Frame {
public:
	Sell_addon(Window& window);
	virtual ~Sell_addon();

protected:
	void on_addon_button_clicked(const Addon& addon);
	void on_addon_cancel_button_clicked();

	void on_confirm_confirm_button_clicked();
	void on_confirm_cancel_button_clicked();

	Window& m_window;

	Gtk::Grid addon_selection;
	Gtk::Grid confirmation;

	boost::optional<std::string> current_addon;
};

}
