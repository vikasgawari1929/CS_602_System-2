#ifndef REGISTER_VALIDATOR_H
#define REGISTER_VALIDATOR_H

#include <fstream>
#include <string>
#include <set>
#include <cctype>

using namespace std;

class RegisterValidator
{
    set<string> registers;

    string upper(string str)
    {
        for (char &c : str)
            c = toupper((unsigned char)c);
        return str;
    }

public:
    bool loadRegisterFile(const string &filename)
    {
        ifstream file(filename);
        if (!file) return false;

        string reg;

        while (file >> reg)
            registers.insert(upper(reg));

        return true;
    }

    bool isRegister(const string &operand)
    {
        return registers.find(upper(operand)) != registers.end();
    }
};

#endif
