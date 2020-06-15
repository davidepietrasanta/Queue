#include "Queue.h"
#include <iostream>
#include <cassert>
#include <string>

//#define DEBUGGING

/**
	@file main.cpp
	@brief File di testing per la classe templata Queue
*/


/**
	Funtore custom per testare transformif.
	funct(A) = true, se A pari
	funct(A) = false, se A dispari

	@brief Pari
	@param T Tipo del dato template
*/
template <typename T>
struct pari{
	bool operator()(T a) const {
		return (a % 2 == 0);	
	}
};


/**
	Funtore custom per testare transformif.
	funct(A) ritorna A*2

	@brief Operatore custom
	@param T Tipo del dato template
*/
template <typename T>
struct operatore_custom{
	T operator()(T a) {
		return a * 2;	
	}
};


/**
	Classe custom per il test della classe
	Queue.

	@brief Classe custom
*/
class Classe_custom{
    
private:
    int numero;
	char lettera;
public:
	Classe_custom() {
		this->numero = 0;
		this->lettera = 'a';
	}
    
	Classe_custom(int n, char l) {
		this->numero = n;
		this->lettera = l;
	}

	Classe_custom(const Classe_custom &other){
		this->numero = other.numero;
		this->lettera = other.lettera;
	}

	Classe_custom& operator=(const Classe_custom &other){
		this->numero = other.numero;
		this->lettera = other.lettera;

		return *this;
	}
    
	~Classe_custom() {}

	int get_numero() const{
		return numero;
	}

	char get_lettera() const{
		return lettera;
	}

	bool operator==(const Classe_custom& other) const {
		bool n = ( numero == other.get_numero() );
		bool l = ( lettera == other.get_lettera() );
		return ( l && n ) ;
	}

	bool operator!=(const Classe_custom& other) const {
		bool n = ( numero == other.get_numero() );
		bool l = ( lettera == other.get_lettera() );
		return !( l && n ) ;
	}

	bool operator>(const Classe_custom& other) const {
		if( numero > other.get_numero() ){
			return true;
		}

		if( numero == other.get_numero() && 
			lettera > other.get_lettera() ){
			return true;
		}
		return false;
	}

	bool operator<(const Classe_custom& other) const {
		if( numero < other.get_numero() ){
			return true;
		}

		if( numero == other.get_numero() && 
			lettera < other.get_lettera() ){
			return true;
		}
		return false;
	}
    
};


/**
    @brief Ridefinizione operatore <<


	Ridefinizione operatore <<.
	Permette dunque la stampa tramite std::ostream.

	@param out std::ostream scelto 
	@param t Un oggetto Classe_custom
*/
std::ostream & operator<< (std::ostream &out, const Classe_custom& t) {
	out << "(";
	out << t.get_numero();
	out << ",";
	out << t.get_lettera();
	out << ")";
	return out;
}


void test_costruttori(){
	std::cout << "TEST COSTRUTTORI" << std::endl;
	//test costruttori
	//test getter e setter
	//test my_uninitialized_value 
	//test a BIT of push/pop 

	//test Queue()
	Queue<int> q0;

	assert( q0.size() == 0 );

	//test my_uninitialized_value
	bool unizialied_older = false;
	try{
		q0.get_older(); 
	}
	catch(my_uninitialized_value e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		unizialied_older = true;
	}
	assert ( unizialied_older );

	//test my_uninitialized_value
	bool unizialied_younger = false;
	try{
		q0.get_younger(); 
	}
	catch(my_uninitialized_value e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		unizialied_younger = true;
	}
	assert ( unizialied_younger );

	//test my_uninitialized_value
	bool unizialied_set_younger = false;
	try{
		q0.set_younger(5); 
	}
	catch(my_uninitialized_value e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		unizialied_set_younger = true;
	}
	assert ( unizialied_set_younger );

	//test my_uninitialized_value
	bool unizialied_set_older= false;
	try{
		q0.set_older(5); 
	}
	catch(my_uninitialized_value e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		unizialied_set_older = true;
	}
	assert ( unizialied_set_older );


	//test Queue(const T &v)
	Queue<int> q1(10);
	assert( q1.size() == 1 );
	assert( q1.get_older() == 10 );
	assert( q1.get_younger() == 10 );
	q1.set_older(6);
	assert( q1.size() == 1 );
	assert( q1.get_older() == 6 );
	assert( q1.get_younger() == 6 );
	q1.set_younger(8);
	assert( q1.size() == 1 );
	assert( q1.get_older() == 8 );
	assert( q1.get_younger() == 8 );
	q1.set_older(8);
	assert( q1.size() == 1 );
	assert( q1.get_older() == 8 );
	assert( q1.get_younger() == 8 );

	//test Queue(const Queue<T> &other)
	Queue<int> q2(q1); // other.size() == 1
	assert( q2.size() == 1 );
	assert( q2.get_older() == 8 );
	assert( q2.get_younger() == 8 );
	assert( q1.size() == 1 );
	assert( q1.get_older() == 8 );
	assert( q1.get_younger() == 8 );

	q2.set_younger(15);
	assert( q2.size() == 1 );
	assert( q2.get_younger() == 15 );
	assert( q2.get_older() == 15 );
	assert( q1.size() == 1 );
	assert( q1.get_younger() == 8 );
	assert( q1.get_older() == 8 );

	q1.set_younger(3);
	assert( q2.size() == 1 );
	assert( q2.get_younger() == 15 );
	assert( q2.get_older() == 15 );
	assert( q1.size() == 1 );
	assert( q1.get_younger() == 3 );
	assert( q1.get_older() == 3 );

	Queue<int> q3(q0); //other.size() == 0
	assert( q3.size() == 0 );
	assert( q0.size() == 0 );

	//test my_uninitialized_value
	unizialied_older = false;
	try{
		q3.get_older(); 
	}
	catch(my_uninitialized_value e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		unizialied_older = true;
	}
	assert ( unizialied_older );

	//test my_uninitialized_value
	unizialied_younger = false;
	try{
		q3.get_younger(); 
	}
	catch(my_uninitialized_value e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		unizialied_younger = true;
	}
	assert ( unizialied_younger );

	//test my_uninitialized_value
	unizialied_set_younger = false;
	try{
		q3.set_younger(5); 
	}
	catch(my_uninitialized_value e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		unizialied_set_younger = true;
	}
	assert ( unizialied_set_younger );

	//test my_uninitialized_value
	unizialied_set_older= false;
	try{
		q3.set_older(5); 
	}
	catch(my_uninitialized_value e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		unizialied_set_older = true;
	}
	assert ( unizialied_set_older );

	//test my_uninitialized_value
	unizialied_older = false;
	try{
		q0.get_older(); 
	}
	catch(my_uninitialized_value e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		unizialied_older = true;
	}
	assert ( unizialied_older );

	//test my_uninitialized_value
	unizialied_younger = false;
	try{
		q0.get_younger(); 
	}
	catch(my_uninitialized_value e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		unizialied_younger = true;
	}
	assert ( unizialied_younger );

	//test my_uninitialized_value
	unizialied_set_younger = false;
	try{
		q0.set_younger(5); 
	}
	catch(my_uninitialized_value e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		unizialied_set_younger = true;
	}
	assert ( unizialied_set_younger );

	//test my_uninitialized_value
	unizialied_set_older= false;
	try{
		q0.set_older(5); 
	}
	catch(my_uninitialized_value e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		unizialied_set_older = true;
	}
	assert ( unizialied_set_older );

	//other.size() > 1
	Queue<int> q4(1);
	assert( q4.size() == 1);
	assert( q4.get_older() == 1);
	assert( q4.get_younger() == 1);
	q4.push(2);
	assert( q4.size() == 2);
	assert( q4.get_older() == 1);
	assert( q4.get_younger() == 2);
	q4.push(3);
	assert( q4.size() == 3);
	assert( q4.get_older() == 1);
	assert( q4.get_younger() == 3);
	q4.push(4);
	assert( q4.size() == 4);
	assert( q4.get_older() == 1);
	assert( q4.get_younger() == 4);

	Queue<int> q5(q4); //test Queue(&other) with other.size() > 1
	assert( q5.size() == 4);
	assert( q5.get_older() == 1);
	assert( q5.get_younger() == 4);
	assert( q4.size() == 4);
	assert( q4.get_older() == 1);
	assert( q4.get_younger() == 4);
	q5.set_older(9);
	assert( q5.size() == 4);
	assert( q5.get_older() == 9);
	assert( q5.get_younger() == 4);
	assert( q4.size() == 4);
	assert( q4.get_older() == 1);
	assert( q4.get_younger() == 4);
	q4.set_younger(6);
	assert( q5.size() == 4);
	assert( q5.get_older() == 9);
	assert( q5.get_younger() == 4);
	assert( q4.size() == 4);
	assert( q4.get_older() == 1);
	assert( q4.get_younger() == 6);
	q5.set_younger(-20);
	assert( q5.size() == 4);
	assert( q5.get_older() == 9);
	assert( q5.get_younger() == -20);
	assert( q4.size() == 4);
	assert( q4.get_older() == 1);
	assert( q4.get_younger() == 6);
	

}


