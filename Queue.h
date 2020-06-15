#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <iterator> // std::forward_iterator_tag
#include <cstddef>  // std::ptrdiff_t
#include <stdexcept>

//#define DEBUGGING

/**
	@file Queue.h 
	@brief Dichiarazione della classe templata Queue
*/


/**
	Classe eccezione custom che deriva da std::runtime_error
	Viene generata quando si tenta di fare pop()
	da una coda vuota

	@brief bad_pop_exception
*/
class bad_pop_exception : public std::runtime_error {
public:
	/**
		Costruttore di default 
	*/
    bad_pop_exception() : std::runtime_error("Pop on empty queue") {}
}; 


/**
	Classe eccezione custom che deriva da std::runtime_error
	Viene generata quando si tenta di accedere a valori
	non ancora inizializzati

	@brief my_uninitialized_value
*/
class my_uninitialized_value : public std::runtime_error {
public:
	/**
		Costruttore di default 
	*/
    my_uninitialized_value() : std::runtime_error("Value not inizializated") {}
};

/**
	Classe eccezione custom che deriva da std::runtime_error
	Viene generata quando si tenta di accedere ad indici 
	maggiori di end() con l'iteratore

	@brief  out_of_range_iterator
*/
class out_of_range_iterator : public std::runtime_error {
public:
	/**
		Costruttore di default 
	*/
    out_of_range_iterator() : std::runtime_error("Out of range with Iterator") {}
}; 

/**
	Classe che implementa una coda FIFO (Queue) di
	elementi generici T.

	@brief Coda FIFO (Queue)
	@param T Tipo del dato
*/
template<typename T>
class Queue{
private:

	/**
		Struttura che implementa un nodo della coda

		@brief Nodo della coda FIFO
	*/
	struct Node {
		T value; //dato inserito nel nodo
		Node *next; //puntatore al prossimo nodo
		Node *prev; //puntatore al nodo precedente


		/**
			@brief Costruttore default

			Costruttore di default che istanzia un nodo
			con value 0
		*/
		Node() : value(0), next(nullptr), prev(nullptr) {}


		/**
			@brief Costruttore 

			Costruttore che istanzia un nodo con 
			value v
			@param v Valore del nodo
		*/
		explicit Node(const T &v) : value(v), next(nullptr), prev(nullptr) { }


		/**
			@brief Costruttore

			Costruttore che istanzia un nodo 
			copia di n
			@param n nodo da copiare
			@throw my_uninitialized_value
		*/
		explicit Node(const Node *n) {
			if( n == nullptr ){
				throw my_uninitialized_value();
				#ifdef DEBUGGING
				std::cout << "Node null" << std::endl;
				#endif //DEBUGGING
			}
			else{
				this->value = n->value;
				this->prev = nullptr;
				
				if( n->next != nullptr ){
					try{
						this->next = new Node(n->next);
					}catch(...){
						this->next = nullptr; 
						throw;
					}
					this->next->prev = this;
				}
				else{
					this->next = nullptr;
				}
			}

		} 


		/**
			Funzione che calcola la dimensione
			dell'insieme di nodi, guardando solo
			in avanti

			@brief Ritorna la dimensione dell'insieme
			di nodi
		*/
		unsigned int size() const {
			if( this == nullptr ){
				return 0;
			}

			unsigned int sz = 1;
			return sz + this->next->size();
		}


		/**
			Funzione che distrugge l'insieme di nodi.
			Attenzione, distrugge solo in avanti!!

			@brief Distrugge l'insieme di nodi
		*/
		void destroy(){
			#ifdef DEBUGGING
			std::cout << "Size " << size() << std::endl;
			#endif //DEBUGGING
			if( this != nullptr ) {
				#ifdef DEBUGGING
				std::cout << "Destroy NOT null" << std::endl;
				#endif //DEBUGGING
				if( this->next != nullptr )
					this->next->destroy();
				delete this;
			}
			else{
				#ifdef DEBUGGING
				std::cout << "Destroy null" << std::endl;
				#endif //DEBUGGING
			}

		}


