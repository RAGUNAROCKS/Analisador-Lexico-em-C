# Analisador-Lexico-em-C
Trabalho de Teoria da Computação e Compiladores.

Esse trabalho consiste em um analisador léxico, utilizando o metodo de automato deterministico de pilha. 
Formulei as seguintes regras:
 - Aspas pegam todos os simbolos, inclusive os invalidos. Não considerando como erro.
 - Não pode ter mais de parentese/colchetes/chaves de abertura do que de fechamento e vice-versa.
 - Palavras com todos os simbolos validos é reconhecido como identificador.
 - Palavras só com o alfabeto {0...9} é reconhecido como numeros.
 - * é uma palavra válida, mesmo não estando no alfabeto.
 - Palavras reservadas: for, step, sqrt, if, else, return, print, read, to, num, string, :=