void test_push_pop(){
	std::cout << "TEST PUSH & POP" << std::endl;
	//test push and pop
	//test setter and getter
	//test my_uninitialized_value 
	//test bad_pop_exception

	//test Queue()
	Queue<int> q0;
	assert( q0.size() == 0 );

	bool pop_error = false;
	try{
		q0.pop(); 
	}
	catch(bad_pop_exception e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		pop_error = true;
	}
	assert ( pop_error );

	q0.push(5);
	assert( q0.size() == 1 );
	assert( q0.get_older() == 5 );
	assert( q0.get_younger() == 5 ); 
	q0.push(700056);
	assert( q0.size() == 2 );
	assert( q0.get_older() == 5 );
	assert( q0.get_younger() == 700056 );
	q0.set_younger(6);
	assert( q0.size() == 2 );
	assert( q0.get_older() == 5 );
	assert( q0.get_younger() == 6 ); 
	q0.push(3);
	assert( q0.size() == 3 );
	assert( q0.get_older() == 5 );
	assert( q0.get_younger() == 3 );
	q0.pop();
	assert( q0.size() == 2 );
	assert( q0.get_older() == 6 );
	assert( q0.get_younger() == 3 );
	q0.set_older(8);
	assert( q0.size() == 2 );
	assert( q0.get_older() == 8 );
	assert( q0.get_younger() == 3 );; 
	q0.pop();
	assert( q0.size() == 1 );
	assert( q0.get_older() == 3 );
	assert( q0.get_younger() == 3 );
	q0.pop();
	assert( q0.size() == 0 );
	
	//test my_uninitialized_value
	bool unizialied_older = false;
	try{
		q0.get_older(); 
	}
	catch(my_uninitialized_value e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		unizialied_older = true;
	}
	assert ( unizialied_older );

	//test my_uninitialized_value
	bool unizialied_younger = false;
	try{
		q0.get_younger(); 
	}
	catch(my_uninitialized_value e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		unizialied_younger = true;
	}
	assert ( unizialied_younger );

	//test my_uninitialized_value
	bool unizialied_set_younger = false;
	try{
		q0.set_younger(5); 
	}
	catch(my_uninitialized_value e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		unizialied_set_younger = true;
	}
	assert ( unizialied_set_younger );

	//test my_uninitialized_value
	bool unizialied_set_older= false;
	try{
		q0.set_older(5); 
	}
	catch(my_uninitialized_value e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		unizialied_set_older = true;
	}
	assert ( unizialied_set_older );

	bool pop_error_2 = false;
	try{
		q0.pop(); 
	}
	catch(bad_pop_exception e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		pop_error_2 = true;
	}
	assert ( pop_error_2 );


	//test Queue(const T &v)
	Queue<int> q1(10);
	assert( q1.size() == 1 );
	assert( q1.get_older() == 10 );
	assert( q1.get_younger() == 10 ); 
	q1.push(5);
	assert( q1.size() == 2 );
	assert( q1.get_older() == 10 );
	assert( q1.get_younger() == 5 ); 
	q1.push(7);
	assert( q1.size() == 3 );
	assert( q1.get_older() == 10 );
	assert( q1.get_younger() == 7 );  
	q1.push(3);
	assert( q1.size() == 4 );
	assert( q1.get_older() == 10 );
	assert( q1.get_younger() == 3 );

	q1.set_older(8);
	assert( q1.size() == 4 );
	assert( q1.get_older() == 8 );
	assert( q1.get_younger() == 3 );
	q1.set_younger(-1);
	assert( q1.size() == 4 );
	assert( q1.get_older() == 8 );
	assert( q1.get_younger() == -1 );

	//Test size
	assert( q1.size() == 4 );
	unsigned int size_copia = q1.size();
	assert( size_copia == 4 );
	size_copia = 10;
	assert( size_copia == 10 );
	assert( q1.size() == 4 );


	q1.pop();
	assert( q1.size() == 3 );
	assert( q1.get_older() == 5 );
	assert( q1.get_younger() == -1 );
	q1.pop();
	assert( q1.size() == 2 );
	assert( q1.get_older() == 7 );
	assert( q1.get_younger() == -1 );
	q1.pop();
	assert( q1.size() == 1 );
	assert( q1.get_older() == -1 );
	assert( q1.get_younger() == -1 );
	q1.pop();
	assert( q1.size() == 0 );

	//test my_uninitialized_value
	unizialied_older = false;
	try{
		q1.get_older(); 
	}
	catch(my_uninitialized_value e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		unizialied_older = true;
	}
	assert ( unizialied_older );

	//test my_uninitialized_value
	unizialied_younger = false;
	try{
		q1.get_younger(); 
	}
	catch(my_uninitialized_value e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		unizialied_younger = true;
	}
	assert ( unizialied_younger );

	//test my_uninitialized_value
	unizialied_set_younger = false;
	try{
		q1.set_younger(5); 
	}
	catch(my_uninitialized_value e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		unizialied_set_younger = true;
	}
	assert ( unizialied_set_younger );

	//test my_uninitialized_value
	unizialied_set_older= false;
	try{
		q1.set_older(5); 
	}
	catch(my_uninitialized_value e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		unizialied_set_older = true;
	}
	assert ( unizialied_set_older );

	pop_error = false;
	try{
		q1.pop(); 
	}
	catch(bad_pop_exception e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		pop_error = true;
	}
	assert ( pop_error );

	q1.push(8);
	assert( q1.size() == 1 );
	assert( q1.get_older() == 8 );
	assert( q1.get_younger() == 8 );
	q1.set_older(0);
	assert( q1.size() == 1 );
	assert( q1.get_older() == 0 );
	assert( q1.get_younger() == 0 );
	q1.set_younger(8);
	assert( q1.size() == 1 );
	assert( q1.get_older() == 8 );
	assert( q1.get_younger() == 8 );

	//test Queue(const Queue<T> &other)
	Queue<int> q2(q1);
	assert( q2.size() == 1 );
	assert( q2.get_older() == 8 );
	assert( q2.get_younger() == 8 );

	q2.set_younger(15);
	assert( q2.size() == 1 );
	assert( q2.get_younger() == 15 );
	assert( q2.get_older() == 15 );
	assert( q1.size() == 1 );
	assert( q1.get_younger() == 8 );
	assert( q1.get_older() == 8 );

	q2.push(-10);
	assert( q2.size() == 2 );
	assert( q2.get_younger() == -10 );
	assert( q2.get_older() == 15 );
	assert( q1.size() == 1 );
	assert( q1.get_younger() == 8 );
	assert( q1.get_older() == 8 );

	q2.push(4000);
	assert( q2.size() == 3 );
	assert( q2.get_younger() == 4000 );
	assert( q2.get_older() == 15 );
	assert( q1.size() == 1 );
	assert( q1.get_younger() == 8 );
	assert( q1.get_older() == 8 );

	Queue<int> q3(q2);
	assert( q3.size() == 3 );
	assert( q3.get_younger() == 4000 );
	assert( q3.get_older() == 15 );
	assert( q2.size() == 3 );
	assert( q2.get_younger() == 4000 );
	assert( q2.get_older() == 15 );
	assert( q1.size() == 1 );
	assert( q1.get_younger() == 8 );
	assert( q1.get_older() == 8 );

	q2.pop();
	assert( q3.size() == 3 );
	assert( q3.get_younger() == 4000 );
	assert( q3.get_older() == 15 );
	assert( q2.size() == 2 );
	assert( q2.get_younger() == 4000 );
	assert( q2.get_older() == -10 );
	assert( q1.size() == 1 );
	assert( q1.get_younger() == 8 );
	assert( q1.get_older() == 8 );

	q3.pop();
	assert( q3.size() == 2 );
	assert( q3.get_younger() == 4000 );
	assert( q3.get_older() == -10 );
	assert( q2.size() == 2 );
	assert( q2.get_younger() == 4000 );
	int y_copia = q2.get_younger();
	assert( q2.get_younger() == 4000 );
	assert( y_copia == 4000 );
	y_copia++;
	assert( q2.get_younger() == 4000 );
	assert( y_copia == 4001 );
	


	assert( q2.get_older() == -10 );
	assert( q1.size() == 1 );
	assert( q1.get_younger() == 8 );
	assert( q1.get_older() == 8 );

	q3.pop();
	assert( q3.size() == 1 );
	assert( q3.get_younger() == 4000 );
	assert( q3.get_older() == 4000 );
	assert( q2.size() == 2 );
	assert( q2.get_younger() == 4000 );
	assert( q2.get_older() == -10 );
	assert( q1.size() == 1 );
	assert( q1.get_younger() == 8 );
	assert( q1.get_older() == 8 );

	q3.pop();
	assert( q3.size() == 0 );
	assert( q2.size() == 2 );
	assert( q2.get_younger() == 4000 );
	assert( q2.get_older() == -10 );
	assert( q1.size() == 1 );
	assert( q1.get_younger() == 8 );
	assert( q1.get_older() == 8 );

	//test my_uninitialized_value
	unizialied_older = false;
	try{
		q3.get_older(); 
	}
	catch(my_uninitialized_value e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		unizialied_older = true;
	}
	assert ( unizialied_older );

	//test my_uninitialized_value
	unizialied_younger = false;
	try{
		q3.get_younger(); 
	}
	catch(my_uninitialized_value e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		unizialied_younger = true;
	}
	assert ( unizialied_younger );

	//test my_uninitialized_value
	unizialied_set_younger = false;
	try{
		q3.set_younger(5); 
	}
	catch(my_uninitialized_value e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		unizialied_set_younger = true;
	}
	assert ( unizialied_set_younger );

	//test my_uninitialized_value
	unizialied_set_older= false;
	try{
		q3.set_older(5); 
	}
	catch(my_uninitialized_value e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		unizialied_set_older = true;
	}
	assert ( unizialied_set_older );

	pop_error = false;
	try{
		q3.pop(); 
	}
	catch(bad_pop_exception e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		pop_error = true;
	}
	assert ( pop_error );

	q3.push(-1000);
	assert( q3.size() == 1 );
	assert( q3.get_younger() == -1000 );
	assert( q3.get_older() == -1000 );
	assert( q2.size() == 2 );
	assert( q2.get_younger() == 4000 );
	assert( q2.get_older() == -10 );
	assert( q1.size() == 1 );
	assert( q1.get_younger() == 8 );
	assert( q1.get_older() == 8 );

}