		/**
			Funzione setter per il valore di un nodo

			@brief Modifica il valore del nodo
			@throw my_uninitialized_value
		*/
		void set(const T &value) {
			if( this != nullptr ){
				this->value = value;
			}
			else{
				throw my_uninitialized_value();
			}
		}


		/**
			Funzione che stampa un insieme 
			di nodi in ordine di anzianita'
			decrescente.
			Funziona solo se T ha un operator<<
			definito!

			@brief Funzione di stampa dei nodi
		*/
		void show() const {
			if(this != nullptr){

				std::cout << this->value << "|";

				if( this->next != nullptr )
					this->next->show();
				else
					std::cout << "\n";
			}
			else{
				std::cout << "Empty Queue" << std::endl;
			}
		}

	};

	//Attributi della classe
	unsigned int sz; // dimensione della coda
	Node *root; // radice della coda ( older )
	Node *last;	// ultimo elemento della coda ( younger )

public:

	/**
		@brief Costruttore default

		Costruttore di default che istanzia una coda
		vuota
	*/
	Queue() : sz(0), root(nullptr), last(nullptr) {
		#ifdef DEBUGGING
		std::cout << "Queue()" << std::endl;
		#endif
	}


	/**
		@brief Costruttore

		Costruttore che istanzia una coda 
		di dimensione 1 e con valore v
		@param v Valore della radice
	*/
	explicit Queue(const T &v) : sz(1) {
		try{
			root = new Node(v);
		}catch(...){
			root = nullptr; 
			throw;
		}
		last = root;
	}


	/*
	private:
			@brief Costruttore privato

			Costruttore che istanzia una coda
			che ha come root n

			@param n Nodo da copiare e mettere come root
		
		Queue(const Node *n) {
			try{
				root = new Node(n);
			}catch(...){
				root = nullptr; 
				throw;
			}

			last = root;
			while( last->next != nullptr ){
				last = last->next;
			} //Ora last corrisponde all'ultimo nodo

			sz = root->size();

		} //se serve
	public:
	*/


	/**
		@brief Costruttore copia

		Costruttore che istanzia una coda
		come copia della coda other
		
		@param other Coda da copiare
	*/
	Queue(const Queue<T> &other) { 
		if( other.size() == 0 ){
			this->sz = 0;
			this->root = nullptr;
			this->last = nullptr;
		}
		else{
			try{
				root = new Node(other.root);
			}catch(...){
				root = nullptr; 
				throw;
			}

			last = root;
			while( last->next != nullptr ){
				last = last->next;
			} //Ora last corrisponde all'ultimo nodo

			sz = other.size();
		}

	}


	/**
		@brief Distruttore

		Distruttore. 
		Rimuove la memoria allocata dalla coda.
	*/
	~Queue() {
		root->destroy(); 
		#ifdef DEBUGGING
		std::cout << "~Queue" << std::endl;
		#endif //DEBUGGING
	}
	

	/**
		@brief Operatore di assegnamento

        Operatore di assegnamento.
		Ridefinizione operator =.
		Permette la copia tra code.
		
		@param other coda da copiare
	*/
	Queue<T>& operator=(const Queue<T> &other){	
		//destroy()
		if( other.size() == 0 ){
			root->destroy();
			this->sz = 0;
			this->root = nullptr;
			this->last = nullptr;
		}
		else{
			try{
				root->destroy();
				root = new Node(other.root);
			}catch(...){
				root = nullptr; 
				throw;
			}

			last = root;
			while( last->next != nullptr ){
				last = last->next;
			} //Ora last corrisponde all'ultimo nodo

			sz = other.size();
		}


	}
	

	/**
		Funzione che ritorna la dimensione della coda

		@brief Dimensione della coda
	*/
	unsigned int size() const{
		return sz;
	}


