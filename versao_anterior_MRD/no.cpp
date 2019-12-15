/**

 Programa: M�TODO DA RIGIDEZ DIRETA - MRD

 Disciplina: An�lise de Estruturas II

 Autor: Iggo Guimar�es/David Kennedy/Amanda Lyz

 Professor: Maur�cio Mello

 Arquivo: no.cpp

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
