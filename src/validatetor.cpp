#include "../include/validatetor.h"
#include "../include/limits.h"
#include "../include/database.h"
#include "../include/choice.h"

#include <string>


bool validatetor::validate_username(const std::string& username) {
	if (username.length() >= MAX_USERNAME_LEN || username.length() < MIN_USERNAME_LEN) {
		Choice::show_err("Username too long or short\nTry again..");
		return false;
	}
	if (username.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQ"
		"RSTUVWXYZ0123456789_.") !=
		std::string::npos) {
		Choice::show_err("Invalid username\nTry again...");
		return false;
	}
	if (database.find(username) != database.end()) {
		Choice::show_err("Username already exists\nTry again...");
		return false;
	}
	return true;
}

bool validatetor::validate_password(const std::string& pw) {
	if (pw.length() >= MAX_PASSWORD_LEN || pw.length() < MIN_PASSWORD_LEN) {
		Choice::show_err("Password too long or short\nTry again...");
		return false;
	}
	if (pw.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVW"
		"XYZ0123456789!@#$%^&*()_+=-[];',./{}:\"<>?\\|") !=
		std::string::npos) {
		Choice::show_err("Invalid password\nTry again...");
		return false;
	}
	return true;
}

bool validatetor::validate_email(const std::string& email) {
	if (email.length() >= MAX_EMAIL_LEN) {
		Choice::show_err("Email too long\nTry again...");
		return false;
	}
	if (email.find('@') == std::string::npos) {
		Choice::show_err("Invalid email\nTry again...");
		return false;
	}
	if (email.find('.') == std::string::npos) {
		Choice::show_err("Invalid email\nTry again...");
		return false;
	}
	if (email.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRST"
		"UVWXYZ0123456789@._-") != std::string::npos) {
		Choice::show_err("Invalid email\nTry again");
		return false;
	}
	return true;
}

bool validatetor::validate_str(const std::string& s) {
	if (s.length() >= MAX_BIO_LEN) {
		Choice::show_err("Too long\nTry again...");
		return false;
	}
	return true;
}