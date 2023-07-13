/*
Codigo ILOC

Autores:
  --> Douglas Gehring
  --> Tobias Soares

Grupo: O
*/

#ifndef CODE_GENERATOR_HPP
#define CODE_GENERATOR_HPP

using namespace std;
#include <string>
#include <utility>
#include "AST.hpp"
#include "Code.hpp"

class CodeGenerator
{
private:
    int registerNumber;
    int getRegister();
    int labelNumber;
    
    InstructionCode makeOffsetLocalVariables(int offset);
    InstructionCode makeNop(int label);
    void appendCode(AST *parent, list<InstructionCode> newCode);
    void prependCode(AST *node, list<InstructionCode> newCode);
    list<InstructionCode> makeCompare(CodeOperand r1Operand, CodeOperand labelTrue, CodeOperand labelFalse);
    InstructionCode makeCBR(CodeOperand r3Operand, CodeOperand labelTrue, CodeOperand labelFalse);
    list<InstructionCode> makeCMPNE(CodeOperand r1Operand, CodeOperand r3Operand);
    void coverPatchworks(list<InstructionCode> &code, CodeOperand labelOperand, bool patchworkType);
    InstructionCode loadConstant(int constant, CodeOperand registerDestination);
    InstructionCode makeBinaryInstruction(InstructionType instructionType, int prefixLabel, CodeOperand r1Operand, 
    CodeOperand r2Operand, CodeOperand r3Operand);
    InstructionCode makeStoreAI(int prefixLabel, CodeOperand op1, CodeOperand op2, CodeOperand op3);
    InstructionCode makeJumpInstruction(CodeOperand destinationLabel);
    InstructionCode makeHalt();
    list<InstructionCode> makeInitialCode(int preliminaryCodeSize);
    InstructionCode makeLoad(CodeOperand r1, CodeOperand c1, CodeOperand r2);
    InstructionCode makeStore(CodeOperand r1, CodeOperand r2);
    void resolveParameters(AST* functionCallNode, AST *firstParameterNode);
    void pushParameters(AST* functionCallNode, AST *firstParameterNode);
    list<InstructionCode> makeParameterCopy(int quantityOfParameters, int offsetLocalVariables);
    void pushRegisters(AST *functionCallNode, pair<int, int> registerRange, int initialOffset);
    void popRegisters(AST *returnNode, pair<int, int> registerRange, int initialOffset);

    //aka remenda
    void coverPatchworks(AST *node, CodeOperand labelOperand, bool patchworkType);
    list<InstructionCode> createBoolFlow(AST *node, int destinationLabel, CodeOperand destinationRegister);
    InstructionCode loadBooleanCode(bool boolean, CodeOperand registerDestination);
    void resolveTernaryOperand(AST *rootNode, AST *nodeExp1, CodeOperand resultRegisterOperand);
    void resolveArithmetic(AST *rootNode, AST *nodeExp, int resultRegister, int nextInstructionLabel);
    void resolveLogical(AST *rootNode, AST *nodeExp, CodeOperand labelTrue, CodeOperand labelFalse);
    void makeSub(AST *expressionNode, AST *symbolNode);
    void makeNot(AST *expressionNode, AST *symbolNode);

public:
    int getLabel();
    int getRegisterNumber();
    void restartRegisterNumber();
    CodeGenerator();
    void makeLiteralCode(AST *literalNode);
    void makeAttributionLocalVariable(AST *attSymbolNode, AST *attributionNode, OffsetAndScope offsetAndScope);
    void makeFunction(AST *functionNode, int offsetLocalVarFunction, 
    int quantityOfParameters, int functionLabel, AST *fuctionBlockNode);
    void appendCode(AST *parent, AST*child);
    void makeBinaryOperation(AST *leftOperandNode, AST *symbolNode, AST *rightOperandNode);
    void makeAnd(AST *leftOperandNode, AST *symbolNode, AST *rightOperandNode);
    void makeOr(AST *leftOperandNode, AST *symbolNode, AST *rightOperandNode);
    void makeIf(AST *ifNode, AST *expNode, AST *ifBlockNode, AST *elseBlockNode);
    void makeWhile(AST *whileNode, AST *expNode, AST *whileBlockNode);
    void makeFor(AST *forNode, AST *att1Node, AST *expNode, AST *att2Node, AST *forBlockNode);
    void makeDeclaredVariable(AST *variableNode, OffsetAndScope offsetAndScope);
    void makeReturn(AST* returnNode, AST *expNode, int offsetReturnValue);
    void makeEmptyReturn(AST *functionNode, int offsetRetValue);
    void makeFunctionCall(AST* functionCallNode, AST *firstParameterNode, int functionLabel, 
    int returnValueOffset, int quantityOfParameters);
    void makeUnaryOperation(AST *expressionNode, AST *symbolNode);
    void makeTernaryOperation(AST *exp1, AST *rootNode, AST *exp2, AST *exp3);
    
    void generateFinalCode(AST *finalTree);
    void generateInitialCode(AST *finalTree);
    
};


#endif