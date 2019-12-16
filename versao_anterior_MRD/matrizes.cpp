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

double** invermat(int n, double** a) {
    double** ainv;

    ainv = new double* [n];

    for (int i = 0; i < n; i++) {

        ainv[i] = new double[n];

    }

    // Algoritmo para la eliminación simple de Gauss

    int i, j, k;

    double factor;

    double** L, * D, * X;

    X = new double[n]; D = new double[n];

    L = new double* [n];

    for (j = 0; j < n; j++)

        L[j] = new double[n];

    for (k = 0; k < n - 1; k++) {

        for (i = k + 1; i < n; i++) {

            factor = a[i][k] / a[k][k];

            for (j = k + 1; j < n + 1; j++) {

                a[i][j] = a[i][j] - factor * a[k][j];

            }

        }

    }

    // Cálculo del determinante

    double determ = 1.;

    for (i = 0; i < n; i++) {

        determ = determ * a[i][i];

    }

    // Rutina para determinar las matrices  L (inferior)
    //  y U (superior) de ladescomposición LU

    for (i = 0; i < n; i++) {

        for (j = 0; j < n; j++) {

            if (i > j) {

                L[i][j] = a[i][j] / a[j][j];

                a[i][j] = 0;

            }

        }

    }

    for (i = 0; i < n; i++) {

        for (j = 0; j < n; j++) {

            L[j][j] = 1;

        }

    }

    // cálculo de la inversa

    for (k = 0; k < n; k++) {

        // Esta rutina inicializa los L[i][n] 

        for (i = 0; i < n; i++) {

            if (i == k) L[i][n] = 1;

            else  L[i][n] = 0;

        }

        // Esta función implementa la sustitución hacia adelante con
        // los L[i][n] que produce la rutina anterior

        double sum;

        D[0] = L[0][n];

        for (i = 1; i < n; i++) {

            sum = 0;

            for (j = 0; j < i; j++) {

                sum = sum + L[i][j] * D[j];

            }

            D[i] = L[i][n] - sum;

        }

        // Esta rutina asigna los D[i] que produce forward para
        // ser utilizados con la matriz U

        for (i = 0; i < n; i++) {

            a[i][n] = D[i];

        }

        // Rutina que aplica la sustitución hacia atras

        X[n - 1] = a[n - 1][n] / a[n - 1][n - 1];

        // Determinación de las raíces restantes

        for (i = n - 2; i > -1; i--) {

            sum = 0;

            for (j = i + 1; j < n; j++) {

                sum = sum + a[i][j] * X[j];

            }

            X[i] = (a[i][n] - sum) / a[i][i];

        }

        // Esta rutina asigna los X[i] que produce Sustituir
        // como los elementos de la matriz inversa

        for (i = 0; i < n; i++) {

            ainv[i][k] = X[i];

        }

    }   // llave de cierre del for para k
    return ainv;
}

/*
double determinante(double** matrix, int tam)
{
    //imprimir_mat(matrix, tam, tam);

    double s = 1, det = 0;
    
    double **m_minor = new double*[tam];

    for (int i = 0; i < tam; i++)
        m_minor[i] = new double[tam];

    //m_minor = (double**)malloc(tam * sizeof(double*));

    //for (int i = 0; i < tam; i++)
        //m_minor[i] = (double*)malloc(tam * sizeof(double));

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
                    //cout << "i " << i << " j " << j << " m " << m << " n " << n << endl;
                }
            }
            det = det + s * (matrix[0][c] * determinante(m_minor, tam - 1));
            //cout << det << endl;
            s = -1 * s;
        }
    }
    return (det);

    //mat_free(m_minor, tam, tam);

    // Deleta o array de cada uma das linhas
    for (int i = 0; i < tam; ++i)
        delete[] m_minor[i];
    // Deleta o array de ponteiros
    delete[] m_minor;
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
                        if (n < (tam - 2)) {
                            n++;
                        }
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
*/

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