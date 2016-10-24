#pragma once

template<typename T>
class allocator
{
protected:
T* array_;
size_t array_size_;
size_t count_;

allocator(size_t size = 0);
allocator(const allocator & obj) = delete;
~allocator();
auto swap(allocator & obj) ->void;
auto operator = (const allocator &)->allocator & = delete;
};

 template <typename T>
stack<T>::stack(size_t size) : allocator<T>(size){};

template <typename T>
stack<T>::stack(const stack& obj) : allocator<T>(obj.array_size_){
for (size_t i = 0; i < obj.count_; i++) {
construct(allocator<T>::array_ + i, obj.array_[i]);
}
	allocator<T>::count_ = obj.count_;
};

template <typename T1, typename T2>
void construct(T1 * ptr, T2 const & value) {
new (ptr) T1 (value);
}

template <typename T>
void destroy(T * ptr){
ptr->~T();
}

template <typename FwdIter>
void destroy(FwdIter first, FwdIter last) 
{
for (; first != last; ++first) 
{
destroy(&*first);
}
}

template<typename T>
void allocator<T>::swap(allocator & other) 
{
std::swap(array_, other.array_);
std::swap(array_size_, other.array_size_);
std::swap(count_, other.count_);
}

template<typename T>
allocator<T>::~allocator() 
{
operator delete(array_); 
}