void test_operatore_assegnamento(){

	std::cout << "TEST ASSEGNAMENTO" << std::endl;
	//test operatore assegnamento operator=
	//test iterator
	//test const_iterator
	//test push_iterator

	Queue<int> q0;
	q0.push(10);
	q0.push(20);
	q0.push(30);
	assert( q0.size() == 3 );

	Queue<int> q1;
	q1.push(66);
	q1.push(99);
	q1.push(0);
	q1.push(11);
	assert( q1.size() == 4 );

	q1 = q0; // some = some
	assert( q1.size() == 3 );
	assert( q0.size() == 3 );
	assert( q1.get_older() == 10 );
	assert( q1.get_younger() == 30 );

	q1.set_older(15);
	q0.set_younger(20);
	assert( q1.size() == 3 );
	assert( q1.get_older() == 15 );
	assert( q1.get_younger() == 30 );
	assert( q0.size() == 3 );
	assert( q0.get_older() == 10 );
	assert( q0.get_younger() == 20 );


	Queue<int> q2;
	assert( q2.size() == 0 );
	assert( q1.size() == 3 );
	assert( q1.get_older() == 15 );
	assert( q1.get_younger() == 30 );
	q2 = q1; // empty = some 
	assert( q2.size() == 3 );
	assert( q2.get_older() == 15 );
	assert( q2.get_younger() == 30 );
	assert( q0.size() == 3 );
	assert( q0.get_older() == 10 );
	assert( q0.get_younger() == 20 );
	assert( q1.size() == 3 );
	assert( q1.get_older() == 15 );
	assert( q1.get_younger() == 30 );

	q2.pop();
	assert( q2.size() == 2 );
	assert( q2.get_older() == 20 );
	assert( q2.get_younger() == 30 );
	q2.push(-10);
	assert( q2.size() == 3 );
	assert( q2.get_older() == 20 );
	assert( q2.get_younger() == -10 );
	q2.push(0);
	assert( q2.size() == 4 );
	assert( q2.get_older() == 20 );
	assert( q2.get_younger() == 0 );

	Queue<int> q3(20000);
	assert( q3.size() == 1 );
	assert( q3.get_older() == 20000 );
	assert( q3.get_younger() == 20000 );
	q3.set_older(20);
	assert( q3.size() == 1 );
	assert( q3.get_older() == 20 );
	assert( q3.get_younger() == 20 );
	q3.set_younger(200);
	assert( q3.size() == 1 );
	assert( q3.get_older() == 200 );
	assert( q3.get_younger() == 200 );

	q3 = q2; // one = some
	assert( q3.size() == 4 );
	assert( q3.get_older() == 20 );
	assert( q3.get_younger() == 0 );
	assert( q2.size() == 4 );
	assert( q2.get_older() == 20 );
	assert( q2.get_younger() == 0 );

	q3.pop();
	assert( q3.size() == 3 );
	assert( q3.get_older() == 30 );
	assert( q3.get_younger() == 0 );
	assert( q2.size() == 4 );
	assert( q2.get_older() == 20 );
	assert( q2.get_younger() == 0 );

	
	Queue<int> q_empty;
	assert( q_empty.size() == 0 );

	Queue<int> q4(20);
	q4.push(66);
	q4.push(-99);
	q4.push(0);
	assert( q4.size() == 4 );
	assert( q4.get_older() == 20 );
	assert( q4.get_younger() == 0 );

	q4 = q_empty; // some = empty

	assert( q_empty.size() == 0 );
	assert( q4.size() == 0 );

	q4.push(888);
	assert( q_empty.size() == 0 );
	assert( q4.size() == 1 );
	assert( q4.get_older() == 888 );
	assert( q4.get_younger() == 888 );

	Queue<int> q_empty_2;
	assert( q_empty.size() == 0 );
	assert( q_empty_2.size() == 0 );

	q_empty_2 = q_empty; // empty = empty
	assert( q_empty.size() == 0 );
	assert( q_empty_2.size() == 0 );

	q_empty_2.push(99999);
	assert( q_empty.size() == 0 );
	assert( q_empty_2.size() == 1 );
	assert( q_empty_2.get_older() == 99999 );
	assert( q_empty_2.get_younger() == 99999 );
	q_empty_2.pop();
	assert( q_empty.size() == 0 );
	assert( q_empty_2.size() == 0 );

	Queue<int> q5(4);
	assert( q5.size() == 1 );
	assert( q5.get_older() == 4 );
	assert( q5.get_younger() == 4 );
	assert( q_empty_2.size() == 0 );
	q_empty_2 = q5; // empty = one
	assert( q5.size() == 1 );
	assert( q5.get_older() == 4 );
	assert( q5.get_younger() == 4 );
	assert( q_empty_2.size() == 1 );
	assert( q_empty_2.get_older() == 4 );
	assert( q_empty_2.get_younger() == 4 );

	Queue<int> q6(q0);
	assert( q6.size() == 3 );
	assert( q6.get_older() == 10 );
	assert( q6.get_younger() == 20 );
	assert( q0.size() == 3 );
	assert( q0.get_older() == 10 );
	assert( q0.get_younger() == 20 );

	
	Queue<int>::iterator i,ie;
	i = q1.begin();
	ie = q1.end();
	q6.push(i, ie);
	assert( q6.size() == 6 );
	assert( q6.get_older() == 10 );
	assert( q6.get_younger() == 30 );
	assert( q0.size() == 3 );
	assert( q0.get_older() == 10 );
	assert( q0.get_younger() == 20 );
	assert( q1.size() == 3 );
	assert( q1.get_older() == 15 );
	assert( q1.get_younger() == 30 );
	
	Queue<int> q7(19);
	assert( q7.size() == 1 );
	assert( q7.get_older() == 19 );
	assert( q7.get_younger() == 19 );

	Queue<int> q6_c;
	Queue<int>::const_iterator i_c, ie_c;
	i_c = q6.begin();
	ie_c = q6.end();
	q6_c.push(i_c, ie_c );

	assert( q6.size() == 6 );
	assert( q6.get_older() == 10 );
	assert( q6.get_younger() == 30 );
	assert( q6_c.size() == 6 );
	assert( q6_c.get_older() == 10 );
	assert( q6_c.get_younger() == 30 );

	Queue<int> q6_c_copia;
	assert( q6_c_copia.size() == 0 );
	assert( q6.size() == 6 );
	assert( q6.get_older() == 10 );
	assert( q6.get_younger() == 30 );
	assert( q6_c.size() == 6 );
	assert( q6_c.get_older() == 10 );
	assert( q6_c.get_younger() == 30 );

	q6_c_copia = q6_c; // empty = const_iterator_push
	assert( q6.size() == 6 );
	assert( q6.get_older() == 10 );
	assert( q6.get_younger() == 30 );
	assert( q6_c.size() == 6 );
	assert( q6_c.get_older() == 10 );
	assert( q6_c.get_younger() == 30 );
	assert( q6_c_copia.size() == 6 );
	assert( q6_c_copia.get_older() == 10 );
	assert( q6_c_copia.get_younger() == 30 );

	q6_c_copia.set_younger(3333);
	q6_c.set_older(111);
	assert( q6.size() == 6 );
	assert( q6.get_older() == 10 );
	assert( q6.get_younger() == 30 );
	assert( q6_c.size() == 6 );
	assert( q6_c.get_older() == 111 );
	assert( q6_c.get_younger() == 30 );
	assert( q6_c_copia.size() == 6 );
	assert( q6_c_copia.get_older() == 10 );
	assert( q6_c_copia.get_younger() == 3333 );

	q7 = q6; // some = iterator_push
	assert( q6.size() == 6 );
	assert( q6.get_older() == 10 );
	assert( q6.get_younger() == 30 );
	assert( q7.size() == 6 );
	assert( q7.get_older() == 10 );
	assert( q7.get_younger() == 30 );

	q7.set_older(21);
	q7.set_younger(11);
	assert( q6.size() == 6 );
	assert( q6.get_older() == 10 );
	assert( q6.get_younger() == 30 );
	assert( q7.size() == 6 );
	assert( q7.get_older() == 21 );
	assert( q7.get_younger() == 11 );

	Queue<int> q8(55);
	assert( q8.size() == 1 );
	assert( q8.get_older() == 55 );
	assert( q8.get_younger() == 55 );
	assert( q6.size() == 6 );
	assert( q6.get_older() == 10 );
	assert( q6.get_younger() == 30 );

	q6 = q8; // iterator_push = some
	assert( q6.size() == 1 );
	assert( q6.get_older() == 55 );
	assert( q6.get_younger() == 55 );
	q6.set_younger(11);
	assert( q6.size() == 1 );
	assert( q6.get_older() == 11 );
	assert( q6.get_younger() == 11 );


	assert( q0.size() == 3 );
	assert( q0.get_older() == 10 );
	assert( q0.get_younger() == 20 );

	assert( q1.size() == 3 );
	assert( q1.get_older() == 15 );
	assert( q1.get_younger() == 30 );

	assert( q2.size() == 4 );
	assert( q2.get_older() == 20 );
	assert( q2.get_younger() == 0 );

	assert( q3.size() == 3 );
	assert( q3.get_older() == 30 );
	assert( q3.get_younger() == 0 );

	assert( q4.size() == 1 );
	assert( q4.get_older() == 888 );
	assert( q4.get_younger() == 888 );

	assert( q5.size() == 1 );
	assert( q5.get_older() == 4 );
	assert( q5.get_younger() == 4 );
	
	assert( q6.size() == 1 );
	assert( q6.get_older() == 11 );
	assert( q6.get_younger() == 11 );

	assert( q7.size() == 6 );
	assert( q7.get_older() == 21 );
	assert( q7.get_younger() == 11 );

	assert( q8.size() == 1 );
	assert( q8.get_older() == 55 );
	assert( q8.get_younger() == 55 );
	
}


