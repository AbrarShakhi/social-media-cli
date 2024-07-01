#pragma once
#include <string>


void cstrcpy(char* dest, const char* src);

template <typename T> T input(const std::string& prompt);

std::string readLine(const std::string& prompt);

std::string c_2_str(const char* c);

void about_page();