	/**
		Funzione getter per il valore piu' anziano,
		cioe' il primo inserito.

		@brief Ritorna il primo valore della coda

		@throw my_uninitialized_value
	*/
	const T& get_older() const{
		if(root == nullptr){
			throw my_uninitialized_value();
		}
		return root->value;
	}


	/**
		Funzione setter per il valore piu' anziano,
		cioe' il primo inserito.

		@brief Modifica il valore del primo elemento

		@throw my_uninitialized_value
	*/
	void set_older(const T &value) {
		if(root == nullptr){
			throw my_uninitialized_value();
		}
		else{
			root->set(value);
		} 
	}


	/**
		Funzione getter per il valore piu' giovane,
		cioe' l'ultimo inserito.

		@brief Ritorna l'ultimo valore della coda

		@throw my_uninitialized_value
	*/
	const T& get_younger() const{
		if(last == nullptr){
			throw my_uninitialized_value();
		}
		return last->value;
	}


	/**
		Funzione setter per il valore piu' giovane,
		cioe' l'ultimo inserito.

		@brief Modifica il valore dell'ultimo elemento

		@throw my_uninitialized_value
	*/
	void set_younger(const T &value) {
		if(last == nullptr){ // root == nullptr
			throw my_uninitialized_value();
		}
		else{
			last->set(value);
		} 
	}


	/**
		Funzione che inserisce un nodo con
		valore value in fondo alla coda.

		@brief Funzione di inserimento

		@param value Valore da inserire
	*/
	void push(const T &value) {
		if(root != nullptr) {
			try{
				last->next = new Node(value);
			}catch(...){
				last->next = nullptr; 
				throw;
			}
			last->next->prev = last;
			last = last->next;
			sz++;
		}
		else {
			try{
				root = new Node(value);
			}catch(...){
				root = nullptr; 
				throw;
			}
			last = root;
			sz++;
		}
		#ifdef DEBUGGING
		std::cout <<"Size: ";
		std::cout << sz << std::endl;
		#endif
	}


	/**
		Funzione che elimina il primo nodo
		cioe' piu' anziano (politica FIFO).

		@brief Funzione di delete

		@throw bad_pop_exception
	*/
	void pop() {
		if(root != nullptr && this->size() == 1) {
			root->destroy();
			root = nullptr;
			last = nullptr;
			sz--;
		}
		else if(root != nullptr) {
			root = root->next;
			root->prev->next = nullptr;
			root->prev->destroy();
			root->prev = nullptr;
			sz--;
		}
		else { // size == 0
			#ifdef DEBUGGING
			std::cout <<"Coda vuota"<< std::endl;
			#endif
			throw bad_pop_exception();

		}
		#ifdef DEBUGGING
		std::cout <<"Size: ";
		std::cout << sz << std::endl;
		#endif
	}


	/**
		Funzione che ritorna True se un 
		elemento di valore value e' presente,
		altrimenti False.

		@brief Funzione che verifica la presenza
		di un elemento

		@param value Valore da cercare
	*/
	bool contain(const T &value) const{
		if( this->size() == 0 ){
			return false;
		}
		Node *temp;
		temp = root;
		while( temp->next != nullptr ){
			if( temp->value == value ){
				//delete temp;
				return true;
			}
			temp = temp->next;
		} //Ora temp corrisponde all'ultimo nodo

		if( temp->value == value ){
				//delete temp;
				return true;
		}
		return false;

	}


	/**
		Funzione che stampa una coda in 
		ordine di anzianita' decrescente.

		@brief Funzione di stampa
	*/
	void show() const {
		root->show();
	}


	// Solo se serve anche const_iterator aggiungere la seguente riga
	class const_iterator; // forward declaration

	/**
		Iteratore della coda.
		@brief Iteratore.
	*/
	class iterator {
		//	
	public:
		typedef std::forward_iterator_tag iterator_category;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T& reference;