void test_contain(){

	std::cout << "TEST CONTAIN" << std::endl;
	//test contain
	//test assegnamento
	//test push/pop
	//test iterator_push
	//test const_iterator_push

	Queue<int> q0;
	q0.push(10);
	q0.push(20);
	q0.push(30);
	assert( q0.size() == 3 );
	assert( q0.contain(10) == true );
	assert( q0.contain(20) == true );
	assert( q0.contain(30) == true );
	assert( q0.contain(0) == false );
	assert( q0.contain(-10) == false );
	assert( q0.contain(1542) == false );
	q0.pop();
	q0.pop();
	q0.pop();
	assert( q0.size() == 0 );
	assert( q0.contain(10) == false );
	assert( q0.contain(20) == false );
	assert( q0.contain(30) == false );
	assert( q0.contain(0) == false );
	assert( q0.contain(-10) == false );
	assert( q0.contain(1542) == false );
	q0.push(2);
	assert( q0.size() == 1 );
	assert( q0.contain(2) == true );
	assert( q0.contain(10) == false );
	assert( q0.contain(20) == false );
	assert( q0.contain(30) == false );
	assert( q0.contain(0) == false );
	assert( q0.contain(-10) == false );
	assert( q0.contain(1542) == false );

	
	Queue<int> q1(11);	//q1(11)
	assert( q1.size() == 1 );
	assert( q1.get_older() == 11 );
	assert( q1.get_younger() == 11 );

	assert( q1.contain(11) == true );
	assert( q1.contain(10) == false );
	assert( q1.contain(20) == false );
	assert( q1.contain(30) == false );
	assert( q1.contain(0) == false );
	assert( q1.contain(-10) == false );
	assert( q1.contain(1542) == false );

	Queue<int> q2(q1);	//q2(q1)

	assert( q2.size() == 1 );
	assert( q2.get_older() == 11 );
	assert( q2.get_younger() == 11 );

	assert( q2.contain(11) == true );
	assert( q2.contain(10) == false );
	assert( q2.contain(20) == false );
	assert( q2.contain(30) == false );
	assert( q2.contain(0) == false );
	assert( q2.contain(-10) == false );
	assert( q2.contain(1542) == false );

	assert( q1.size() == 1 );
	assert( q1.get_older() == 11 );
	assert( q1.get_younger() == 11 );

	assert( q1.contain(11) == true );
	assert( q1.contain(10) == false );
	assert( q1.contain(20) == false );
	assert( q1.contain(30) == false );
	assert( q1.contain(0) == false );
	assert( q1.contain(-10) == false );
	assert( q1.contain(1542) == false );

	q2.push(22);
	assert( q2.size() == 2 );
	assert( q2.get_older() == 11 );
	assert( q2.get_younger() == 22 );

	assert( q2.contain(11) == true );
	assert( q2.contain(22) == true );
	assert( q2.contain(10) == false );
	assert( q2.contain(20) == false );
	assert( q2.contain(30) == false );
	assert( q2.contain(0) == false );
	assert( q2.contain(-10) == false );
	assert( q2.contain(1542) == false );
	
	Queue<int> q3; //empty q
	assert( q3.size() == 0 );
	assert( q3.contain(10) == false );
	assert( q3.contain(20) == false );
	assert( q3.contain(30) == false );
	assert( q3.contain(0) == false );
	assert( q3.contain(-10) == false );
	assert( q3.contain(1542) == false );

	Queue<int> q4(q3); //q4(q_empty)

	assert( q3.size() == 0 );
	q3.push(55);
	assert( q3.size() == 1 );
	assert( q3.get_older() == 55 );
	assert( q3.get_younger() == 55 );
	assert( q3.contain(55) == true );

	assert( q3.contain(10) == false );
	assert( q3.contain(20) == false );
	assert( q3.contain(30) == false );
	assert( q3.contain(0) == false );
	assert( q3.contain(-10) == false );
	assert( q3.contain(1542) == false );

	assert( q4.size() == 0 );
	assert( q4.contain(10) == false );
	assert( q4.contain(20) == false );
	assert( q4.contain(30) == false );
	assert( q4.contain(0) == false );
	assert( q4.contain(-10) == false );
	assert( q4.contain(1542) == false );
	assert( q4.contain(55) == false );


	Queue<int> q5; //q5 = q2
	q5 = q2;

	assert( q2.size() == 2 );
	assert( q2.get_older() == 11 );
	assert( q2.get_younger() == 22 );

	assert( q2.contain(11) == true );
	assert( q2.contain(22) == true );
	assert( q2.contain(10) == false );
	assert( q2.contain(20) == false );
	assert( q2.contain(30) == false );
	assert( q2.contain(0) == false );
	assert( q2.contain(-10) == false );
	assert( q2.contain(1542) == false );

	assert( q5.size() == 2 );
	assert( q5.get_older() == 11 );
	assert( q5.get_younger() == 22 );

	assert( q5.contain(11) == true );
	assert( q5.contain(22) == true );
	assert( q5.contain(10) == false );
	assert( q5.contain(20) == false );
	assert( q5.contain(30) == false );
	assert( q5.contain(0) == false );
	assert( q5.contain(-10) == false );
	assert( q5.contain(1542) == false );

	Queue<int> q6;
	Queue<int>::iterator i,ie;
	i = q5.begin();
	ie = q5.end();
	assert( q6.size() == 0 );
	assert( q5.size() == 2 );
	assert( q5.get_older() == 11 );
	assert( q5.get_younger() == 22 );

	q6.push(i, ie); //iterator_push
	assert( q6.size() == 2 );
	assert( q6.get_older() == 11 );
	assert( q6.get_younger() == 22 );
	assert( q5.size() == 2 );
	assert( q5.get_older() == 11 );
	assert( q5.get_younger() == 22 );

	assert( q5.contain(11) == true );
	assert( q5.contain(22) == true );
	assert( q5.contain(10) == false );
	assert( q5.contain(20) == false );
	assert( q5.contain(30) == false );
	assert( q5.contain(0) == false );
	assert( q5.contain(-10) == false );
	assert( q5.contain(1542) == false );

	assert( q6.contain(11) == true );
	assert( q6.contain(22) == true );
	assert( q6.contain(10) == false );
	assert( q6.contain(20) == false );
	assert( q6.contain(30) == false );
	assert( q6.contain(0) == false );
	assert( q6.contain(-10) == false );
	assert( q6.contain(1542) == false );

	q6.set_younger(33);
	q5.set_older(101);

	assert( q6.size() == 2 );
	assert( q6.get_older() == 11 );
	assert( q6.get_younger() == 33 );
	assert( q5.size() == 2 );
	assert( q5.get_older() == 101 );
	assert( q5.get_younger() == 22 );

	assert( q5.contain(11) == false );
	assert( q5.contain(22) == true );
	assert( q5.contain(10) == false );
	assert( q5.contain(20) == false );
	assert( q5.contain(30) == false );
	assert( q5.contain(0) == false );
	assert( q5.contain(-10) == false );
	assert( q5.contain(1542) == false );
	assert( q5.contain(101) == true );

	assert( q6.contain(11) == true );
	assert( q6.contain(22) == false );
	assert( q6.contain(10) == false );
	assert( q6.contain(20) == false );
	assert( q6.contain(30) == false );
	assert( q6.contain(0) == false );
	assert( q6.contain(-10) == false );
	assert( q6.contain(1542) == false );
	assert( q6.contain(33) == true );

	Queue<int> q7;
	Queue<int>::const_iterator i_c,ie_c;
	i_c = q5.begin();
	ie_c = q5.end();

	assert( q7.size() == 0 );
	assert( q5.size() == 2 );
	assert( q5.get_older() == 101 );
	assert( q5.get_younger() == 22 );
	q7.push(i_c, ie_c); //const_iterator_push

	assert( q7.size() == 2 );
	assert( q7.get_older() == 101 );
	assert( q7.get_younger() == 22 );
	assert( q5.size() == 2 );
	assert( q5.get_older() == 101 );
	assert( q5.get_younger() == 22 );

	assert( q7.contain(101) == true );
	assert( q7.contain(22) == true );
	assert( q7.contain(11) == false );
	assert( q7.contain(20) == false );
	assert( q7.contain(30) == false );
	assert( q7.contain(0) == false );
	assert( q7.contain(-10) == false );
	assert( q7.contain(1542) == false );

	assert( q5.contain(101) == true );
	assert( q5.contain(22) == true );
	assert( q5.contain(11) == false );
	assert( q5.contain(20) == false );
	assert( q5.contain(30) == false );
	assert( q5.contain(0) == false );
	assert( q5.contain(-10) == false );
	assert( q5.contain(1542) == false );


	q7.set_younger(30);
	q5.set_older(11);

	assert( q7.size() == 2 );
	assert( q7.get_older() == 101 );
	assert( q7.get_younger() == 30 );
	assert( q5.size() == 2 );
	assert( q5.get_older() == 11 );
	assert( q5.get_younger() == 22 );

	assert( q7.contain(101) == true );
	assert( q7.contain(22) == false );
	assert( q7.contain(11) == false );
	assert( q7.contain(20) == false );
	assert( q7.contain(30) == true );
	assert( q7.contain(0) == false );
	assert( q7.contain(-10) == false );
	assert( q7.contain(1542) == false );

	assert( q5.contain(101) == false );
	assert( q5.contain(22) == true );
	assert( q5.contain(11) == true );
	assert( q5.contain(20) == false );
	assert( q5.contain(30) == false );
	assert( q5.contain(0) == false );
	assert( q5.contain(-10) == false );
	assert( q5.contain(1542) == false );


}


