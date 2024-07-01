#pragma once
#include "../include/user.h"

#include <map>
#include <string>

#ifndef DB
inline std::map<std::string, User*> database;
#endif
#define BD