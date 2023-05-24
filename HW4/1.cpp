// 헤더파일
#include <iostream>

// namespace
using namespace std;

// BST 전방 선언
template <typename K, typename E> class BST;

// Node 클래스(TreeNode)
template <typename K, typename E>
class TreeNode {
  friend class BST<K, E>;
  private:
    pair<K,E> data;
    int leftSize;
    TreeNode<K,E> *leftChild;
    TreeNode<K,E> *rightChild;

    TreeNode<K,E>(const pair<K,E>& data) : data(data), leftSize(1), leftChild(0), rightChild(0) {}
};

// 이원 탐색 트리 클래스(BST)
template <typename K, typename E>
class BST {
  public:
    void Insert(const pair<K,E>&);
    void Inorder();
    void Delete(const K&);
    pair<K,E>* Get(const K&);
    pair<K,E>* Rank(int);
    
  private:
    void Visit(TreeNode<K,E> *);
    void Inorder(TreeNode<K,E> *);
    
    TreeNode<K,E> *root;

    class LinkedStack;
};

// Insert 함수
template <typename K, typename E>
void BST<K,E>::Insert(const pair<K,E> &thePair)
{
  BST<K,E>::LinkedStack stack;
  TreeNode<K,E> *p = root, *pp = 0;
  while (p) {
    pp = p;
    if (thePair.first < p->data.first) {
      p = p->leftChild;
      stack.push(pp);   // leftSize가 증가하는 노드만 골라내기
    }
    else if (thePair.first > p->data.first) p = p->rightChild;
    else { p->data.second = thePair.second; return;}  // Key 값이 같으면 Element 갱신
  }

  p = new TreeNode<K,E>(thePair);
  if (root) {
    if (thePair.first < pp->data.first) pp ->leftChild = p;
    else pp->rightChild = p;
    while (stack.isEmpty()) {
      TreeNode<K,E>* temp = stack.Top();
      temp->leftSize++;
      stack.pop();
    }
  }
  else root = p;
}

// 중위 순회 Inorder 함수(public)
template <typename K,typename E>
void BST<K,E>::Inorder() { Inorder(root); }

// 중위 순회 Inorder 함수(private)
template <typename K, typename E>
void BST<K,E>::Inorder(TreeNode<K,E> *currentNode)
{
  if (currentNode) {
    Inorder(currentNode->leftChild);
    Visit(currentNode);
    Inorder(currentNode->rightChild);
  }
}

// Visit 함수(print)
template <typename K, typename E>
void BST<K,E>::Visit(TreeNode<K,E> *currentNode) {
  cout << currentNode->data.first << " " << currentNode->data.second << endl;
}

// 연결 스택
template <typename K, typename E>
class BST<K,E>::LinkedStack {
  private:
    // 연결 스택 노드
    struct Node {
      TreeNode<K,E>* data;
      Node* next;

      Node(const TreeNode<K,E>*& data) : data(data), next(0) {}
    };

    Node* top;

  public:
    LinkedStack() : top(0) {}
    ~LinkedStack() { while (!isEmpty()) { pop(); } }

    void push(const TreeNode<K,E>*& element) {
      Node* newNode = new Node(element);
      newNode->next = top;
      top = newNode;
    }

    void pop() {
      if (isEmpty()) throw "Stack is empty.";
      Node* temp = top;
      top = top->next;
      delete temp;
    }

    TreeNode<K,E>*& Top() const {
      if (isEmpty()) throw "Stack is empty.";
      return top->data;
    }
    
    bool isEmpty() const { return top == 0; }
};