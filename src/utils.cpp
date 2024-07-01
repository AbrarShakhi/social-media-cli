#include "../include/colors.h"
#include "../include/getkey.h"
#include "../include/utils.h"

#include <iostream>
#include <sstream>
#include <string>

void cstrcpy(char* dest, const char* src) {
	while (*src) {
		*dest = *src;
		++dest;
		++src;
	}
	*dest = '\0';
}

template <typename T> T input(const std::string& prompt) {
	T t;
	std::cout << prompt;
	std::cin >> t;
	// fflush(stdin);
	std::cin.ignore();
	return t;
}

std::string readLine(const std::string& prompt) {
	std::string t;
	std::cout << prompt;
	std::getline(std::cin, t);
	// fflush(stdin);
	// std::cin.ignore();
	return t;
}

std::string c_2_str(const char* c) {
	std::stringstream s;
	s << c;
	return s.str();
}

void about_page() {
	std::stringstream ss;
	ss << "This is a simple social media CLI app created by - " << std::endl
		<< Color().FG.BLUE << "1. Md.Shakhiul Abrar" << std::endl
		<< "2. Fahim Shahriar" << std::endl
		<< "3. Nusroth Nourin" << std::endl 
		<< "3. Sumaiya Binte Naser" << std::endl << std::endl << Color().NORMAL
		<< "In this project, we use some of the core topics of Data Structure such as - "
		<< Color().FG.GREEN << "* Merge sort" << std::endl
		<< "* AVL tree" << std::endl
		<< "* Binary search tree" << std::endl
		<< "* Linked list" << std::endl
		<< "* Stack" << std::endl << Color().NORMAL;
	
	system(cls);
	std::cout << ss.str();
}