void test_iterator(){
	std::cout << "TEST ITERATOR" << std::endl;
	//test iterator
	//test out_of_range_iterator

	Queue<int> r1(4);
	r1.push(3);
	r1.push(5);
	r1.push(8);
	r1.push(-4);
	assert( r1.size() == 5 ); 
	assert( r1.get_older() == 4 );
	assert( r1.get_younger() == -4 );

	Queue<int>::iterator i,ie; //test iterator()
	i = r1.begin();
	ie = r1.end();
	assert( *i == 4 ); //test operator*()
	assert( *ie == -4 ); //test operator*()
	assert( r1.size() == 5 ); 
	assert( r1.get_older() == 4 );
	assert( r1.get_younger() == -4 );
	*i = 999;
	*ie = 123;
	assert( r1.size() == 5 ); 
	assert( r1.get_older() == 999 );
	assert( r1.get_younger() == 123 );

	Queue<int>::iterator i1(i); //test iterator(const iterator &other)
	assert( *i == 999 ); 
	assert( *i1 == 999 );
	assert ( i == i1 ); //test operator==
	assert ( ie != i1 ); //test operator!=

	i1 = ie; //test operator=
	assert( *ie == 123 ); 
	assert( *i1 == 123 );
	assert ( ie == i1 );
	assert ( i != i1 );

	i++; //test operator++(int) 
	assert( *i == 3 );
	i++; 
	assert( *i == 5 );
	++i; //test operator++()
	assert( *i == 8 );
	i++; 
	assert( *i == 123 );

	//test out_of_range_iterator
	bool error_iterator_post = false;
	try{
		i++;
	}
	catch(out_of_range_iterator e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		error_iterator_post = true;
	}
	assert ( error_iterator_post );

	//test out_of_range_iterator
	bool error_iterator_pre = false;
	try{
		++i;
	}
	catch(out_of_range_iterator e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		error_iterator_pre = true;
	}
	assert ( error_iterator_pre );

	//test out_of_range_iterator
	error_iterator_post = false;
	try{
		ie++;
	}
	catch(out_of_range_iterator e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		error_iterator_post = true;
	}
	assert ( error_iterator_post );

	//test out_of_range_iterator
	error_iterator_pre = false;
	try{
		++ie;
	}
	catch(out_of_range_iterator e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		error_iterator_pre = true;
	}
	assert ( error_iterator_pre );


	Queue<int> bt(10);
	bt.push(5);
	bt.push(4);
	bt.push(14);
	bt.push(44);
	bt.push(-3);
	bt.push(6);
	bt.push(2);
	assert( bt.size() == 8 );

	Queue<int>::iterator in, ien;

	in = bt.begin();
	ien = bt.end();

	int contatore_while = 0;
	while(in != ien){

		switch(contatore_while){ //test operator*()
			case 0 : assert( *in == 10 ); break;
			case 1 : assert( *in == 5 ); break;
			case 2 : assert( *in == 4 ); break;
			case 3 : assert( *in == 14 ); break;
			case 4 : assert( *in == 44 ); break;
			case 5 : assert( *in == -3 ); break;
			case 6 : assert( *in == 6 ); break;
			default : assert( false );
		}
		contatore_while++;
		in++ ; // testato anche i++
	}
	assert( *in == 2 );


	Queue<int> q0;
	q0.push(5);
	q0.push(4);
	q0.push(14);
	q0.push(20);
	assert( q0.size() == 4 );

	Queue<int>::iterator i0, ie0;

	i0 = q0.begin();
	ie0 = q0.end();

	contatore_while = 0;
	while(i0 != ie0){

		switch(contatore_while){ //test operator*()
			case 0 : assert( *i0 == 5 ); break;
			case 1 : assert( *i0 == 4 ); break;
			case 2 : assert( *i0 == 14 ); break;
			default : assert( false );
		}
		contatore_while++;
		i0++ ; // testato anche i++
	}
	assert( *i0 == 20 );

	q0.push(98);
	i0++;
	assert( *i0 == 98 );
	assert( *ie0 = 20 );

	i0 = q0.begin();
	ie0 = q0.end();

	assert( *i0 == 5 );
	assert( *ie0 == 98 );

	q0.pop();
	i0 = q0.begin();
	assert( *i0 == 4 );
	assert( *ie0 == 98 );

	
	Queue<int> same;
	same.push(1);
	same.push(1);

	Queue<int>::iterator i_same, ie_same;

	i_same = same.begin();
	ie_same = same.end();

	assert( i_same != ie_same );
	assert( *i_same == *ie_same ); 

	i_same++;

	assert( i_same == ie_same );
	assert( *i_same == *ie_same ); 


	Queue<int> empty;

	Queue<int>::iterator i_empty, ie_empty;
	i_empty = empty.begin();
	ie_empty = empty.end();


	//test my_uninitialized_value
	bool error_iterator_null = false;
	try{
		*i_empty;
	}
	catch(my_uninitialized_value e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		error_iterator_null = true;
	}
	assert ( error_iterator_null );

	//test my_uninitialized_value
	error_iterator_null = false;
	try{
		*ie_empty;
	}
	catch(my_uninitialized_value e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		error_iterator_null = true;
	}
	assert ( error_iterator_null );


	Queue<int>::iterator i2;
	
	i2 = i_empty;
	assert( i2 == i_empty );
	
}


