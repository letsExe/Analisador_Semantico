%{
	#include <stdio.h>
    #include <stdlib.h>
    #include "semantico.h"
    #include "hash.h"
    #include "sintatico.tab.h"
    
    char err[10000];
    int caractere = 0;
    extern int linha;
    extern Hash *h, *simbolo; 
%}

%option noyywrap

INTEIRO     [0-9]+
REAL        [0-9]+"."[0-9]+
LETRA       [a-zA-z]
ID          [a-zA-Z][a-zA-Z0-9]*
BIB         [a-zA-Z][a-zA-Z0-9]*"."[a-zA-Z][a-zA-Z0-9]*

WHITESPACE  [ \t]
ENTER       [\n]
ERRO        [@$¨~çÇ§¹²³£¢¬₢°`]
ASPAS       ["]

IF_TOK      if
ELSE_TOK    else
FOR_TOK     for
WHILE_TOK   while

CHAR_TOK    char
INT_TOK     int
FLOAT_TOK   float
DOUBLE_TOK  double
VOID_TOK    void

MAIN_TOK    main
PRINT_TOK   print
SCAN_TOK    scan
RETURN_TOK  return
IMPORT_TOK  #import
DEFINE_TOK  #define

MAIS_TOK    "+"
MENOS_TOK   "-"
DIV_TOK     "/"
MULT_TOK    "*"
MOD_TOK     "%"

NEG_TOK     "!"
OR_TOK      "|"
XOR_TOK     "^"
AND_TOK     "&"

L_AND_TOK   "&&"
L_OR_TOK    "||"
L_SHL_TOK   "<<"
L_SHR_TOK   ">>"

INC_TOK     "++"
DEC_TOK     "--"

ATR_TOK     "="
ATR_SM_TOK  "+="
ATR_DC_TOK  "-="
ATR_MT_TOK  "*="
ATR_DV_TOK  "/="
ATR_MD_TOK  "%="

IG_TOK      "=="
DIF_TOK     "!="
MEN_TOK     "<"
MAI_TOK     ">"
MAI_IG_TOK  ">="
MEN_IG_TOK  "<="

VIRG_TOK    ","
PVIRG_TOK   ";"
DPONT_TOK   ":"

A_PAR_TOK   "("
F_PAR_TOK   ")"
A_COL_TOK   "["
F_COL_TOK   "]"
A_CHA_TOK   "{"
F_CHA_TOK   "}"

%%

{IF_TOK}         {strcat(err, yytext); inserirHash(h, yytext, "CONDICIONAL", NULL, 0, 0); yylval.sval = strdup(yytext); return IF_TOK;}
{ELSE_TOK}       {strcat(err, yytext); inserirHash(h, yytext, "CONDICIONAL", NULL, 0, 0); yylval.sval = strdup(yytext); return ELSE_TOK;}

{FOR_TOK}        {strcat(err, yytext); inserirHash(h, yytext, "REPETICAO", NULL, 0, 0); yylval.sval = strdup(yytext); return FOR_TOK;}
{WHILE_TOK}      {strcat(err, yytext); inserirHash(h, yytext, "REPETICAO", NULL, 0, 0); yylval.sval = strdup(yytext); return WHILE_TOK;}

{CHAR_TOK}       {strcat(err, yytext); inserirHash(h, yytext, "TIPO DE DADO", NULL, 0, 0); yylval.sval = strdup(yytext); return CHAR_TOK;}
{INT_TOK}        {strcat(err, yytext); inserirHash(h, yytext, "TIPO DE DADO", NULL, 0, 0); yylval.sval = strdup(yytext); return INT_TOK;}
{FLOAT_TOK}      {strcat(err, yytext); inserirHash(h, yytext, "TIPO DE DADO", NULL, 0, 0); yylval.sval = strdup(yytext); return FLOAT_TOK;}
{DOUBLE_TOK}     {strcat(err, yytext); inserirHash(h, yytext, "TIPO DE DADO", NULL, 0, 0); yylval.sval = strdup(yytext); return DOUBLE_TOK;}
{VOID_TOK}       {strcat(err, yytext); inserirHash(h, yytext, "TIPO DE DADO", NULL, 0, 0); yylval.sval = strdup(yytext); return VOID_TOK;}

{MAIN_TOK}       {strcat(err, yytext); inserirHash(h, yytext, "FUNCAO PRINCIPAL", NULL, 0, 0); yylval.sval = strdup(yytext); return MAIN_TOK;}
{PRINT_TOK}      {strcat(err, yytext); inserirHash(h, yytext, "FUNCAO DE SAIDA", NULL, 0, 0); yylval.sval = strdup(yytext); return PRINT_TOK;}
{SCAN_TOK}       {strcat(err, yytext); inserirHash(h, yytext, "FUNCAO DE LEITURA", NULL, 0, 0); yylval.sval = strdup(yytext); return SCAN_TOK;}
{RETURN_TOK}     {strcat(err, yytext); inserirHash(h, yytext, "COMANDO DE RETORNO", NULL, 0, 0); yylval.sval = strdup(yytext); return RETURN_TOK;}
{IMPORT_TOK}     {strcat(err, yytext); inserirHash(h, yytext, "COMANDO DE CABEÇALHO", NULL, 0, 0); yylval.sval = strdup(yytext); return IMPORT_TOK;}
{DEFINE_TOK}     {strcat(err, yytext); inserirHash(h, yytext, "COMANDO DE DEFINICAO", NULL, 0, 0); yylval.sval = strdup(yytext); return DEFINE_TOK;}

{MAIS_TOK}       {strcat(err, yytext); inserirHash(h, yytext, "OPERADOR SOMA", NULL, 0, 0); yylval.sval = strdup(yytext); return MAIS_TOK;}
{MENOS_TOK}      {strcat(err, yytext); inserirHash(h, yytext, "OPERADOR SUBTRACAO", NULL, 0, 0); yylval.sval = strdup(yytext); return MENOS_TOK;}
{DIV_TOK}        {strcat(err, yytext); inserirHash(h, yytext, "OPERADOR DIVISAO", NULL, 0, 0); yylval.sval = strdup(yytext); return DIV_TOK;}
{MULT_TOK}       {strcat(err, yytext); inserirHash(h, yytext, "OPERADOR MULTIPLICACAO", NULL, 0, 0); yylval.sval = strdup(yytext); return MULT_TOK;}
{MOD_TOK}        {strcat(err, yytext); inserirHash(h, yytext, "OPERADOR RESTO", NULL, 0, 0); yylval.sval = strdup(yytext); return MOD_TOK;}
{NEG_TOK}        {strcat(err, yytext); inserirHash(h, yytext, "OPERADOR DE NEGACAO", NULL, 0, 0); yylval.sval = strdup(yytext); return NEG_TOK;}
{OR_TOK}         {strcat(err, yytext); inserirHash(h, yytext, "OPERADOR DE OR", NULL, 0, 0); yylval.sval = strdup(yytext); return OR_TOK;}
{XOR_TOK}        {strcat(err, yytext); inserirHash(h, yytext, "OPERADOR DE XOR", NULL, 0, 0); yylval.sval = strdup(yytext); return XOR_TOK;}
{AND_TOK}        {strcat(err, yytext); inserirHash(h, yytext, "OPERADOR DE AND", NULL, 0, 0); yylval.sval = strdup(yytext); return AND_TOK;}

{L_AND_TOK}      {strcat(err, yytext); inserirHash(h, yytext, "AND LOGICO", NULL, 0, 0); yylval.sval = strdup(yytext); return L_AND_TOK;}
{L_OR_TOK}       {strcat(err, yytext); inserirHash(h, yytext, "OR LOGICO", NULL, 0, 0); yylval.sval = strdup(yytext); return L_OR_TOK;}
{L_SHL_TOK}      {strcat(err, yytext); inserirHash(h, yytext, "SHIFT LEFT", NULL, 0, 0); yylval.sval = strdup(yytext); return L_SHL_TOK;}
{L_SHR_TOK}      {strcat(err, yytext); inserirHash(h, yytext, "SHIFT RIGTH", NULL, 0, 0); yylval.sval = strdup(yytext); return L_SHR_TOK;}

{INC_TOK}        {strcat(err, yytext); inserirHash(h, yytext, "OPERADOR INCREMENTO", NULL, 0, 0); yylval.sval = strdup(yytext); return INC_TOK;}
{DEC_TOK}        {strcat(err, yytext); inserirHash(h, yytext, "OPERADOR DECREMENTO", NULL, 0, 0); yylval.sval = strdup(yytext); return DEC_TOK;}

{ATR_TOK}        {strcat(err, yytext); inserirHash(h, yytext, "OPERADOR ATRIBUICAO", NULL, 0, 0); yylval.sval = strdup(yytext); return ATR_TOK;}
{ATR_SM_TOK}     {strcat(err, yytext); inserirHash(h, yytext, "OPERADOR ATRIBUICAO COM SOMA", NULL, 0, 0); yylval.sval = strdup(yytext); return ATR_SM_TOK;}
{ATR_DC_TOK}     {strcat(err, yytext); inserirHash(h, yytext, "OPERADOR ATRIBUICAO COM DECREMENTO", NULL, 0, 0); yylval.sval = strdup(yytext); return ATR_DC_TOK;}
{ATR_MT_TOK}     {strcat(err, yytext); inserirHash(h, yytext, "OPERADOR ATRIBUICAO COM MULTIPLICACAO", NULL, 0, 0); yylval.sval = strdup(yytext); return ATR_MT_TOK;}
{ATR_DV_TOK}     {strcat(err, yytext); inserirHash(h, yytext, "OPERADOR ATRIBUICAO COM DIVISAO", NULL, 0, 0); yylval.sval = strdup(yytext); return ATR_DV_TOK;}
{ATR_MD_TOK}     {strcat(err, yytext); inserirHash(h, yytext, "OPERADOR ATRIBUICAO COM RESTO", NULL, 0, 0); yylval.sval = strdup(yytext); return ATR_MD_TOK;}

{IG_TOK}         {strcat(err, yytext); inserirHash(h, yytext, "OPERADOR IGUALDADE", NULL, 0, 0); yylval.sval = strdup(yytext); return IG_TOK;}
{DIF_TOK}        {strcat(err, yytext); inserirHash(h, yytext, "OPERADOR DIFERENTE", NULL, 0, 0); yylval.sval = strdup(yytext); return DIF_TOK;}
{MEN_TOK}        {strcat(err, yytext); inserirHash(h, yytext, "OPERADOR MENOR", NULL, 0, 0); yylval.sval = strdup(yytext); return MEN_TOK;}
{MAI_TOK}        {strcat(err, yytext); inserirHash(h, yytext, "OPERADOR MAIOR", NULL, 0, 0); yylval.sval = strdup(yytext); return MAI_TOK;}
{MAI_IG_TOK}     {strcat(err, yytext); inserirHash(h, yytext, "OPERADOR MAIOR IGUAL", NULL, 0, 0); yylval.sval = strdup(yytext); return MAI_IG_TOK;}
{MEN_IG_TOK}     {strcat(err, yytext); inserirHash(h, yytext, "OPERADOR MENOR IGUAL", NULL, 0, 0); yylval.sval = strdup(yytext); return MEN_IG_TOK;}

{VIRG_TOK}       {strcat(err, yytext); inserirHash(h, yytext, "VIRGULA", NULL, 0, 0); yylval.sval = strdup(yytext); return VIRG_TOK;}
{PVIRG_TOK}      {strcat(err, yytext); inserirHash(h, yytext, "PONTO E VIRGULA", NULL, 0, 0); yylval.sval = strdup(yytext); return PVIRG_TOK;}
{DPONT_TOK}      {strcat(err, yytext); inserirHash(h, yytext, "DOIS PONTO", NULL, 0, 0); yylval.sval = strdup(yytext); return DPONT_TOK;}

{A_PAR_TOK}      {strcat(err, yytext); inserirHash(h, yytext, "ABERTURA PARENTESES", NULL, 0, 0); yylval.sval = strdup(yytext); return A_PAR_TOK;}
{F_PAR_TOK}      {strcat(err, yytext); inserirHash(h, yytext, "FECHAMENTO PARENTESE", NULL, 0, 0); yylval.sval = strdup(yytext); return F_PAR_TOK;}
{A_CHA_TOK}      {strcat(err, yytext); inserirHash(h, yytext, "ABERTURA CHAVES", NULL, 0, 0); yylval.sval = strdup(yytext); return A_CHA_TOK;}
{F_CHA_TOK}      {strcat(err, yytext); inserirHash(h, yytext, "FECHAMENTO CHAVES", NULL, 0, 0); yylval.sval = strdup(yytext); return F_CHA_TOK;}
{A_COL_TOK}      {strcat(err, yytext); inserirHash(h, yytext, "ABERTURA COLCHETE", NULL, 0, 0); yylval.sval = strdup(yytext); return A_COL_TOK;}
{F_COL_TOK}      {strcat(err, yytext); inserirHash(h, yytext, "FECHAMENTO COLCHETE", NULL, 0, 0); yylval.sval = strdup(yytext); return F_COL_TOK;}

"//"[^\n]*\n     {strcat(err, yytext); yylval.sval = strdup(yytext);  return COMENTARIO;}
"/*"[^'*/']*"*/" {strcat(err, yytext); inserirHash(h, yytext, "COMENTARIO", NULL, 0, 0); yylval.sval = strdup(yytext); return COMENTARIO;}

{BIB}            {strcat(err, yytext); inserirHash(simbolo, yytext, "BIBLIOTECA", NULL, 0, 0); yylval.sval = strdup(yytext); return BIB;}
{ID}             {strcat(err, yytext); inserirHash(simbolo, yytext, "IDENTIFICADOR", NULL, 0, 0); yylval.sval = strdup(yytext);return ID;}

{REAL}           {strcat(err, yytext); char str[100]; sprintf(str, "%lf", atof(yytext)); inserirHash(simbolo, yytext, "REAL", NULL, 0, 0); yylval.dval = atof(yytext); return REAL;}
{INTEIRO}        {strcat(err, yytext); inserirHash(simbolo, yytext, "INTEIRO", NULL, 0, 0); yylval.ival = atoi(yytext); return INTEIRO;}
\"[^\"]*\"       {strcat(err, yytext); inserirHash(simbolo, yytext, "STRING", NULL, 0, 0); yylval.sval = strdup(yytext); return STRING;}

{WHITESPACE}     {strcat(err, yytext);}
{ENTER}          {caractere = verificaErro(err, linha); linha++; strcpy(err, "");}
{ERRO}           {strcat(err, yytext);}

[[:^space:]]+;

%%


