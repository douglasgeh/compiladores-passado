/*
Codigo ILOC

Autores:
  --> Douglas Gehring
  --> Tobias Soares

Grupo: O
*/

#include "Code.hpp"

/* 
returns the value that should be added to the RSP when a function is called 
so that it points to the next free space of the stack
16 is the sum of the spaces of: 
4 = return value
4 = return address
4 = old RSP
4 = old RFP
It assumes that all parameters have 4 bytes
*/
int getRSPIncrement(int sizeOfLocalVariables, int quantityOfParameters) {

	return 16 + sizeOfLocalVariables + quantityOfParameters * 4;
}

/*
returns the offset relative to the RFP in which the first local variable of a function is located
If the function has no parameters, this value is equal to 16
*/
int getOffsetLocalVariables(int quantityOfParameters) {
	return 16 + quantityOfParameters * 4;
}

/*
returns the offset relative to the RFP in which the return value is located
*/
int getReturnValueOffset(int sizeOfParameters) {
	return 12 + sizeOfParameters;
}