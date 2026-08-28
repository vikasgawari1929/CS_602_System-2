#ifndef OPERAND_VALIDATOR_H
#define OPERAND_VALIDATOR_H

#include <string>
#include <cctype>
#include "register_validator.h"

using namespace std;

class OperandValidator
{
    RegisterValidator registerValidator;

    bool isNumber(const string &op)
    {
        if (op.empty())
            return false;

        size_t i = (op[0] == '-' || op[0] == '+') ? 1 : 0;

        if (i == op.length())
            return false;

        for (; i < op.length(); i++)
            if (!isdigit((unsigned char)op[i]))
                return false;

        return true;
    }

    bool isHexConstant(const string &op)
    {
        if (op.empty())
            return false;

        if (op.back() == 'H')
        {
            if (op.length() == 1)
                return false;

            for (size_t i = 0; i < op.length() - 1; i++)
                if (!isxdigit((unsigned char)op[i]))
                    return false;

            return true;
        }

        if (op.length() > 2 && op[0] == '0' &&
            (op[1] == 'X' || op[1] == 'x'))
        {
            for (size_t i = 2; i < op.length(); i++)
                if (!isxdigit((unsigned char)op[i]))
                    return false;

            return true;
        }

        return false;
    }

    bool isMemoryOperand(const string &op)
    {
        return op.length() >= 2 &&
               op.front() == '[' && op.back() == ']';
    }

public:
    bool loadRegisters(const string &filename)
    {
        return registerValidator.loadRegisterFile(filename);
    }

    string getOperandType(string operand)
    {
        string cleaned;

        for (char c : operand)
            if (!isspace((unsigned char)c))
                cleaned += toupper((unsigned char)c);

        if (registerValidator.isRegister(cleaned))
            return "Register";

        if (isMemoryOperand(cleaned))
            return "Memory Operand";

        if (isNumber(cleaned) || isHexConstant(cleaned))
            return "Constant";

        return "Symbol";
    }
};

#endif
