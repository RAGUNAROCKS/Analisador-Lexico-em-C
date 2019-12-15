#include <stdio.h>
#include <string.h>
#include <time.h>
 
#define ET -1   //ERRO de TRANSICAO
#define EP 0    //ESTADO de PARADA
#define EF 250  //ESTADO FINAL
#define SI -5   //SIMBOLO INVALIDO
#define TC ' '  //ESPACO VAZIO
#define TE '\n' //QUEBRA DE LINHA
#define ID 28   //INDENTIFICADOR
#define AS 29   //ASPAS
#define NU 30   //NUMERO
#define SG 31   //OPERADOR RELACIONAL
#define PR 32   //PARENTESES
#define CC 33   //COLCHETES
#define CH 34   //CHAVES
#define OA 35   //OPERADOR ARITMETICO
#define AO 36   //:=

#define COMP_FITA 1000
#define MAX_SIMBOLOS 52
#define MAX_ESTADOS 250
 
/*#####################################################################*/
 
void _completa_fita(FILE *arq);
void _varrer_a_fita(void);
int _varrer_modo_padrao(void);
int _encontra_simbolo(char);
 
/*#####################################################################*/
 
int tabela_t[MAX_ESTADOS][MAX_SIMBOLOS] = {
	/*Estado 0*/
	{ ID, ID, ID,  4,  1, ID, ID,  3, ID, ID, ID, ID,  8, ID,  6, ID,  5,  2,  7, ID, ID, ID, ID, ID, ID, NU, NU, NU, NU, NU, NU, NU, NU, NU, NU, SG, SG, SG, PR, PR, CH, CH, OA, OA, OA, ET, ET, AS, CC, CC, OA, AO},
    /*Estado 1*/
	{ ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID,  9, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ET, ET, ET, ET, ET, ET, ET, ET, ET, ET, ID, ET, AS, ET, ET, ET, ET},
    /*Estado 2*/
	{ ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, 11, ID, ID, 10, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ET, ET, ET, ET, ET, ET, ET, ET, ET, ET, ID, ET, AS, ET, ET, ET, ET},
    /*Estado 3 (IF)*/
	{ ID, ID, ID, ID, EP, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ET, ET, ET, ET, ET, ET, ET, ET, ET, ET, ID, ET, AS, ET, ET, ET, ET},
    /*Estado 4*/
	{ ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, 12, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ET, ET, ET, ET, ET, ET, ET, ET, ET, ET, ID, ET, AS, ET, ET, ET, ET},
    /*Estado 5*/
	{ ID, ID, ID, 13, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ET, ET, ET, ET, ET, ET, ET, ET, ET, ET, ID, ET, AS, ET, ET, ET, ET},
    /*Estado 6*/
	{ ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, 14, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ET, ET, ET, ET, ET, ET, ET, ET, ET, ET, ID, ET, AS, ET, ET, ET, ET},
    /*Estado 7 (TO)*/
	{ ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, EP, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ET, ET, ET, ET, ET, ET, ET, ET, ET, ET, ID, ET, AS, ET, ET, ET, ET},
    /*Estado 8*/
	{ ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, 15, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ET, ET, ET, ET, ET, ET, ET, ET, ET, ET, ID, ET, AS, ET, ET, ET, ET},
    /*Estado 9 (FOR)*/
	{ ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, EP, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ET, ET, ET, ET, ET, ET, ET, ET, ET, ET, ID, ET, AS, ET, ET, ET, ET},
    /*Estado 10*/
	{ ID, ID, ID, 16, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, 17, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ET, ET, ET, ET, ET, ET, ET, ET, ET, ET, ID, ET, AS, ET, ET, ET, ET},
    /*Estado 11*/
	{ ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, 18, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ET, ET, ET, ET, ET, ET, ET, ET, ET, ET, ID, ET, AS, ET, ET, ET, ET},
    /*Estado 12*/
	{ ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, 19, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ET, ET, ET, ET, ET, ET, ET, ET, ET, ET, ID, ET, AS, ET, ET, ET, ET},
    /*Estado 13*/
	{ 20, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, 21, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ET, ET, ET, ET, ET, ET, ET, ET, ET, ET, ID, ET, AS, ET, ET, ET, ET},
    /*Estado 14*/
	{ ID, ID, ID, ID, ID, ID, ID, 22, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ET, ET, ET, ET, ET, ET, ET, ET, ET, ET, ID, ET, AS, ET, ET, ET, ET},
    /*Estado 15 (NUM)*/
	{ ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, EP, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ET, ET, ET, ET, ET, ET, ET, ET, ET, ET, ID, ET, AS, ET, ET, ET, ET},
    /*Estado 16 (STEP)*/
	{ ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, EP, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ET, ET, ET, ET, ET, ET, ET, ET, ET, ET, ID, ET, AS, ET, ET, ET, ET},
    /*Estado 17*/
	{ ID, ID, ID, ID, ID, ID, ID, 23, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ET, ET, ET, ET, ET, ET, ET, ET, ET, ET, ID, ET, AS, ET, ET, ET, ET},
    /*Estado 18 (SQRT)*/
	{ ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, EP, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ET, ET, ET, ET, ET, ET, ET, ET, ET, ET, ID, ET, AS, ET, ET, ET, ET},
    /*Estado 19(ELSE)*/
	{ ID, ID, ID, EP, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ET, ET, ET, ET, ET, ET, ET, ET, ET, ET, ID, ET, AS, ET, ET, ET, ET},
    /*Estado 20 (READ)*/
	{ ID, ID, EP, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ET, ET, ET, ET, ET, ET, ET, ET, ET, ET, ID, ET, AS, ET, ET, ET, ET},
    /*Estado 21*/
	{ ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, 24, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ET, ET, ET, ET, ET, ET, ET, ET, ET, ET, ID, ET, AS, ET, ET, ET, ET},
    /*Estado 22*/
	{ ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, 25, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ET, ET, ET, ET, ET, ET, ET, ET, ET, ET, ID, ET, AS, ET, ET, ET, ET},
    /*Estado 23*/
	{ ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, 26, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ET, ET, ET, ET, ET, ET, ET, ET, ET, ET, ID, ET, AS, ET, ET, ET, ET},
    /*Estado 24*/
	{ ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, 27, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ET, ET, ET, ET, ET, ET, ET, ET, ET, ET, ID, ET, AS, ET, ET, ET, ET},
    /*Estado 25 (PRINT)*/
	{ ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, EP, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ET, ET, ET, ET, ET, ET, ET, ET, ET, ET, ID, ET, AS, ET, ET, ET, ET},
    /*Estado 26 (STRING)*/
	{ ID, ID, ID, ID, ID, EP, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ET, ET, ET, ET, ET, ET, ET, ET, ET, ET, ID, ET, AS, ET, ET, ET, ET},
    /*Estado 27 (RETURN)*/
	{ ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, EF, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ET, ET, ET, ET, ET, ET, ET, ET, ET, ET, ID, ET, AS, ET, ET, ET, ET},
	/*Estado 28 (Indentificador)*/
	{ ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ET, ET, ET, ET, EF, ET, ET, ET, ET, ET, EP, ET, AS, ET, ET, ET, ET},
    /*Estado 29 (Aspas)*/
	{ AS, AS, AS, AS, AS, AS, AS, AS, AS, AS, AS, AS, AS, AS, AS, AS, AS, AS, AS, AS, AS, AS, AS, AS, AS, AS, AS, AS, AS, AS, AS, AS, AS, AS, AS, AS, AS, AS, AS, AS, AS, AS, AS, AS, AS, AS, AS, EP, AS, AS, AS, AS},
    /*Estado 30 (Numero)*/
    { ET, ET, ET, ET, ET, ET, ET, ET, ET, ET, ET, ET, ET, ET, ET, ET, ET, ET, ET, ET, ET, ET, ET, ET, ET, NU, NU, NU, NU, NU, NU, NU, NU, NU, NU, SG, SG, SG, ET, PR, ET, ET, ET, ET, ET, EP, ET, AS, ET, ET, ET, ET},
    /*Estado 31 (Operador Relacional)*/
    { ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, NU, NU, NU, NU, NU, NU, NU, NU, NU, NU, EF, EF, EF, ET, ET, ET, ET, ET, ET, ET, EP, ET, AS, ET, ET, ET, ET},
    /*Estado 32 (Parenteses)*/
	{ ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, NU, NU, NU, NU, NU, NU, NU, NU, NU, NU, ET, ET, ET, PR, EF, ET, ET, ET, ET, ET, EP, EP, AS, ID, ID, ID, ID},
	/*Estado 33 (Colchetes)*/
	{ ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, NU, NU, NU, NU, NU, NU, NU, NU, NU, NU, ET, ET, ET, ET, ET, ET, ET, ET, ET, ET, ET, ET, AS, CC, EF, ID, ID},
	/*Estado 34 (Chaves)*/
	{ ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, NU, NU, NU, NU, NU, NU, NU, NU, NU, NU, ET, ET, ET, PR, ET, CH, ET, ET, ET, ET, EP, EP, AS, CC, EF, ID, ID},
	/*Estado 35 (Operador Aritmético)*/
    { ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, NU, NU, NU, NU, NU, NU, NU, NU, NU, NU, ET, ET, ET, ET, ET, ET, ET, ET, ET, ET, EP, ET, AS, ET, ET, ET, ET},
    /*Estado 36 (=:)*/
	{ ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, NU, NU, NU, NU, NU, NU, NU, NU, NU, NU, EP, ET, ET, ET, EF, ET, ET, ET, ET, ET, ET, ET, AS, ET, ET, ET, ET},
	
};
 
