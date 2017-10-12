// Template de lista doblemente enlazada

#ifndef LIST_H
#define LIST_H


template <class T> class List
{
public:
	
private:
	class Node
	{
		public:
			friend class List;
			Node(){exit(1);}//Un nodo sin dato no tiene sentido
			Node(T Data,Node* Next, Node* Prev){
				this->SetData(Data);
				this->SetNext(Next);
				this->SetPrev(Prev);}
			

		private:
			T _Data;
			Node * _Next;
			Node * _Previous;
	}
}

#endif