void test_const_iterator(){
	std::cout << "TEST CONST_ITERATOR" << std::endl;
	//test const_iterator
	//test out_of_range_iterator
	//test const_iterator with iterator

	Queue<int> r1(4);
	r1.push(3);
	r1.push(5);
	r1.push(8);
	r1.push(-4);
	assert( r1.size() == 5 ); 
	assert( r1.get_older() == 4 );
	assert( r1.get_younger() == -4 );

	Queue<int>::const_iterator i,ie; //test const_iterator()
	i = r1.begin();
	ie = r1.end();
	assert( *i == 4 ); //test operator*()
	assert( *ie == -4 ); //test operator*()
	assert( r1.size() == 5 ); 
	assert( r1.get_older() == 4 );
	assert( r1.get_younger() == -4 );

	Queue<int>::const_iterator i1(i); //test const_iterator(const const_iterator &other)
	assert( *i == 4 ); 
	assert( *i1 == 4 );
	assert ( i == i1 ); //test operator==
	assert ( ie != i1 ); //test operator!=

	i1 = ie;
	assert( *ie == -4 ); 
	assert( *i1 == -4 );
	assert ( ie == i1 );
	assert ( i != i1 );

	i++; //test operator++(int) 
	assert( *i == 3 );
	i++; 
	assert( *i == 5 );
	++i; //test operator++()
	assert( *i == 8 );
	i++; 
	assert( *i == -4 );

	//test out_of_range_iterator
	bool error_iterator_post = false;
	try{
		i++;
	}
	catch(out_of_range_iterator e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		error_iterator_post = true;
	}
	assert ( error_iterator_post );

	//test out_of_range_iterator
	bool error_iterator_pre = false;
	try{
		++i;
	}
	catch(out_of_range_iterator e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		error_iterator_pre = true;
	}
	assert ( error_iterator_pre );

	//test out_of_range_iterator
	error_iterator_post = false;
	try{
		ie++;
	}
	catch(out_of_range_iterator e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		error_iterator_post = true;
	}
	assert ( error_iterator_post );

	//test out_of_range_iterator
	error_iterator_pre = false;
	try{
		++ie;
	}
	catch(out_of_range_iterator e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		error_iterator_pre = true;
	}
	assert ( error_iterator_pre );



	Queue<int> bt(10);
	bt.push(5);
	bt.push(4);
	bt.push(14);
	bt.push(44);
	bt.push(-3);
	bt.push(6);
	bt.push(2);
	assert( bt.size() == 8 );

	Queue<int>::const_iterator in, ien;

	in = bt.begin();
	ien = bt.end();

	int contatore_while = 0;
	while(in != ien){

		switch(contatore_while){ //test operator*()
			case 0 : assert( *in == 10 ); break;
			case 1 : assert( *in == 5 ); break;
			case 2 : assert( *in == 4 ); break;
			case 3 : assert( *in == 14 ); break;
			case 4 : assert( *in == 44 ); break;
			case 5 : assert( *in == -3 ); break;
			case 6 : assert( *in == 6 ); break;
			default : assert( false );
		}
		contatore_while++;
		in++ ; // testato anche i++
	}
	assert( *in == 2 );


	Queue<int> q0;
	q0.push(5);
	q0.push(4);
	q0.push(14);
	q0.push(20);
	assert( q0.size() == 4 );

	Queue<int>::const_iterator i0, ie0;

	i0 = q0.begin();
	ie0 = q0.end();

	contatore_while = 0;
	while(i0 != ie0){

		switch(contatore_while){ //test operator*()
			case 0 : assert( *i0 == 5 ); break;
			case 1 : assert( *i0 == 4 ); break;
			case 2 : assert( *i0 == 14 ); break;
			default : assert( false );
		}
		contatore_while++;
		i0++ ; // testato anche i++
	}
	assert( *i0 == 20 );

	q0.push(98);
	i0++;
	assert( *i0 == 98 );
	assert( *ie0 == 20 );

	i0 = q0.begin();
	ie0 = q0.end();

	assert( *i0 == 5 );
	assert( *ie0 == 98 );

	q0.pop();
	i0 = q0.begin();
	assert( *i0 == 4 );
	assert( *ie0 == 98 );

	//If you try
	//*i0 = 44 or *i0 = anything
	//You will be blocked by: assignment of read-only location


	Queue<int> same;
	same.push(1);
	same.push(1);

	Queue<int>::const_iterator i_same, ie_same;

	i_same = same.begin();
	ie_same = same.end();

	assert( i_same != ie_same );
	assert( *i_same == *ie_same ); 

	i_same++;

	assert( i_same == ie_same );
	assert( *i_same == *ie_same ); 


	Queue<int> empty;

	Queue<int>::const_iterator i_empty, ie_empty;
	i_empty = empty.begin();
	ie_empty = empty.end();


	//test my_uninitialized_value
	bool error_const_iterator_null = false;
	try{
		*i_empty;
	}
	catch(my_uninitialized_value e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		error_const_iterator_null = true;
	}
	assert ( error_const_iterator_null );

	//test my_uninitialized_value
	error_const_iterator_null = false;
	try{
		*ie_empty;
	}
	catch(my_uninitialized_value e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		error_const_iterator_null = true;
	}
	assert ( error_const_iterator_null );


	Queue<int>::const_iterator i2;
	
	i2 = i_empty;
	assert( i2 == i_empty );



	Queue<int>::iterator i_bt, ie_bt;
	Queue<int>::const_iterator ic_bt, iec_bt;

	i_bt = bt.begin();
	ic_bt = bt.begin();

	assert( i_bt == ic_bt ); // ==(const const_iterator &other)
	assert( ic_bt == i_bt ); // ==(const iterator &other)

	ie_bt = bt.end();
	iec_bt = bt.end();

	assert( ie_bt == iec_bt ); // ==(const const_iterator &other)
	assert( iec_bt == ie_bt ); // ==(const iterator &other)

	assert( ie_bt != ic_bt ); // !=(const const_iterator &other)
	assert( ic_bt != ie_bt ); // !=(const iterator &other)

	Queue<int>::const_iterator ic_bt2(i_bt); //const_iterator(const iterator &other)

	assert( i_bt == ic_bt2 ); // ==(const const_iterator &other)
	assert( ic_bt2 == i_bt ); // ==(const iterator &other)
	
}


void test_transformif(){
	std::cout << "TEST TRANSFORMIF" << std::endl;
	//test transformif


	Queue<int> q0(4);
	q0.push(3);
	q0.push(5);
	q0.push(8);
	q0.push(-4);
	assert( q0.size() == 5 ); 
	assert( q0.get_older() == 4 );
	assert( q0.get_younger() == -4 );

	Queue<int>::const_iterator i, ie;

	i = q0.begin();
	ie = q0.end();

	int contatore_while = 0;
	while(i != ie){

		switch(contatore_while){ //test operator*()
			case 0 : assert( *i == 4 ); break;
			case 1 : assert( *i == 3 ); break;
			case 2 : assert( *i == 5 ); break;
			case 3 : assert( *i == 8 ); break;
			default : assert( false );
		}
		contatore_while++;
		i++ ; // testato anche i++
	}
	assert( *i == -4 );

	operatore_custom<int> f;
	pari<int> pred;
	transformif(q0, pred, f);

	i = q0.begin();
	ie = q0.end();

	contatore_while = 0;
	while(i != ie){

		switch(contatore_while){ //test operator*()
			case 0 : assert( *i == 8 ); break;
			case 1 : assert( *i == 3 ); break;
			case 2 : assert( *i == 5 ); break;
			case 3 : assert( *i == 16 ); break;
			default : assert( false );
		}
		contatore_while++;
		i++ ; // testato anche i++
	}
	assert( *i == -8 );

	q0.push(40);
	transformif(q0, pred, f);

	i = q0.begin();
	ie = q0.end();

	contatore_while = 0;
	while(i != ie){

		switch(contatore_while){ //test operator*()
			case 0 : assert( *i == 16 ); break;
			case 1 : assert( *i == 3 ); break;
			case 2 : assert( *i == 5 ); break;
			case 3 : assert( *i == 32 ); break;
			case 4 : assert( *i == -16 ); break;
			default : assert( false );
		}
		contatore_while++;
		i++ ; // testato anche i++
	}
	assert( *i == 80 );

	q0.pop();
	q0.set_older( q0.get_older() * 2 ); // 6
	transformif(q0, pred, f);
	
	i = q0.begin();
	ie = q0.end();

	contatore_while = 0;
	while(i != ie){

		switch(contatore_while){ //test operator*()
			case 0 : assert( *i == 12 ); break; // 6 * 2
			case 1 : assert( *i == 5 ); break;
			case 2 : assert( *i == 64 ); break;
			case 3 : assert( *i == -32 ); break;
			default : assert( false );
		}
		contatore_while++;
		i++ ; // testato anche i++
	}
	assert( *i == 160 );


	Queue<int> q1;

	assert( q1.size() == 0 );
	transformif(q1, pred, f);
	assert( q1.size() == 0 );

	//test my_uninitialized_value
	bool unizialied_older = false;
	try{
		q1.get_older(); 
	}
	catch(my_uninitialized_value e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		unizialied_older = true;
	}
	assert ( unizialied_older );

	//test my_uninitialized_value
	bool unizialied_younger = false;
	try{
		q1.get_younger(); 
	}
	catch(my_uninitialized_value e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		unizialied_younger = true;
	}
	assert ( unizialied_younger );

	q1.push(1);
	q1.push(-3);
	assert( q1.size() == 2 );
	assert( q1.get_younger() == -3);
	assert( q1.get_older() == 1);

	transformif(q1, pred, f);
	assert( q1.size() == 2 );
	assert( q1.get_younger() == -3);
	assert( q1.get_older() == 1);

	Queue<int> q2;
	q2.push(2);
	q2.push(-4);
	q2.push(0);
	q2.push(12);

	transformif(q2, pred, f);

	i = q2.begin();
	ie = q2.end();

	contatore_while = 0;
	while(i != ie){

		switch(contatore_while){ //test operator*()
			case 0 : assert( *i == 4 ); break; 
			case 1 : assert( *i == -8 ); break;
			case 2 : assert( *i == 0 ); break;
			default : assert( false );
		}
		contatore_while++;
		i++ ; // testato anche i++
	}
	assert( *i == 24 );


	
	i = q2.begin();
	ie = q2.end();

	transformif(q2, pred, f);

	contatore_while = 0;
	while(i != ie){

		switch(contatore_while){ //test operator*()
			case 0 : assert( *i == 8 ); break; 
			case 1 : assert( *i == -16 ); break;
			case 2 : assert( *i == 0 ); break;
			default : assert( false );
		}
		contatore_while++;
		i++ ; // testato anche i++
	}
	assert( *i == 48 );


	q2.pop();

	transformif(q2, pred, f);

	i = q2.begin();
	ie = q2.end();

	contatore_while = 0;
	while(i != ie){

		switch(contatore_while){ //test operator*()
			case 0 : assert( *i == -32 ); break; 
			case 1 : assert( *i == 0 ); break;
			default : assert( false );
		}
		contatore_while++;
		i++ ; // testato anche i++
	}
	assert( *i == 96 );


}


