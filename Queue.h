#ifndef QUEUE_H
#define QUEUE_H
#include "List.h"

//queue class
template<typename T>
class Queue{
public:
	void pop();
	void push(const T& d);
	T front();
	T back();
	int size();
	bool isEmpty();

private:
	List<T> list;
};

//pop off the queue front by calling lists class method removeFront()
template<typename T>
void Queue<T>::pop(){
	list.removeFront();
}

//push on the queue by calling lists class method insertBack()
template<typename T>
void Queue<T>::push(const T& d){
	list.insertBack(d);
}

//return the front data by calling lists class method peekFront()
template<typename T>
T Queue<T>::front(){
	return list.peekFront();
}

//return the back data by calling lists class method peekBack()
template<typename T>
T Queue<T>::back(){
	return list.peekBack();
}

//return the size of queue by calling lists class method size()
template<typename T>
int Queue<T>::size(){
	return list.size();
}

//return if empty by calling lists method isEmpty()
template<typename T>
bool Queue<T>::isEmpty() {
	return list.isEmpty();
}
#endif
