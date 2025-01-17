#include "Helpers.h"
#include "Register.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

std::map<std::string, std::shared_ptr<Register>> _registers;
std::vector<std::string> _operations = { "add", "subtract", "multiply" };

bool registerExists(const std::string& r) {
  return _registers.find(r) != _registers.end();
}

bool isAllowed(const std::string& operation)
{
  for (auto& op : _operations) {
    if (op == operation) {
      return true;
    }
  }

  return false;
}

int main(int argc, char* argv[])
{
  std::istream* istream;
  std::ifstream ifstream;

  // Input from command line
  if (argc == 1) {
    istream = &std::cin;
  }
  // Input from file
  else if (argc == 2) {
    ifstream.open(argv[1]);
    if (!ifstream) {
      std::cout << "Could not read the specified file." << std::endl;
      return 1;
    }
    istream = &ifstream;
  }
  else {
    std::cout << "Input arguments are not valid." << std::endl;
    return 1;
  }

  std::string input;
  while (std::getline(*istream, input)) {

    if (!isAlphanumeric(removeSpaces(input))) {
      std::cout << "Input is not alphanumeric, please submit a new input." << std::endl;
      continue;
    }

    if (toLower(input) == "quit") {
      return 0;
    }

    std::vector<std::string> splittedInput(split(input));

    int inputSize = splittedInput.size();
    std::string reg = splittedInput.front();

    if (isNumber(reg)) {
      std::cout << "A register name cannot be a number, please submit a new value." << std::endl;
      continue;
    }
    
    if (inputSize == 2) {
      if (toLower(reg) == "print") {
        std::string r = splittedInput.back();
        if (registerExists(r)) {
          std::cout << _registers[r]->evaluate() << std::endl;
        }
        else {
          std::cout << "There is no register with the name: " << r << std::endl;
          continue;
        }
      }
    }
    else if (inputSize == 3) {
      if (!registerExists(reg)) {
        _registers[reg] = std::make_shared<Register>(reg);
      }

      std::string operand = toLower(splittedInput[1]);
      if (!isAllowed(operand)) {
        std::cout << "Operation is not supported, please submit a new input." << std::endl;
        continue;
      }

      std::string value = splittedInput.back();
      if (isNumber(value)) {
        _registers[reg]->addOperation(operand, std::stoi(value), nullptr);
      }
      else {
        // Add a non exisiting register
        if (!registerExists(value)) {
          _registers[value] = std::make_shared<Register>(value);
        }

        if (!_registers[reg]->addOperation(operand, 0, _registers[value])) {
          std::cout << "Operation was not added because a cyclic dependency was detected, please submit a new value." << std::endl;
          continue;
        }
      }
    }
  }

  // If input was a file, close it
  if (ifstream) {
    if (ifstream.is_open()) {
      ifstream.close();
    }
  }
}

