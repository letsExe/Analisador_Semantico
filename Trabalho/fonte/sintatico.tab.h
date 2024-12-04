/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_SINTATICO_TAB_H_INCLUDED
# define YY_YY_SINTATICO_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INTEIRO = 258,
     REAL = 259,
     LETRA = 260,
     ID = 261,
     BIB = 262,
     WHITESPACE = 263,
     ENTER = 264,
     ERRO = 265,
     ASPAS = 266,
     IF_TOK = 267,
     ELSE_TOK = 268,
     FOR_TOK = 269,
     WHILE_TOK = 270,
     CHAR_TOK = 271,
     INT_TOK = 272,
     FLOAT_TOK = 273,
     DOUBLE_TOK = 274,
     VOID_TOK = 275,
     MAIN_TOK = 276,
     PRINT_TOK = 277,
     SCAN_TOK = 278,
     RETURN_TOK = 279,
     IMPORT_TOK = 280,
     DEFINE_TOK = 281,
     MAIS_TOK = 282,
     MENOS_TOK = 283,
     DIV_TOK = 284,
     MULT_TOK = 285,
     MOD_TOK = 286,
     NEG_TOK = 287,
     OR_TOK = 288,
     XOR_TOK = 289,
     AND_TOK = 290,
     L_AND_TOK = 291,
     L_OR_TOK = 292,
     L_SHL_TOK = 293,
     L_SHR_TOK = 294,
     INC_TOK = 295,
     DEC_TOK = 296,
     ATR_TOK = 297,
     ATR_SM_TOK = 298,
     ATR_DC_TOK = 299,
     ATR_MT_TOK = 300,
     ATR_DV_TOK = 301,
     ATR_MD_TOK = 302,
     IG_TOK = 303,
     DIF_TOK = 304,
     MEN_TOK = 305,
     MAI_TOK = 306,
     MAI_IG_TOK = 307,
     MEN_IG_TOK = 308,
     VIRG_TOK = 309,
     PVIRG_TOK = 310,
     DPONT_TOK = 311,
     A_PAR_TOK = 312,
     F_PAR_TOK = 313,
     A_COL_TOK = 314,
     F_COL_TOK = 315,
     A_CHA_TOK = 316,
     F_CHA_TOK = 317,
     COMENTARIO = 318,
     STRING = 319
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 2058 of yacc.c  */
#line 27 "sintatico.y"

    char *sval;
    double dval;
    int ival;


/* Line 2058 of yacc.c  */
#line 128 "sintatico.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_SINTATICO_TAB_H_INCLUDED  */
