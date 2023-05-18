#include <iostream>

template <typename T> class DblList;

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
        //생성자
        DblList(DblListNode<T>* startNode = 0) 
            {current = startNode;}
        
        //역참조
        T& operator*() const {return current -> data;}
        T* operator->() const {return &current->data;}

        //증가
        DblList* operator++()
            {current = current->link; return *this;}
        DblList operator++(int)
        {
            DblList old = *this;
            current = current->link;
            return old;
        }
        DblList operator--()

        bool operator!=(const DblList right) const
            {return current != right.current;}
        bool operator==(const DblList right) const
            {return current == right.current;}

    private:
        DblListNode<T> *first; //헤더노드를 가리킴
};

template <typename T>
DblList<T> begin() {return DblList(first);}
DblList<T> end() {return DblList(0);}

template <typename T>
void DblList<T>::Insert(DblListNode<T> *p, DblListNode<T> *x)
{// 노드 x의 오른편에 노드 p 삽입
    p→left = x; p→right = x→right;
    x→right→left = p; x→right = p;
}

template <typename T>
void DblList<T>::Delete(DblListNode<T>* x) 
{
    if ( x == first ) throw "De;etion of header node not permitted"
    else {
        x->left->right = x->right;
        x->right->left = x->left;
        delete x;
    }
}