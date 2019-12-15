#ifndef SIS_GLOBAL_H_INCLUDED
#define SIS_GLOBAL_H_INCLUDED


class sis_global{
    public:
        sis_global();

        /*SET'S*/

        void set_gls(int n); //aloca o gls

        void set_tam_matriz_gloobal(int tam);   //aloca o tamanho da matriz global

        void set_mat_global(membro * mem, int num_membros, int n);  //calcula e aloca a matriz global K

        void set_vet_deslocamento(double** matriz, double* forcas, int gl); //calcula e aloca o vetor de deslocamentos dos nós

        void set_vet_forcas(double** matriz, double* forcas, int gl, int n); //calcula e aloca as reações dos nós
        
        /*GET'S*/

        int get_gls();

        int get_tam_mat_global();

        double **get_mat();

        double get_mat_global(int i, int j);

        double *get_vet_des();

        double get_vet_deslocamento(int pos);

        double *get_vet_f();

        double get_vet_forcas(int pos);

        /*MÉTODOS*/

        void free_sis_global();

        virtual ~sis_global();

    protected:

    private:
        int     gls;                //graus livre
        int     tam_mat_global;      //tamanho da matriz global
        double  **matriz_global;    //matriz global
        double  *vet_deslocamento;  //vetor de deslocamento
        double  *vet_forcas;        //vetor de força
};

#endif // SIS_GLOBAL_H_INCLUDED