/**

 Programa: MÉTODO DA RIGIDEZ DIRETA - MRD

 Disciplina: Análise de Estruturas II

 Autor: Iggo Guimarães/David Kennedy/Amanda Lyz

 Professor: Maurício Mello

 Arquivo: matriz.h

 Descrição:
    Análise de treliças planas sujeitas a carregamentos nódais pelo Método da Rigidez Direta.
 Critérios:
    -As equipes poderão utilizar qualquer linguagem/ambiente de programação para desenvolver o algoritmo;
    -A ferramenta não precisa conter interface gráfica com o usuário;
    -A ferramenta deverá ser capaz de calcular deslocamentos, reações de apoio e esforços internos nas
    barras de uma estrutura com configurações e parâmetros de entrada quaisquer;
    -Não será necessário considerar ações de recalques de apoio, apoio elástico nem variação de
    temperatura. Apenas devem ser consideradas ações de cargas concentradas em nós da estrutura.

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
