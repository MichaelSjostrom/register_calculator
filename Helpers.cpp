#include "Helpers.h"

#include <algorithm>
#include <sstream>
#include <iterator>
#include <cctype>

std::string toLower(const std::string& string) {

  std::string result;
  std::transform(string.begin(), string.end(), std::back_inserter(result),
    [](unsigned char c) { return tolower(c); });

  return result;
}

std::vector<std::string> split(const std::string& string) {
  std::istringstream iss(string);
  std::vector<std::string> results(std::istream_iterator<std::string>{iss},
    std::istream_iterator<std::string>());

  return results;
}

bool isAlphanumeric(const std::string& string) {

  for (int i = 0; i < string.size(); i++) {
    if (!std::isalnum(string[i])) {
      return false;
    }
  }
  return true;
}

bool isNumber(const std::string& string) {

  return !string.empty() && std::find_if(string.begin(),
    string.end(), [](unsigned char c) { return !std::isdigit(c); }) == string.end();
}

std::string removeSpaces(const std::string& string) {
  std::string result = string;
  result.erase(remove_if(result.begin(), result.end(), isspace), result.end());

  return result;
}