		/**
			Costruttore dell'iteratore

			@brief Mette il nodo a nullptr
		*/
		iterator() : ItPtr(nullptr) {}
		
		/**
			Costruttore copia dell'iteratore

			@brief Costruttore Copia 
			@param other Un altro iteratore
		*/
		iterator(const iterator &other) : ItPtr(other.ItPtr) {}

		/**
			Ridefinizione operator =

			@brief Operatore di assegnamento
			@param other Un altro iteratore costante
		*/
		iterator& operator=(const iterator &other) {
			ItPtr = other.ItPtr;
            return *this;
		}

		/**
			Distruttore dell'iteratore

			@brief Distruttore
		*/
		~iterator() {}

		/** 
			Ritorna il dato riferito dall'iteratore 
			(dereferenziamento)
			
			@brief Operatore di deferenziamento
			@throw my_uninitialized_value
		*/
		reference operator*() const {
			if( ItPtr == nullptr ){
				throw my_uninitialized_value();
			}
			return ItPtr->value;
		}

		/** 
			Ritorna il dato riferito dall'iteratore

			@brief operatore ->
			@throw my_uninitialized_value
		*/
		pointer operator->() const {
			if( ItPtr == nullptr ){
				throw my_uninitialized_value();
			}
			return &(ItPtr->value);
		}

		/**
			Operatore di iterazione post-incremento

			@brief Operatore di iterazione post-incremento
			@throw out_of_range_iterator
		*/
		iterator operator++(int) {
			if( ItPtr->next == nullptr ){
				throw out_of_range_iterator();
			}

			iterator tmp(*this);
            ItPtr = ItPtr->next;
            return tmp;
		}

		/**
			Operatore di iterazione pre-incremento

			@brief Operatore di iterazione pre-incremento
			@throw out_of_range_iterator
		*/
		iterator& operator++() {
			if( ItPtr->next == nullptr ){
				throw out_of_range_iterator();
			}

			ItPtr = ItPtr -> next;
			return *this;
		}

		/** 
		 	Ridefinizione dell'operatore di uguaglianza

			@brief Operatore di uguaglianza
			@param other Un altro iterator
		*/
		bool operator==(const iterator &other) const {
			return ItPtr == other.ItPtr;
		}

		/** 
		 	Ridefinizione dell'operatore di diseguaglianza

			@brief Operatore di uguaglianza
			@param other Un altro iterator
		*/
		bool operator!=(const iterator &other) const {
			return ItPtr != other.ItPtr;
		}
		
		
		// Solo se serve anche const_iterator aggiungere le seguenti definizioni
		friend class const_iterator;

		/** 
		 	Ridefinizione dell'operatore di uguaglianza 
			tra iteratore e const_iterator

			@brief Operatore di uguaglianza con const_iterator
			@param other Un iteratore const_iterator
		*/
		bool operator==(const const_iterator &other) const {
			return ItPtr == other.ItPtr;
		}

		/** 
		 	Ridefinizione dell'operatore di diseguaglianza 
			tra iteratore e const_iterator

			@brief Operatore di uguaglianza con const_iterator
			@param other Un iteratore const_iterator
		*/
		bool operator!=(const const_iterator &other) const {
			return ItPtr != other.ItPtr;
		}

		// Solo se serve anche const_iterator aggiungere le precedenti definizioni

	private:
		//Dati membro
		Node *ItPtr; //puntatore ai nodi
		// La classe container deve essere messa friend dell'iteratore per poter
		// usare il costruttore di inizializzazione.
		friend class Queue; 

		/**
			Costruttore privato di inizializzazione usato 
			dalla classe container tipicamente
			nei metodi begin e end
		*/
		iterator(Node *n) : ItPtr(n){}
		
		// !!! Eventuali altri metodi privati
		
	}; // classe iterator
	
