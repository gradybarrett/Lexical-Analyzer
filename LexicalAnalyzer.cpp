//LexicalAnalyzer.cpp
#include <iostream>
using std::cout;
using std::endl;
using std::cerr;
using std::ios;
#include <cctype>
#include <fstream>
#include <cstdlib>
#include <iomanip>
using std::setw;
using std::setfill;
#include "LexicalAnalyzer.h"

//constructor that calls loadData file
LexicalAnalyzer::LexicalAnalyzer(const string filename){
	loadData(filename);
}

//Checks to see if identifier is a keyword
bool LexicalAnalyzer::iskeyword(string str){
	string keyword[] = {"if", "else", "for", "do", "while", "switch",
		"case", "default", "break", "return"};
	for(int i = 0; i < 10; i++){
		if(str == keyword[i]){
			return true;
		}
	}
	return false;
}

//checks to see if character is a special
bool LexicalAnalyzer::isspecial(char ch){
	char special[] = {'(', ')', '[', ']', '+', '-', '=', ',', ';', '{', 
		'}', '&', '*', '/'};
	for(int i = 0; i < 14; i++){
		if(ch == special[i])
			return true;
	}
	return false;
}

//Prints all of the data about the contents of the input file
void LexicalAnalyzer::printTable(){
	string classTypes[] = {"Keyword", "Identifier", "Int Literal", 
		"Real Literal", "String Literal", "Special"};
		int classCounters[] = {0, 0, 0, 0, 0, 0};
	string lexemeName;
	Lexememap::iterator iter;
	
	cout << "File reading finished."<< endl;
	cout << setfill('=') << setw(24)<<"="<<endl;
	cout << "Symbol table"<<endl;
	cout << setfill('=') << setw(24)<<"="<<endl;
	cout << setfill(' ') << "Lexeme"<<setw(20)<<"|"<<"  # Appearances  |  Class"<<endl;
	cout << "-------------------------+-----------------+-------------"<<endl;
	
	//print out map information and increment token class counters
	for(iter = lexmap.begin(); iter != lexmap.end(); ++iter){
		cout.setf(ios::left);
		cout<<setw(25)<<iter->first<<"|"<<setw(17)
			<<iter->second.frequency<<"|"
			<<iter->second.tokClass<<endl;
		//!!!!!!!!!!!!!!!!!could use for loop	
		if(iter->second.tokClass == "Keyword"){
			classCounters[0]+= iter->second.frequency;
		}else if(iter->second.tokClass == "Identifier"){
			classCounters[1]+= iter->second.frequency;
		}else if(iter->second.tokClass == "Int Literal"){
			classCounters[2]+= iter->second.frequency;
		}else if(iter->second.tokClass == "Real Literal"){
			classCounters[3]+= iter->second.frequency;
		}else if(iter->second.tokClass == "String Literal"){
			classCounters[4]+= iter->second.frequency;
		}else if(iter->second.tokClass == "Special"){
			classCounters[5]+= iter->second.frequency;
		}
	}
	
	//print out statistics for token classes
	cout << endl << setfill('=') << setw(24)<<"="<<endl;
	cout << "Statistics"<<endl;
	cout << setfill('=') << setw(24)<<"="<<endl;
	cout << setfill(' ') <<setw(16)<< "Class"<<"|"<<"  # Appearances"<<endl;
	cout << "----------------+-------------"<<endl;
	for(int i = 0; i < 6; i++){
		cout<<setw(16)<<classTypes[i]<<"|"<<classCounters[i]<<endl;
	}
}

//Loads and analyzes the data in an input file of name "filename"
void LexicalAnalyzer::loadData(string filename){
	string lexeme; //string to hold assembled lexeme
	char c;//character from file
	
	//open file
	std::ifstream inFile;
	inFile.open(filename.c_str());
	
	
	//check for no filename/non-existant file
	if(!inFile){
		cerr << "Could not open " << filename << " for reading.";
		std::exit(1);
	}
	
	// Read file one character at a time
	c = inFile.get();
	while( !inFile.eof()){
		Lexeme lex;
		lexeme = "";
		Lexememap::iterator iter;
		
		//check for string literal
		if(c == '"'){
			lexeme.append(1,c);
			do{
				c = inFile.get();
				lexeme.append(1,c);
			}while(c != '"');
			
			//check to see if extracted lexeme is in map already
			if((iter = lexmap.find(lexeme)) != lexmap.end()){
				(iter->second.frequency)++;
			}
			//otherwise, add new lexeme object to map.
			else{
				lex.frequency = 1;
				lex.tokClass = "String Literal";
				lexmap[lexeme] = lex;
			}			
		}
		//check for special character
		else if(isspecial(c)){
			lexeme.append(1,c);
			if((iter = lexmap.find(lexeme)) != lexmap.end()){
				(iter->second.frequency)++;
			}
			//otherwise, add new lexeme object to map.
			else{
				lex.frequency = 1;
				lex.tokClass = "Special";
				lexmap[lexeme] = lex;
			}
		}
		
		//check for real literal or int literal
		else if(isdigit(c)||c == '.'){
			if(isdigit(c)){
				do{
					lexeme.append(1,c);
					c = inFile.get();
				}while(isdigit(c));
			}
			//check for real literal
			if(c == '.'){
				do{
					lexeme.append(1,c);
					c = inFile.get();
				}while(isdigit(c));
				inFile.putback(c);
				
				//Put real literal in map
				//check to see if real literal is in map
				if((iter = lexmap.find(lexeme)) != lexmap.end()){
					(iter->second.frequency)++;
				}
				//otherwise, add new real literal to map.
				else{
					lex.frequency = 1;
					lex.tokClass = "Real Literal";
					lexmap[lexeme] = lex;
				}
			}
			//otherwise it is an int literal
			else{
				inFile.putback(c);
				
				//Put int literal in map
				//check to see if int literal is in map
				if((iter = lexmap.find(lexeme)) != lexmap.end()){
					(iter->second.frequency)++;
				}
				//otherwise, add new int literal to map.
				else{
					lex.frequency = 1;
					lex.tokClass = "Int Literal";
					lexmap[lexeme] = lex;
				}
			}
		}
		
		//Check for identifier or keyword
		else if (isalpha(c)){
			do{
				lexeme.append(1,c);
				c = inFile.get();
			}while(isalpha(c)||isdigit(c));
			inFile.putback(c);
			
			//check if lexeme is a keyword
			if(iskeyword(lexeme)){
				
				//Put keyword in map
				//check to see if keyword is in map
				if((iter = lexmap.find(lexeme)) != lexmap.end()){
					(iter->second.frequency)++;
				}
				//otherwise, add new keyword to map.
				else{
					lex.frequency = 1;
					lex.tokClass = "Keyword";
					lexmap[lexeme] = lex;
				}
			}
			//otherwise lexeme is identifier
			else{
				//Put identifier in map
				//check to see if identifier is in map
				if((iter = lexmap.find(lexeme)) != lexmap.end()){
					(iter->second.frequency)++;
				}
				//otherwise, add new identifier to map.
				else{
					lex.frequency = 1;
					lex.tokClass = "Identifier";
					lexmap[lexeme] = lex;
				}
			}
		}
		//get another character from the file
		c = inFile.get();
	}
}


