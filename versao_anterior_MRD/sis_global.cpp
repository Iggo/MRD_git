#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "no.h"
#include "membro.h"
#include "sis_global.h"
#include "matrizes.h"

using namespace std;

sis_global::sis_global() {}

/*SET'S*/
void sis_global::set_gls(int n) { gls = n; }

void sis_global::set_tam_matriz_gloobal(int tam) { tam_mat_global = tam; }

void sis_global::set_mat_global(membro * mem, int num_membros, int n)
{
    set_tam_matriz_gloobal(n);

    matriz_global = (double **) malloc(n * sizeof(double *));

    for(int i = 0; i < n; i++)
        matriz_global[i] = (double *) malloc(n * sizeof(double));

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            matriz_global[i][j]=0;
 
    for(int i = 0; i < num_membros; i++)
    {
        matriz_global[mem[i].get_no_i().get_id_x()][mem[i].get_no_i().get_id_x()] +=  pow(mem[i].cos(),2)       * mem[i].k();
        matriz_global[mem[i].get_no_i().get_id_x()][mem[i].get_no_i().get_id_y()] +=  mem[i].cos()*mem[i].sen() * mem[i].k();
        matriz_global[mem[i].get_no_i().get_id_x()][mem[i].get_no_f().get_id_x()] +=  -pow(mem[i].cos(),2)      * mem[i].k();
        matriz_global[mem[i].get_no_i().get_id_x()][mem[i].get_no_f().get_id_y()] +=  -mem[i].cos()*mem[i].sen()* mem[i].k();

        matriz_global[mem[i].get_no_i().get_id_y()][mem[i].get_no_i().get_id_x()] +=  mem[i].cos()*mem[i].sen() * mem[i].k();
        matriz_global[mem[i].get_no_i().get_id_y()][mem[i].get_no_i().get_id_y()] +=  pow(mem[i].sen(),2)       * mem[i].k();
        matriz_global[mem[i].get_no_i().get_id_y()][mem[i].get_no_f().get_id_x()] +=  -mem[i].cos()*mem[i].sen()* mem[i].k();
        matriz_global[mem[i].get_no_i().get_id_y()][mem[i].get_no_f().get_id_y()] +=  -pow(mem[i].sen(),2)      * mem[i].k();

        matriz_global[mem[i].get_no_f().get_id_x()][mem[i].get_no_i().get_id_x()] +=  -pow(mem[i].cos(),2)      * mem[i].k();
        matriz_global[mem[i].get_no_f().get_id_x()][mem[i].get_no_i().get_id_y()] +=  -mem[i].cos()*mem[i].sen()* mem[i].k();
        matriz_global[mem[i].get_no_f().get_id_x()][mem[i].get_no_f().get_id_x()] +=  pow(mem[i].cos(),2)       * mem[i].k();
        matriz_global[mem[i].get_no_f().get_id_x()][mem[i].get_no_f().get_id_y()] +=  mem[i].cos()*mem[i].sen() * mem[i].k();

        matriz_global[mem[i].get_no_f().get_id_y()][mem[i].get_no_i().get_id_x()] +=  -mem[i].cos()*mem[i].sen()* mem[i].k();
        matriz_global[mem[i].get_no_f().get_id_y()][mem[i].get_no_i().get_id_y()] +=  -pow(mem[i].sen(),2)      * mem[i].k();
        matriz_global[mem[i].get_no_f().get_id_y()][mem[i].get_no_f().get_id_x()] +=  mem[i].cos()*mem[i].sen() * mem[i].k();
        matriz_global[mem[i].get_no_f().get_id_y()][mem[i].get_no_f().get_id_y()] +=  pow(mem[i].sen(),2)       * mem[i].k();
    }
}

void sis_global::set_vet_deslocamento(double** matriz, double* forcas, int gl)
{
    vet_deslocamento = (double*)malloc(gl * sizeof(double));

    vet_deslocamento = multi_mat(inversa(matriz, gl), forcas, gl, gl);
}

void sis_global::set_vet_forcas(double** matriz, double* forcas, int gl, int n)
{
    int temp = n - gl;

    double** mat_temp;

    mat_temp = (double**)malloc(temp * sizeof(double*));

    for (int i = 0; i < temp; i++)
        mat_temp[i] = (double*)malloc(gl * sizeof(double));

    for (int i = 0; i < temp; i++)
        for (int j = 0; j < gl; j++)
            mat_temp[i][j] = matriz[gl + i][j];

    vet_forcas = (double*)malloc((temp) * sizeof(double));

    vet_forcas = multi_mat(mat_temp, forcas, temp, gl);
}

/*GET'S*/

int sis_global::get_gls() { return this->gls; }

int sis_global::get_tam_mat_global() { return tam_mat_global; }

double **sis_global::get_mat() { return matriz_global; }

double sis_global::get_mat_global(int i, int j) { return matriz_global[i][j]; }

double *sis_global::get_vet_des() { return vet_deslocamento; }

double sis_global::get_vet_deslocamento(int pos) { return vet_deslocamento[pos]; }

double *sis_global::get_vet_f() { return vet_forcas; }

double sis_global::get_vet_forcas(int pos) { return vet_forcas[pos]; }

/*MÉTODOS*/

void sis_global::free_sis_global() {
    mat_free(matriz_global, get_tam_mat_global(), get_tam_mat_global());

    free(vet_deslocamento);

    free(vet_forcas);
}

sis_global::~sis_global() {}