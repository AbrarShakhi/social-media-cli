#pragma once
#include <string>
#include <vector>
#include <sstream>


class Choice {
public:
	Choice();
	~Choice();

	static void show_line(const std::string& line, bool is_selected);

	static int selection_post(const std::stringstream& ss, const std::vector<std::string>& choices);

	static void show_err(const std::string& err);

	static int select_user_profile_option(std::stringstream& ss,std::vector<std::string>& vs);

	static int select_menu(const std::stringstream& ss,const std::vector<std::string>& choices);
};