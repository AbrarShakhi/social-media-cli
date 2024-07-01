#pragma once
#include "../include/limits.h"
#include "../include/avl_tree_set.h"
#include "../include/utils.h"

#include <vector>
#include <string>
#include <ctime>


class User {
public:
	struct Post {
		std::string content = "";
		unsigned long long likes = 0;
		AVLTreeSet likes_set;
		time_t publish_time = 0;
		User *post_owner = nullptr;
		Post* next = nullptr;
	};

private:
	std::string username = "";
	char password[MAX_PASSWORD_LEN] = "";
	std::string email = "";
	unsigned long long uuid;
	std::string bio = "";
	AVLTreeSet following, followers;
	Post* post_head = nullptr;

public:
	User();
	~User();
	User(const std::string& username, const char* password, const std::string& bio, const std::string& email);
	User(const User& user);
	User(const std::string& username, const char* password, const std::string& email);

	void follow(User& user);
	void unfollow(User& user);

	void change_password(const char* new_password);

	void change_bio(const std::string& new_bio);

	void change_email(const std::string& new_email);

	std::string get_username() const;
	std::string get_email() const;
	std::string get_bio() const;
	char* get_password();
	bool is_following(const std::string& username);
	bool is_followed_by(const std::string& username);

	std::vector<std::string> get_following();

	std::vector<std::string> get_followers();

public:
	void publish_post(const std::string& content);

	std::vector<Post*> get_posts();
};