void test_iterator_push(){
	std::cout << "TEST ITERATOR PUSH" << std::endl;
	//test push(const iterator &i, const iterator &ie)
	//test push(const const_iterator &i, const const_iterator &ie)


	Queue<int> q0(4);
	q0.push(3);
	q0.push(5);
	q0.push(8);
	q0.push(-4);
	assert( q0.size() == 5 ); 
	assert( q0.get_older() == 4 );
	assert( q0.get_younger() == -4 );

	Queue<int> q1(0);
	q1.push(1);
	q1.push(2);
	q1.push(3);
	q1.push(4);
	q1.push(5);
	q1.push(6);
	assert( q1.size() == 7 ); 
	assert( q1.get_older() == 0 );
	assert( q1.get_younger() == 6 );

	Queue<int>::iterator i, ie;
	i = q1.begin();
	ie = q1.end();

	q0.push(i, ie); // push(const iterator &i, const iterator &ie)
	assert( q0.size() == 12 ); 
	assert( q0.get_older() == 4 );
	assert( q0.get_younger() == 6 );

	ie = q1.begin(); //0
	ie++; //1
	ie++; //2

	q0.push(i, ie);
	assert( q0.size() == 15 ); 
	assert( q0.get_older() == 4 );
	assert( q0.get_younger() == 2 );

	Queue<int> empty;
	Queue<int>::iterator i_empty, ie_empty;
	i_empty = empty.begin();
	ie_empty = empty.end();

	//test my_uninitialized_value
	bool error_iterator_null = false;
	try{
		q0.push(i_empty, ie_empty); //controlli nullptr
	}
	catch(my_uninitialized_value e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		error_iterator_null = true;
	}
	assert ( error_iterator_null );
	
	assert( empty.size() == 0 );

	Queue<int> empty_2;
	//test my_uninitialized_value
	error_iterator_null = false;
	try{
		empty_2.push(i_empty, ie_empty); //controlli nullptr
	}
	catch(my_uninitialized_value e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		error_iterator_null = true;
	}
	assert ( error_iterator_null );

	assert( empty_2.size() == 0 );
	assert( empty.size() == 0 );

	assert( q0.size() == 15 ); 
	assert( q0.get_older() == 4 );
	assert( q0.get_younger() == 2 );


	q0.pop();
	assert( q0.size() == 14 ); 
	assert( q0.get_older() == 3 );
	assert( q0.get_younger() == 2 );

	i = q1.begin();
	ie = q1.begin();
	assert( i == ie );
	q0.push(i, ie); 
	assert( q0.size() == 15 ); 
	assert( q0.get_older() == 3 );
	assert( q0.get_younger() == 0 );

	assert( empty.size() == 0 );
	i = q0.begin();
	ie = q0.end();
	empty.push(i, ie); //push into empty
	assert( empty.size() == 15 ); 
	assert( empty.get_older() == 3 );
	assert( empty.get_younger() == 0 );
	assert( q0.size() == 15 ); 
	assert( q0.get_older() == 3 );
	assert( q0.get_younger() == 0 );

	
	Queue<int> q0c(4);
	q0c.push(3);
	q0c.push(5);
	q0c.push(8);
	q0c.push(-4);
	assert( q0c.size() == 5 ); 
	assert( q0c.get_older() == 4 );
	assert( q0c.get_younger() == -4 );

	Queue<int> q1c(0);
	q1c.push(1);
	q1c.push(2);
	q1c.push(3);
	q1c.push(4);
	q1c.push(5);
	q1c.push(6);
	assert( q1c.size() == 7 ); 
	assert( q1c.get_older() == 0 );
	assert( q1c.get_younger() == 6 );

	Queue<int>::const_iterator ic, iec;
	ic = q1c.begin();
	iec = q1c.end();

	q0c.push(ic, iec); // push(const const_iterator &i, const const_iterator &iec)
	assert( q0c.size() == 12 ); 
	assert( q0c.get_older() == 4 );
	assert( q0c.get_younger() == 6 );

	iec = q1c.begin(); //0
	iec++; //1
	iec++; //2

	q0c.push(ic, iec);
	assert( q0c.size() == 15 ); 
	assert( q0c.get_older() == 4 );
	assert( q0c.get_younger() == 2 );

	Queue<int> empty_c;
	Queue<int>::const_iterator ic_empty, iec_empty;
	ic_empty = empty_c.begin();
	iec_empty = empty_c.end();

	//test my_uninitialized_value
	bool error_const_iterator_null = false;
	try{
		q0c.push(ic_empty, iec_empty); //controlli nullptr
	}
	catch(my_uninitialized_value e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		error_const_iterator_null = true;
	}
	assert ( error_const_iterator_null );

	assert( empty_c.size() == 0 );

	Queue<int> empty_c_2;
	//test my_uninitialized_value
	error_const_iterator_null = false;
	try{
		empty_c_2.push(ic_empty, iec_empty); //controlli nullptr
	}
	catch(my_uninitialized_value e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		error_const_iterator_null = true;
	}
	assert ( error_const_iterator_null );

	assert( empty_c_2.size() == 0 );
	assert( empty_c.size() == 0 );

	assert( q0c.size() == 15 ); 
	assert( q0c.get_older() == 4 );
	assert( q0c.get_younger() == 2 );


	q0c.pop();
	assert( q0c.size() == 14 ); 
	assert( q0c.get_older() == 3 );
	assert( q0c.get_younger() == 2 );

	ic = q1c.begin();
	iec = q1c.begin();
	assert( ic == iec );
	q0c.push(ic, iec);
	assert( q0c.size() == 15 ); 
	assert( q0c.get_older() == 3 );
	assert( q0c.get_younger() == 0 );

	assert( empty_c.size() == 0 );
	ic = q0c.begin();
	iec = q0c.end();
	empty_c.push(ic, iec); //push into empty
	assert( empty_c.size() == 15 ); 
	assert( empty_c.get_older() == 3 );
	assert( empty_c.get_younger() == 0 );
	assert( q0c.size() == 15 ); 
	assert( q0c.get_older() == 3 );
	assert( q0c.get_younger() == 0 );



	Queue<int> p(1);
	p.push(2);
	p.push(3);
	p.push(4);
	p.push(5);

	assert( p.size() == 5 );

	Queue<int> single(100);

	Queue<int>::iterator ip, iep;
	ip = p.begin();
	iep = p.end();

	

	//test out_of_range_iterator
	bool error_iterator_push = false;
	try{
		single.push(iep, ip); //perche' iep > ip
	}
	catch(out_of_range_iterator e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		error_iterator_push = true;
	}
	assert ( error_iterator_push );

	Queue<int>::iterator ipc, iepc;
	ipc = p.begin();
	iepc = p.end();
	
	//test out_of_range_iterator
	error_iterator_push = false;
	try{
		single.push(iepc, ipc); //perche' iepc > ipc
	}
	catch(out_of_range_iterator e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		error_iterator_push = true;
	}
	assert ( error_iterator_push );

	

}


