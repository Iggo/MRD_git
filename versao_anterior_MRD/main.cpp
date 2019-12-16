/**

 Programa: M�TODO DA RIGIDEZ DIRETA - MRD

 Disciplina: An�lise de Estruturas II

 Autor: Iggo Guimar�es/David Kennedy/Amanda Lyz

 Professor: Maur�cio Mello

 Arquivo: main.cpp

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
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <math.h>
#include <iomanip>
#include "no.h"
#include "membro.h"
#include "sis_global.h"
#include "matrizes.h"

using namespace std;

int main()
{
    setlocale(LC_ALL,"");
    cout << fixed << setprecision(5);

    cout << "\t\tM�TODO DA RIGIDEZ DIRETA - MRD:" << endl;
    cout << "An�lise de treli�as planas sujeitas a carregamentos " << endl;
    cout << "\tn�dais pelo M�todo da Rigidez Direta" << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "\t\tINSTRU��ES DE USO DO PROGRAMA:" << endl;
    cout << "-O PROGRAMA LER� DOIS ARQUIVOS (.txt). " << endl;
    cout << "UM COM AS INFORMA��ES SOBRE OS N�S DO SISTEMA E" << endl;
    cout << "OUTRO COM AS INFORMA��ES DOS MEMBROS DO SISTEMA." << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "-FORMATO DO ARQUIVO DE N�S:" << endl;
    cout << "ID_N�\tX(m)\tY(m)\tDESL. EM X (1 ou 0)\tDESL. EM Y (1 ou 0 )\tFx(KN)\tFy(KN)" << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "OBS. 1: O ARQUIVO N�O PRECISA DE CABE�ALHO." << endl;
    cout << "OBS. 2: EM DESLOCABILIDADE 1 E 0 SIGNIFICAM LIVRE E FIXO, RESPECTIVAMENTE." << endl;
    cout << "OBS. 3: CADA LINHA DO ARQUIVO REFERE-SE A UM N�." << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "-FORMATO DO ARQUIVO DE MEMBROS:" << endl;
    cout << "ID_MEMBRO\tN� INICIAL\tN� FINAL\tM�DULO DE ELAST(MPa)\t�REA DA SE��O TRANS(cm�)" << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "OBS. 1: O ARQUIVO N�O PRECISA DE CABE�ALHO." << endl;
    cout << "OBS. 2: A COLUNA DE N� RECEBE ID DOS N�S CRIANDOS NO ARQUIVO DE N�S." << endl;
    cout << "OBS. 3: CADA LINHA DO ARQUIVO REFERE-SE A UM N�." << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "----------GARANTA QUE OS ARQUIVOS J� FORAM---------" << endl;
    cout << "--------CRIADOS ANTES DE INICIAR O PROGRAMA!-------" << endl;
    cout << "---------------------------------------------------" << endl<< endl;

    string nome_nos;
    cout << "DIGITE O NOME DO ARQUIVO DE N�S (m�nusculo com a extens�o .txt): ";
    cin  >> nome_nos;

    nome_nos += ".txt";

    ifstream arq_nos;
    //cout << nome_nos << endl;

    arq_nos.open(nome_nos.c_str(), ios::in); // abre o arquivo para leitura

    while(! arq_nos)
    {
        cout << "ARQUIVO " << nome_nos << " N�O PODE SER ABERTO!" << endl;
        cout << "DIGITE NOVAMENTE O NOME DO ARQUIVO DE NOS (m�nusculo com a extens�o .txt): ";
        cin >> nome_nos;
        nome_nos += ".txt";
        arq_nos.open(nome_nos.c_str(), ios::in); // abre o arquivo para leitura
    }

    int num_nos;
    cout << "DIGITE A QUANTIDADE DE N�S DA ESTRUTURA: ";
    cin  >> num_nos;

    no * vet_nos;
    vet_nos = (no *) malloc(num_nos * sizeof(no)); //cria��o e aloca��o do vetor de n�s que armazenar� os dados fornecidos pelo usu�rio

    double temp; //vari�vel para armazenar a leitura

    for (int i = 0; i < num_nos; i++){              // estrutura de repeti��o que rodar� para cada n� existente

        arq_nos  >> temp;
        vet_nos[i].set_id_no(temp);

        arq_nos  >> temp;
        vet_nos[i].set_x(temp);

        arq_nos  >> temp;
        vet_nos[i].set_y(temp);

        arq_nos  >> temp;
        vet_nos[i].set_des_x(temp);

        arq_nos  >> temp;
        vet_nos[i].set_des_y(temp);

        arq_nos  >> temp;
        vet_nos[i].set_forca_x(temp);

        arq_nos  >> temp;
        vet_nos[i].set_forca_y(temp);

    }

    arq_nos.close();

    int contador = 0;   //contador que ir� armazenar a �ltima posi��o numerada como n� livre
    for(int i = 0; i < num_nos; i++){       //Estrutura de repeti��o para percorer todos os n�s e identificar  de 1 a n o n�mero de n�s livres
        if(vet_nos[i].get_des_x() != 0){    //Testa se o n� � livre na dire��o x
            vet_nos[i].set_id_x(contador);
            ++contador;
        }
        if(vet_nos[i].get_des_y() != 0){    //Testa se o n� � livre na dire��o y
            vet_nos[i].set_id_y(contador);
            ++contador;
        }
    }

    int gls = contador; //armazena o n�mero de  graus de liberdade (menos um pq gls acessar� a matriz de o a (n - 1)

    double * forcas;

    forcas = (double*) malloc(gls * sizeof(double));
    
    int c = 0;
    for(int i = 0; i < num_nos; i++){       //Estrutura de repeti��o para percorer todos os n�s e identificar  de 1 a n o n�mero de n�s livres
        if(vet_nos[i].get_des_x() != 0){
            forcas[c] = vet_nos[i].get_forca_x();
            ++c;
        }
        if(vet_nos[i].get_des_y() != 0){
            forcas[c] = vet_nos[i].get_forca_y();
            ++c;
        }
        
    }
   
    

    for(int i = 0; i < num_nos; i++){       //Estrutura de repeti��o para percorer todos os n�s e identificar  de 1 a n o n�mero de n�s fixos
        if(vet_nos[i].get_des_x() == 0){
            vet_nos[i].set_id_x(contador);
            ++contador;
        }
        if(vet_nos[i].get_des_y() == 0){
            vet_nos[i].set_id_y(contador);
            ++contador;
        }
    }

    for (int i = 0; i < num_nos; i++) {
        cout << i << " " << " id_x " << vet_nos[i].get_id_x() << " id_y " << vet_nos[i].get_id_y() << endl;
    }

    string nome_membros;
    cout << "DIGITE O NOME DO ARQUIVO DE MEMBROS (m�nusculo com a extens�o .txt): ";
    cin  >> nome_membros;

    nome_membros += ".txt";

    ifstream arq_membros;

    arq_membros.open(nome_membros.c_str(), ios::in); // abre o arquivo para leitura

    while(! arq_membros)
    {
        cout << "Arquivo vet_membros.txt nao pode ser aberto" << endl;
        cout << "DIGITE NOVAMENTE O NOME DO ARQUIVO DE MEMBROS (m�nusculo com a extens�o .txt): ";
        cin >> nome_membros;
        nome_membros += ".txt";
        arq_membros.open(nome_membros.c_str(), ios::in); // abre o arquivo para leitura
    }

    int num_membros;    //vari�vel que armazenar� o n�mero de membross
    cout << "DIGITE A QUANTIDADE DE MEMBROS DA ESTRUTURA: ";
    cin  >> num_membros;    //leitura do n�mero de membros

    membro * vet_membros;
    vet_membros = (membro*) malloc(num_membros * sizeof(membro)); //cria��o e aloca��o do vetor de membros que armazenar� os dados fornecidos pelo usu�rio

    int pos;    //vari�vel que armazenar� a posi��o do n� inicial e final dos membros dentro do ventor de n�s
    double ea;   //vari�vel que armazenar� o m�dulo de elasticidad e a �rea de cada membro digitado pelo usu�rio

    for(int i = 0; i < num_membros; i++){
        arq_membros >> pos;
        vet_membros[i].set_id(pos);

        arq_membros >> pos; //leitura da posi��o do n� no vetor de n�s
        vet_membros[i].set_no_i(vet_nos[pos-1]);    //atribui o n� na posi��o digitada pelo usu�rio ao n� inicial


        arq_membros >> pos; //leitura da posi��o do n� no vetor de n�s
        vet_membros[i].set_no_f(vet_nos[pos-1]);    //atribui o n� na posi��o digitada pelo usu�rio ao n� final


        arq_membros >> ea; //leitura da posi��o do n� no vetor de n�s
        vet_membros[i].set_e(ea);


        arq_membros >> ea; //leitura da posi��o do n� no vetor de n�s
        vet_membros[i].set_a(ea);
    }

    arq_membros.close();

    string nome_resultado;
    cout << "DIGITE O NOME QUE TER� O ARQUIVO COM O RESULTADO (m�nusculo com a extens�o .txt): ";
    cin >> nome_resultado;
    nome_resultado += ".txt";

    ofstream arq_resultado(nome_resultado.c_str(),ios::out);

    arq_resultado << scientific << setprecision(2);

    if (! arq_resultado)
    {
        cout << "Arquivo arq_resultado.txt nao pode ser aberto" << endl;
        abort();
    }

    sis_global k;

    k.set_gls(gls);

    k.set_mat_global(vet_membros,num_membros, contador);

    double **mat_inv;

    mat_inv = new double*[gls];

    for (int i = 0; i < gls; i++)
        mat_inv[i] = new double[gls];

    for (int i = 0; i < gls; i++)
        for (int j = 0; j < gls; j++)
            mat_inv[i][j] = k.get_mat_global(i, j);

    cout << "gls: " << k.get_gls() << endl;

    imprimir_mat(k.get_mat(), contador, contador);

    k.set_vet_deslocamento(k.get_mat(),forcas,gls);

    k.set_vet_forcas(k.get_mat(),k.get_vet_des(), gls, contador);

    arq_resultado << "#####################################" << endl;
    arq_resultado << "DESLOCMENTO NOS N�S" << endl;
    arq_resultado << "-------------------------------------" << endl;
    arq_resultado << "N�\tDES. X (mm)\tDES. Y (mm)" << endl;
    arq_resultado << "-------------------------------------" << endl;

    //estrutura de repeti��o que percorre todos os nos verificando se as dire��es s�o livres ou n�o
    double temp_x, temp_y, cont = 0;//vari�veis auxili�res. cont -> guarda a posi��o do vetor deslocamento que j� foi alocada
    for (int i = 0; i < num_nos; i++) {
        temp_x = 0;//armazena o deslocamento na dire��o x caso o n� seja livre na dire��o x
        temp_y = 0;//armazena o deslocamento na dire��o y caso o n� seja livre na dire��o y

        if (vet_nos[i].get_des_x() != 0) {
            temp_x = k.get_vet_deslocamento(cont); //atribui o valor do deslocamento da posi��o "cont" do veotor de deslocamento a variavel tempor�rio
            ++cont;
        }
        if (vet_nos[i].get_des_y() != 0) {
            temp_y = k.get_vet_deslocamento(cont); //atribui o valor do deslocamento da posi��o "cont" do veotor de deslocamento a variavel tempor�rio
            ++cont;
        }
        arq_resultado << noshowpos << vet_nos[i].get_id_no() << showpos << "\t" << temp_x << "\t" << temp_y << endl;
        vet_nos[i].set_Dx(temp_x);
        vet_nos[i].set_Dy(temp_y);
    }

    arq_resultado << fixed << setprecision(3);

    arq_resultado << "#####################################" << endl;
    arq_resultado << "REA��ES DE APOIO" << endl;
    arq_resultado << "-------------------------------------" << endl;
    arq_resultado << "N�\tFx(kN)\t\tFy(kN)" << endl;
    arq_resultado << "-------------------------------------" << endl;

    cont = 0;
    for (int i = 0; i < num_nos; i++) {
        temp_x = 0;
        temp_y = 0;

        if (vet_nos[i].get_des_x() == 0) {
            temp_x = k.get_vet_forcas(cont) - vet_nos[i].get_forca_x();
            ++cont;
        }
        if (vet_nos[i].get_des_y() == 0) {
            temp_y = k.get_vet_forcas(cont) - vet_nos[i].get_forca_y();
            ++cont;
        }
        arq_resultado << noshowpos << vet_nos[i].get_id_no() << showpos << "\t" << temp_x << "\t\t" << temp_y << endl;
    }

    for (int i = 0; i < num_membros; i++) {
        
        vet_membros[i].set_vet_desl_nos(vet_nos);
    }

    for (int i = 0; i < num_membros; i++) {
        
        vet_membros[i].set_vet_desl_locais();
    }

    arq_resultado << "###########################################" << endl;
    arq_resultado << "DESLOCAMENTOS AXIAIS DOS MEMBROS" << endl;
    arq_resultado << "-------------------------------------------" << endl;
    arq_resultado << "MEMBRO\t\tD'i (mm)\tD'j (mm)" << endl;
    arq_resultado << "-------------------------------------------" << endl;

    arq_resultado << scientific << setprecision(2);
    
    for (int i = 0; i < num_membros; i++) {
        arq_resultado << noshowpos << vet_membros[i].get_id() << "(";
        arq_resultado << vet_membros[i].get_no_i().get_id_no() << ",";
        arq_resultado << vet_membros[i].get_no_f().get_id_no() << ")\t";
        arq_resultado << "\t" << showpos << vet_membros[i].get_desl_locais(0);
        arq_resultado << "\t" << vet_membros[i].get_desl_locais(1) << endl;
    }

    for (int i = 0; i < num_membros; i++) {
        vet_membros[i].set_vet_esf_int();
    }

    arq_resultado << "###########################################################" << endl;
    arq_resultado << "ESFOR�OS AXIAIS NOS MEMBROS" << endl;
    arq_resultado << "-----------------------------------------------------------" << endl;
    arq_resultado << "MEMBRO\t\tF'i (KN)\tF'j (KN)\tTENS�ES" << endl;
    arq_resultado << "-----------------------------------------------------------" << endl;

    arq_resultado << fixed << setprecision(3);

    for (int i = 0; i < num_membros; i++) {
        arq_resultado << noshowpos << vet_membros[i].get_id() << "(";
        arq_resultado << vet_membros[i].get_no_i().get_id_no() << ",";
        arq_resultado << vet_membros[i].get_no_f().get_id_no() << ")\t";
        arq_resultado << "\t" << showpos << vet_membros[i].get_esf_axi(0);
        arq_resultado << "\t\t" << vet_membros[i].get_esf_axi(1) << "\t\t"; 

        if (vet_membros[i].get_esf_axi(0) < 0) 
            arq_resultado << "TRA��O" << endl;
        else if (vet_membros[i].get_esf_axi(0) == 0)
            arq_resultado << "NEUTRA" << endl;
        else
            arq_resultado << "COMPRESS�O" << endl;
    }

    arq_resultado.close();

    k.free_sis_global();

    for (int i = 0; i < num_membros; i++)
        vet_membros[i].free_membro();

    free(vet_membros);

    free(vet_nos);

    free(forcas);

    cout << "Deu Certo" << endl;

    return 0;
}
