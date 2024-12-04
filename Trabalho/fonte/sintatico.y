%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <conio.h>

    #include "semantico.h"
    #include "arvore.h"
    #include "hash.h"
    #include "sintatico.tab.h"

    extern FILE *yyin;
    int linha = 1;
    char str[100]; 

    int yylex(void);
    void yyerror(char *);

    Item *tokens = NULL;
    Item *usuario = NULL;
    Item *item = NULL;
    Hash *h = NULL;
    Hash *simbolo = NULL;
    Pilha *p = NULL;
%}

%union{
    char *sval;
    double dval;
    int ival;
}

%token <ival> INTEIRO
%token <dval> REAL
%token <sval> LETRA
%token <sval> ID
%token <sval> BIB
%token WHITESPACE
%token ENTER
%token <sval> ERRO
%token <sval> ASPAS

%token <sval> IF_TOK
%token <sval> ELSE_TOK
%token <sval> FOR_TOK
%token <sval> WHILE_TOK

%token <sval> CHAR_TOK
%token <sval> INT_TOK
%token <sval> FLOAT_TOK
%token <sval> DOUBLE_TOK
%token <sval> VOID_TOK

%token <sval> MAIN_TOK
%token <sval> PRINT_TOK
%token <sval> SCAN_TOK
%token <sval> RETURN_TOK
%token <sval> IMPORT_TOK
%token <sval> DEFINE_TOK

%left <sval> MAIS_TOK
%left <sval> MENOS_TOK
%left <sval> DIV_TOK
%left <sval> MULT_TOK
%token <sval> MOD_TOK
%token <sval> NEG_TOK
%token <sval> OR_TOK
%token <sval> XOR_TOK
%token <sval> AND_TOK

%token <sval> L_AND_TOK
%token <sval> L_OR_TOK
%token <sval> L_SHL_TOK
%token <sval> L_SHR_TOK

%token <sval> INC_TOK
%token <sval> DEC_TOK

%token <sval> ATR_TOK
%token <sval> ATR_SM_TOK
%token <sval> ATR_DC_TOK
%token <sval> ATR_MT_TOK
%token <sval> ATR_DV_TOK
%token <sval> ATR_MD_TOK

%token <sval> IG_TOK
%token <sval> DIF_TOK
%token <sval> MEN_TOK
%token <sval> MAI_TOK
%token <sval> MAI_IG_TOK
%token <sval> MEN_IG_TOK

%token <sval> VIRG_TOK
%token <sval> PVIRG_TOK
%token <sval> DPONT_TOK

%token <sval> A_PAR_TOK
%token <sval> F_PAR_TOK
%token <sval> A_COL_TOK
%token <sval> F_COL_TOK
%token <sval> A_CHA_TOK
%token <sval> F_CHA_TOK

%token <sval> COMENTARIO
%token <sval> STRING

%type <ival> tipo 
%type <sval> id
%type <sval> main
%type <sval> exp
%type <sval> exp_simples
%type <sval> termo
%type <sval> fator
%type <sval> numero
%type <sval> sinal_atr
%type <sval> dec_var
%type <sval> soma
%type <sval> comp
%type <sval> mult
%type <sval> seq
%type <sval> dec
%type <sval> dec_ret
%type <sval> dec_cond
%type <sval> dec_rep
%type <sval> dec_atr
%type <sval> dec_lei
%type <sval> dec_esc
%type <sval> dec_func
%type <sval> comm
%type <sval> string
%type <sval> func
%type <sval> rep
%type <sval> logic

%%
inicio:
    definicoes                                      {p = insere(p, "Inicio", 1); printf("Sintaticamente Correto!!\n");}
    |                                               {printf("Vazio\n");}
    ;
definicoes:
    dec_imp definicoes                              {p = insere(p, "Definicoes", 2);}
    | dec_def definicoes                            {p = insere(p, "Definicoes", 2);}
    | seq                                           {p = insere(p, "Definicoes", 1);}
    ;
seq:
    dec pvirg                                       {$$ = strdup($1); p = insere(p, "Sequencia", 2);}
    | dec pvirg seq                                 {$$ = strdup($1); p = insere(p, "Sequencia", 3);}
    ;   
dec:
    main                                            {$$ = strdup($1); p = insere(p, "Declaracao", 1);}
    | dec_cond                                      {$$ = strdup($1); p = insere(p, "Declaracao", 1);}
    | dec_rep                                       {$$ = strdup($1); p = insere(p, "Declaracao", 1);}
    | dec_atr                                       {$$ = strdup($1); p = insere(p, "Declaracao", 1);}
    | dec_lei                                       {$$ = strdup($1); p = insere(p, "Declaracao", 1);}
    | dec_esc                                       {$$ = strdup($1); p = insere(p, "Declaracao", 1);}
    | exp                                           {$$ = strdup($1); p = insere(p, "Declaracao", 1);}
    | dec_func                                      {$$ = strdup($1); p = insere(p, "Declaracao", 1);}
    | dec_ret                                       {$$ = strdup($1); p = insere(p, "Declaracao", 1);}
    | comm                                          {$$ = strdup($1); p = insere(p, "Declaracao", 1);}
    | string                                        {$$ = strdup($1); p = insere(p, "Declaracao", 1);}
    | dec_var                                       {$$ = strdup($1); p = insere(p, "Declaracao", 1);}
    ;
