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
    BST() : root(0) {}
    void Insert(const pair<K,E>&);
    void Inorder();
    void Delete(const K&);
    pair<K,E>* Get(const K&);
    pair<K,E>* Rank(int);
    
  private:
    void Visit(TreeNode<K,E> *);
    void Inorder(TreeNode<K,E> *);
    pair<K,E>* Get(TreeNode<K,E> *, const K&);

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
      stack.push(pp);       // 추가될 노드의 부모 노드를 스택에 저장
    }
    else if (thePair.first > p->data.first) p = p->rightChild;
    else { p->data.second = thePair.second; return;}  // Key 값이 같으면 Element 갱신
  }

  p = new TreeNode<K,E>(thePair);
  if (root) {
    if (thePair.first < pp->data.first) pp ->leftChild = p;
    else pp->rightChild = p;

    // 추가된 노드의 부모 노드부터 상위로 올라가면서 leftSize 값 갱신
    while (!stack.isEmpty()) {
      TreeNode<K,E>* parent = stack.pop();  
      parent->leftSize++;
    }
  }
  else root = p;
}

// 연결 스택
template <typename K, typename E>
class BST<K,E>::LinkedStack {
  private:
    // 연결 스택 노드
    struct Node {
      TreeNode<K,E>* data;
      Node* next;

      Node(TreeNode<K,E>* data) : data(data), next(0) {}
    };

    Node* top;

  public:
    LinkedStack() : top(0) {}
    ~LinkedStack() { while (!isEmpty()) { pop(); } }

    void push(TreeNode<K,E>* element) {
      Node* newNode = new Node(element);
      newNode->next = top;
      top = newNode;
    }

    TreeNode<K,E>* pop() {
      if (isEmpty()) return 0;
      TreeNode<K,E>* poppedNode = top->data;
      Node* temp = top;
      top = top->next;
      delete temp;

      return poppedNode;
    }

    bool isEmpty() const { return top == 0; }
};

// Inorder 함수(Driver)
template <typename K,typename E>
void BST<K,E>::Inorder() { Inorder(root); }

// Inorder 함수(Workhorse)
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

// Delete 함수
template <typename K, typename E>
void BST<K,E>::Delete(const K& k) {
  TreeNode<K,E>* p = root, *pp = 0;
  BST<K,E>::LinkedStack stack;

  // 삭제할 노드 탐색
  while (p && p->data.first != k) {
    pp = p;
    if (k < p->data.first) {
      p = p->leftChild;
      stack.push(pp);   // 삭제될 노드의 부모 노드를 스택에 저장
    }
    else {p = p->rightChild;}
  }

  if (!p) return;   // 삭제할 노드가 존재하지 않음

  // Case 1: 리프 원소의 삭제
  if (!p->leftChild && !p->rightChild) {
    if (!pp)         // 삭제할 노드가 루트 노드인 경우
      root = 0;
    else if (pp->leftChild == p) 
      pp->leftChild = 0;
    else 
      pp->rightChild = 0;
    delete p;
  }
  // Case 2: 하나의 자식을 가진 비리프 노드의 삭제
  else if (!p->leftChild || !p->rightChild) {
    TreeNode<K,E>* child;
    if (p->leftChild) 
      child = p->leftChild;
    else 
      child = p->rightChild;

    if (!pp)    // 삭제할 노드가 루트 노드인 경우
      root = child;
    else if (pp->leftChild == p) 
      pp->leftChild = child;
    else 
      pp->rightChild = child;
    delete p;
  }
  // Case 3: 두 개 이상의 자식을 가진 비리프 노드의 삭제
  else {
    TreeNode<K,E>* replacementParent = p;         // 대체될 노드의 부모 노드
    TreeNode<K,E>* replacement = p->rightChild;   // 대체될 노드

    while (replacement->leftChild) {              // 가장 작은 원소 탐색
      replacementParent = replacement;
      replacement = replacement->leftChild;
      stack.push(replacementParent);
    }

    p-> data = replacement->data;

    // 대체된 노드의 삭제
    if (replacementParent->leftChild == replacement) 
      replacementParent->leftChild = replacement->rightChild;
    else 
      replacementParent->rightChild = replacement->rightChild;
    delete replacement;    
  }

  // 삭제된 노드의 부모 노드부터 상위로 올라가면서 leftSize 값을 갱신
  while (!stack.isEmpty()) {
    TreeNode<K,E>* parent = stack.pop();
    parent->leftSize--;
  }
}

// Get 함수(Driver)
template <typename K, typename E>
pair<K,E>* BST<K,E>::Get(const K& k) { return Get(root, k); }

// Get 함수(Workhorse)
template <typename K, typename E>
pair<K,E>* BST<K,E>::Get(TreeNode<K,E>*p, const K& k) {
  if(!p) return 0;
  if(k < p->data.first) return Get(p->leftChild, k);
  if(k > p->data.first) return Get(p->rightChild, k);
  return &p->data;
}

// Rank 함수
template <typename K, typename E>
pair<K,E>* BST<K,E>::Rank(int r) {
  TreeNode<K,E>* curretnNode = root;
  while (curretnNode) {
    if(r < curretnNode->leftSize) curretnNode = curretnNode->leftChild;
    else if(r > curretnNode->leftSize) {
      r -= curretnNode->leftSize;
      curretnNode = curretnNode->rightChild;
    }
    else return &curretnNode->data;
  }
  return 0;
}

int main(void)
{
  BST<int, int> bst;

  // 1. 노드 추가
  bst.Insert(make_pair(33, 90));
  bst.Insert(make_pair(50, 73));
  bst.Insert(make_pair(43, 99));
  bst.Insert(make_pair(11, 82));
  bst.Insert(make_pair(24, 78));
  bst.Insert(make_pair(46, 96));
  bst.Insert(make_pair(1, 72));
  bst.Insert(make_pair(8, 88));
  bst.Insert(make_pair(36, 77));
  bst.Insert(make_pair(56, 93));
  bst.Insert(make_pair(53, 82));
  bst.Insert(make_pair(59, 100));

  // 2. 중위 순회
  cout << endl << "<< 1-2 (Insert nodes) >>" << endl << "Number Score" << endl;
  bst.Inorder();

  // 3. 번호가 50인 노드 삭제
  bst.Delete(50);

  // 4. 중위 순회
  cout << endl << "<< 3-4 (Delte(50)) >>" << endl << "Number Score" << endl;
  bst.Inorder();

  // 5. 번호가 8인 노드 삭제
  bst.Delete(8);

  // 6. 중위 순회
  cout << endl << "<< 5-6 (Delete(8)) >>" << endl << "Number Score" << endl;
  bst.Inorder();

  // 7. 번호가 56인 노드 삭제
  bst.Delete(56);

  // 8. 중위 순회
  cout << endl << "<< 7-8 (Delete(56)) >>" << endl << "Number Score" << endl;
  bst.Inorder();

  // 9. 번호가 43인 노드 출력
  cout << endl << "<< 9 (Get(43)) >>" << endl;
  pair<int, int>* getPair = bst.Get(43);
  if(getPair != 0)
    cout << "Number: " << getPair->first << ", Score: " << getPair->second << endl;
  else
    cout << "Not Exist" << endl;

  // 10. 순위가 5인 노드 출력
  cout << endl << "<< 10 (Rank(5)) >>" << endl;
  getPair = bst.Rank(5);
  if(getPair != 0)
    cout << "Number: " << getPair->first << ", Score: " << getPair->second << endl << endl;
  else
    cout << "Not Exist" <<endl;
  return 0;
}