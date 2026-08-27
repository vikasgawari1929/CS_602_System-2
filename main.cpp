#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

vector<string> opcodes;

bool isRegister(string s)
{
    string r[] = {"EAX","ECX","EDX","EBX","ESP","EBP","ESI","EDI"};

    for(string x : r)
        if(s == x) return true;

    return false;
}

string getType(string s)
{
    if(s.empty())
        return "UNKNOWN";

    if(isRegister(s))
        return "REGISTER";

    if(s[0] == '[' && s.back() == ']')
        return "MEMORY";

    if(isdigit(s[0]) || s.back() == 'H' || s.back() == 'h')
        return "CONSTANT";

    return "SYMBOL";
}

bool isFound(string m)
{
    for(string x : opcodes)
        if(m == x) return true;

    return false;
}

int main()
{
    ifstream opFile("opcode.txt");

    string m, code;

    while(opFile >> m >> code)
    {
        if(m != "Mnemonic")
            opcodes.push_back(m);
    }

    opFile.close();

    ifstream asmFile("program.asm");

    string line;

    cout << "\nMnemonic\tExists\t\tOperand\t\tType\n";
    cout << "------------------------------------------------\n";

    while(getline(asmFile, line))
    {
        if(line.empty())
            continue;

        stringstream ss(line);
        string mnemonic, operands;

        ss >> mnemonic;

        if(mnemonic.back() == ':')
            continue;

        if(mnemonic == "SECTION" ||
           mnemonic == "DB" ||
           mnemonic == "DW" ||
           mnemonic == "DD")
            continue;

        getline(ss, operands);

        transform(mnemonic.begin(), mnemonic.end(),
                  mnemonic.begin(), ::toupper);

        bool status = isFound(mnemonic);

        stringstream os(operands);
        string operand;

        while(getline(os, operand, ','))
        {
            operand.erase(0, operand.find_first_not_of(" \t"));
            operand.erase(operand.find_last_not_of(" \t") + 1);

            if(operand.empty())
                continue;

            cout << mnemonic << "\t\t"
                 << (status ? "FOUND" : "NOT FOUND")
                 << "\t\t"
                 << operand << "\t\t"
                 << getType(operand) << endl;
        }
    }

    asmFile.close();

    return 0;
}