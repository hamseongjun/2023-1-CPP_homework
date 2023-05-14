#include <iostream>

template <typename T>
class DblList;

template <typename T>
class DblListNode {
    friend class DblList<T>;
    private:
        int data;
        DblListNode<T> *left, *right;
};

template <typename T>
class DblList {
    public:
        //반복자
        class Iterator {    
            public :
                //생성자
                Iterator(DblListNode<T>* startNode = 0) {current = startNode;}

                //역참조
                T& operator*() const {return current->data;}
                T* operator->() const {return &current-> data;}

                // 증가
                Iterator& operator++();     //전위 증가
                Iterator operator++(int);   //후위 증가

                // 감소
                Iterator& operator--();     //전위 감소
                Iterator operator--(int)    //후위 감소

                //등위
                bool operator!=(const Iterator ok) const    //다른 노드인지 확인
                    {return current != ok.current;}
                bool operator==(const Iterator ok) const    //같은 노드인지 확인
                    {return current == ok.current;}

            private:
                DblListNode<T>* current;    //현재 노드를 가리키는 포인터
        };

        //리스트 조작연산
        DblList();
        ~DblList();

        Iterator begin();
        Iterator end();

        void Delete(DblListNode<T> *);
        void Insert(DblListNode<T> *, DblListNode<T> *);

        T accumulate(const Iterator&, const Iterator&, const T&);

    private:
        DblListNode<T> * first; //헤더노드를 가리킴
};

// 1) 생성자
template <typename T>
DblList<T>::DblList() {
    
}

// 2) 소멸자
template <typename T>
DblList<T>::~DblList() {

}


// 3) begin 함수
template <typename T>
typename DblList<T>::Iterator DblList<T>::begin() {
    return Iterator(first->right);
}

// 4) end 함수
template <typename T>
typename DblList<T>::Iterator DblList<T>::end() {
    return Iterator(first)
}

// 5) i번째 노드 뒤에 삽입하는 함수
template <typename T>
void DblList<T>::Insert(DblListNode<T> *p, DblListNode<T> *x)
{
    p->left = x; p->right = x->right;
    x->right->left = p; x->right = p;
}

// 6) i번째 노드 뒤에 삽입하는 함수
template <typename T>
void DblList<T>::Delete(DblListNode<T> *x)
{
    if (x==first) throw "Deletion of header node not permitted";
    else {
        x->left->right = x->right;
        x->right->left = x->left;
        delete x;
    }
}

// 7) 전진, 후진 반복자
template <typename T>
typename DblList<T>::Iterator& DblList<T>::Iterator::operator++() { //전위 증가
    current = current->right; 
    return *this;
}
template <typename T>
typename DblList<T>::Iterator DblList<T>::Iterator::operator++(int) {   //후위 증가
    Iterator old = *this;
    current = current->link;
    return old;
}
template <typename T>
typename DblList<T>::Iterator& DblList<T>::Iterator::operator--() { //전위 감소
    current = current->left; 
    return *this;
}
template <typename T>
typename DblList<T>::Iterator DblList<T>::Iterator::operator--(int) {   //후위 감소
    Iterator old = *this;
    current = current->left;
    return old;
}

// 8) accumulate 알고리즘
template <typename T>
T DblList<T>::accumulate(const Iterator& begin, const Iterator& end, const T& init) {
    T sum = init;
    for (Iterator iterator = begin; iterator != end; iterator++) {
        sum += *iterator;
    }
    return sum;
}

//메인 함수
int main(void)
{

    return 0;
}
