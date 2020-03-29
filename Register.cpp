#include "Register.h"

Register::Register(const std::string& name)
  : _name(name)
{
}

std::string Register::name()
{
  return _name;
}

bool Register::addOperation(const std::string& operand, const int& optionalValue, std::shared_ptr<Register> optionalRegister)
{
  // Check for cyclic dependencies
  if (optionalRegister != nullptr) {
    if (optionalRegister->name() == _name) {
      return false;
    }
    for (auto& op1 : optionalRegister->getOperations()) {
      if (op1.reg) {
        if (_name == op1.reg->name()) {
          return false;
        }
        for (auto& op2 : op1.reg->getOperations()) {
          if (op2.reg) {
            if (_name == op2.reg->name()) {
              return false;
            }
          }
        }
      }
    }

    // Input is a register
    _operations.emplace_back(operation{ optionalRegister, optionalValue, operand });
    return true;
  }

  // Input is value
  _operations.emplace_back(operation{ nullptr, optionalValue, operand });
 
  return true;
}

std::vector<Register::operation> Register::getOperations()
{
  return _operations;
}

int Register::evaluate()
{
  int result = 0;
  for (auto& op : _operations) {
    if (op.operand == "add") {
      result += op.reg ? op.reg->evaluate() : op.value;
    }
    else if (op.operand == "subtract") {
      result -= op.reg ? op.reg->evaluate() : op.value;
    }
    else if (op.operand == "multiply") {
      result *= op.reg ? op.reg->evaluate() : op.value;
    }
  }

  return result;
}

