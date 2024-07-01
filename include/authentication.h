#pragma once
#include "../include/user.h"

class Authentication {
private:
	bool is_logged_in = false;

public:
	Authentication();
	~Authentication();

	User* log_out();

	User* menu();
	bool is_success() const;

private:

	User* sign_up();
	User* log_in();
};