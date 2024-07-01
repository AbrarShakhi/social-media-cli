#include <sstream>
#include <string>
#include <vector>
#include <iostream>

// #include "../include/choice.h"
// #include "../include/colors.h"
// #include "../include/dashboard.h"
// #include "../include/getkey.h"
#include "../../include/choice.h"
#include "../../include/colors.h"
#include "../../include/database.h"
#include "../../include/getkey.h"


void load_dami_users() {
	std::stringstream ss;
	ss << "USE 'w'/'W' to move up\n";
	ss << "USE 's'/'S' to move down\n";
	ss << "USE 'Enter' to select\n";

	std::vector<std::string> v = {
		"EXIT", "OK"
	};

	int choice = Choice::select_menu(ss, v);
	if (choice != 2) {
		exit(0);
	}

	
	ss.str(std::string());
	std::vector<std::string> unsername = {
		"abrar", "fahim", "nourin", "sumaya", "cse207", "test"
	};

	database["admin"] = new User("admin", "admin", "dami bio", "admin@mail.com");

	for (auto&& i : unsername) {
		ss.str(std::string());
		ss << "HI I'm " << i << " and I'm a student of CSE207";
		database[i] = new User(i, "test", ss.str(), "mail@mail.com");
		database["admin"]->follow(*database[i]);
	}

	database["abrar"]->follow(*database["fahim"]);
	database["abrar"]->follow(*database["nourin"]);
	database["fahim"]->follow(*database["abrar"]);
	database["fahim"]->follow(*database["sumaya"]);
	database["fahim"]->follow(*database["cse207"]);
	database["nourin"]->follow(*database["cse207"]);
	database["sumaya"]->follow(*database["cse207"]);

	database["abrar"]->publish_post("Hello from abrar");
	database["fahim"]->publish_post("This post has been generated for showcasing");
	database["fahim"]->publish_post("Hello Its meeeeeee.");
	database["nourin"]->publish_post("Hello World");

	ss.str(std::string());
	ss << "Welcome to our social media app.." << std::endl;
	ss << "Please sign up or log in to continue.." << std::endl;
	ss << "If you want to test our application." << std::endl;
	ss << "We suggest you to login with our pre-created accout." << std::endl;
	ss << "Username: admin" << std::endl;
	ss << "Password: admin" << std::endl;
	ss << "pre-created accout follows some people so you can see some posts ";
	ss << "or you can create your own account then login as well" << std::endl;

	std::cout << Color().FG.YELLOW << ss.str() << Color().NORMAL << std::endl;
	std::cout << "Press any key to continue..";
	int _ =  GETKEY();
}

