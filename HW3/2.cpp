#include <iostream>

using namespace std;

template <typename T>
class DblList;

// 노드 클래스
template <typename T>
class DblListNode {
    friend class DblList<T>;    // 연결 리스트와 friend 선언
    private:
        T data;
        DblListNode<T> *left, *right;
        
        // 생성자
        DblListNode<T>(void) {}
        DblListNode<T>(const T& data, DblListNode<T> *left, DblListNode<T> *right)  // Insert() 호출시 사용될 생성자
            : data(data), left(left), right(right) {}
};

// 이중 연결 원형 리스트 클래스
template <typename T>
class DblList {
    public:
        // 반복자
        class Iterator {    
            public :
                // 생성자
                Iterator(DblListNode<T>* startNode = 0) {current = startNode;}

                // 역참조
                T& operator*() const {return current->data;}
                T* operator->() const {return &current-> data;}

                // 증가
                Iterator& operator++();     // 전위 증가
                Iterator operator++(int);   // 후위 증가

                // 감소
                Iterator& operator--();     // 전위 감소
                Iterator operator--(int);    // 후위 감소

                // 등위
                bool operator!=(const Iterator ok) const    // 다른 노드인지 확인
                    {return current != ok.current;}
                bool operator==(const Iterator ok) const    // 같은 노드인지 확인
                    {return current == ok.current;}

            private:
                DblListNode<T>* current;    // 현재 노드를 가리키는 포인터
        };

        // 리스트 조작연산
        DblList();
        ~DblList();

        Iterator begin();
        Iterator end();

        void Insert(int i, const T& data);
        void Delete(int i);

        T accumulate(const Iterator& begin, const Iterator& end, const T& init);

    private:
        DblListNode<T> * first;     // 헤더노드를 가리킴
};

// 1) 생성자
template <typename T>
DblList<T>::DblList() {
    first = new DblListNode<T>;     // 헤더 노드를 가진 공백 리스트 생성
    first->right = first;
    first->left = first;
}

// 2) 소멸자
template <typename T>
DblList<T>::~DblList() {
    DblListNode<T>* curr = first->right;
    while (curr != first) {     // 모든 노드 삭제
        DblListNode<T>* temp = curr;
        curr = curr -> right;
        delete temp;
    }
    delete first;       // 헤더 노드까지 삭제
}


// 3) begin 함수
template <typename T>
typename DblList<T>::Iterator DblList<T>::begin() {
    return Iterator(first->right);  // 0번째 노드 리턴
}

// 4) end 함수
template <typename T>
typename DblList<T>::Iterator DblList<T>::end() {
    return Iterator(first);
}

// 5) i번째 노드 뒤에 삽입하는 함수
template <typename T>
void DblList<T>::Insert(int i, const T& data)
{
    DblListNode<T>* curr = first;   // 헤더 노드에서 시작
    for (int j = 0; j < i; j++)     // i번째 노드까지 이동
        curr = curr -> right;
    DblListNode<T>* newNode = new DblListNode<T>(data, curr, curr->right);    // 새로운 노드 생성
    curr->right->left = newNode;                                    // i+1번째 노드를 추가될 노드에 연결
    curr->right = newNode;                                          // i번째 노드를 추가될 노드에 연결
}

// 6) i번째 노드를 삭제하는 함수
template <typename T>
void DblList<T>::Delete(int i)
{
    DblListNode<T>* curr = first;   // 헤더 노드에서 시작
    for (int j = 0; j < i; j++)     // i번째 노드까지 이동
        curr = curr->right;   
    curr->right->left = curr->left;     // 다음 노드와 이전 노드 연결
    curr->left->right = curr->right;    // 이전 노드와 다음 노드 연결
    delete curr;                        // 현재 노드 삭제
}

// 7) 전진, 후진 반복자
template <typename T>
typename DblList<T>::Iterator& DblList<T>::Iterator::operator++() {     // 전위 증가
    current = current->right; 
    return *this;
}
template <typename T>
typename DblList<T>::Iterator DblList<T>::Iterator::operator++(int) {   // 후위 증가
    Iterator old = *this;
    current = current->right;
    return old;
}
template <typename T>
typename DblList<T>::Iterator& DblList<T>::Iterator::operator--() {     // 전위 감소
    current = current->left; 
    return *this;
}
template <typename T>
typename DblList<T>::Iterator DblList<T>::Iterator::operator--(int) {   // 후위 감소
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

// Number 클래스
class Number
{
    private:
        int num;
    public:
        Number() : num(0) { }
        Number(int n) : num(n) { }
        void ShowData() { cout<<num<<endl; }
        Number * operator->()
        {
            return this;
        }
        Number& operator*()
        {
            return *this;
        }
};

// 메인 함수
int main(void)
{
    DblList<Number> myList;     // 연결 리스트 생성

    // 1. 1부터 9까지의 정수를 갖는 노드를 추가
    for (int i = 0; i < 9; i++) {
        myList.Insert(i, Number(i));
    }

    // 2. 체인의 각 노드들을 출력하여 1부터 9까지 순차적으로 출력되는지 확인
    DblList<Number>::Iterator it = myList.begin();
    DblList<Number>::Iterator endIt = myList.end();
    while(it != endIt) {
        cout << *it << " ";
        it++;
    }
    cout << endl;

    return 0;
}
