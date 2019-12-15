/**

 Programa: M�TODO DA RIGIDEZ DIRETA - MRD

 Disciplina: An�lise de Estruturas II

 Autor: Iggo Guimar�es/David Kennedy/Amanda Lyz

 Professor: Maur�cio Mello

 Arquivo: matriz.h

 Descri��o:
    An�lise de treli�as planas sujeitas a carregamentos n�dais pelo M�todo da Rigidez Direta.
 Crit�rios:
    -As equipes poder�o utilizar qualquer linguagem/ambiente de programa��o para desenvolver o algoritmo;
    -A ferramenta n�o precisa conter interface gr�fica com o usu�rio;
    -A ferramenta dever� ser capaz de calcular deslocamentos, rea��es de apoio e esfor�os internos nas
    barras de uma estrutura com configura��es e par�metros de entrada quaisquer;
    -N�o ser� necess�rio considerar a��es de recalques de apoio, apoio el�stico nem varia��o de
    temperatura. Apenas devem ser consideradas a��es de cargas concentradas em n�s da estrutura.

 Data: 17/12/2019

*/
#ifndef MATRIZES_H_INCLUDED
#define MATRIZES_H_INCLUDED

using namespace std;

double determinante(double** matriz, int tamanho);

double** inversa(double** matrix, int tam);

double** transposta(double** matriz, double** matriz_cofator, int tam);

double* multi_mat(double** mat_1, double* mat_2, int lin_1, int col_1);

void imprimir_mat(double** matriz, int linhas, int colunas);

void imprimir_vet(double* vet, int tam);

void mat_free(double** matriz, int lin, int col);

#endif // MATRIZES_H_INCLUDED
