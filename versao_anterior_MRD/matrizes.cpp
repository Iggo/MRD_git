/**

 Programa: MÉTODO DA RIGIDEZ DIRETA - MRD

 Disciplina: Análise de Estruturas II

 Autor: Iggo Guimarães/David Kennedy/Amanda Lyz

 Professor: Maurício Mello

 Arquivo: matriz.cpp

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
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "matrizes.h"

double determinante(double** matrix, int tam)
{
    double s = 1, det = 0, ** m_minor;

    m_minor = (double**)malloc(tam * sizeof(double*));

    for (int i = 0; i < tam; i++){
        m_minor[i] = (double*)malloc(tam * sizeof(double));}

    int i, j, m, n, c;
    if (tam == 1)
    {
        return (matrix[0][0]);
    }
    else
    {
        det = 0;
        for (c = 0; c < tam; c++)
        {
            m = 0;
            n = 0;
            for (i = 0; i < tam; i++)
            {
                for (j = 0; j < tam; j++)
                {
                    m_minor[i][j] = 0;
                    if (i != 0 && j != c)
                    {
                        m_minor[m][n] = matrix[i][j];
                        if (n < (tam - 2)) {
                            n++;
                        }else
                        {
                            n = 0;
                            m++;
                        }
                    }
                }
            }
            det = det + s * (matrix[0][c] * determinante(m_minor, tam - 1));
            
            s = -1 * s;
        }
    }
    return (det);

    mat_free(m_minor, tam, tam);
}

double** inversa(double** matriz, int tam)
{
    //cout << "multiplicaçã de cofatores" << endl;
    double **m_cofator;
    double **matriz_cofator;

    m_cofator = (double**)malloc(tam * sizeof(double*));

    for (int i = 0; i < tam; i++){
        m_cofator[i] = (double*)malloc(tam * sizeof(double));}

    matriz_cofator = (double**)malloc(tam * sizeof(double*));

    for (int i = 0; i < tam; i++)
        matriz_cofator[i] = (double*)malloc(tam * sizeof(double));

    int p, q, m, n, i, j;
    for (q = 0; q < tam; q++)
    {
        for (p = 0; p < tam; p++)
        {
            m = 0;
            n = 0;
            for (i = 0; i < tam; i++)
            {
                for (j = 0; j < tam; j++)
                {
                    if (i != q && j != p)
                    {
                        m_cofator[m][n] = matriz[i][j];
                        if (n < (tam - 2))
                            n++;
                        else
                        {
                            n = 0;
                            m++;
                        }
                    }
                }
            }
            matriz_cofator[q][p] = pow(-1, q + p) * determinante(m_cofator, tam - 1);
        }
    }

    return transposta(matriz, matriz_cofator, tam);

    mat_free(m_cofator, tam, tam);
    mat_free(matriz_cofator, tam, tam);
}

double** transposta(double** matriz, double** matriz_cofator, int tam)
{
    int i, j;
    double** m_transposta, ** m_inversa, d;

    m_transposta = (double**)malloc(tam * sizeof(double*));

    for (int i = 0; i < tam; i++)
        m_transposta[i] = (double*)malloc(tam * sizeof(double));

    m_inversa = (double**)malloc(tam * sizeof(double*));

    for (int i = 0; i < tam; i++)
        m_inversa[i] = (double*)malloc(tam * sizeof(double));
    

    for (i = 0; i < tam; i++)
        for (j = 0; j < tam; j++)
            m_transposta[i][j] = matriz_cofator[j][i];
  
    d = determinante(matriz, tam);

    for (i = 0; i < tam; i++)
        for (j = 0; j < tam; j++)
            m_inversa[i][j] = m_transposta[i][j] / d;

    return  m_inversa;

    mat_free(m_transposta, tam, tam);
    mat_free(m_inversa, tam, tam);
}

double* multi_mat(double** mat, double* vet, int lin_1, int col_1)
{
    double* vet_saida;
    vet_saida = (double*)malloc(lin_1 * sizeof(double));

    for (int i = 0; i < lin_1; i++)
        vet_saida[i] = 0;

    for (int i = 0; i < lin_1; i++)
        for (int j = 0; j < col_1; j++)
            vet_saida[i] += mat[i][j] * vet[j];
        
    return vet_saida;

    free(vet_saida);
}

void imprimir_mat(double** matriz, int linhas, int colunas)
{
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
}

void imprimir_vet(double* vet, int tam) {
    for (int i = 0; i < tam; i++){
        cout << vet[i] << " ";
        
    }   
    cout << endl;
}

void mat_free(double** matriz, int lin, int col) {
    for (int i = 0; i < lin; i++)
        free(matriz[i]);
    free(matriz);
}