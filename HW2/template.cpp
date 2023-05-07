#include <iostream>

using namespace std;



template <class T>
class Bag
{
public:
  Bag (int bagCapacity = 3);
  ~Bag(); 
  
  int Size() const;  
  bool IsEmpty() const; 
  T& Element() const;  
  
  void Push(const T&); 
  void Pop(); 

private:
  T *array;
  int capacity; 
  int top; 
};

template <class T>
Bag<T>::Bag (int bagCapacity): capacity ( bagCapacity ) {
  if (capacity < 1) throw "Capacity must be > 0";
  array = new T[capacity];
  top = -1;
}

template <class T>
Bag<T>::~Bag() {delete [ ] array; }

template <class T>
void Bag<T>::Push(const T& x) {
  if (capacity ==top+1) 
  {
    ChangeSize1D(array, capacity, 2 * capacity);
    capacity *=2;
  }
  array[++top] = x;
}

template <class T>
void Bag<T>::Pop() {
  if (IsEmpty()) throw "Bag is empty, cannot delete";
  int deletePos = top / 2;
  copy(array+deletePos+1,array+top+1,array+deletePos);
      // compact array
  array[top--].~T();   // destructor for T
}

