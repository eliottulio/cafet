#include "data_structures.hpp"
#include <boost/optional/optional_io.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/phoenix/phoenix.hpp>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <string>

std::unordered_map<std::string, Cafet::Drink> Cafet::map_of_drinks = {};
std::unordered_map<char, Cafet::Drink_size> Cafet::map_of_drink_sizes = {};
std::unordered_map<std::string, Cafet::Addon> Cafet::map_of_addons = {};
std::unordered_map<std::string, Cafet::Food> Cafet::map_of_foods = {};

Cafet::Addon::Addon(const std::string& name_, std::size_t price_): name(name_), price(price_) {}

Cafet::Drink_size::Drink_size(char name_, std::size_t price_) : name(name_), price(price_) {}
Cafet::Drink_size::Drink_size(char name_, std::size_t price_, bool invisible_): name(name_), price(price_), invisible(invisible_) {}

Cafet::Drink::Drink(const std::string& name_): name(name_) {}
Cafet::Drink::Drink(const std::string& name_, const boost::optional<Drink_size>& default_size_): name(name_), default_size(default_size_) {}

Cafet::Food::Food(const std::string& name_, std::size_t price_): name(name_), price(price_) {}



void Cafet::init_cafet_info() {


	using boost::spirit::qi::byte_;
	using boost::spirit::qi::ascii::char_;
	using boost::spirit::qi::ascii::digit;
	using boost::spirit::qi::ulong_;
	using boost::spirit::qi::eoi;
	using boost::spirit::qi::as_string;
	using boost::spirit::_1;
	using boost::spirit::_2;
	using boost::spirit::_3;

	using boost::phoenix::construct;
	using boost::phoenix::push_back;
	using boost::phoenix::if_else;
	using boost::phoenix::at;
	namespace phx = boost::phoenix;

	{
		std::vector<std::string> lines = {};

		{
			std::ifstream sizes_file("ressources/drink_prices.txt");
			std::string line;
			while (std::getline(sizes_file, line))
				lines.push_back(line);
		}

		std::vector<Cafet::Drink_size> drink_sizes = {};

		for (const std::string& str : lines) {
			auto b_it = str.begin();
			auto r = boost::spirit::qi::parse(b_it, str.end(),
						(char_ >> ':' >> ulong_ >> -(':' >> char_('0')))[push_back(phx::ref(drink_sizes), construct<Cafet::Drink_size>(_1, _2, if_else(_3, true, false)))]);
			if (!r || b_it != str.end())
				throw std::runtime_error("Incorrect size definition: " + str);
		}

		for (const auto& elem : drink_sizes)
			Cafet::map_of_drink_sizes.insert({elem.name, elem});
	}
	{
		std::vector<std::string> lines = {};

		{
			std::ifstream drinks_file("ressources/drinks_defs.txt");
			std::string line;
			while (std::getline(drinks_file, line))
				lines.push_back(line);
		}

		std::vector<Cafet::Drink> drinks = {};

		for (const std::string& str : lines) {
			auto b_it = str.begin();
			boost::optional<char> size;
			auto r = boost::spirit::qi::parse(b_it, str.end(),
						(as_string[+(byte_ - ':')] >> -(':' >> char_))[push_back(phx::ref(drinks), construct<Cafet::Drink>(_1)), phx::ref(size) = _2]);
			if (!r || b_it != str.end())
				throw std::runtime_error("Incorrect drink definition: \"" + str + '"');
			if (size) {
				drinks.back().default_size = map_of_drink_sizes.at(*size);
			}
		}

		for (const auto& elem : drinks)
			Cafet::map_of_drinks.insert({elem.name, elem});
	}
	{
		std::vector<std::string> lines = {};

		{
			std::ifstream supps_file("ressources/supp_defs.txt");
			std::string line;
			while (std::getline(supps_file, line))
				lines.push_back(line);
		}

		std::vector<Cafet::Addon> addons = {};

		for (const std::string& str : lines) {
			auto b_it = str.begin();
			auto r = boost::spirit::qi::parse(b_it, str.end(),
						(as_string[+(byte_ - ':')] >> ':' >> ulong_)[push_back(phx::ref(addons), construct<Cafet::Addon>(_1, _2))]);
			if (!r || b_it != str.end())
				throw std::runtime_error("Incorrect addon definition: " + str);
		}
		for (const auto& elem : addons)
			Cafet::map_of_addons.insert({elem.name, elem});
	}

	{
		std::vector<std::string> lines = {};

		{
			std::ifstream food_file("ressources/food_defs.txt");
			std::string line;
			while (std::getline(food_file, line))
				lines.push_back(line);
		}

		std::vector<Cafet::Food> foods = {};

		for (const std::string& str : lines) {
			auto b_it = str.begin();
			auto r = boost::spirit::qi::parse(b_it, str.end(),
						(as_string[+(byte_ - ':')] >> ':' >> ulong_)[push_back(phx::ref(foods), construct<Cafet::Food>(_1, _2))]);
			if (!r || b_it != str.end())
				throw std::runtime_error("Incorrect addon definition: " + str);
		}
		for (const auto& elem : foods)
			Cafet::map_of_foods.insert({elem.name, elem});
	}

}
