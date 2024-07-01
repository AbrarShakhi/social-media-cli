#include "../include/dashboard.h"
#include "../include/user.h"
#include "../include/database.h"
#include "../include/limits.h"
#include "../include/choice.h"
#include "../include/getkey.h"
#include "../include/colors.h"
#include "../include/utils.h"
#include "../include/validatetor.h"
#include "../include/binary_tree_frequency_map.h"
#include "../include/avl_tree_set.h"

#include <vector>
#include <string>
#include <string.h>
#include <sstream>
#include <iostream>
#include <ctime>


Dashboard::Dashboard(User* user) {
	this->user = user;
	is_logedin = true;
}
Dashboard::~Dashboard() = default;

bool Dashboard::isLogedin() { return is_logedin; }

void Dashboard::homepage() {
	const std::vector<std::string> m = {
		"News feed",
		"Profile",
		"Find friends",
		"settings",
		"Logout"
	};

	int choice = Choice::select_menu(std::stringstream(), m);
	switch (choice) {
	case 1:
		news_feed();
		break;
	case 2:
		show_profile(this->user);
		break;
	case 3:
		find_friends();
		break;
	case 4:
		setting();
		break;
	case 5:
		logout();
		return;
	}
	std::cout << "Press any key to continue..";
	int _ = GETKEY();
}


void Dashboard::find_friends() {
	std::vector<std::string> vs = { "Back", "search by username" };

	BinaryTreeFrequencyMap btf;

	std::vector<std::string> all_following = user->get_following();
	AVLTreeSet personal_following_set;
	for (auto&& i : all_following) {
		personal_following_set.insert(i);
	}

	for (auto&& i : all_following) {
		std::vector<std::string> mutual = (database[i])->get_following();
		for (auto&& j : mutual) {
			if (j != user->get_username() && !personal_following_set.find(j.c_str())) {
				btf.insert(j);
			}
		}
	}

	std::vector<std::string> mutual = btf.get_frequency_sorted();
	vs.reserve(vs.size() + mutual.size());

	std::stringstream ss;
	for (auto&& i : mutual) {
		ss.str(std::string());
		ss << i << " " << Color().FG.GRAY << btf.get_value(i) << " mutual following" << Color().NORMAL;
		vs.push_back(ss.str());
	}

	int choice = Choice::select_menu(std::stringstream(), vs);

	switch (choice) {
	case 1:
		return;
	case 2:
		search_by_username();
		break;
	default:
		show_profile(database[mutual[choice - 3]]);
		break;
	}
}

void Dashboard::search_by_username() {
	std::string username = readLine("Enter username: ");
	if (database.find(username) == database.end()) {
		Choice::show_err("User not found..");
		return;
	}
	show_profile(database[username]);
}

std::vector<User::Post*> Dashboard::gen_all_sorted_posts() {
	time_t now = time(nullptr);
	std::vector<User::Post*> posts;
	std::vector<std::string> following = user->get_following();

	for (auto&& usr : following) {
		std::vector<User::Post*> p = database[usr]->get_posts();

		std::vector<User::Post*> temp;
		temp.reserve(p.size() + posts.size());

		int i = 0, j = 0;
		while (i < p.size() && j < posts.size()) {
			if (difftime(now, p[i]->publish_time) > 31536000) {
				i = (int)p.size();
				continue;
			}
			if (difftime(now, p[i]->publish_time) > difftime(now, posts[j]->publish_time)) {
				temp.push_back(p[i]);
				++i;
			}
			else if (difftime(now, p[i]->publish_time) < difftime(now, posts[j]->publish_time)) {
				temp.push_back(posts[j]);
				++j;
			}
			else {
				temp.push_back(p[i]);
				temp.push_back(posts[j]);
				++i;
				++j;
			}
		}

		while (i < p.size()) {
			temp.push_back(p[i]);
			++i;
		}

		while (j < posts.size()) {
			temp.push_back(posts[j]);
			++j;
		}

		posts = temp;
	}

	return posts;
}

void Dashboard::news_feed() {
	std::vector<User::Post*> posts = gen_all_sorted_posts();
	std::vector<std::string> vp = configure_post(posts, user);

	int choice;
	if (vp.size() <= 1) {
		std::stringstream ss;
		ss << "No posts found..\nFollow some friends. if they post. It will appear here..\n";
		choice = Choice::selection_post(ss, vp);
	}
	else {
		choice = choice = Choice::selection_post(std::stringstream(), vp);
	}
	switch (choice) {
	case 1:
		return;
	default:
		if (posts[choice - 2]->likes_set.find(user->get_username().c_str())) {
			posts[choice - 2]->likes_set.remove(user->get_username());
			--posts[choice - 2]->likes;
		}
		else {
			posts[choice - 2]->likes_set.insert(user->get_username());
			++posts[choice - 2]->likes;
		}
		break;
	}
	news_feed();
}

std::vector<std::string> Dashboard::configure_post(std::vector<User::Post*> posts, User* profile) {
	std::vector<std::string> vp;
	vp.reserve(posts.size() + 1);

	vp.push_back("Back");
	for (auto&& i : posts) {
		std::stringstream s;
		s << i->post_owner->get_username() << " " << Color().FG.GRAY << ctime(&i->publish_time)
			<< Color().NORMAL << i->content << std::endl;

		if (i->likes_set.find(user->get_username().c_str())) {
			s << Color().FG.RED << "Unlike" << "(" << i->likes << ")" << Color().NORMAL << " ";
		}
		else {
			s << Color().FG.GREEN << "Like" << "(" << i->likes << ")" << Color().NORMAL << " ";
		}

		vp.push_back(s.str());
	}
	return vp;
}

