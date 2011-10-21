//LexicalAnalyzer.h
#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H

#include <string>
using std::string;

#include<map>
#include "Lexeme.h"

typedef std::map<string, Lexeme> Lexememap;

class LexicalAnalyzer {
private:
	Lexememap lexmap;
	
	void loadData(string);
	
public:
	LexicalAnalyzer(const string filename);
	bool iskeyword(string);
	bool isspecial(char);
	void printTable();
};
#endif
