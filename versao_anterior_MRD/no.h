/**

 Programa: MÉTODO DA RIGIDEZ DIRETA - MRD

 Disciplina: Análise de Estruturas II

 Autor: Iggo Guimarães/David Kennedy/Amanda Lyz

 Professor: Maurício Mello

 Arquivo: no.h

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

#ifndef NO_H
#define NO_H

class no
{
    public:
        no();

        /*SET'S*/

        void set_id_no(int i);

        void set_x(double pos);

        void set_y(double pos);

        void set_id_x(int id);

        void set_id_y(int id);

        void set_des_x(double pos);

        void set_des_y(double pos);

        void set_forca_x(double pos);

        void set_forca_y(double pos);

        void set_Dx(double d);

        void set_Dy(double d);

        /*GET'S*/
        int get_id_no();

        double get_x();

        double get_y();

        int get_id_x();

        int get_id_y();

        int get_des_x();

        int get_des_y();

        double get_forca_x();

        double get_forca_y();

        double get_Dx();

        double get_Dy();

        virtual ~no();

    protected:

    private:
        int     id;       //identificação do nó
        double  pos_x;    //coordenada x inicial
        double  pos_y;    //coordenada y inicial
        int     id_x;     //id do deslocamento na direção x
        int     id_y;     //id do deslocamento na direção y
        double  des_x;    //deslocabilidade em x (0 -> fixo / 1 -> móvel)
        double  des_y;    //deslocabilidade em y (0 -> fixo / 1 -> móvel)
        double  forca_x;  //força na direção x
        double  forca_y;  //força na direção y
        double  Dx;       //deslocamento na direção x   
        double  Dy;       //deslocamento na direção y
};

#endif // NO_H