void Dashboard::logout() {
	std::cout << "Are you sure? " << std::endl;
	std::vector<std::string> chv = { "no", "yes" };
	int ch = Choice::select_menu(std::stringstream(), chv);
	if (ch != 2) {
		return;
	}
	is_logedin = false;
	this->user = NULL;
}

void Dashboard::show_profile(User* profile) {
	if (!profile) {
		Choice::show_err("User not found..");
		return;
	}

	std::stringstream ss;
	ss << Color().FG.GREEN << profile->get_username() << Color().NORMAL
		<< std::endl;
	ss << Color().FG.GRAY << profile->get_bio() << Color().NORMAL << std::endl;

	std::vector<std::string> vs = { "Back" };
	bool self, follow;
	if (profile->get_username() == user->get_username()) {
		vs.push_back("Settings");
		vs.push_back("add posts");
		self = true;
	}
	else {
		self = false;
		if (user->is_following(profile->get_username())) {
			vs.push_back("Unfollow");
			follow = true;
		}
		else {
			follow = false;
			vs.push_back("Follow");
		}
	}

	vs.push_back("See followers");
	vs.push_back("See followings");
	vs.push_back("See posts");

	int choice = Choice::select_user_profile_option(ss, vs);
	if (choice == 1) {
		return;
	}
	if (self) {
		if (choice == 2) {
			setting();
		}
		else if (choice == 3) {
			add_post();
		}
		else if (choice == 4) {
			show_follower(profile);
		}
		else if (choice == 5) {
			show_following(profile);
		}
		else if (choice == 6) {
			show_posts(profile);
		}
	}
	else {
		if (choice == 2) {
			if (follow) {
				user->unfollow(*profile);
			}
			else {
				user->follow(*profile);
			}
		}
		else if (choice == 3) {
			show_follower(profile);
		}
		else if (choice == 4) {
			show_following(profile);
		}
		else if (choice == 5) {
			show_posts(profile);
		}
	}
}

void Dashboard::setting() {
	std::vector<std::string> vs = { "Change password","Change bio", "Change email", "back" };

	int choice = Choice::select_menu(std::stringstream(), vs);
	switch (choice) {
	case 1:
		if (change_password()) {
			return;
		}
		break;
	case 2:
		if (change_bio()) {
			return;
		}
		break;
	case 3:
		if (change_email()) {
			return;
		}
		break;
	default:
		return;
	}
	std::cout << "Press any key to continue..";
	int _ = GETKEY();
}

bool Dashboard::change_password() {
	std::string previous_password = readLine("Enter previous password: ");
	if (strcmp(user->get_password(), previous_password.c_str())) {
		Choice::show_err("Incorrect password...");
		return false;
	}

	std::stringstream s;
	s << "Enter password (max " << MAX_PASSWORD_LEN - 1 << ", min " << MIN_PASSWORD_LEN << "): ";
	std::string pw = readLine(s.str());
	if (!validatetor::validate_password(pw)) {
		return false;
	}
	user->change_password(pw.c_str());
	return true;
}

bool Dashboard::change_bio() {
	std::stringstream s;
	s << "Enter bio (max " << MAX_BIO_LEN - 1 << "): ";
	std::string bio = readLine(s.str());
	if (!validatetor::validate_str(bio)) {
		return false;
	}
	user->change_bio(bio);
	return true;
}

bool Dashboard::change_email() {
	std::stringstream s;
	s << "Enter email (max " << MAX_EMAIL_LEN - 1 << "): ";
	std::string email = readLine(s.str());
	if (!validatetor::validate_email(email)) {
		return false;
	}
	user->change_email(email);
	return true;
}

void Dashboard::add_post() {
	std::stringstream s;
	s << "Type your post (max " << MAX_POST_CONTENT_LEN << "): ";
	std::string content = readLine(s.str());
	if (content.length() > MAX_POST_CONTENT_LEN) {
		Choice::show_err("Post too long...");
		return;
	}
	user->publish_post(content);
}

void Dashboard::show_posts(User* profile) {
	std::vector<User::Post*> posts = profile->get_posts();
	std::vector<std::string> vp = configure_post(posts, profile);
	int choice;
	if (vp.size() <= 1) {
		std::stringstream ss;
		ss << "No posts found.\nif they post. It will appear here..\n";
		choice = Choice::selection_post(ss, vp);
	}
	else {
		choice = choice = Choice::selection_post(std::stringstream(), vp);
	}
	switch (choice) {
	case 1:
		return;
	default:
			if (posts[choice - 2]->likes_set.find(user->get_username().c_str())) {
				posts[choice - 2]->likes_set.remove(user->get_username());
				--posts[choice - 2]->likes;
			}
			else {
				posts[choice - 2]->likes_set.insert(user->get_username());
				++posts[choice - 2]->likes;
			}
		break;
	}
	show_posts(profile);
}

void Dashboard::show_follower(User* profile) {
	std::vector<std::string> vs = profile->get_followers();

	vs.insert(vs.begin(), "Back");

	int choice = Choice::select_menu(std::stringstream(), vs);
	switch (choice) {
	case 1:
		return;
	default:
		if (choice > 1 && choice <= vs.size()) {
			show_profile(database[vs[choice - 1]]);
		}
		break;
	}
}

void Dashboard::show_following(User* profile) {
	std::vector<std::string> vs = profile->get_following();

	vs.insert(vs.begin(), "Back");

	int choice = Choice::select_menu(std::stringstream(), vs);
	switch (choice) {
	case 1:
		return;
	default:
		if (choice > 1 && choice <= vs.size()) {
			show_profile(database[vs[choice - 1]]);
		}
		break;
	}
}
