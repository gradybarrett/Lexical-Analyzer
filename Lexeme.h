/*
 Name: Grady Barrett
 Assignment: #2
 Title: A C Lexical Analyzer
 Course: CSCE 343
 Semester: Fall 2010
 Instructor: Laurie Murphy
 Date: 10/10/2010
 Sources consulted: http://www.cs.hmc.edu/~geoff/classes/hmc.cs070.200109/notes/io.html
 		    Laurie Murphy
 Known Bugs: none
 Program description: gets passed a program file, analyzes and records
 			lexemes and information about them(token class
 			and frequency) and prints the info. in a table.
 			Also prints frequency of each token class type
 			in the file to a formatted table.
 Creativity: anything extra that you added to the assignment (not required).
 Instructions: compile LexicalAnalyzer.cpp and test.cpp together and then
 		run ./a.out with the input filename as a command-line argument.
*/

//Lexeme.h
#ifndef LEXEME_H
#define LEXEME_H
#include <string>
using std::string;

class Lexeme{
public:
	int frequency;
	string tokClass;	
};
#endif
