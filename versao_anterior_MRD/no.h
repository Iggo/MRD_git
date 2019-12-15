/**

 Programa: M�TODO DA RIGIDEZ DIRETA - MRD

 Disciplina: An�lise de Estruturas II

 Autor: Iggo Guimar�es/David Kennedy/Amanda Lyz

 Professor: Maur�cio Mello

 Arquivo: no.h

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
        int     id;       //identifica��o do n�
        double  pos_x;    //coordenada x inicial
        double  pos_y;    //coordenada y inicial
        int     id_x;     //id do deslocamento na dire��o x
        int     id_y;     //id do deslocamento na dire��o y
        double  des_x;    //deslocabilidade em x (0 -> fixo / 1 -> m�vel)
        double  des_y;    //deslocabilidade em y (0 -> fixo / 1 -> m�vel)
        double  forca_x;  //for�a na dire��o x
        double  forca_y;  //for�a na dire��o y
        double  Dx;       //deslocamento na dire��o x   
        double  Dy;       //deslocamento na dire��o y
};

#endif // NO_H
