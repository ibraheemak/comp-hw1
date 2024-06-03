%{
/* Declaration section */
#include <stdio.h>
#include "tokens.hpp"
%}
%option noyywrap
%option yylineno
relop   ([=!<>]=|<|>)
binop   (\+|\-|\*|\/)
comment (\/\/[^/r/n]*)
digit ([0-9])
positive ([1-9])
whitespace ([\t\n\r ])
legalStringChar ([ !#-\[\]-~])
escape ([\\\\|\\"|\\n|\\r|\\t|\\0])
hexa (\\x([0-9A-Fa-f])([0-9A-Fa-f]))
letter ([a-zA-Z])
%%
int                                         return INT;
byte                                        return BYTE;
b                                           return B;
bool                                        return BOOL;
and                                         return AND;
or                                          return OR;
not                                         return NOT;
true                                        return TRUE;
false                                       return FALSE; 
return                                      return RETURN; 
if                                          return IF;
else                                        return ELSE; 
while                                       return WHILE; 
break                                       return BREAK;
continue                                    return CONTINUE; 
;                                           return SC;
\(                                          return LPAREN;
\)                                          return RPAREN;
\{                                          return LBRACE;
\}                                          return RBRACE;
=                                           return ASSIGN;
{relop}                                     return RELOP; 
{binop}                                     return BINOP;
{comment}                                   return COMMENT; 
{letter}({letter}|{digit})*                 return ID;
({positive}{digit}*|0)                      return NUM;
\"({legalStringChar}|{escape}|{hexa})*\"    return STRING;
\"({legalStringChar}|{escape}|{hexa})*\\?   return UNCLOSED_STRING;
\"({legalStringChar}|{escape}|{hexa})*\\[^\\\"nrt0]  return UNDEFINED_ESCAPE;
\"({legalStringChar}|{escape}|{hexa})*\\((x([0-9a-fA-F][^0-9A-Fa-f]|[^0-9A-Fa-f][0-9A-Fa-f]|[^0-9A-Fa-f][^0-9A-Fa-f]|[^0-9A-Fa-f]))|x) return ILLEGAL_HEX;
{whitespace}                                  ;
.                                           return ERROR;
