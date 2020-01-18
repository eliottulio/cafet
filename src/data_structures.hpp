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

#include <string>
#include <boost/optional.hpp>
#include <optional>
#include <unordered_map>

namespace Cafet {
	void init_cafet_info();

	struct Addon {
		Addon(const std::string&, std::size_t);
		std::string name;
		std::size_t price;
	};

	struct Drink_size {
		Drink_size(char, std::size_t);
		Drink_size(char, std::size_t, bool);
		char name;
		std::size_t price;
		bool invisible = false;
	};

	struct Drink {
		Drink(const std::string&);
		Drink(const std::string&, const boost::optional<Drink_size>&);
		std::string name;
		boost::optional<Drink_size> default_size = boost::optional<Drink_size>();
	};

	struct Food {
		Food(const std::string&, std::size_t);
		std::string name;
		std::size_t price;
	};


	extern std::unordered_map<std::string, Drink> map_of_drinks;
	extern std::unordered_map<char, Drink_size> map_of_drink_sizes;
	extern std::unordered_map<std::string, Addon> map_of_addons;
	extern std::unordered_map<std::string, Food> map_of_foods;
}
