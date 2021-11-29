%{
#include <stdio.h>
#include "hashtable.h"
extern FILE* yyin;

void yyerror(char *s);
int yylex(void);
int yyparse();
extern int yylineno;
hashtable *htable;
%}

%union {
    char *s;
    double d;
    int i;
}

%locations

%token PLUS MINUS DIVIDE TIMES EQUALS  TYPE PRINT  EOL END
%token P_LEFT P_RIGHT

%left P_LEFT P_RIGHT
%left PLUS MINUS
%left TIMES DIVIDE

%token <d> NUMBER 
%token <s> IDENTIFIER
%type <d> IDENTIFIER_CALC CALC PRINT_EXP

%%

PROGRAM:
    STATEMENT END{YYACCEPT;}
    ;

STATEMENT:
    LINE
    | STATEMENT STATEMENT
    ;

LINE:
    ATTRIBUTION
    | PRINT_EXP
    | DECLARATION
    | EOL
    ;

ATTRIBUTION:
    IDENTIFIER EQUALS CALC EOL { 
        Variable* variable = (Variable*)malloc(sizeof(Variable));
        variable->name = $1;
        variable->value = $3;
        hash_insert(htable,variable->name,variable);}
    | IDENTIFIER EQUALS IDENTIFIER_CALC EOL { 
        Variable* variable = (Variable*)malloc(sizeof(Variable));
        variable->name = $1;
        variable->value = $3;
        hash_insert(htable,variable->name,variable);}
    ;

IDENTIFIER_CALC:
    IDENTIFIER PLUS IDENTIFIER  {
        $$ = hash_lookup(htable,$1)->value + hash_lookup(htable,$3)->value;}
    | IDENTIFIER MINUS IDENTIFIER {
        $$ = hash_lookup(htable,$1)->value - hash_lookup(htable,$3)->value;}
    | IDENTIFIER DIVIDE IDENTIFIER {
        $$ = hash_lookup(htable,$1)->value / hash_lookup(htable,$3)->value;}
    | IDENTIFIER TIMES IDENTIFIER {
        $$ = hash_lookup(htable,$1)->value * hash_lookup(htable,$3)->value;}
    ;

CALC:
    NUMBER
    | CALC PLUS CALC {$$ = $1 + $3}
    | CALC MINUS CALC {$$ = $1 - $3}
    | CALC DIVIDE CALC {$$ = $1 / $3}
    | CALC TIMES CALC {$$ = $1 * $3}
    | P_LEFT CALC P_RIGHT {$$ = $2}
    ;

PRINT_EXP:
    PRINT P_LEFT IDENTIFIER P_RIGHT EOL { 
        printf("print: %s: %d\n", $3, hash_lookup(htable,$3)->value);
    }
    ;
 
DECLARATION:
    TYPE IDENTIFIER EOL
    ;

%%

void yyerror(char *s)
{
	printf("Error: %s\n", s);
    printf("Line: %d\n", yylineno);
}

int main(int argc, char *argv[])
{
    htable = hash_init(101);
    /*#ifdef YYDEBUG
        yydebug = 1;
    #endif
	*/
    int result;
    yyin = fopen(argv[1], "r");
    result = yyparse();
    if (result == 0){
        printf("Correct\n");
    }
	return 0;
}
