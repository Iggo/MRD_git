/**

 Programa: M�TODO DA RIGIDEZ DIRETA - MRD

 Disciplina: An�lise de Estruturas II

 Autor: Iggo Guimar�es/David Kennedy/Amanda Lyz

 Professor: Maur�cio Mello

 Arquivo: membro.h

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
#ifndef MEMBRO_H
#define MEMBRO_H
#include "no.h"

class membro
{
    public:
        membro();

        /*SET'S*/

        void set_id(int id);    //modifica o id do membro

        void set_no_i(no i);    //modifica o n� inicial

        void set_no_f(no f);    //modifica o n� final

        void set_e(double me);   //modifica o m�dulo de elasticidade

        void set_a(double ab);   //modifica a �rea transversal

        void set_kappa();       //calcula a matriz kappa e armazena na variavel matriz kappa

        void set_mat_sen_cos(); //inicializa a matriz de seno e cosseno na matriz seno_cosseno

        void set_vet_desl_nos(no* no);  //aloca os delocamentos calculados pelo sistema local aos n�s iniciais e finais do membro

        void set_vet_desl_locais();     //aloca os deslocamentos axiais do membro D'i e D'j

        void set_vet_esf_int();     //aloca os esfor�os internos do membro

        /*GET'S*/
        
        int get_id();   //retorno o id do membro
        
        no get_no_i();  //retorna o n� inicial

        no get_no_f();  //retorna o n� final

        double get_e(); //retorna o m�dumo de elasticidade

        double get_a(); //retorna a �rea da se��o tranversal barra

        double** get_kappa(); //retorna a matriz kappa

        double** get_mat_sen_cos(); //retorna a matriz seno e cosseno

        double* get_vet_desl_nos(); //retorna o vetro de deslocamentos do n� inicial e final

        double get_desl_locais(int pos); //retorna o valor do deslocamento axial da barra na posi��o inicial ou final (0 ou 1)

        double* get_vet_desl_axi(); //retorna o vetor com os deslocamentos axiais da barra

        double get_esf_axi(int pos); //retorna o vetor com as for�as axias da barra   

        /*M�TODOS*/

        double k();      //c�lcula kappa

        double tam();    //tamanho do membro

        double cos();    //cosseno do membro

        double sen();    //seno do membro

        void   free_membro();   //libera a m�moria dos vetores e matrizes

        virtual ~membro();

    protected:

    private:
        int     id_membro;          //iddo membro
        no      no_i;               //n� inicial
        no      no_f;               //n� final
        double  e;                  //m�dulo de elasticidade em MPa
        double  a;                  //�rea da se��o transversal em cm�
        double  **kappa;            //matriz de rigidez do membro kappa
        double  **mat_sen_cos;      //matriz de senos e cossenos
        double  *vet_desl_nos;      //Dix, Diy, Djx e Djy
        double  *vet_desl_locais;   //D'i e D'j
        double  *vet_esf_internos;  //fi e fj
};

#endif // MEMBRO_H
