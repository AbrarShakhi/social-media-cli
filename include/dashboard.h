#pragma once
#include "../include/user.h"

#include <vector>


class Dashboard {
private:
	User* user;
	bool is_logedin = false;

public:
	Dashboard(User* user);
	~Dashboard();

	bool isLogedin();

	void homepage();

private:

	void find_friends();

	void search_by_username();

	std::vector<User::Post*> gen_all_sorted_posts();

	void news_feed();

	std::vector<std::string> configure_post(std::vector<User::Post*> posts, User* profile);

	void logout();

	void show_profile(User* profile);

	void setting();

	bool change_password();

	bool change_bio();

	bool change_email();

	void add_post();

	void show_posts(User* profile);

	void show_follower(User* profile);

	void show_following(User* profile);
};