void test_other_type(){
	std::cout << "TEST OTHER TYPE" << std::endl;
	//Classe_custom
	//string
	//test iterator->
	//test my_uninitialized_value with ->


	Classe_custom c0; //test costruttore default
	assert( c0.get_lettera() == 'a' );
	assert( c0.get_numero() == 0 );

	Classe_custom c1(12, 'f'); //test costruttore
	assert( c1.get_lettera() == 'f' );
	assert( c1.get_numero() == 12 );

	Classe_custom c2(c1); //test costruttore copia
	assert( c2.get_lettera() == 'f' );
	assert( c2.get_numero() == 12 );
	assert( c1 == c2 );
	assert( c1 != c0 );
	assert( c2 != c0 );
	assert( c1 > c0 );
	assert( c2 > c0 );
	assert( c0 < c1 );
	assert( c0 < c2 );


	c0 = c1;
	assert( c0.get_lettera() == 'f' );
	assert( c0.get_numero() == 12 );
	assert( c0 == c2 );
	assert( c2.get_lettera() == 'f' );
	assert( c2.get_numero() == 12 );
	assert( c1 == c2 );
	assert( c1.get_lettera() == 'f' );
	assert( c1.get_numero() == 12 );
	assert( c0 == c1 );

	Classe_custom c3;
	c0 = c3;
	std::cout << "(0,a) -> ";
	std::cout << c0 << std::endl; //(0,a)
	Classe_custom c4(12, 'r');

	Queue<Classe_custom> q_custom;
	assert( q_custom.size() == 0 );
	std::cout << "Empty Queue -> ";
	q_custom.show(); //Empty Queue

	bool pop_error = false;
	try{
		q_custom.pop(); 
	}
	catch(bad_pop_exception e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		pop_error = true;
	}
	assert ( pop_error );

	bool unizialied_older = false;
	try{
		q_custom.get_older(); 
	}
	catch(my_uninitialized_value e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		unizialied_older = true;
	}
	assert ( unizialied_older );

	//test my_uninitialized_value
	bool unizialied_younger = false;
	try{
		q_custom.get_younger(); 
	}
	catch(my_uninitialized_value e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		unizialied_younger = true;
	}
	assert ( unizialied_younger );

	q_custom.push(c0);
	assert( q_custom.size() == 1 );
	assert( q_custom.get_older().get_lettera() == 'a' );
	assert( q_custom.get_older().get_numero() == 0 );
	assert( q_custom.get_younger().get_lettera() == 'a' );
	assert( q_custom.get_younger().get_numero() == 0 );
	q_custom.push(c1);
	assert( q_custom.size() == 2 );
	assert( q_custom.get_older().get_lettera() == 'a' );
	assert( q_custom.get_older().get_numero() == 0 );
	assert( q_custom.get_younger().get_lettera() == 'f' );
	assert( q_custom.get_younger().get_numero() == 12 );
	q_custom.push(c4);
	assert( q_custom.size() == 3 );
	assert( q_custom.get_older().get_lettera() == 'a' );
	assert( q_custom.get_older().get_numero() == 0 );
	assert( q_custom.get_younger().get_lettera() == 'r' );
	assert( q_custom.get_younger().get_numero() == 12 );

	std::cout << "(0,a)|(12,f)|(12,r)| -> ";
	q_custom.show(); // (0,a)|(12,f)|(12,r)|

	Queue<Classe_custom> q0;
	assert(q0.size() == 0 );

	Queue<Classe_custom>::iterator i, ie;
	i = q0.begin();
	ie = q0.end();

	//test my_uninitialized_value
	bool error_iterator_null = false;
	try{
		*i;
	}
	catch(my_uninitialized_value e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		error_iterator_null = true;
	}
	assert ( error_iterator_null );

	//test my_uninitialized_value
	error_iterator_null = false;
	try{
		*ie;
	}
	catch(my_uninitialized_value e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		error_iterator_null = true;
	}
	assert ( error_iterator_null );

	//test my_uninitialized_value
	error_iterator_null = false;
	try{
		ie->get_lettera();
	}
	catch(my_uninitialized_value e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		error_iterator_null = true;
	}
	assert ( error_iterator_null );

	//test my_uninitialized_value
	error_iterator_null = false;
	try{
		i->get_lettera();
	}
	catch(my_uninitialized_value e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		error_iterator_null = true;
	}
	assert ( error_iterator_null );


	q0 = q_custom;
	assert( q0.size() == 3 );
	assert( q0.get_older().get_lettera() == 'a' );
	assert( q0.get_older().get_numero() == 0 );
	assert( q0.get_younger().get_lettera() == 'r' );
	assert( q0.get_younger().get_numero() == 12 );
	assert( q_custom.size() == 3 );
	assert( q_custom.get_older().get_lettera() == 'a' );
	assert( q_custom.get_older().get_numero() == 0 );
	assert( q_custom.get_younger().get_lettera() == 'r' );
	assert( q_custom.get_younger().get_numero() == 12 );

	q_custom.pop();
	assert( q0.size() == 3 );
	assert( q0.get_older().get_lettera() == 'a' );
	assert( q0.get_older().get_numero() == 0 );
	assert( q0.get_younger().get_lettera() == 'r' );
	assert( q0.get_younger().get_numero() == 12 );
	assert( q_custom.size() == 2 );
	assert( q_custom.get_older().get_lettera() == 'f' );
	assert( q_custom.get_older().get_numero() == 12 );
	assert( q_custom.get_younger().get_lettera() == 'r' );
	assert( q_custom.get_younger().get_numero() == 12 );

	i = q0.begin();
	ie = q0.end();

	assert( q0.size() == 3 );
	assert( q0.get_older().get_lettera() == 'a' );
	assert( q0.get_older().get_numero() == 0 );
	assert( q0.get_younger().get_lettera() == 'r' );
	assert( q0.get_younger().get_numero() == 12 );

	assert( i->get_lettera() == 'a' );
	assert( i->get_numero() == 0 );
	i++;
	assert( (*i).get_lettera() == 'f' );
	assert( (*i).get_numero() == 12 );
	assert( i->get_lettera() == 'f' );
	assert( i->get_numero() == 12 );
	++i;
	assert( i->get_lettera() == 'r' );
	assert( i->get_numero() == 12 );

	Classe_custom c5(25, 'k');
	q0.set_younger(c5);
	assert( q0.size() == 3 );
	assert( q0.get_older().get_lettera() == 'a' );
	assert( q0.get_older().get_numero() == 0 );
	assert( q0.get_younger().get_lettera() == 'k' );
	assert( q0.get_younger().get_numero() == 25 );

	*i = c4;
	assert( i->get_lettera() == 'r' );
	assert( i->get_numero() == 12 );

	assert( q0.size() == 3 );
	assert( q0.get_older().get_lettera() == 'a' );
	assert( q0.get_older().get_numero() == 0 );
	assert( q0.get_younger().get_lettera() == 'r' );
	assert( q0.get_younger().get_numero() == 12 );

	//test out_of_range_iterator
	bool error_iterator_post = false;
	try{
		i++;
	}
	catch(out_of_range_iterator e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		error_iterator_post = true;
	}
	assert ( error_iterator_post );

	//test out_of_range_iterator
	bool error_iterator_pre = false;
	try{
		++i;
	}
	catch(out_of_range_iterator e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		error_iterator_pre = true;
	}
	assert ( error_iterator_pre );


	Classe_custom c6(12,'e');
	assert( q0.contain(c6) == false );

	assert( i == ie );
	i = q0.begin();
	assert( i != ie );

	Classe_custom c_default;
	assert( q0.contain(c_default) == true );

	Queue<Classe_custom>::const_iterator i_c, ie_c;
	
	i_c = q0.begin();
	ie_c = q0.end();

	assert( i_c->get_numero() == 0 );
	assert( i_c->get_lettera() == 'a' );
	assert( ie_c->get_numero() == 12 );
	assert( ie_c->get_lettera() == 'r' );



	std::string s0 = "Mario";
	std::string s1 = "Anna";
	std::string s2 = "Ilaria";
	std::string s3 = "Davide";
	std::string s4 = "Roberto";


	Queue<std::string> coda_poste;
	assert( coda_poste.size() == 0 );

	std::cout << "Empty Queue -> ";
	coda_poste.show(); // Empty Queue

	pop_error = false;
	try{
		coda_poste.pop(); 
	}
	catch(bad_pop_exception e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		pop_error = true;
	}
	assert ( pop_error );

	unizialied_older = false;
	try{
		coda_poste.get_older(); 
	}
	catch(my_uninitialized_value e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		unizialied_older = true;
	}
	assert ( unizialied_older );

	//test my_uninitialized_value
	unizialied_younger = false;
	try{
		coda_poste.get_younger(); 
	}
	catch(my_uninitialized_value e){
		#ifdef DEBUGGING
		std::cerr << e.what() << std::endl;
		#endif
		unizialied_younger = true;
	}
	assert ( unizialied_younger );

	coda_poste.push(s0);
	assert( coda_poste.size() == 1 );
	assert( coda_poste.get_younger() == "Mario" );
	assert( coda_poste.get_older() == "Mario" );
	coda_poste.push(s1);
	assert( coda_poste.size() == 2 );
	assert( coda_poste.get_younger() == "Anna" );
	assert( coda_poste.get_older() == "Mario" );
	coda_poste.push(s2);
	assert( coda_poste.size() == 3 );
	assert( coda_poste.get_younger() == "Ilaria" );
	assert( coda_poste.get_older() == "Mario" );
	coda_poste.push(s3);
	assert( coda_poste.size() == 4 );
	assert( coda_poste.get_younger() == "Davide" );
	assert( coda_poste.get_older() == "Mario" );

	std::cout << "Mario|Anna|Ilaria|Davide| -> ";
	coda_poste.show(); // Mario|Anna|Ilaria|Davide|




	Queue<std::string> amici("Giacomino");
	assert( amici.size() == 1 );
	assert( amici.get_younger() == "Giacomino" );
	assert( amici.get_older() == "Giacomino" );

	amici.push(s4);
	assert( amici.size() == 2 );
	assert( amici.get_younger() == "Roberto" );
	assert( amici.get_older() == "Giacomino" );

	Queue<std::string>::iterator i_string;

	i_string = amici.begin();
	assert( i_string->size() == 9 );

	coda_poste = amici;
	assert( coda_poste.size() == 2 );
	assert( coda_poste.get_younger() == "Roberto" );
	assert( coda_poste.get_older() == "Giacomino" );
	assert( amici.size() == 2 );
	assert( amici.get_younger() == "Roberto" );
	assert( amici.get_older() == "Giacomino" );

	


}


int main(){

	test_costruttori(); //ok
	test_push_pop(); //ok
	test_operatore_assegnamento(); //ok
	test_contain(); //ok
	test_iterator(); //ok
	test_const_iterator(); //ok
	test_transformif(); //ok
	test_iterator_push(); //ok
	test_other_type(); //ok

	std::cout <<"END TEST" << std::endl;
	

}	