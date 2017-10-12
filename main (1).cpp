#include <iostream>
#include <Array.h>

using namespace std;

class Nodo {

    private:
        /*los puntos que definen la region*/
        Array <double> botleft;
        Array <double> topright;
        /*el corte de la variable*/
        char breakdimension;
        double breakpoint;
        /*conjunto de puntos en este nodo*/
        Array <Array <double> > tiberium_points;
        /*los punteros al resto del arbol*/
        Nodo* branch_left;
        Nodo* branch_right;
        Nodo* father;
    public:
        //constructor de rama: requiere un punto de corte para dividir la region
        Nodo(char bkd, double bkp[2]) {
            //determina el corte
            this->set_breakdimension(bkd);
            this->set_breakpoint(bkp);
            //aca hace falta setear el resto de los datos
            /**definir la region (set_toprigh y set_botleft, o bien set_region con ambos)*/
            /**copiar el array de puntos correspondiente a la region*/
            //prepara punteros vacios para la inicializacion de nuevos nodos debajo del actual
            this->set_branch_left(NULL);
            this->set_branch_right(NULL);
            this->set_father(NULL);
        }
        virtual ~Nodo() {}//de nuevo, habria que preguntar lo del destructor virtual porque no lo termine de entender

        double get_breakpoint() {
            return this->breakpoint;
        }
        char get_breakdimension()
        {
            return this->breakdimension;
        }
        Array <double> get_topright
        {
            return topright;
        }
        Array <double> get_botleft
        {
            return botleft;
        }
        void set_breakpoint(double bkp[2])
        {
            this->breakpoint=bkp;
        }
        void set_breakdimension(char bkd)
        {
            this->breakdimension=bkd;
        }
        void set_region(Array <double> bl, Array <double> tr)
        {
            this->topright=tr;
            this->botleft=bl;
        }
        Array <Array <double> > get_region_points()/**falta completar bien*/
        {
            int i=0; Array <Array <double> lista=NULL;
            while(this->tiberium_points[i])
            {
                if(esta_en_region(topright,botleft,tiberium_points[i]))//hay que hacer una funcion que determine si el punto esta en la region determinada
                    lista.append(tiberium_points[i]);//esto era asi para agregarle la coordenada?
            }
        }
        void set_branch_left(Nodo* nodo) {
            this->branch_left = nodo;
        }
        void set_branch_right(Nodo* nodo) {
            this->branch_right = nodo;
        }
        Nodo* get_branch_left() {
            return this->branch_left;
        }
        Nodo* get_branch_right() {
            return this->branch_right;
        }
        bool tienebranch_left() const {

            return (this->branch_left != NULL);
        }
        bool tienebranch_right() const {

            return (this->branch_right != NULL);
        }
        void set_father(Nodo *nodo) {
            this->father = nodo;
        }
        Nodo* get_father() {
            return this->father;
        }
        bool has_father() const {
            return (this->father != NULL);
        }
        void add_branch_left(T datonuevo)
        {
            if(this->get_branch_left()==NULL)
            {
                Nodo *aux=new Nodo(datonuevo);
                this->set_branch_left(aux);
                aux->set_branch_right(NULL);
                aux->set_branch_left(NULL);
                aux->set_father(this);
            }
            else
            {
                if(datonuevo<this->get_Dato())
                    get_branch_left()->add_branch_left(datonuevo);
                else
                    get_branch_left()->add_branch_right(datonuevo);
            }
        }
        void add_branch_right(T datonuevo)
        {
            if(this->get_branch_right()==NULL)
            {
                Nodo *aux=new Nodo(datonuevo);
                this->set_branch_right(aux);
                aux->set_branch_right(NULL);
                aux->set_branch_left(NULL);
                aux->set_father(this);
            }
            else
            {
                if(datonuevo<this->get_breakpoint())//esto no es exactamente asi porque lo que va a hacer es separar la region
                    get_branch_right()->add_branch_left(datonuevo);
                else
                    get_branch_right()->add_branch_right(datonuevo);
            }
        }
        void add_root(/**aca decia T dato, lo reemplazo por todo lo que necesite inicializar en la raiz (region, puntos, corte)*/)
        {
            /**setear los datos*/
            this->set_branch_right(NULL);
            this->set_branch_left(NULL);
            this->set_father(NULL);
        }
    void destroy()/**esto funcionaba porque dato era memoria estatica por cada nodo, ahora habria que agregar un destructor mas complejo con los arrays que hay para las coordenadas*/
    {
        if(this->get_branch_left()!=NULL)
            get_branch_left()->destroy();
        if(this->get_branch_right()!=NULL)
            get_branch_right()->destroy();
        delete this;
        //cout<<"se ha eliminado un nodo"<<endl;
    }
};

class kdtree{
private:
    Nodo* root;
public:
    kdtree(){root=NULL;}
    kdtree(const kdtree& orig){root=orig.root;}
    ~kdtree(){
        if(!vacia())
        {
            this->root->destroy();
            //cout<<"se ha eliminado un arbol"<<endl;
        }
    }
    bool vacia()
    {
        return(root==NULL);
    }
    void add_root(T datonuevo)/**esto tiene que dar de alta una raiz*/
    {
        Nodo *aux=new Nodo(datonuevo);
        root=aux;
        root->set_branch_left(NULL);
        root->set_branch_right(NULL);
        root->set_father(NULL);
    }
    void add_branch(T datonuevo)/**hay que rearmar esto para dar de alta una rama u hoja*/
    {
        if(root==NULL)
            inicializar(datonuevo);
        else
        {
            if(datonuevo<root->get_Dato())
                root->add_branch_left(datonuevo);
            else
                root->add_branch_right(datonuevo);
        }

    }
};







int main()
{
    kdtree<int> jorge;
    cout<<"arbol vacio: "<<jorge.vacia()<<endl;
    return 0;
}
