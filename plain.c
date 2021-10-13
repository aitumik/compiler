#include <stdio.h>
#include "lex.h"

int statements()
{
    expression();

    if(match(SEMI))
        advance();
    else
        fprintf(stderr,"%d: Insertmissing semicolon\n",yylineno);
    if(!match(EOI))
        statements();
}

int expression()
{
    term();
    expr_prime();
}

int expr_prime()
{
    if(match(PLUS))
    {
        advance();
        term();
        expr_prime();
    }
}

int term()
{
    factor();
    term_prime();
}

int term_prime()
{
    if(match(TIMES))
    {
        advance();
        factor();
        term_prime();
    }
}

int factor()
{
    if(match(NUM_OR_ID)) advance();
    else if (match(LP))
    {
        advance();
        expression();
        if(match(RP)) advance();
        else fprintf(stderr,"%d Mismatched parenthesis",yylineno);
    } else {
        fprintf(stderr,"%d expected a number or identifier",yylineno);
    }
}
