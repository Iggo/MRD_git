/**

 Programa: MÉTODO DA RIGIDEZ DIRETA - MRD

 Disciplina: Análise de Estruturas II

 Autor: Iggo Guimarães/David Kennedy/Amanda Lyz

 Professor: Maurício Mello

 Arquivo: membro.h

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
#ifndef MEMBRO_H
#define MEMBRO_H
#include "no.h"

class membro
{
    public:
        membro();

        /*SET'S*/

        void set_id(int id);    //modifica o id do membro

        void set_no_i(no i);    //modifica o nó inicial

        void set_no_f(no f);    //modifica o nó final

        void set_e(double me);   //modifica o módulo de elasticidade

        void set_a(double ab);   //modifica a área transversal

        void set_kappa();       //calcula a matriz kappa e armazena na variavel matriz kappa

        void set_mat_sen_cos(); //inicializa a matriz de seno e cosseno na matriz seno_cosseno

        void set_vet_desl_nos(no* no);  //aloca os delocamentos calculados pelo sistema local aos nós iniciais e finais do membro

        void set_vet_desl_locais();     //aloca os deslocamentos axiais do membro D'i e D'j

        void set_vet_esf_int();     //aloca os esforços internos do membro

        /*GET'S*/
        
        int get_id();   //retorno o id do membro
        
        no get_no_i();  //retorna o nó inicial

        no get_no_f();  //retorna o nó final

        double get_e(); //retorna o módumo de elasticidade

        double get_a(); //retorna a área da seção tranversal barra

        double** get_kappa(); //retorna a matriz kappa

        double** get_mat_sen_cos(); //retorna a matriz seno e cosseno

        double* get_vet_desl_nos(); //retorna o vetro de deslocamentos do nó inicial e final

        double get_desl_locais(int pos); //retorna o valor do deslocamento axial da barra na posição inicial ou final (0 ou 1)

        double* get_vet_desl_axi(); //retorna o vetor com os deslocamentos axiais da barra

        double get_esf_axi(int pos); //retorna o vetor com as forças axias da barra   

        /*MÉTODOS*/

        double k();      //cálcula kappa

        double tam();    //tamanho do membro

        double cos();    //cosseno do membro

        double sen();    //seno do membro

        void   free_membro();   //libera a mémoria dos vetores e matrizes

        virtual ~membro();

    protected:

    private:
        int     id_membro;          //iddo membro
        no      no_i;               //nó inicial
        no      no_f;               //nó final
        double  e;                  //módulo de elasticidade em MPa
        double  a;                  //área da seção transversal em cm²
        double  **kappa;            //matriz de rigidez do membro kappa
        double  **mat_sen_cos;      //matriz de senos e cossenos
        double  *vet_desl_nos;      //Dix, Diy, Djx e Djy
        double  *vet_desl_locais;   //D'i e D'j
        double  *vet_esf_internos;  //fi e fj
};

#endif // MEMBRO_H