dec_cond:
    cond_if abre_p exp fecha_p abre_c seq fecha_c                                           {$$ = strdup($6); p = insere(p, "Dec_cond", 7);}
    | cond_if abre_p exp fecha_p abre_c seq fecha_c cond_else abre_c seq fecha_c            {$$ = strdup($10); p = insere(p, "Dec_cond", 11);}
    ;
dec_rep: 
    rep abre_p dec_atr pvirg exp pvirg dec_atr fecha_p abre_c seq fecha_c                   {$$ = strdup($10); p = insere(p, "Dec_rep", 11);}
    | rep abre_p exp fecha_p abre_c seq fecha_c                                             {$$ = strdup($6); p = insere(p, "Dec_rep", 7);}
    ;
dec_atr:
    id sinal_atr exp                        {setValorId(simbolo, $1, $2, $3); p = insere(p, "Atribuicao", 3);}
    | dec_var sinal_atr exp                 {setValorId(simbolo, $1, $2, $3); p = insere(p, "Atribuicao", 3);}
    | id sinal_atr                          {incDec(simbolo, $1, $2); p = insere(p, "Atribuicao", 2);}
    ; 
dec_lei:
    scan abre_p id fecha_p                  {p = insere(p, "Dec_lei", 4);}
    ;
dec_esc:    
    print abre_p exp fecha_p                {p = insere(p, "Dec_esc", 4);}
    ;
dec_ret:
    ret exp                                 {$$ = strdup($2); p = insere(p, "Dec_ret", 2);}
    ;
dec_imp:
    imp comp bib comp                       {p = insere(p, "Dec_imp", 4);}
    ;
dec_def:
    def id exp                              {p = insere(p, "Dec_def", 3);}
    ;
dec_var:
    tipo id                                 {$$ = strdup($2); setCategoriaId(simbolo, 1, $2); setTipoId(simbolo, $1, $2); inicializaId(simbolo, $2); p = insere(p, "Dec_var", 2);}
    ;
exp:
    exp_simples comp exp_simples            {$$ = comparacao(simbolo, $1, $2, $3); p = insere(p, "Exp", 3);}
    | exp_simples                           {$$ = strdup($1); p = insere(p, "Exp", 1);}
    | exp_simples logic exp_simples         {$$ = logica(simbolo, $1, $2, $3); p = insere(p, "Exp", 3);}
    ;
dec_func:
    func abre_p lista_parametros fecha_p abre_c seq fecha_c         {$$ = strdup($1); setValorId(simbolo, $1, "=", $6); p = insere(p, "Dec_func", 7);}
    | func abre_p fecha_p abre_c seq fecha_c                        {$$ = strdup($1); setValorId(simbolo, $1, "=", $5); p = insere(p, "Dec_func", 6);}
    | tipo main abre_p fecha_p abre_c seq fecha_c                   {setCategoriaId(simbolo, 2, $2); setTipoId(simbolo, $1, $2); p = insere(p, "Dec_func", 7);}
    ;
func:
    tipo id                                 {$$ = strdup($2); setCategoriaId(simbolo, 2, $2); setTipoId(simbolo, $1, $2); inicializaId(simbolo, $2); p = insere(p, "Func", 2);}
    ;
lista_parametros:
    dec_var                                   {p = insere(p, "Lista_par", 1);}
    | dec_var virgula lista_parametros        {p = insere(p, "Lista_par", 3);}
    ;
exp_simples: 
    exp_simples soma termo      {$$ = soma(simbolo, $1, $2, $3, str); p = insere(p, "Exp_S", 3);}
    | termo                     {$$ = strdup($1); p = insere(p, "Exp_S", 1);}
    ;
termo:
    termo mult termo            {$$ = mult(simbolo, $1, $2, $3, str); p = insere(p, "Termo", 3);}
    | fator                     {$$ = strdup($1); p = insere(p, "Termo", 1);}
    ;
fator:
    abre_p exp fecha_p          {$$ = strdup($2); p = insere(p, "Fator", 3);}
    | numero                    {$$ = strdup($1); p = insere(p, "Fator", 1);}
    | id                        {$$ = strdup($1); p = insere(p, "Fator", 1);}
    ;

