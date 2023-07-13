/*
Imprime codigo ILOC

Autores:
  --> Douglas Gehring
  --> Tobias Soares

Grupo: O
*/

#include "CodePrinter.hpp"
#include "AST.hpp"
#include "Code.hpp"
#include <list>
#include <iostream>

using namespace std;

CodePrinter::CodePrinter() { }

void CodePrinter::printTree(void *tree) {

    AST *rootNode = (AST *) tree;

    list<InstructionCode>::iterator it;

    for (it = rootNode->code.begin(); it != rootNode->code.end(); ++it) {

       this->printCode(*it);
    }
    
}

void CodePrinter::printCode(InstructionCode code) {
     
    if (code.prefixLabel != -1) {
        cout << "L" << to_string(code.prefixLabel) << ": ";
    }
    printInstructionType(code.instructionType);
    if (code.leftOperands.size() > 0) {
        cout << " ";
        printOperands(code.leftOperands);
    }
    if (code.rightOperands.size() > 0) {
        cout << " => ";
        printOperands(code.rightOperands);
    }
    
    cout << endl;

}

void CodePrinter::printOperands(list<CodeOperand> operands) {

    list<CodeOperand>::iterator it;
    it = operands.begin();
    this->printOperand(*it);
    it++;

    for (it; it != operands.end(); ++it) {
        cout << ", ";
        this->printOperand(*it);
    }

}

void CodePrinter::printOperand(CodeOperand operand) {

    string numbericalValueString = to_string(operand.numericalValue);
    RegisterPointerType type;
    switch (operand.operandType) {
    case _register:
        cout << "r" << numbericalValueString;
        break;
    case registerPointer:
        type = (RegisterPointerType) operand.numericalValue;
        this->printRegisterPointer(type);
        break;
    case label:
        cout << "L" << numbericalValueString;
        break;
    case number:
        cout << numbericalValueString;
        break;
    default:
        break;
    }

}

void CodePrinter::printRegisterPointer(RegisterPointerType type) {


    switch (type)
    {
    case rbss:
        cout << "rbss";
        break;
    case rfp:
        cout << "rfp";
        break;
    case rsp:
        cout << "rsp";
        break;
    case rpc:
        cout << "rpc";
        break;
    default:
        break;
    }
}

void CodePrinter::printInstructionType(InstructionType type) {

    switch (type)
    {
    case nop:
        cout << "nop";
        break;
    case add:
        cout << "add";
        break;
    case sub:
        cout << "sub";
		break;
    case mult:
        cout << "mult";
		break;
    case _div:
        cout << "div";
		break;
    case addI:
        cout << "addI";
		break;
    case subI:
        cout << "subI";
		break;
    case rsubI:
        cout << "rsubI";
		break;
    case multI:
        cout << "multI";
		break;
    case divI:
        cout << "divI";
		break;
    case rdivI:
        cout << "rdivI";
		break;
    case lshift:
        cout << "lshift";
		break;
    case lshiftI:
        cout << "lshiftI";
		break;
    case rshift:
        cout << "rshift";
		break;
    case rshiftI:
        cout << "rshiftI";
		break;
    case _and:
        cout << "and";
		break;
    case andI:
        cout << "andI";
		break;
    case _or:
        cout << "or";
		break;
    case orI:
        cout << "orI";
		break;
    case _xor:
        cout << "xor";
		break;
    case xorI:
        cout << "xorI";
		break;
    case load:
        cout << "load";
		break; 
    case loadI:
        cout << "loadI";
		break; 
    case loadAI:
        cout << "loadAI";
		break; 
    case loadAO:
        cout << "loadAO";
		break; 
    case cload:
        cout << "cload";
		break;
    case cloadAI:
        cout << "cloadAI";
		break;
    case cloadAO:
        cout << "cloadAO";
		break;
    case store:
        cout << "store";
		break; 
    case storeAI:
        cout << "storeAI";
		break; 
    case storeAO:
        cout << "storeAO";
		break; 
    case cstore:
        cout << "cstore";
		break; 
    case cstoreAI:
        cout << "cstoreAI";
		break; 
    case cstoreAO:
        cout << "cstoreAO";
		break; 
    case i2i:
        cout << "i2i";
		break;
    case c2c:
        cout << "c2c";
		break;
    case c2i:
        cout << "c2i";
		break;
    case i2c:
        cout << "i2c";
		break;
    case jump:
        cout << "jump";
		break;
    case jumpI:
        cout << "jumpI";
		break;
    case cbr:
        cout << "cbr";
		break;
    case cmp_LT:
        cout << "cmp_LT";
		break;
    case cmp_LE:
        cout << "cmp_LE";
		break;
    case cmp_EQ:
        cout << "cmp_EQ";
		break;
    case cmp_GE:
        cout << "cmp_GE";
		break;
    case cmp_GT:
        cout << "cmp_GT";
		break;
    case cmp_NE:
        cout << "cmp_NE";
		break;
    case halt:
        cout << "halt";
		break;
    }

}