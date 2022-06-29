#pragma once

#include <iostream>
#include <initializer_list>
#include <cassert>

template<typename T>
struct node
{
	T data;
	node* prev;
	node* next;
};

template<typename T>
class LinkedList
{
public:
	// конструктор со списком инициализации 
	LinkedList(std::initializer_list<T> list);
	// конструктор без параметров
	LinkedList();
	// конструктор кпирования
	LinkedList(const LinkedList& list);
	// конструктор перемещения
	LinkedList(LinkedList&& list);
	// деструктор
	~LinkedList();

	// добавить элемент в конец
	LinkedList& addTail(T t);
	// добавить элемент в начало
	LinkedList& addHead(T t);
	// вставить элемент
	LinkedList& insert(T t, int position);
	// удалить элемент с начала
	void deleteHead();
	// удалить элемент с конца
	void deleteTail();
	// очистить
	void clear();

	size_t getSize()const { return this->size_; }
	node<T>* getHead()const { return this->head_; }
	node<T>* getTail()const { return this->tail_; }
	void print()const;

	// перегрузка оператора присваивания
	LinkedList& operator=(const LinkedList& list);

	// перегрузка []
	T& operator[](const int i);

	bool operator==(const LinkedList& list);
	bool operator!=(const LinkedList& list);



private:
	node<T>* head_;
	node<T>* tail_;
	size_t size_;
};


template<typename T>
LinkedList<T>::LinkedList(std::initializer_list<T> list)
{
	this->head_ = nullptr;
	this->tail_ = nullptr;
	for (auto element : list)
	{
		this->addTail(element);
	}
	this->size_ = list.size();
}

template<typename T>
LinkedList<T>::LinkedList() : head_{nullptr}, tail_{nullptr}, size_{0}
{}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList& list)
{
	this->head_ = nullptr;
	this->tail_ = nullptr;
	node<T>* temp = list.head_;
	while (temp)
	{
		this->addTail(temp->data);
		temp = temp->next;
	}
}
template<typename T>
LinkedList<T>::LinkedList(LinkedList&& list)
{
	this->head_ = list.head_;
	this->tail_ = list.tail_;
	this->size_ = list.size_;

	list.head_ = nullptr;
	list.tail_ = nullptr;
	list.size_ = 0;
}

template<typename T>
LinkedList<T>::~LinkedList()
{
	this->clear();
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& list)
{
	if (this == &list)
		return *this;

	if (this->size_ != list.size_)
		this->clear();

	node<T>* temp = list.head_;
	while (temp)
	{
		this->addTail(temp->data);
		temp = temp->next;
	}

	return *this;
}

template<typename T>
T& LinkedList<T>::operator[](const int i)
{
	int num{ 0 };
	node<T>* temp = this->head_;
	while (num++ != i)
	{
		temp = temp->next;
	}

	return temp->data;
}

template<typename T>
bool LinkedList<T>::operator==(const LinkedList& list)
{
	if (this->size_ != list.size_)
		return false;

	node<T>* temp1 = this->head_;
	node<T>* temp2 = list.head_;
	for (int i{ 0 }; i < this->size_; ++i)
	{
		if (temp1->data != temp2->data)
			return false;
	}
	return true;
}

template<typename T>
bool LinkedList<T>::operator!=(const LinkedList& list)
{
	return !(*this == list);
}


template<typename T>
LinkedList<T>& LinkedList<T>::addTail(T t)
{
	if (this->head_ == nullptr)
	{
		this->head_ = new node<T>{ t, nullptr, nullptr };
		this->tail_ = this->head_;
	}
	else
	{
		node<T>* temp = new node<T>{ t, this->tail_, nullptr };
		this->tail_->next = temp;
		this->tail_ = temp;
	}
	++(this->size_);

	return *this;
}

template<typename T>
LinkedList<T>& LinkedList<T>::addHead(T t)
{
	node<T>* temp = new node<T>{ t, nullptr, this->head_ };
	this->head_->prev = temp;
	this->head_ = temp;
	++(this->size_);
	return *this;
}

template<typename T>
LinkedList<T>& LinkedList<T>::insert(T t, int position)
{
	assert(position >= 0 && position <= this->size_ - 1 && "index of range");

	if (!position)
	{
		return this->addHead(t);
	}
	else if (position == this->size_ - 1)
	{
		return this->addTail(t);
	}

	int i{ 0 };
	node<T>* temp;
	if (position > (this->size_ / 2))
	{
		temp = this->tail_;
		i = this->size_ - 1;
		while (i-- != position)
			temp = temp->prev;
		node<T>* temp2 = new node<T>{ t, temp, temp->next };
		temp->next = temp2;
		++(this->size_);
		return *this;
	}

	temp = this->head_;
	while (i++ != position - 1)
		temp = temp->next;
	node<T>* temp2 = new node<T>{ t, temp, temp->next };
	temp->next = temp2;
	++(this->size_);
	return *this;
}

template<typename T>
void LinkedList<T>::deleteHead()
{
	node<T>* temp = this->head_;
	this->head_ = temp->next;
	delete temp;
	if (this->head_ != nullptr)
	{
		this->head_->prev = nullptr;
	}
	--(this->size_);
}

template<typename T>
void LinkedList<T>::deleteTail()
{
	node<T>* temp = this->tail_;
	this->tail_ = tail_->prev;
	if (this->tail_ != nullptr)
		this->tail_->next = nullptr;
	--(this->size_);
}

template<typename T>
void LinkedList<T>::clear()
{
	while(this->size_)
		this->deleteHead();
}

template<typename T>
void LinkedList<T>::print()const
{
	node<T>* temp = this->head_;
	while (temp)
	{
		std::cout << temp->data << " ";
		temp = temp->next;
	}
	std::cout << std::endl;
}