rep:
    FOR_TOK                     {$$ = strdup($1); p = insere(p, $1, 0); p = insere(p, "Rep", 1);}
    | WHILE_TOK                 {$$ = strdup($1); p = insere(p, $1, 0); p = insere(p, "Rep", 1);}
    ;
sinal_atr:
    ATR_TOK                     {$$ = strdup($1); p = insere(p, $1, 0); p = insere(p, "Sinal", 1);}
    | INC_TOK                   {$$ = strdup($1); p = insere(p, $1, 0); p = insere(p, "Sinal", 1);}
    | DEC_TOK                   {$$ = strdup($1); p = insere(p, $1, 0); p = insere(p, "Sinal", 1);}
    | ATR_SM_TOK                {$$ = strdup($1); p = insere(p, $1, 0); p = insere(p, "Sinal", 1);}
    | ATR_DC_TOK                {$$ = strdup($1); p = insere(p, $1, 0); p = insere(p, "Sinal", 1);}
    | ATR_MT_TOK                {$$ = strdup($1); p = insere(p, $1, 0); p = insere(p, "Sinal", 1);}
    | ATR_DV_TOK                {$$ = strdup($1); p = insere(p, $1, 0); p = insere(p, "Sinal", 1);}
    | ATR_MD_TOK                {$$ = strdup($1); p = insere(p, $1, 0); p = insere(p, "Sinal", 1);}
    ;
comp:
    MEN_TOK                     {$$ = strdup($1); p = insere(p, $1, 0); p = insere(p, "Comp", 1);}
    | IG_TOK                    {$$ = strdup($1); p = insere(p, $1, 0); p = insere(p, "Comp", 1);}
    | MAI_TOK                   {$$ = strdup($1); p = insere(p, $1, 0); p = insere(p, "Comp", 1);}
    | DIF_TOK                   {$$ = strdup($1); p = insere(p, $1, 0); p = insere(p, "Comp", 1);}
    | MAI_IG_TOK                {$$ = strdup($1); p = insere(p, $1, 0); p = insere(p, "Comp", 1);}
    | MEN_IG_TOK                {$$ = strdup($1); p = insere(p, $1, 0); p = insere(p, "Comp", 1);}
    ;
mult:
    MULT_TOK                    {$$ = strdup($1); p = insere(p, $1, 0); p = insere(p, "Mult", 1);}
    | DIV_TOK                   {$$ = strdup($1); p = insere(p, $1, 0); p = insere(p, "Mult", 1);}
    ;
soma:
    MAIS_TOK                    {$$ = strdup($1); p = insere(p, $1, 0); p = insere(p, "Soma", 1);}
    | MENOS_TOK                 {$$ = strdup($1); p = insere(p, $1, 0); p = insere(p, "Soma", 1);}
    ;
numero:
    INTEIRO                     {sprintf(str, "%d", $1); setTipoId(simbolo, 2, str); setCategoriaId(simbolo, 3, str); inicializaNum(simbolo, str); $$ = strdup(str); p = insereInt(p, $1, 0); p = insere(p, "Num", 1);}
    | REAL                      {sprintf(str, "%lf", $1); setTipoId(simbolo, 4, str); setCategoriaId(simbolo, 3, str); inicializaNum(simbolo, str); $$ = strdup(str); p = insereDouble(p, $1, 0); p = insere(p, "Num", 1);}
    ;
tipo:
    CHAR_TOK                    {$$ = 1; p = insere(p, $1, 0); p = insere(p, "Tipo", 1);}
    | INT_TOK                   {$$ = 2; p = insere(p, $1, 0); p = insere(p, "Tipo", 1);}
    | FLOAT_TOK                 {$$ = 3; p = insere(p, $1, 0); p = insere(p, "Tipo", 1);}
    | DOUBLE_TOK                {$$ = 4; p = insere(p, $1, 0); p = insere(p, "Tipo", 1);}
    | VOID_TOK                  {$$ = 5; p = insere(p, $1, 0); p = insere(p, "Tipo", 1);}
    ;
logic:
    L_AND_TOK                   {$$ = strdup($1); p = insere(p, $1, 0); p = insere(p, "Logic", 1);}
    | L_OR_TOK                  {$$ = strdup($1); p = insere(p, $1, 0); p = insere(p, "Logic", 1);}
    | L_SHL_TOK                 {$$ = strdup($1); p = insere(p, $1, 0); p = insere(p, "Logic", 1);}
    | L_SHR_TOK                 {$$ = strdup($1); p = insere(p, $1, 0); p = insere(p, "Logic", 1);}
    ;
comm:
    COMENTARIO                  {p = insere(p, $1, 0); p = insere(p, "Comentario", 1);}
    ;
string:
    STRING                      {p = insere(p, $1, 0); p = insere(p, "String", 1);}
    ;
