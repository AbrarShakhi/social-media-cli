
/**
* @file main.cpp
* @date 16/05/2024
* @brief A simple social media CLI app created by - 
* 
* @author Md.Shakhiul Abrar (2022-3-60-022)
* @author Fahim Shahriar (2022-3-60-020)
* @author Nusroth Nourin (2022-3-60-006)
* @author Sumaiya Binte Naser (2022-2-60-155)
*/


#include "extra/welcome.cpp"
#include "../include/authentication.h"
#include "../include/dashboard.h"
#include <stdlib.h>

int main() {

	load_dami_users();

	while (true) {
		Authentication auth;
		User* user = nullptr;

		do {
			user = auth.menu();
		} while (!auth.is_success() && !user);

		Dashboard dashboard(user);
		do {
			dashboard.homepage();
		} while (dashboard.isLogedin());

		user = auth.log_out();
	}
	return EXIT_FAILURE;
}
