#pragma once
#include <string>


class validatetor {
public:
	static bool validate_username(const std::string& username);

	static bool validate_password(const std::string& pw);

	static bool validate_email(const std::string& email);

	static bool validate_str(const std::string& s);
};