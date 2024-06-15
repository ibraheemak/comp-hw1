#include "tokens.hpp"
#include <iostream>
#include <string>
#include <sstream>
using std::cout;
using std::endl;
using std::string;

void printToken(int token);
std::string TokenToString(int token);
string processString();
void printHexError();
int main()
{
	int token;
	while(token = yylex()) {
		printToken(token);
	}
	return 0;
}

void printToken(int token){
	std::string tokenName=TokenToString(token);
	if(tokenName!="STRING"&&tokenName!="COMMENT"&&tokenName!="ERROR"&&tokenName!="UNCLOSED_STRING"&&tokenName!="UNDEFINED_ESCAPE"&&tokenName!="ILLEGAL_HEX"){
		cout<<yylineno<<" "<<TokenToString(token)<<" "<<yytext<<endl;
	}
	if(tokenName=="STRING"){
		cout<<yylineno<<" "<<TokenToString(token)<<" "<<processString()<<endl;
	}
	if (tokenName=="COMMENT"){
		cout<<yylineno<<" "<<TokenToString(token)<<" "<<"//"<<endl;
	}
	if (tokenName=="ERROR")
	{
		cout<<"Error "<<yytext<<endl;
		exit(0);
	}
	if (tokenName=="UNCLOSED_STRING")
	{
		cout<<"Error unclosed string"<<endl;
		exit(0);
	}
	if (tokenName=="UNDEFINED_ESCAPE")
	{
		cout<<"Error undefined escape sequence "<<yytext[yyleng-1]<<endl;
		exit(0);
	}
	if(tokenName=="ILLEGAL_HEX"){
		cout<<"Error undefined escape sequence ";
		printHexError();
		exit(0);
	}
	
}

void printHexError(){
 if(yytext[yyleng-1]=='"'){
	if(yytext[yyleng-2]=='x'&&yytext[yyleng-3]=='\\'){
		cout<<"x"<<endl;
	}
	else if (yytext[yyleng-3]=='x'&&yytext[yyleng-4]=='\\'){
		cout<<"x"<<yytext[yyleng-2]<<endl;
	}
	else if(yytext[yyleng-4]=='x'&&yytext[yyleng-5]=='\\'){
		cout<<"x"<<yytext[yyleng-3]<<yytext[yyleng-2]<<endl;
	}
 }else{
	if(yytext[yyleng-1]=='x'&&yytext[yyleng-2]=='\\'){
		cout<<"x"<<endl;
	}
	else if (yytext[yyleng-2]=='x'&&yytext[yyleng-3]=='\\'){
		cout<<"x"<<yytext[yyleng-1]<<endl;
	}
	else if(yytext[yyleng-3]=='x'&&yytext[yyleng-4]=='\\'){
		cout<<"x"<<yytext[yyleng-2]<<yytext[yyleng-1]<<endl;
	}
 }
}

std::string TokenToString(int token){
switch (token)
{
case INT: return "INT";
case BYTE: return "BYTE";
case B: return "B";
case BOOL: return "BOOL";
case AND: return "AND";
case OR: return "OR";
case NOT: return "NOT";
case TRUE: return "TRUE";
case FALSE: return "FALSE";
case RETURN: return "RETURN";
case IF: return "IF";
case ELSE: return "ELSE";
case WHILE: return "WHILE";
case BREAK: return "BREAK";
case CONTINUE: return "CONTINUE";
case SC: return "SC";
case LPAREN: return "LPAREN";
case RPAREN: return "RPAREN";
case LBRACE: return "LBRACE";
case RBRACE: return "RBRACE";
case ASSIGN: return "ASSIGN";
case RELOP: return "RELOP";
case BINOP: return "BINOP";
case COMMENT: return "COMMENT";
case ID: return "ID";
case NUM: return "NUM";
case STRING: return "STRING";
case ERROR: return "ERROR";
case UNCLOSED_STRING: return "UNCLOSED_STRING";
case UNDEFINED_ESCAPE: return "UNDEFINED_ESCAPE";
case ILLEGAL_HEX: return "ILLEGAL_HEX";


default: return "OPS";
}
}

string processString(){
 string  result;
 if(yyleng==2){//it is empty string
	return result;
 }
 for(int i=1;i<yyleng-1;i++){
	if(yytext[i]=='\\'&&yytext[i+1]=='0'){
		return result;
	}
	 if(yytext[i]=='\\'){
		
		if(yytext[i+1]=='x'){
			std::stringstream stream;
            stream << std::hex << yytext[i + 2] << yytext[i + 3];
            int asciiValue;
            stream >> asciiValue;
			if(asciiValue==0){
				return result;
			}
        	result += static_cast<char>(asciiValue);
            i += 3;

		}
		else {
			switch (yytext[i+1])
		{
		case 'n': result+= '\n';
			break;
		case 'r': result+='\r';
			break;
		case 't': result+='\t';
			break;
		case '\\': result+='\\';
			break;
		case '\"': result+='\"';
			break;
		default:
			break;
		}
		i++;
		}
	}
	else{
		result+=yytext[i];
	}
 }
return result;
} 