/*#######################################################################*/
char alfabeto[] = {'a', 'b', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 
'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '=',
 '<', '>', '(', ')', '{', '}', '+', '-', '%', ',', ';', '"', '[', ']', '/', ':'};
/*#######################################################################*/
 
int cabeca_leitura;
int estado_maquina;
char cadeia_1[COMP_FITA];
char  C_fita[COMP_FITA];
char caracter_lido;
 
/*####################################################################*/
 

 
int main() {
 
    printf("|========================================|\n");
    printf("|=========== ANALISADOR LEXICO ==========|\n");
    printf("|========================================|\n");
    printf("|========================================|\n\n");
    
    FILE* arq1 = fopen("ArquivoFonte1.mln", "r");
    FILE* arq2 = fopen("ArquivoFonte2.mln", "r");
    _completa_fita(arq1);
    _varrer_a_fita();
	_completa_fita(arq2);
	_varrer_a_fita();
    fclose(arq1);
    fclose(arq2);
	fflush(stdin);
    return (0);
}
 
/*######################################################################*/
 
void _completa_fita(FILE *arq) {
    int i = 0;
    C_fita[i] = fgetc(arq);
    printf("\n\n");
    while (C_fita[i] != EOF)
        C_fita[++i] = fgetc(arq);
    C_fita[i++] = TC;
    C_fita[i] = '\0';
 
    for (i = 0; C_fita[i] != TC; i++)
        cadeia_1[i] = C_fita[i];
    cadeia_1[i++] = TC;
    cadeia_1[i] = '\0';
}
 
