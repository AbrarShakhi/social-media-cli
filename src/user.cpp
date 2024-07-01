#include "../include/user.h"
#include "../include/utils.h"

#include <vector>
#include <string>
#include <ctime>


User::User() {}
User::~User() {
	Post* post = post_head;
	while (post) {
		Post* temp = post;
		post = post->next;
		delete temp;
	}
}

User::User(const std::string& username, const char* password, const std::string& bio, const std::string& email) {
	this->username = username;
	cstrcpy(this->password, password);
	this->bio = bio;
	this->email = email;
}

User::User(const User& user) {
	username = user.username;
	cstrcpy(password, user.password);
	bio = user.bio;
	email = user.email;
	post_head = user.post_head;
}

User::User(const std::string& username, const char* password,
	const std::string& email) {
	this->username = username;
	cstrcpy(this->password, password);
	this->email = email;
}

void User::follow(User& user) {
	if (!following.find(user.username.c_str())) {
		following.insert(user.username);
	}
	if (!user.followers.find(username.c_str())) {
		user.followers.insert(username);
	}
}

void User::unfollow(User& user) {
	if (following.find(user.username.c_str())) {
		following.remove(user.username);
	}
	if (user.followers.find(username.c_str())) {
		user.followers.remove(username);
	}
}

void User::change_password(const char* new_password) {
	cstrcpy(password, new_password);
}

void User::change_bio(const std::string& new_bio) {
	bio = new_bio;
}

void User::change_email(const std::string& new_email) {
	email = new_email;
}

std::string User::get_username() const {
	return username;
}

std::string User::get_email() const {
	return email;
}

std::string User::get_bio() const {
	return bio;
}

char* User::get_password() {
	return password;
}

bool User::is_following(const std::string& username) {
	return following.find(username.c_str());
}
bool User::is_followed_by(const std::string& username) {
	return followers.find(username.c_str());
}

std::vector<std::string> User::get_following() {
	return following.get_all();
}

std::vector<std::string> User::get_followers() {
	return followers.get_all();
}

void User::publish_post(const std::string& content) {
	Post* p = new Post;
	p->content = content;
	p->likes = 0;
	p->publish_time = time(nullptr);
	p->next = nullptr;
	p->post_owner = this;
	p->next = post_head;
	post_head = p;
}

std::vector<User::Post*> User::get_posts() {
	std::vector<Post*> posts;
	Post* post = post_head;
	while (post) {
		posts.push_back(post);
		post = post->next;
	}
	return posts;
}
