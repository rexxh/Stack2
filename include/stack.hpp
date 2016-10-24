


#pragma once
#include <stdlib.h>
#include <iostream>
#include <string>
#include "allocator.hpp"

#define MULTIPLIER 2 

using namespace std;

template<typename T>
T* New_n_copy(size_t ar_size, size_t count_, T* ar_){ /* strong */
T*temp = new T[ar_size];
try {
std::copy(ar_, ar_ + count_, temp);
}
catch (...) {
delete[] temp;
throw;
}
return temp;
}

template <typename T>
class stack : private allocator<T>
{
public:
stack(size_t size = 0); /* noexcept */
stack(stack<T> const & obj); /* strong */
size_t count() const; /* noexcept */
size_t array_size() const; /* noexcept */
void push(T const &); /* strong */
void pop(); /* strong */
const T& top() const; /* strong */
stack<T>& operator=(const stack<T> &); /* strong */
auto operator==(const stack & obj) const -> bool; /* strong */
bool empty() const; /* noexcept */
~stack(); /* noexcept */
}

template <typename T>
stack<T>::stack(size_t size) : allocator<T>(size){};

template <typename T>
stack<T>::stack(const stack& obj) : allocator<T>(obj.array_size_){
for (size_t i = 0; i < obj.count_; i++) {
construct(allocator<T>::array_ + i, obj.array_[i]);
}
	allocator<T>::count_ = obj.count_;
};

template <typename T>
size_t stack<T>::count() const {
return this->count_;
}

template <typename T>
stack<T>::~stack(){
destroy(this->array_, this->array_ + this->count_);
}

template <typename T>
size_t stack<T>::array_size() const {
return this->array_size_;
}

template <typename T>
void stack<T>::push(T const &obj) {
if (allocator<T>::count_ == allocator<T>::array_size_) {
size_t array_size = allocator<T>::size_ * MULTIPLIER + (allocator<T>::array_size_ == 0);
stack<T> temp(array_size);
while (temp.count() < allocator<T>::count_) temp.push(allocator<T>::array_[temp.count()]);
this->swap(temp);
}
construct(allocator<T>::array_ + allocator<T>::count_, obj);
++allocator<T>::count_;
}

template <typename T>
void stack<T>::pop() {
if (empty())
{
throw("the stack is empty");
}
destroy(&(this->array_[this->count_ - 1]));
this->count_--;
}

template <typename T>
const T& stack<T>::top() {
if (empty())
{
throw("the stack is empty");
}
return this->array_[this->count_ - 1];
}

template <typename T>
stack<T>& stack<T>::operator=(const stack<T> &obj) {
if (this != &obj){
stack<T> temp(obj);
this->swap(temp);
}
return *this;
}

template <typename T>
auto stack<T>::operator==(const stack & object) const -> bool
{
if (count_ != object.count_) {
throw ("Wrong Dimension");
}
for (unsigned int i = 0; i < count_; ++i) {
if (array_[i] != object.array_[i])
{
return false;
}
}
return true;
}

template <typename T>
bool stack<T>::empty() const{
if (!count_)
{
return true;
}
return false;
}