/*########################################################################*/
 
void _varrer_a_fita(void) {
 FILE* res = fopen("Resultado.txt", "w");
 fprintf(res, "\nLendo o ArquivoFonte.mln\n\n");
 int cad_valida = 0, total_cadeias = 0, erro = 0, quant_parenteses = 0, quant_colchetes = 0, quant_chaves = 0;
    estado_maquina = 0;
    cabeca_leitura = 0;
 
    while (C_fita[cabeca_leitura] != '\0') {
        caracter_lido = _encontra_simbolo(C_fita[cabeca_leitura]);
        printf("%c", C_fita[cabeca_leitura]);
        if (caracter_lido == SI) {
        	if (C_fita[cabeca_leitura] == TC) {
                printf("\n");
                if(estado_maquina != AS)
                estado_maquina = 0;
            }else if(C_fita[cabeca_leitura] == TE){
                printf("Quebra de linha\n");
                if(estado_maquina != AS)
                estado_maquina = 0;
            }else if(C_fita[cabeca_leitura] == '*'){
				printf("  OPERADOR ARITMETICO '*'!\n");
				if(estado_maquina != AS){
                estado_maquina = 0;
                cad_valida++;
            	total_cadeias++;
            	}	    
			}else{
            	fprintf(res, "Palavra ");
            	while (C_fita[cabeca_leitura] != TE){
            		fprintf(res, "%c", C_fita[cabeca_leitura]);
            		cabeca_leitura++;
            		caracter_lido = _encontra_simbolo(C_fita[cabeca_leitura]);
            		if(C_fita[cabeca_leitura] == TC) break;
            		if(C_fita[cabeca_leitura] == '"') break;
            		if(C_fita[cabeca_leitura] == ',') break;
            		if(C_fita[cabeca_leitura] == ')') break;
            		if(C_fita[cabeca_leitura] == '(') break;
            		if(C_fita[cabeca_leitura] == '{') break;
            		if(C_fita[cabeca_leitura] == '}') break;
            		if(C_fita[cabeca_leitura] == '[') break;
            		if(C_fita[cabeca_leitura] == ']') break;
            		if(C_fita[cabeca_leitura] == ':') break;
            		caracter_lido = _encontra_simbolo(C_fita[cabeca_leitura]);
            		printf("%c", C_fita[cabeca_leitura]);
            		estado_maquina = tabela_t[estado_maquina][caracter_lido];
				}
                fprintf(res, " não reconhecida\n");
                if(estado_maquina != AS){
                  estado_maquina = 0;
				  total_cadeias++;
				  erro++;
				  printf("  'e uma palavra INVALIDA'\n\n");	
				}else{
				  estado_maquina = AS;
				  printf("  'e uma palavra dentro de ASPAS'\n\n");
				}
            }
        } else {
            sleep(1);
            printf("  [%d] %d  \n", estado_maquina, tabela_t[estado_maquina][caracter_lido]);
            if (tabela_t[estado_maquina][caracter_lido] == ET) {
                printf("  Houve um ERRO DE TRANSICAO!\n");
                estado_maquina = 0;
            }  else if (estado_maquina == 9 && tabela_t[9][caracter_lido] == EP && C_fita[cabeca_leitura + 1] == TC){
            	printf("\nPalavra reservada (FOR)\n");
            	cad_valida++;
            	total_cadeias++;
            	estado_maquina = 0;
            } else if (estado_maquina == 16 && tabela_t[16][caracter_lido] == EP && C_fita[cabeca_leitura + 1] == TC){
            	printf("\nPalavra reservada (STEP)\n");
            	cad_valida++;
            	total_cadeias++;
            	estado_maquina = 0;
			} else if (estado_maquina == 18 && tabela_t[18][caracter_lido] == EP && C_fita[cabeca_leitura + 1] == TC){
            	printf("\nPalavra reservada (SQRT)\n");
            	cad_valida++;
            	total_cadeias++;
            	estado_maquina = 0;
            } else if (estado_maquina == 3 && tabela_t[3][caracter_lido] == EP && C_fita[cabeca_leitura + 1] == TC){
            	printf("\nPalavra reservada (IF)\n");
            	cad_valida++;
            	total_cadeias++;
            	estado_maquina = 0;
			} else if (estado_maquina == 19 && tabela_t[19][caracter_lido] == EP && C_fita[cabeca_leitura + 1] == TC){
            	printf("\nPalavra reservada (ELSE)\n");
            	cad_valida++;
            	total_cadeias++;
            	estado_maquina = 0;
            } else if (estado_maquina == 27 && tabela_t[27][caracter_lido] == EP && C_fita[cabeca_leitura + 1] == TC){
            	printf("\nPalavra reservada (RETURN)\n");
            	cad_valida++;
            	total_cadeias++;
            	estado_maquina = 0;
            } else if (estado_maquina == 25 && tabela_t[25][caracter_lido] == EP && C_fita[cabeca_leitura + 1] == TC){
            	printf("\nPalavra reservada (PRINT)\n");
            	cad_valida++;
            	total_cadeias++;
            	estado_maquina = 0;
            } else if (estado_maquina == 20 && tabela_t[20][caracter_lido] == EP && C_fita[cabeca_leitura + 1] == TC){
            	printf("\nPalavra reservada (READ)\n");
            	cad_valida++;
            	total_cadeias++;
            	estado_maquina = 0;
            } else if (estado_maquina == 7 && tabela_t[7][caracter_lido] == EP && C_fita[cabeca_leitura + 1] == TC){
            	printf("\nPalavra reservada (TO)\n");
            	cad_valida++;
            	total_cadeias++;
            	estado_maquina = 0;
			} else if (estado_maquina == 15 && tabela_t[15][caracter_lido] == EP && C_fita[cabeca_leitura + 1] == TC){
            	printf("\nPalavra reservada (NUM)\n");
            	cad_valida++;
            	total_cadeias++;
            	estado_maquina = 0;
			} else if (estado_maquina == 26 && tabela_t[26][caracter_lido] == EP && C_fita[cabeca_leitura + 1] == TC){
            	printf("\nPalavra reservada (STRING)\n");
            	cad_valida++;
            	total_cadeias++;
            	estado_maquina = 0;
        	}else if(tabela_t[estado_maquina][caracter_lido] == PR){
				if(C_fita[cabeca_leitura] = '('){
					printf("\nAbre Parentese\n");
					cad_valida++;
            		total_cadeias++;
            		quant_parenteses++;
            		estado_maquina = 0;
				}else if(C_fita[cabeca_leitura] = ')' && quant_parenteses > 0){
					printf("\nFecha Parentese\n");
					cad_valida++;
            		total_cadeias++;
            		estado_maquina = 0;
            		quant_parenteses--;
				}else{
					fprintf(res, "Falta de fechamento de código");
					total_cadeias++;
					erro++;
					estado_maquina = 0;	
				}
			}else if(tabela_t[estado_maquina][caracter_lido] == CC){
				if(C_fita[cabeca_leitura] = '['){
					printf("\nAbre Colchete\n");
					cad_valida++;
            		total_cadeias++;
            		quant_colchetes++;
            		estado_maquina = 0;
				}else if(C_fita[cabeca_leitura] = ']' && quant_colchetes > 0){
					printf("\nFecha Colchete\n");
					cad_valida++;
            		total_cadeias++;
            		quant_colchetes--;
            		estado_maquina = 0;
            	}else{
					fprintf(res, "Falta de fechamento de código");
					total_cadeias++;
					erro++;
					estado_maquina = 0;
				}
			}else if(tabela_t[estado_maquina][caracter_lido] == CH){
				if(C_fita[cabeca_leitura] = '{'){
					printf("\nAbre Chave\n");
					cad_valida++;
            		total_cadeias++;
            		quant_chaves++;
            		estado_maquina = 0;
				}	
				else if(C_fita[cabeca_leitura] = '}' && quant_chaves > 0){
					printf("\nFecha Chave\n");
					cad_valida++;
            		total_cadeias++;
            		quant_chaves--;
            		estado_maquina = 0;
            	}else{
					fprintf(res, "Falta de fechamento de código");
					total_cadeias++;
					erro++;
					estado_maquina = 0;
				}
				}else if(tabela_t[estado_maquina][caracter_lido] == OA){
				printf("OPERADOR ARITMETICO '%c'!\n", C_fita[cabeca_leitura]);
                cad_valida++;
            	total_cadeias++;
            	estado_maquina = 0;	
            }else if(tabela_t[estado_maquina][caracter_lido] == SG){
            	while(caracter_lido != SI){
            		estado_maquina = tabela_t[estado_maquina][caracter_lido];
            		cabeca_leitura++;
            		if(tabela_t[estado_maquina][caracter_lido] != SG) break;
            		caracter_lido = _encontra_simbolo(C_fita[cabeca_leitura]);
            		printf("%c", C_fita[cabeca_leitura]);
					printf("  [%d] %d  \n", estado_maquina, tabela_t[estado_maquina][caracter_lido]);
				}
				printf("OPERADOR RELACIONAL '%c%c'\n", C_fita[cabeca_leitura - 1], C_fita[cabeca_leitura]);
				cad_valida++;
                total_cadeias++;
				estado_maquina = 0;
				
			} else if (tabela_t[estado_maquina][caracter_lido] == ID){
				while(caracter_lido != SI){
					estado_maquina = tabela_t[estado_maquina][caracter_lido];
			    	cabeca_leitura++;
					if(C_fita[cabeca_leitura] == ',') break;	
					caracter_lido = _encontra_simbolo(C_fita[cabeca_leitura]);
					printf("%c", C_fita[cabeca_leitura]);
					printf("  [%d] %d  \n", estado_maquina, tabela_t[estado_maquina][caracter_lido]);
            	}	
                printf("\nIDENTIFICADOR\n");
                estado_maquina = 0;
                cad_valida++;
                total_cadeias++;
            }else if(tabela_t[estado_maquina][caracter_lido] == NU){
            	while(caracter_lido != SI){
			    	cabeca_leitura++;
					if(tabela_t[estado_maquina][caracter_lido] != NU) break;	
					caracter_lido = _encontra_simbolo(C_fita[cabeca_leitura]);
					printf("%c", C_fita[cabeca_leitura]);
					printf("  [%d] %d  \n", estado_maquina, tabela_t[estado_maquina][caracter_lido]);
            		estado_maquina = tabela_t[estado_maquina][caracter_lido];
				}
				printf("\nNUMERO\n");
				cad_valida++;
				total_cadeias++;
			}else{
            estado_maquina = tabela_t[estado_maquina][caracter_lido];
            }
        }
        cabeca_leitura++;
    }
    printf("Cadeias Existentes: %d\n", total_cadeias);
    printf("Total de cadeias Validas: %d\n\n\n\n", cad_valida);
    if(quant_parenteses > 0 || quant_colchetes > 0 || quant_chaves > 0)
	fprintf(res, " Falta de fechamento de código.\n");
    if(erro > 0){
     	fprintf(res, " ArquivoFonte.mln contendo erros.\n");	
	}else{
		fprintf(res, " ArquivoFonte.mln analisado corretamente.\n");
	}
    fclose(res);
}
 
/*######################################################################*/
 
int _encontra_simbolo(char simbolo) {
 
    int i;
    for (i = 0; i < MAX_SIMBOLOS; i++)
        if (alfabeto[i] == simbolo)
            return (i);
    return (SI);
}

/*########################################################################*/
