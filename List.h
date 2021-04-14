#ifndef LIST_H
#define LIST_H

//list interface class (pure virtual class)
template <typename T>
class ListInterface{
public:
	virtual void clear() = 0;
	virtual int size() = 0;
	virtual bool isEmpty() = 0;
	virtual void removeFront() = 0;
	virtual void removeBack()  = 0;
	virtual void insertFront(const T& d) = 0;
	virtual void insertBack(const T& d) = 0;
	virtual T peekFront() = 0;
	virtual T peekBack() = 0;
};

//list node class
template <typename T>
class ListNode{
public:
	ListNode<T>(const T& data, ListNode<T>* next = NULL, ListNode<T>* prev = NULL);
	T data;							//data to track
	ListNode<T>* next;  //next pointer
	ListNode<T>* prev;	//previous pointer
};

template <typename T>
ListNode<T>::ListNode(const T& data, ListNode<T>* next, ListNode<T>* prev){
	//member assignment
	this->data = data;
	this->next = next;
	this->prev = prev;
}

//list implementation class that inherits above virtual ListInterface class
template<typename T>
class List : public ListInterface<T>{
public:
	List<T>();
	virtual ~List<T>();
	void clear();
	int size();
	bool isEmpty();
	void removeFront();
	void removeBack();
	void insertFront(const T& d);
	void insertBack(const T& d);
	T peekFront();
	T peekBack();

private:
	ListNode<T>* front;  //front pointer
	ListNode<T>* back;   //back pointer
	int isize;
};

template <typename T>
List<T>::List(){
	front = back = NULL;
	isize = 0;
}

template <typename T>
List<T>::~List(){
	//call the clear method
	clear();
}

template <typename T>
void List<T>::clear(){
	//create new node
	ListNode<T>* current = front;
	//delete
	while (current != NULL){
		ListNode<T>* temp = current;
		current = current->next;
		delete temp;
	}
	//the front and back will be nulled out and size is 0
	front = back = NULL;
	isize = 0;
}

template <typename T>
bool List<T>::isEmpty(){ //constant
	return isize == 0;
}

template <typename T>
int List<T>::size(){ //constant
	return isize;
}

template <typename T>
void List<T>::removeBack(){
	//check if empty
	if (isEmpty()){
		//if the back is empty then return
		return;
	}
	//if single element
	else if (isize == 1){
		//call the clear method and return
		clear();
		return;
	}
	else{
		//create temp pointer
		ListNode<T>* temp = back;
		//the back is the back's previous pointer
		back = back->prev;
		//back's next pointer is temp
		back->next = temp;
		//delete temp
		delete temp;
	}
	//decrement the size
	--isize;
}

template <typename T>
void List<T>::removeFront(){ //remove from front of queue
	//check if empty
	if (isEmpty()){
		//if the front is empty then return
		return;
	}
	//if single element
	else if (isize == 1){
		//call the clear method and return
		clear();
		return;
	}
	else{
		//create temp pointer
		ListNode<T>* temp = front;
		//front equals the front's next pointer
		front = front->next;
		//front's previous pointer is now nulled out
		front->prev = NULL;
		//delete temp pointer
		delete temp;
	}
	//decrement the size
	--isize;
}

template <typename T>
void List<T>::insertFront(const T& d){ //insert at the back of queue
	//create newnode
	ListNode<T>* newNode = new ListNode<T>(d, front);
	// assign newnode to the front pointer
	front = newNode;
	//check if the size is 0
	if (isize == 0){
		back = newNode;
	}
	//increment the size
	++isize;
}

template <typename T>
void List<T>::insertBack(const T& d){ //insert at the back of queue
	//create newnode
	ListNode<T>* newNode = new ListNode<T>(d, NULL, back);
	//check if empty
	if (isize == 0){
		//if 0 then the front and back are the new node because single item
		front = back = newNode;
	}
	else{
		//backs next pointer is the newnode
		back->next = newNode;
	}
	//back now is the new node
	back = newNode;
	//increment the size
	++isize;
}

template <typename T>
T List<T>::peekFront(){
	//returns the front data
	return front->data;
}

template <typename T>
T List<T>::peekBack(){
	//returns the back data
	return back->data;
}
#endif
