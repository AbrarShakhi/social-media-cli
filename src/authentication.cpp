#include "../include/authentication.h"
#include "../include/user.h"
#include "../include/choice.h"
#include "../include/getkey.h"
#include "../include/utils.h"
#include "../include/validatetor.h"
#include "../include/limits.h"
#include "../include/database.h"

#include <vector>
#include <string.h>
#include <string>
#include <sstream>
#include <iostream>



Authentication::Authentication() = default;
Authentication::~Authentication() { log_out(); }

User* Authentication::log_out() {
	is_logged_in = false;
	return nullptr;
}

User* Authentication::menu() {
	std::vector<std::string> choices = { "Sign up", "Log in","about", "Exit" };

	int choice = Choice::select_menu(std::stringstream(), choices);
	User* user = nullptr;
	switch (choice) {
	case 1:
		user = sign_up();
		break;
	case 2:
		user = log_in();
		break;
	case 3:
		about_page();
		break;
	default:
		exit(0);
	}

	std::cout << "Press any key to continue..";
	int _ = GETKEY();

	return user;
}

bool Authentication::is_success() const { return is_logged_in; }

User* Authentication::sign_up() {
	std::stringstream prompt;

	prompt << "Enter username (max " << MAX_USERNAME_LEN - 1 << ", min " << MIN_USERNAME_LEN << "): ";
	std::string username = readLine(prompt.str());
	if (!validatetor::validate_username(username)) {
		return nullptr;
	}

	prompt.str(std::string());
	prompt << "Enter password (max " << MAX_PASSWORD_LEN - 1 << ", min " << MIN_PASSWORD_LEN << "): ";
	std::string pw = readLine(prompt.str());
	if (!validatetor::validate_password(pw)) {
		return nullptr;
	}

	char password[MAX_PASSWORD_LEN];
	for (int i = 0; i < pw.length(); ++i) {
		password[i] = pw[i];
	}
	password[pw.length()] = '\0';

	prompt.str(std::string());
	prompt << "Enter email (max " << MAX_EMAIL_LEN - 1 << "): ";
	std::string email = readLine(prompt.str());
	if (!validatetor::validate_email(email)) {
		return nullptr;
	}

	prompt.str(std::string());
	prompt << "Enter bio (max " << MAX_BIO_LEN - 1 << "): ";
	std::string bio = readLine(prompt.str());
	if (!validatetor::validate_str(bio)) {
		return nullptr;
	}

	User* user = new User(username, password, bio, email);
	database[username] = user;
	is_logged_in = true;

	return user;
}
User* Authentication::log_in() {

	std::string username;
	char password[MAX_PASSWORD_LEN];

	username = readLine("Enter username: ");
	if (database.find(username) == database.end()) {
		Choice::show_err("User not found\nTry again...");
		return nullptr;
	}

	std::string pw = readLine("Enter password: ");
	if (pw.size() > MAX_PASSWORD_LEN - 1) {
		return nullptr;
	}
	for (int i = 0; i < pw.size(); i++) {
		password[i] = pw[i];
	}

	password[pw.size()] = '\0';

	if (strcmp(database[username]->get_password(), password)) {
		Choice::show_err("Incorrect password...");
		return nullptr;
	}

	is_logged_in = true;
	return database[username];
}