#pragma once

#include <string>
#include <vector>

class Register
{

public:
  Register(const std::string& name);

  ~Register() = default;

  std::string name();

  bool addOperation(const std::string& operand, const int& optionalValue = 0, std::shared_ptr<Register> optionalRegister = nullptr);

  int evaluate();

  struct operation {
    std::shared_ptr<Register> reg;
    int value;
    std::string operand;
  };

  std::vector<operation> getOperations();

private:
  std::string _name;
  std::vector<operation> _operations;
};

