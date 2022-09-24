//Marianna Matousek
//2/8/19
//added the collection class implementing the linked list
//to: 

// node class tempate used to contruct lists
// Mikhail Nesterenko
// 5/01/00

#ifndef LIST_H_
#define LIST_H_

// the pointer part of every list is the same
// lists differ by data part
template <typename T>
class node {
public:

	node() : next_(nullptr) {}

	// functions can be inlined
	T getData()const { return data_; }
	void setData(const T& data) { data_ = data; }

	// or can be defined outside
	node<T>* getNext() const;
	void setNext(node<T> *const);

private:
	T data_;
	node<T> *next_;
};

//
// member functions for node
//
template <typename T>
node<T>* node<T>::getNext()const {
	return next_;
}

template<typename T>
void node<T>::setNext(node<T> *const next) {
	next_ = next;
}

template <typename T>
class Collection {
	public:
		Collection() : head_(nullptr) {}
	//item as arg and adds it to the collection, does not check duplicates
	void addItem( T item);

	//takes item and removes all instances from collection
	void removeItem(T item);

	//returns the last item added to the collection
	node<T> lastItem(); 

	//prints all items in the collection
	void printCollection(); 

	//compares two collections for equality 
	///bool equal<T>(const Collection&, const Collection&);
	private:
		node<T> * head_;//points to next node or nullptr 
		


};

//
//member functions for Collection
//

//item as arg and adds it to the collection, does not check duplicates
template<typename T>
void Collection<T>::addItem(T item) {
	node<T> *newNode = new node<T>;
	newNode->setData(item);
	
	if (head_ == nullptr) {
	
		
		head_ = newNode; //point at new node	

		
		
	}
	else
	{
		
		newNode->setNext(head_);//point newNode to where head is pointing
		head_ = newNode; //point head to new node; 

	}

}

//prints all items in the collection
template<typename T>
void Collection<T>::printCollection() {
	if (head_ != nullptr) {
		node<T> * currentNode = head_;
		do{
			std::cout << currentNode->getData() << " "; 
			currentNode = currentNode->getNext(); 
		} while (currentNode != nullptr);
		std::cout << std::endl;
	}
	else {
		std::cout << "empty collection" << std::endl;
	}	
}

//takes item and removes all instances from collection
template<typename T>
void Collection<T>::removeItem(T item) {
	node<T>* previous = nullptr;
	node<T>* current = head_;
	while (current != nullptr) {
		if (head_->getData() == item) {
			current = current->getNext();
			delete head_;
			head_ = current; 
		}
		else {
			//previous = head_;
			//current = head_->getNext();
			if (current->getData() == item) {
				//set previous next_ to 1 node over
				previous->setNext(current->getNext()); 
				delete current;
				//point current to next node
				if(previous != nullptr)
				{
					current = previous->getNext();
				}
				else {
					current = nullptr;
				}
				

			}
			else {
				previous = current;
				current = previous->getNext();
			}
		}
	}
}


//not sure if this is right
//supposed to return last item in collection
//I'm taking that to mean last node?
template<typename T>
node<T>* Collection<T>::lastItem() {
	return head_;
}

	
	





#endif // LIST_H_
