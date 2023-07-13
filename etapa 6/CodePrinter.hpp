/*
Imprime codigo ILOC

Autores:
  --> Douglas Gehring
  --> Tobias Soares

Grupo: O
*/

#ifndef CODE_PRINTER_HPP
#define CODE_PRINTER_HPP

#include "AST.hpp"
#include "Code.hpp"

class CodePrinter {

private:
    void printInstructionType(InstructionType type);
    void printOperands(list<CodeOperand> operands);
    void printOperand(CodeOperand operand);
    void printRegisterPointer(RegisterPointerType type);

public:
    CodePrinter();
    void printTree(void *tree);
    void printCode(InstructionCode code);
};



#endif