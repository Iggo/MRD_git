/**

 Programa: M�TODO DA RIGIDEZ DIRETA - MRD

 Disciplina: An�lise de Estruturas II

 Autor: Iggo Guimar�es/David Kennedy/Amanda Lyz

 Professor: Maur�cio Mello

 Arquivo: membro.cpp

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
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "no.h"
#include "membro.h"
#include "matrizes.h"


using namespace std;

membro::membro(){}

/*SET'S*/

void membro::set_id(int id) { id_membro = id; }

void membro::set_no_i(no i) { no_i = i; }

void membro::set_no_f(no f) { no_f = f; }

void membro::set_e(double me) { e = me; }

void membro::set_a(double ab) { a = ab; }

void membro::set_kappa() {
    kappa = (double**)malloc(2 * sizeof(double*));
    for (int i = 0; i < 2; i++)
        kappa[i] = (double*)malloc(2 * sizeof(double));

    kappa[0][0] = k();
    kappa[0][1] = -k();
    kappa[1][0] = -k();
    kappa[1][1] = k();
}

void membro::set_mat_sen_cos() {
    mat_sen_cos = (double**)malloc(2 * sizeof(double*));

    for (int i = 0; i < 2; i++)
        mat_sen_cos[i] = (double*)malloc(4 * sizeof(double));

    mat_sen_cos[0][0] = cos();
    mat_sen_cos[0][1] = sen();
    mat_sen_cos[0][2] = 0;
    mat_sen_cos[0][3] = 0;

    mat_sen_cos[1][0] = 0;
    mat_sen_cos[1][1] = 0;
    mat_sen_cos[1][2] = cos();
    mat_sen_cos[1][3] = sen();
}

void membro::set_vet_desl_nos(no* nos) {
    vet_desl_nos = (double*)malloc(4 * sizeof(double));

    vet_desl_nos[0] = nos[get_no_i().get_id_no() - 1].get_Dx();

    vet_desl_nos[1] = nos[get_no_i().get_id_no() - 1].get_Dy();

    vet_desl_nos[2] = nos[get_no_f().get_id_no() - 1].get_Dx();

    vet_desl_nos[3] = nos[get_no_f().get_id_no() - 1].get_Dy();
}

void membro::set_vet_desl_locais() {
    set_mat_sen_cos();

    vet_desl_locais = (double*)malloc(2 * sizeof(double));

    vet_desl_locais = multi_mat(get_mat_sen_cos(), get_vet_desl_nos(), 2, 4);
}

void membro::set_vet_esf_int() {
    vet_esf_internos = (double*)malloc(2 * sizeof(double));

    set_kappa();

    vet_esf_internos = multi_mat(get_kappa(), get_vet_desl_axi(), 2, 2);
}

/*GET'S*/

int membro::get_id() { return id_membro; }

no membro::get_no_i() { return no_i; }

no membro::get_no_f() { return no_f; }

double membro::get_e() { return e; }

double membro::get_a() { return a; }

double** membro::get_kappa() { return kappa; }

double** membro::get_mat_sen_cos() { return mat_sen_cos; }

double* membro::get_vet_desl_nos() { return vet_desl_nos; }

double membro::get_desl_locais(int pos) { return vet_desl_locais[pos]; }

double* membro::get_vet_desl_axi() { return vet_desl_locais; }

double membro::get_esf_axi(int pos) { return vet_esf_internos[pos]; }

/*M�TODOS*/

double membro::k() { return (e * a) / tam(); }

double membro::tam() { return sqrt(pow(no_f.get_x() - no_i.get_x(), 2) + pow(no_f.get_y() - no_i.get_y(), 2)); }

double membro::cos() { return  (no_f.get_x() - no_i.get_x()) / tam(); }

double membro::sen() { return  (no_f.get_y() - no_i.get_y()) / tam(); }

void   membro::free_membro() {
    mat_free(kappa, 2, 2);

    mat_free(mat_sen_cos, 2, 2);

    free(vet_desl_nos);

    free(vet_desl_locais);

    free(vet_esf_internos);
}

membro::~membro() {}


