id: 
    ID                          {$$ = strdup($1); p = insere(p, $1, 0); p = insere(p, "Id", 1);}
    ;
abre_p:
    A_PAR_TOK                   {p = insere(p, $1, 0); p = insere(p, "AbreP", 1);}
    ;
fecha_p:
    F_PAR_TOK                   {p = insere(p, $1, 0); p = insere(p, "FechaP", 1);}
    ;
abre_c:
    A_CHA_TOK                   {p = insere(p, $1, 0); p = insere(p, "AbreC", 1);}
    ;
fecha_c:
    F_CHA_TOK                   {p = insere(p, $1, 0); p = insere(p, "FechaC", 1);}
    ;
pvirg:
    PVIRG_TOK                   {p = insere(p, $1, 0); p = insere(p, "Pvirg", 1);}
    ;
main:
    MAIN_TOK                    {p = insere(p, $1, 0); p = insere(p, "Main", 1);}
    ;
cond_if:
    IF_TOK                      {p = insere(p, $1, 0); p = insere(p, "If", 1);}
    ;
cond_else:
    ELSE_TOK                    {p = insere(p, $1, 0); p = insere(p, "Else", 1);}
    ;
imp:
    IMPORT_TOK                  {p = insere(p, $1, 0); p = insere(p, "Importacao", 1);}
    ;
bib:
    BIB                         {p = insere(p, $1, 0); p = insere(p, "Biblioteca", 1);}
    ;
ret:
    RETURN_TOK                  {p = insere(p, $1, 0); p = insere(p, "Retorno", 1);}
    ;
def:
    DEFINE_TOK                  {p = insere(p, $1, 0); p = insere(p, "Define", 1);}
    ;
virgula:
    VIRG_TOK                    {p = insere(p, $1, 0); p = insere(p, "Virgula", 1);}
    ;
scan:
    SCAN_TOK                    {p = insere(p, $1, 0); p = insere(p, "Scan", 1);}
    ;
print:
    PRINT_TOK                   {p = insere(p, $1, 0); p = insere(p, "Print", 1);}
    ;
%%

void yyerror(char *s){
    printf("erro na linha %d -> %s\n", linha, s);
}

int main(){	
    char str[50];
    int saida = 1;
    int opcao;
    FILE* arq;
    
        
    do{
        system("cls");
        menu();
        printf("\n1 - Inserir arquivo de leitura\n");
        printf("2 - Imprimir tabela de tokens\n");
        printf("3 - Imprimir tabela de simbolos\n");
        printf("0 - Sair\n");
        printf("\nSelecione uma opcao: ");
        scanf("%d", &opcao);
    
        switch(opcao) {
            case 1 : 
                h = limpaHash(h);
                simbolo = limpaHash(simbolo);
                h = criarHash(200);
                simbolo = criarHash(200);
                system("cls");
                menu();
                printf("\nDigite o nome do arquivo: ");

                char caminho[100] = "..\\testes\\";
                scanf("%s", str);
                strcat(str, ".txt");
                strcat(caminho, str);

                arq = fopen(caminho, "r");
                while(arq == NULL){
                    printf("Digite o nome correto do arquivo: "); 

                    scanf("%s", str);
                    strcat(str, ".txt");
                    strcat(caminho, str);

                    arq = fopen(caminho, "r");
                }
                yyin = arq;
                system("cls");
                menu();
                yyparse(); 
                break;

            case 2 :
                system("cls");
                menu();
                printf("\nTABELA DE TOKENS\n\n"); 
                printf("        Token                   Nome                  Tipo               Categoria               Valor          \n");
                printf(" ______________________ _____________________ _____________________ _____________________ _____________________ \n");
                imprimirHash(h);
                printf(" ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ \n");
                break;
            case 3 : 
                system("cls");
                menu();
                printf("\nTABELA DE SIMBOLOS\n\n"); 
                printf("        Token                   Nome                  Tipo               Categoria               Valor          \n");
                printf(" ______________________ _____________________ _____________________ _____________________ _____________________ \n");
                imprimirHash(simbolo);
                printf(" ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ \n");
                printf("Tipo: 0 = token/nao declarado; 1 = char; 2 = int; 3 = float; 4 = double; 5 = void\n");
                printf("Categoria: 0 = token; 1 = variavel; 2 = procedimento; 3 = numero;\n\n\n");
                // 0 = eh um token, 1 = char, 2 = int, 3 = float, 4 = double, 5 = void;
                
                break;
    
        }
        printf("Total de linhas: %d\n\nPressione qualquer tecla para continuar...", linha);
        getch();
        imprimirPorNivel("arvore.txt", p->token);
        linha = 1;
        fclose(arq);
        
    }while(opcao != 0);
    yyparse();
    return 0;
}





