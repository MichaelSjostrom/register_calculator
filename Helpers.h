#pragma once

#include <string>
#include <vector>

std::string toLower(const std::string& string);
 
std::vector<std::string> split(const std::string& string);

bool isAlphanumeric(const std::string& string);

bool isNumber(const std::string& string);

std::string removeSpaces(const std::string& string);
