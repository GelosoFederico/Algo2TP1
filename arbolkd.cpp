#include <iostream>

using namespace std;

template<class T> class Nodo {
    private:
        T dato;
        Nodo<T>* izquierda;
        Nodo<T>* derecha;
        Nodo<T>* padre;
    public:
        Nodo(T dato) {
            this->setDato(dato);
            this->setizquierda(NULL);
            this->setderecha(NULL);
            this->setpadre(NULL);
        }
        virtual ~Nodo() {}//ESTABA ASI (virtual) PERO QUIERO PREGUNTARLO DESPUES
        void setDato(T dato) {
            this->dato = dato;
        }
        T getDato() {
            return this->dato;
        }
        void setizquierda(Nodo<T>* nodo) {
            this->izquierda = nodo;
        }
        void setderecha(Nodo<T>* nodo) {
            this->derecha = nodo;
        }
        Nodo<T>* getizquierda() {
            return this->izquierda;
        }
        Nodo<T>* getderecha() {
            return this->derecha;
        }
        bool tieneizquierda() const {

            return (this->izquierda != NULL);
        }
        bool tienederecha() const {

            return (this->derecha != NULL);
        }
        void setpadre(Nodo<T> *nodo) {
            this->padre = nodo;
        }
        Nodo<T>* getpadre() {
            return this->padre;
        }
        bool tienepadre() const {
            return (this->padre != NULL);
        }
        void agregarizquierda(T datonuevo)
        {
            if(this->getizquierda()==NULL)
            {
                Nodo<T> *aux=new Nodo<T>(datonuevo);
                this->setizquierda(aux);//problema aca
                aux->setderecha(NULL);
                aux->setizquierda(NULL);
                aux->setpadre(this);
            }
            else
            {
                if(datonuevo<this->getDato())
                    getizquierda()->agregarizquierda(datonuevo);
                else
                    getizquierda()->agregarderecha(datonuevo);
            }
        }
        void agregarderecha(T datonuevo)
        {
            if(this->getderecha()==NULL)
            {
                Nodo<T> *aux=new Nodo<T>(datonuevo);
                this->setderecha(aux);//problema aca
                aux->setderecha(NULL);
                aux->setizquierda(NULL);
                aux->setpadre(this);
            }
            else
            {
                if(datonuevo<this->getDato())
                    getderecha()->agregarizquierda(datonuevo);
                else
                    getderecha()->agregarderecha(datonuevo);
            }
        }
        void agregarraiz(T datonuevo)//TENGO QUE ARREGLARLA
        {

            this->setderecha(NULL);
            this->setizquierda(NULL);
            this->setpadre(NULL);
        }
    void destruir()
    {
        if(this->getizquierda()!=NULL)
            getizquierda()->destruir();
        if(this->getderecha()!=NULL)
            getderecha()->destruir();
        delete this;
        //cout<<"se ha eliminado un nodo"<<endl;
    }
};

template<class T> class pila{
private:
    Nodo<T>* raiz;
public:
    pila(){raiz=NULL;}
    pila(const pila& orig){raiz=orig.raiz;}
    pila(T dato){
        inicializar(dato);
    }
    ~pila(){
        if(!vacia())
        {
            this->raiz->destruir();
            //cout<<"se ha eliminado una pila"<<endl;
        }
    }
    bool vacia()
    {
        return(raiz==NULL);
    }
    void inicializar(T datonuevo)
    {
        Nodo<T> *aux=new Nodo<T>(datonuevo);
        raiz=aux;
        raiz->setizquierda(NULL);
        raiz->setderecha(NULL);
        raiz->setpadre(NULL);
    }
    void agregar(T datonuevo)
    {
        if(raiz==NULL)
            inicializar(datonuevo);
        else
        {
            if(datonuevo<raiz->getDato())
                raiz->agregarizquierda(datonuevo);
            else
                raiz->agregarderecha(datonuevo);
        }

    }
};







int main()
{
    pila<int> jorge;
    cout<<"pila vacia: "<<jorge.vacia()<<endl;
    jorge.inicializar(5);
    cout<<"pila vacia: "<<jorge.vacia()<<endl;
    jorge.agregar(3);
    jorge.agregar(6);
    jorge.agregar(4);
    jorge.agregar(1);
    jorge.agregar(0);
    jorge.agregar(9);
    jorge.agregar(25);
    jorge.agregar(-3);
    cout<<"pila vacia: "<<jorge.vacia()<<endl;
    return 0;
}