	/**
		Ritorna l'iteratore all'inizio della sequenza dati
		@return iteratore all'inizio della sequenza
	*/
	iterator begin() {
		#ifdef DEBUGGING
		std::cout <<"Begin "<< std::endl;
		#endif 
		return iterator(root);
	}
	
	/**
		Ritorna l'iteratore alla fine della sequenza dati
		@return iteratore alla fine della sequenza
	*/
	iterator end() {
		#ifdef DEBUGGING
		std::cout <<"End "<< std::endl;
		#endif 
		return iterator(last);
	}
	
	
	/**
		Iteratore costante della coda.
		@brief Iteratore costante.
	*/
	class const_iterator {
		//	
	public:
		typedef std::forward_iterator_tag iterator_category;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef const T* pointer;
		typedef const T& reference;

	
		const_iterator() : ItPtr(nullptr) {}
		
		/**
			Costruttore copia dell'iteratore costante

			@brief Costruttore Copia 

			@param other Il const_iterator da copiare
		*/
		const_iterator(const const_iterator &other) : ItPtr(other.ItPtr) {}

		/**
			Ridefinizione operator =

			@brief Operatore di assegnamento
			@param other Un altro const_iterator other
		*/
		const_iterator& operator=(const const_iterator &other) {
			ItPtr = other.ItPtr;
			return *this;
		}

		/**
			Distruttore dell'iteratore

			@brief Distruttore dell'iteratore
		*/
		~const_iterator() {}

		/** 
			Ritorna il dato riferito dal 
			const_iterator (dereferenziamento)
			
			@brief operatore di deferenziamento
			@throw my_uninitialized_value
		*/
		reference operator*() const {
			if( ItPtr == nullptr ){
				throw my_uninitialized_value();
			}
			return ItPtr->value;
		}

		/** 
			Ritorna il dato riferito dal const_iterator 

			@brief operatore ->
			@throw my_uninitialized_value
		*/
		pointer operator->() const {
			if( ItPtr == nullptr ){
				throw my_uninitialized_value();
			}
			return &(ItPtr->value);
		}
		
		/**
			Operatore di iterazione post-incremento

			@brief Operatore di iterazione post-incremento

			@throw out_of_range_iterator
		*/
		const_iterator operator++(int) {
			if( ItPtr->next == nullptr ){
				throw out_of_range_iterator();
			}

			const_iterator tmp(*this);
            ItPtr = ItPtr->next;
            return tmp;
		}

		/**
			Operatore di iterazione pre-incremento

			@brief Operatore di iterazione pre-incremento

			@throw out_of_range_iterator
		*/
		const_iterator& operator++() {
			if( ItPtr->next == nullptr ){
				throw out_of_range_iterator();
			}

			ItPtr = ItPtr -> next;
			return *this;
		}

		/** 
		 	Ridefinizione dell'operatore di uguaglianza

			@brief Operatore di uguaglianza
			@param other Un altro const_iterator
		*/
		bool operator==(const const_iterator &other) const {
			return ItPtr == other.ItPtr;
		}
		
		/** 
		 	Ridefinizione dell'operatore di diseguaglianza

			@brief Operatore di uguaglianza
			@param other Un altro const_iterator
		*/
		bool operator!=(const const_iterator &other) const {
			return ItPtr != other.ItPtr;
		}

		// Solo se serve anche iterator aggiungere le seguenti definizioni
		
			friend class iterator;

		/** 
		 	Ridefinizione dell'operatore di uguaglianza 
			tra const_iterator e iterator 

			@brief Operatore di uguaglianza con iterator
			@param other Un iteratore costante
		*/
		bool operator==(const iterator &other) const {
			return ItPtr == other.ItPtr;
		}

		/** 
		 	Ridefinizione dell'operatore di disuguaglianza 
			tra const_iterator e iterator 

			@brief Operatore di uguaglianza con iterator
			@param other Un iteratore costante
		*/
		bool operator!=(const iterator &other) const {
			return ItPtr != other.ItPtr;
		}

