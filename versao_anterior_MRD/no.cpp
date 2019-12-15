/**

 Programa: MÉTODO DA RIGIDEZ DIRETA - MRD

 Disciplina: Análise de Estruturas II

 Autor: Iggo Guimarães/David Kennedy/Amanda Lyz

 Professor: Maurício Mello

 Arquivo: no.cpp

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
#include "no.h"

using namespace std;

no::no(){}

/*SET'S*/

void no::set_id_no(int i) { id = i; }

void no::set_x(double pos) { pos_x = pos; }

void no::set_y(double pos) { pos_y = pos; }

void no::set_id_x(int id) { id_x = id; }

void no::set_id_y(int id) { id_y = id; }

void no::set_des_x(double pos) { des_x = pos; }

void no::set_des_y(double pos) { des_y = pos; }

void no::set_forca_x(double pos) { forca_x = pos; }

void no::set_forca_y(double pos) { forca_y = pos; }

void no::set_Dx(double d) { Dx = d; }

void no::set_Dy(double d) { Dy = d; }

/*GET'S*/

int no::get_id_no() { return id; }

double no::get_x() { return pos_x; }

double no::get_y() { return pos_y; }

int no::get_id_x() { return id_x; }

int no::get_id_y() { return id_y; }

int no::get_des_x() { return des_x; }

int no::get_des_y() { return des_y; }

double no::get_forca_x() { return forca_x; }

double no::get_forca_y() { return forca_y; }

double no::get_Dx() { return Dx; }

double no::get_Dy() { return Dy; }

no::~no() {}
