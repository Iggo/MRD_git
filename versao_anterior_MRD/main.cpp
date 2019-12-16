/**

 Programa: MÉTODO DA RIGIDEZ DIRETA - MRD

 Disciplina: Análise de Estruturas II

 Autor: Iggo Guimarães/David Kennedy/Amanda Lyz

 Professor: Maurício Mello

 Arquivo: main.cpp

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

    cout << "\t\tMÉTODO DA RIGIDEZ DIRETA - MRD:" << endl;
    cout << "Análise de treliças planas sujeitas a carregamentos " << endl;
    cout << "\tnódais pelo Método da Rigidez Direta" << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "\t\tINSTRUÇÕES DE USO DO PROGRAMA:" << endl;
    cout << "-O PROGRAMA LERÁ DOIS ARQUIVOS (.txt). " << endl;
    cout << "UM COM AS INFORMAÇÕES SOBRE OS NÓS DO SISTEMA E" << endl;
    cout << "OUTRO COM AS INFORMAÇÕES DOS MEMBROS DO SISTEMA." << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "-FORMATO DO ARQUIVO DE NÓS:" << endl;
    cout << "ID_NÓ\tX(m)\tY(m)\tDESL. EM X (1 ou 0)\tDESL. EM Y (1 ou 0 )\tFx(KN)\tFy(KN)" << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "OBS. 1: O ARQUIVO NÃO PRECISA DE CABEÇALHO." << endl;
    cout << "OBS. 2: EM DESLOCABILIDADE 1 E 0 SIGNIFICAM LIVRE E FIXO, RESPECTIVAMENTE." << endl;
    cout << "OBS. 3: CADA LINHA DO ARQUIVO REFERE-SE A UM NÓ." << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "-FORMATO DO ARQUIVO DE MEMBROS:" << endl;
    cout << "ID_MEMBRO\tNÓ INICIAL\tNÓ FINAL\tMÓDULO DE ELAST(MPa)\tÁREA DA SEÇÃO TRANS(cm²)" << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "OBS. 1: O ARQUIVO NÃO PRECISA DE CABEÇALHO." << endl;
    cout << "OBS. 2: A COLUNA DE NÓ RECEBE ID DOS NÓS CRIANDOS NO ARQUIVO DE NÓS." << endl;
    cout << "OBS. 3: CADA LINHA DO ARQUIVO REFERE-SE A UM NÓ." << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "----------GARANTA QUE OS ARQUIVOS JÁ FORAM---------" << endl;
    cout << "--------CRIADOS ANTES DE INICIAR O PROGRAMA!-------" << endl;
    cout << "---------------------------------------------------" << endl<< endl;

    string nome_nos;
    cout << "DIGITE O NOME DO ARQUIVO DE NÓS (mínusculo com a extensão .txt): ";
    cin  >> nome_nos;

    nome_nos += ".txt";

    ifstream arq_nos;
    //cout << nome_nos << endl;

    arq_nos.open(nome_nos.c_str(), ios::in); // abre o arquivo para leitura

    while(! arq_nos)
    {
        cout << "ARQUIVO " << nome_nos << " NÃO PODE SER ABERTO!" << endl;
        cout << "DIGITE NOVAMENTE O NOME DO ARQUIVO DE NOS (mínusculo com a extensão .txt): ";
        cin >> nome_nos;
        nome_nos += ".txt";
        arq_nos.open(nome_nos.c_str(), ios::in); // abre o arquivo para leitura
    }

    int num_nos;
    cout << "DIGITE A QUANTIDADE DE NÓS DA ESTRUTURA: ";
    cin  >> num_nos;

    no * vet_nos;
    vet_nos = (no *) malloc(num_nos * sizeof(no)); //criação e alocação do vetor de nós que armazenará os dados fornecidos pelo usuário

    double temp; //variável para armazenar a leitura

    for (int i = 0; i < num_nos; i++){              // estrutura de repetição que rodará para cada nó existente

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

    int contador = 0;   //contador que irá armazenar a última posição numerada como nó livre
    for(int i = 0; i < num_nos; i++){       //Estrutura de repetição para percorer todos os nós e identificar  de 1 a n o número de nós livres
        if(vet_nos[i].get_des_x() != 0){    //Testa se o nó é livre na direção x
            vet_nos[i].set_id_x(contador);
            ++contador;
        }
        if(vet_nos[i].get_des_y() != 0){    //Testa se o nó é livre na direção y
            vet_nos[i].set_id_y(contador);
            ++contador;
        }
    }

    int gls = contador; //armazena o número de  graus de liberdade (menos um pq gls acessará a matriz de o a (n - 1)

    double * forcas;

    forcas = (double*) malloc(gls * sizeof(double));
    
    int c = 0;
    for(int i = 0; i < num_nos; i++){       //Estrutura de repetição para percorer todos os nós e identificar  de 1 a n o número de nós livres
        if(vet_nos[i].get_des_x() != 0){
            forcas[c] = vet_nos[i].get_forca_x();
            ++c;
        }
        if(vet_nos[i].get_des_y() != 0){
            forcas[c] = vet_nos[i].get_forca_y();
            ++c;
        }
        
    }
   
    

    for(int i = 0; i < num_nos; i++){       //Estrutura de repetição para percorer todos os nós e identificar  de 1 a n o número de nós fixos
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
    cout << "DIGITE O NOME DO ARQUIVO DE MEMBROS (mínusculo com a extensão .txt): ";
    cin  >> nome_membros;

    nome_membros += ".txt";

    ifstream arq_membros;

    arq_membros.open(nome_membros.c_str(), ios::in); // abre o arquivo para leitura

    while(! arq_membros)
    {
        cout << "Arquivo vet_membros.txt nao pode ser aberto" << endl;
        cout << "DIGITE NOVAMENTE O NOME DO ARQUIVO DE MEMBROS (mínusculo com a extensão .txt): ";
        cin >> nome_membros;
        nome_membros += ".txt";
        arq_membros.open(nome_membros.c_str(), ios::in); // abre o arquivo para leitura
    }

    int num_membros;    //variável que armazenará o número de membross
    cout << "DIGITE A QUANTIDADE DE MEMBROS DA ESTRUTURA: ";
    cin  >> num_membros;    //leitura do número de membros

    membro * vet_membros;
    vet_membros = (membro*) malloc(num_membros * sizeof(membro)); //criação e alocação do vetor de membros que armazenará os dados fornecidos pelo usuário

    int pos;    //variável que armazenará a posição do nó inicial e final dos membros dentro do ventor de nós
    double ea;   //variável que armazenará o módulo de elasticidad e a área de cada membro digitado pelo usuário

    for(int i = 0; i < num_membros; i++){
        arq_membros >> pos;
        vet_membros[i].set_id(pos);

        arq_membros >> pos; //leitura da posição do nó no vetor de nós
        vet_membros[i].set_no_i(vet_nos[pos-1]);    //atribui o nó na posição digitada pelo usuário ao nó inicial


        arq_membros >> pos; //leitura da posição do nó no vetor de nós
        vet_membros[i].set_no_f(vet_nos[pos-1]);    //atribui o nó na posição digitada pelo usuário ao nó final


        arq_membros >> ea; //leitura da posição do nó no vetor de nós
        vet_membros[i].set_e(ea);


        arq_membros >> ea; //leitura da posição do nó no vetor de nós
        vet_membros[i].set_a(ea);
    }

    arq_membros.close();

    string nome_resultado;
    cout << "DIGITE O NOME QUE TERÁ O ARQUIVO COM O RESULTADO (mínusculo com a extensão .txt): ";
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
    arq_resultado << "DESLOCMENTO NOS NÓS" << endl;
    arq_resultado << "-------------------------------------" << endl;
    arq_resultado << "NÓ\tDES. X (mm)\tDES. Y (mm)" << endl;
    arq_resultado << "-------------------------------------" << endl;

    //estrutura de repetição que percorre todos os nos verificando se as direções são livres ou não
    double temp_x, temp_y, cont = 0;//variáveis auxiliáres. cont -> guarda a posição do vetor deslocamento que já foi alocada
    for (int i = 0; i < num_nos; i++) {
        temp_x = 0;//armazena o deslocamento na direção x caso o nó seja livre na direção x
        temp_y = 0;//armazena o deslocamento na direção y caso o nó seja livre na direção y

        if (vet_nos[i].get_des_x() != 0) {
            temp_x = k.get_vet_deslocamento(cont); //atribui o valor do deslocamento da posição "cont" do veotor de deslocamento a variavel temporário
            ++cont;
        }
        if (vet_nos[i].get_des_y() != 0) {
            temp_y = k.get_vet_deslocamento(cont); //atribui o valor do deslocamento da posição "cont" do veotor de deslocamento a variavel temporário
            ++cont;
        }
        arq_resultado << noshowpos << vet_nos[i].get_id_no() << showpos << "\t" << temp_x << "\t" << temp_y << endl;
        vet_nos[i].set_Dx(temp_x);
        vet_nos[i].set_Dy(temp_y);
    }

    arq_resultado << fixed << setprecision(3);

    arq_resultado << "#####################################" << endl;
    arq_resultado << "REAÇÕES DE APOIO" << endl;
    arq_resultado << "-------------------------------------" << endl;
    arq_resultado << "Nó\tFx(kN)\t\tFy(kN)" << endl;
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
    arq_resultado << "ESFORÇOS AXIAIS NOS MEMBROS" << endl;
    arq_resultado << "-----------------------------------------------------------" << endl;
    arq_resultado << "MEMBRO\t\tF'i (KN)\tF'j (KN)\tTENSÕES" << endl;
    arq_resultado << "-----------------------------------------------------------" << endl;

    arq_resultado << fixed << setprecision(3);

    for (int i = 0; i < num_membros; i++) {
        arq_resultado << noshowpos << vet_membros[i].get_id() << "(";
        arq_resultado << vet_membros[i].get_no_i().get_id_no() << ",";
        arq_resultado << vet_membros[i].get_no_f().get_id_no() << ")\t";
        arq_resultado << "\t" << showpos << vet_membros[i].get_esf_axi(0);
        arq_resultado << "\t\t" << vet_membros[i].get_esf_axi(1) << "\t\t"; 

        if (vet_membros[i].get_esf_axi(0) < 0) 
            arq_resultado << "TRAÇÃO" << endl;
        else if (vet_membros[i].get_esf_axi(0) == 0)
            arq_resultado << "NEUTRA" << endl;
        else
            arq_resultado << "COMPRESSÃO" << endl;
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