		/**
			Costruttore di conversione iterator -> const_iterator
			@brief conversione da iterator a const_iterator
			@param other un altro iterator
		*/		
		const_iterator(const iterator &other) : ItPtr(other.ItPtr) {}

		/**
			Ridefinizione operator = da un iterator a 
			un const_iterator

			@brief operatore di assegnamento
			@param other un altro iterator
		*/
		const_iterator &operator=(const iterator &other) {
			ItPtr = other.ItPtr;
			return *this;
		}

		// Solo se serve anche iterator aggiungere le precedenti definizioni

	private:
		//Dati membro
		const Node* ItPtr;
		// La classe container deve essere messa friend dell'iteratore per poter
		// usare il costruttore di inizializzazione.
		friend class Queue;
		/**
			Costruttore privato di inizializzazione usato
			dalla classe container tipicamente
			nei metodi begin e end
		*/
		const_iterator(const Node* n) : ItPtr(n) {}
		
		// !!! Eventuali altri metodi privati
		
	}; // classe const_iterator

	/**
		Ritorna l'iteratore all'inizio della sequenza dati
		@return iteratore all'inizio della sequenza
	*/
	const_iterator begin() const {
		return const_iterator(root);
	}
	
	/**
		Ritorna l'iteratore alla fine della sequenza dati
		@return iteratore alla fine della sequenza
	*/
	const_iterator end() const {
		return const_iterator(last);
	}


	/**
		Funzione che inserisce un insieme di elementi 
		presi da una sequenza identificata da due iteratori.
		L'ordine di inserimento determina 
		l'anzianità dell'elemento.

		@brief Funzione di inserimento
		@param i const_iterator di inizio della sequenza
		@param ie const_iterator di fine della sequenza
		@throw my_uninitialized_value
		@throw out_of_range_iterator
	*/
	void push(const const_iterator &i, const const_iterator &ie) {
		const_iterator i_temp = i;
		while( i_temp != ie ){
			this->push( *i_temp );
			i_temp++;
		}
		this->push( *i_temp );

		#ifdef DEBUGGING
		std::cout <<"Size: ";
		std::cout << sz << std::endl;
		#endif
	}


	/**
		Funzione che inserisce un insieme di elementi 
		presi da una sequenza identificata da due iteratori.
		L'ordine di inserimento determina 
		l'anzianità dell'elemento.

		@brief Funzione di inserimento
		@param i iterator di inizio della sequenza
		@param ie iterator di fine della sequenza
		@throw my_uninitialized_value
		@throw out_of_range_iterator
	*/
	void push(const iterator &i, const iterator &ie) {
		iterator i_temp = i;
		while( i_temp != ie ){
			this->push( *i_temp );
			i_temp++;
		}
		this->push( *i_temp );

		#ifdef DEBUGGING
		std::cout <<"Size: ";
		std::cout << sz << std::endl;
		#endif
	}


};

/**
    @brief Modifica gli elementi della coda, che soddisfano
	il predicato, tramite l'operatore dato.


	Funzione globale che data una coda Q, un predicato P, 
	e un operatore generico F, modifica con l'operatore 
	i valori contenuti nella coda che soddisfano il
	predicato.

	@param q Coda Queue (FIFO)
	@param pred Il predicato 
	@param f L'operatore generico

*/
template<typename T, typename P, typename F>
void transformif(Queue<T> &q, P pred, F f){
	if( q.size() != 0 ){
		typename Queue<T>::iterator i, ie;

		i = q.begin();
		ie = q.end();

		while(i != ie){

			if( pred( *i ) ){
				*i = f( *i );
			}
			i++;
		}

		if( pred( *i ) ){
			*i = f( *i );
		}

	}
	else{
		#ifdef DEBUGGING
		std::cout << "Empty Queue" << std::endl;
		#endif //DEBUGGING
	}
}

#endif //QUEUE_H