//test.cpp
#include <iostream>
using std::cout;
using std::endl;

#include "LexicalAnalyzer.h"
#include "Lexeme.h"

int main(int argc, char *argv[]){
	LexicalAnalyzer lexical(argv[1]);
	
	lexical.printTable();
}
