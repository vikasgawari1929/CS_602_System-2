#ifndef MNEMONICS_VALIDATOR_H
#define MNEMONICS_VALIDATOR_H

#include <fstream>
#include <string>
#include <set>
#include <sstream>
#include <cctype>

using namespace std;

class MnemonicValidator
{
    set<string> mnemonics;

    string upper(string str)
    {
        for (char &c : str)
            c = toupper((unsigned char)c);
        return str;
    }

public:
    bool loadOpcodeFile(const string &filename)
    {
        ifstream file(filename);
        if (!file) return false;

        string line, mnemonic;

        while (getline(file, line))
        {
            stringstream ss(line);
            ss >> mnemonic;

            if (!mnemonic.empty())
                mnemonics.insert(upper(mnemonic));
        }

        return true;
    }

    bool isValid(const string &mnemonic)
    {
        return mnemonics.find(upper(mnemonic)) != mnemonics.end();
    }
};

#endif
