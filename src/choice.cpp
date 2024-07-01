#include "../include/choice.h"
#include "../include/colors.h"
#include "../include/getkey.h"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>


Choice::Choice() = default;
Choice::~Choice() = default;

void Choice::show_line(const std::string& line, bool is_selected) {
	if (is_selected) {
		std::cout << Color().BG.MAGENTA << line << Color().NORMAL << std::endl;
	}
	else {
		std::cout << line << std::endl;
	}
}

int Choice::selection_post(const std::stringstream& ss, const std::vector<std::string>& choices) {
	int selected = 0;
	while (choices.size()) {
		system(cls);

		std::cout << ss.str();

		for (int i = 0; i < choices.size(); ++i) {
			show_line(choices[i], i == selected);
			if (i == selected && i != 0) {
				show_line("Press enter to to like/unlike above post...\n", true);
			}
		}

		char c = GETKEY();
		if ((c == 'w' || c == 'W') && selected > 0) {
			--selected;
		}
		else if ((c == 's' || c == 'S') && selected < choices.size() - 1) {
			++selected;
		}
		else if (c == '\n' || c == '\r') {
			return selected + 1;
		}
	}
	return -1;
}

void Choice::show_err(const std::string& err) {
	std::cout << Color().FG.RED << err << Color().NORMAL << std::endl;
}

int Choice::select_user_profile_option(std::stringstream& ss,
	std::vector<std::string>& vs) {
	int selected = 0;
	while (true) {
		system(cls);

		show_err(ss.str());

		for (int i = 0; i < vs.size(); ++i) {
			show_line(vs[i], i == selected);
		}

		char c = GETKEY();

		if ((c == 'w' || c == 'W') && selected > 0) {
			--selected;
			--selected;
		}
		else if ((c == 's' || c == 'S') && selected < vs.size() - 1) {
			++selected;
		}
		else if (c == '\n' || c == '\r') {
			return selected + 1;
		}
		else if (c == 'q' || c == 'Q') {
			return 1;
		}
	}
	return -1;
}

int Choice::select_menu(const std::stringstream& ss,
	const std::vector<std::string>& choices) {
	int selected = 0;
	while (choices.size()) {
		system(cls);

		show_line(ss.str(), false);

		for (int i = 0; i < choices.size(); ++i) {
			show_line(choices[i], i == selected);
		}

		char c = GETKEY();
		if ((c == 'w' || c == 'W') && selected > 0) {
			--selected;
		}
		else if ((c == 's' || c == 'S') && selected < choices.size() - 1) {
			++selected;
		}
		else if (c == '\n' || c == '\r') {
			return selected + 1;
		}
	}
	return -1;
}