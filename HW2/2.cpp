#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

//클래스 Bag 템플릿
template <typename T>
class Bag {
public:
    Bag(int bagCapacity = 3);
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

//생성자
template <typename T>
Bag<T>::Bag(int bagCapacity): capacity(bagCapacity) {
    if (capacity < 1) throw "Capacity must be > 0";
    array = new T[capacity];
    top = -1;
}

//소멸자
template <typename T>
Bag<T>::~Bag(){
    delete[] array;
}

//사이즈 Size()
template <typename T>
int Bag<T>::Size() const {
    return top + 1;
}

//비었니? IsEmpty
template <typename T>
bool Bag<T>::IsEmpty() const {
    return Size() == 0;
}

//랜덤 원소 리턴 Element
template <typename T>
T& Bag<T>::Element() const {
    if (IsEmpty()) throw "Bag is empty";
    srand(time(NULL));
    int randomIndex = rand() % (top + 1);
    return array[randomIndex];
}

//배열에 원소 넣기 Push
template <typename T>
void Bag<T>::Push(const T& x) {
    if (capacity == top + 1)
    {
        T* oldArray = array;
        capacity *= 2;
        array = new T[capacity];
        for (int i = 0; i <= top; i++)
            array[i] = oldArray[i];
        delete[] oldArray;
    }
    array[++top] = x;
}

//랜덤 원소 삭제 Pop
template <typename T>
void Bag<T>::Pop() {
    if (IsEmpty()) throw "Bag is empty, cannot delete";
    srand(time(NULL));
    int deletePos = rand() % (top + 1);
    copy(array + deletePos + 1, array + top + 1, array + deletePos);
    top--;
}

int main(void)
{
    Bag<int> bag;

    cout << "Size: " << bag.Size() << endl;
    cout << "IsEmpty: " << bag.IsEmpty() << endl;

    const int a = 3;
    const int b = 4;
    const int c = 1;
    bag.Push(a);
    bag.Push(b);
    bag.Push(c);

    cout << "Size: " << bag.Size() << endl;
    cout << "IsEmpty: " << bag.IsEmpty() << endl;
    cout << "Element: " << bag.Element() << endl;

    const int d = 9;
    const int e = 15;
    const int f = 7;
    const int g = 5;
    const int h = 20;
    const int i = 30;
    bag.Push(d);
    bag.Push(e);
    bag.Push(f);
    bag.Push(g);
    bag.Push(h);
    bag.Push(i);

    cout << "Size: " << bag.Size() << endl;
    cout << "IsEmpty: " << bag.IsEmpty() << endl;
    cout << "Element: " << bag.Element() << endl;

    bag.Pop();
    bag.Pop();

    cout << "Size: " << bag.Size() << endl;
    cout << "IsEmpty: " << bag.IsEmpty() << endl;
    cout << "Element: " << bag.Element() << endl;

    return 0;
}
