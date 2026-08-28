#include <iostream>
#include <fstream>
#include "preprocessor.h"
#include "mnemonics_validator.h"
#include "operand_validator.h"

using namespace std;

int main()
{
    string opcodeFile, asmFile, line;

    cout << "Enter opcode file: ";
    cin >> opcodeFile;
    cout << "Enter assembly file: ";
    cin >> asmFile;

    MnemonicValidator mv;
    OperandValidator ov;

    mv.loadOpcodeFile(opcodeFile);
    ov.loadRegisters("registers.txt");

    ifstream file(asmFile);
    if (!file)
    {
        cout << "File not found!";
        return 1;
    }

    while (getline(file, line))
    {
        if (line.empty() || line.find("SECTION") == 0 ||
            line.find(":") != string::npos)
            continue;

        ParsedLine p = preprocess(line);

        cout << "\nMnemonic: " << p.mnemonic;
        cout << "\nStatus: "
             << (mv.isValid(p.mnemonic) ? "Found" : "Not Found");

        for (const string& op : p.operands)
        {
            cout << "\nOperand: " << op;
            cout << "\nType: " << ov.getOperandType(op);
        }

        cout << "\n";
    }

    return 0;
}
