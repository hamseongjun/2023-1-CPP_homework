ADT 5.1
===============================================
template <class T>
class BinaryTree
{// objects: A finite set of nodes either empty or consisting of a
// root node, left BinaryTree and right BinaryTree.
public:
  BinaryTree();
  // creates an empty binary tree
  
  bool IsEmpty();
  // return true iff the binary tree is empty
  
  BinaryTree(BinaryTree<T>& bt1, T& item, BinaryTree<T>& bt2);
  // creates a binary tree whose left subtree is bt1, whose right subtree
  // is bt2, and whose root node contains item
  
  BinaryTree<T> LeftSubtree();
  // return the left subtree of *this
  
  BinaryTree<T> RightSubtree();
  // return the right subtree of *this
  
  T RootData();
  // return the data in the root node of *this
};
===============================================







Page 257
===============================================
template <class T> class Tree; // forward declaration

template <class T>
class TreeNode {
friend class Tree<T>;
private:
  T data;
  TreeNode<T> *leftChild;
  TreeNode<T> *rightChild;
};

template <class T>
class Tree {
public:
  // Tree operations
   .
private:
  TreeNode<T> *root;
};
===============================================






Program 5.1:Inorder traversal of a binary tree
===============================================
 1 template <class T>
 2 void Tree<T>::Inorder()
 3 {// Driver calls workhorse for traversal of entire tree.  The driver is
 4 // declared as a public member function of Tree.
 5     Inorder(root);
 6 }

 7 template <class T>
 8 void Tree<T>::Inorder(TreeNode<T> *currentNode)
 9 {// Workhorse traverses the subtree rooted at currentNode.
10 // The workhorse is declared as a private member function of Tree.
11   if (currentNode) {
12     Inorder(currentNode->leftChild);
13     Visit(currentNode);
14     Inorder(currentNode->rightChild);
15   }
16 }
===============================================





Program 5.2:Preorder traversal of a binary tree
===============================================
 1 template <class T>
 2 void Tree<T>::Preorder()
 3 {// Driver.
 4     Preorder(root);
 5 }

 6 template <class T>
 7 void Tree<T>::Preorder(TreeNode<T> *currentNode)
 8 {// Workhorse.
 9   if (currentNode) {
10     Visit(currentNode);
11     Preorder(currentNode->leftChild);
12     Preorder(currentNode->rightChild);
13   }
14 }
===============================================





Program 5.3
===============================================
 1 template <class T>
 2 void Tree<T>::Postorder()
 3 {// Driver.
 4    Postorder(root);
 5 }

 6 template <class T>
 7 void Tree<T>::Postorder(TreeNode<T> *currentNode)
 8 {// Workhorse.
 9   if (currentNode) {
10     Postorder(currentNode->leftChild);
11     Postorder(currentNode->rightChild);
12     Visit(currentNode);
13   }
14 }
===============================================





Program 5.4:Nonrecursive inorder traversal
===============================================
 1 template <class T>
 2 void Tree<T>::NonrecInorder()
 3 {// Nonrecursive inorder traversal using a stack.
 4   Stack<TreeNode<T>*>  s;  // declare and initialize stack
 5   TreeNode<T> *currentNode = root;
 6   while(1) {
 7     while (currentNode) { // move down leftChild fields
 8       s.Push(currentNode);  // add to stack
 9       currentNode = currentNode->leftChild;
10     }
11     if (s.IsEmpty()) return;
12     currentNode = s.Top();
13     s.Pop(); // delete from stack
14     Visit(currentNode);
15     currentNode = currentNode->rightChild;
16   }
17 }
===============================================





Program 5.5:Definition of a simple inorder iterator class
===============================================
class InorderIterator {
public:
  InorderIterator(){currentNode = root;};
  T * Next();
private
  Stack<TreeNode<T>*> s;
  TreeNode<T> *currentNode;
};
===============================================







Program 5.6:Code for obtaining the next inorder element
===============================================
T *InorderIterator::Next()
{
  while (currentNode) {
    s.Push(currentNode);
    currentNode = currentNode->leftChild;
  }
  if (s.IsEmpty()) return 0;
  currentNode = s.Top();
  s.Pop();
  T& temp = currentNode->data;
  currentNode = currentNode->rightChild;
  return &temp;
}
===============================================






Program 5.7:Level-order traversal of a binary tree
===============================================
template <class T>
void Tree<T>::LevelOrder()
{// Traverse the binary tree in level order.
  Queue<TreeNode<T>*>  q;
  TreeNode<T> *currentNode = root;
  while (currentNode) {
    Visit(currentNode);
    if (currentNode->leftChild) q.Push(currentNode->leftChild);
    if (currentNode->rightChild) q.Push(currentNode->rightChild);
    if (q.IsEmpty()) return;
    currentNode = q.Front();
    q.Pop();
  }
}
===============================================






Program 5.8:O(1) space inorder traversal
===============================================
template <class T>
void Tree<T>::NoStackInorder()
{// Inorder traversal of binary tree using a fixed amount of additional storage.
   if (!root) return; // empty binary tree
   TreeNode<T> *top = 0, *lastRight = 0, *p, *q, *r, *r1;
   p = q = root;
   while (1) {
      while (1) {
         if ((!p->leftChild) && (!p->rightChild)) { // leaf node
            Visit(p); break;
         }
         if (!p->leftChild) { // visit p and move to p->rightChild
            Visit(p);
            r = p->rightChild; p->rightChild = q;
            q = p; p = r;
         }
         else { // move to p->leftChild
            r = p->leftChild; p->leftChild = q;
            q = p; p = r;
         }
      } // end of inner while
      // p is a leaf node, move upward to a node whose
      // right subtree has not yet been examined
      TreeNode<T> *av = p;
      while (1) {
         if (p == root) return;
         if (!q->leftChild) { // q is linked via rightChild
            r = q->rightChild; q->rightChild = p;
            p = q; q = r;
         }
         else if (!q->rightChild) { // q is linked via leftChild
            r = q->leftChild; q->leftChild = p;
            p = q; q = r;  Visit(p);
         }
         else // check if p is a rightChild of q
            if (q == lastRight) {
                r = top; lastRight = r->leftChild;
                top = r->rightChild; // unstack
                r->leftChild = r->rightChild = 0;
                r = q->rightChild; q->rightChild = p;
                p = q; q = r;
            }
            else { // p is leftChild of q
                Visit(q);
                av->leftChild = lastRight; av->rightChild = top;
                top = av; lastRight = q;
                r = q->leftChild; q->leftChild = p; // restore link to p
                r1 = q->rightChild; q->rightChild = r;
                p = r1;
                break;
            }
      } // end of inner while loop
   } // end of outer while loop
}
===============================================





Program 5.9:Copying a binary tree
===============================================
template <class T>
Tree<T>::Tree(const Tree<T>& s)  // driver
{// Copy constructor
  root = Copy(s.root);
}

template <class T>
TreeNode<T>* Tree<T>::Copy(TreeNode<T> *origNode)  // Workhorse
{// Return a pointer to an exact copy of the binary tree rooted at origNode.
  if (!origNode) return 0;
  return new TreeNode<T>(origNode->data,
  Copy(origNode->leftChild),
  Copy(origNode->rightChild));
}
===============================================





Program 5.10:Binary tree equivalence
===============================================
template <class T>
bool Tree<T>::operator==(const Tree& t) const
{
  return Equal(root, t.root);
}

template <class T>
bool Tree<T>::Equal(TreeNode<T>~ *a, TreeNode<T>~ *b)
{// Workhorse.
  if ((!a) && (!b)) return true;  // both a and b are 0
  return (a && b                // both a and b are non-zero
  && (a->data == b->data)  // data is the same
  && Equal(a->leftChild, b->leftChild) // left subtrees equal
  && Equal(a->rightChild, b->rightChild)); // right subtrees equal
}
===============================================





Program 5.11:First version of satisfiablity algorithm
===============================================
for each of the 2 sup n possible truth value combinations for the n variables
{
  replace the variables by their values in the current truth value combination;
  evaluate the formula by traversing the tree it points to in postorder;
  if (formula.Data().second()) { cout << current combination; return;}
}
cout << "no satisfiable combination";
===============================================





Program 5.12:Visiting a node in an expression tree
===============================================
//  visit the node pointed at by p
switch (p->data.first) {
  case Not: p->data.second = !p->rightChild->data.second; break;
  case And: p->data.second =
      p->leftChild->data.second && p->rightChild->data.second;
  break;
  case Or: p->data.second =
      p->leftChild->data.second || p->rightChild->data.second;
  break;
  case True: p->data.second = true; break;
  case False: p->data.second = false;
}
===============================================





Program 5.13:Finding the inorder successor in a threaded binary tree
===============================================
T* ThreadedInorderIterator::Next()
{// Return the inorder successor of currentNode in a threaded binary tree
  ThreadedNode<T> *temp = currentNode->rightChild;
  if (!currentNode->rightThread)
    while (!temp->leftThread) temp = temp->leftChild;
  currentNode = temp;
  if (currentNode == root) return 0;
  else return &currentNode->data;
}
===============================================







Program 5.14:Inserting r as the right child of s
===============================================
template <class T>
void ThreadedTree<T>::InsertRight(ThreadedNode<T> *s, ThreadedNode<T> *r)
{// Insert r as the right child of s.
  r->rightChild = s->rightChild;
  r->rightThread = s->rightThread;
  r->leftChild = s;
  r->leftThread = true; // leftChild is a thread
  s->rightChild = r;
  s->rightThread = false;
  if (! r->rightThread) {
    ThreadedNode<T> *temp = InorderSucc(r);
         // returns the inorder successor of r
    temp->leftChild = r;
  }
}
===============================================






ADT 5.2:A max priority queue
===============================================
template <class T>
class MaxPQ {
public:
  virtual ~MaxPQ() {}
    // virtual destructor
  virtual bool IsEmpty() const = 0;
    // return true iff the priority queue is empty
  virtual const T& Top() const = 0;
    // return reference to max element
  virtual void Push(const T&) = 0;
    // add an element to the priority queue
  virtual void Pop() = 0;
    // delete element with max priority
};
===============================================





Page 282
===============================================
private:
  T *heap;                 //  element array
  int heapSize; // number of elements in heap
  int capacity; // size of the array heap
===============================================





Program 5.15:Max heap constructor
===============================================
template <class T>
MaxHeap<T>::MaxHeap (int theCapacity = 10)
{
  if (theCapacity < 1) throw "Capacity must be >= 1.";
  capacity = theCapacity;
  heapSize = 0;
  heap = new T[capacity + 1]; // heap[0] is not used
}
===============================================





Program 5.16:Insertion into a max heap
===============================================
template <class T>
void MaxHeap<T>::Push(const T& e)
{// Insert e into the max heap.
  if (heapSize == capacity) {// double the capacity
    ChangeSize1D(heap, capacity, 2 * capacity);
    capacity *=2;
  }
  int currentNode = ++heapSize;
  while (currentNode != 1 && heap[currentNode / 2] < e)
  {// bubble up
    heap[currentNode] = heap[currentNode/2];  // move parent down
    currentNode /= 2; // move to parent
  }
  heap[currentNode] = e;
}
===============================================






Program 5.17:Deletion from a max heap
===============================================
template <class T>
void MaxHeap<T>::Pop()
{// Delete max element.
  if (IsEmpty()) throw "Heap is empty. Cannot delete.";
  heap[1].~T();   // delete max element
  
  // remove last element from heap
  T lastE = heap[heapSize--];
  
  // trickle down
  int currentNode = 1;   // root
  int child =2; // a child of currentNode
  while (child <= heapSize)
  {
    // set child to larger child of currentNode
    if (child < heapSize && heap[child] < heap[child+1]) child++;
    
    // can we put lastE in currentNode?
    if (lastE >= heap[child]) break;   // yes
    
    // no
    heap[currentNode] = heap[child];              // move child up
    currentNode = child; child *= 2;   // move down a level
  }
  heap[currentNode] = lastE;
}
===============================================






ADT 5.3:A dictionary
===============================================
template <class K, class E>
class Dictionary {
public:
  virtual bool IsEmpty() const = 0;
    // return true iff the dictionary is empty
  virtual pair<K,E>* Get(const K&) const = 0;
    // return pointer to the pair with specified key; return 0 if no such pair
  virtual void Insert(const pair<K,E>&) = 0;
    // insert the given pair; if key is a duplicate update associated element
  virtual void Delete(const K&) = 0;
    // delete pair with specified key
};
===============================================





Program 5.18:Recursive search of a binary search tree
===============================================
template <class K, class E>  // Driver
pair<K,E>* BST<K,E>::Get(const K& k)
{// Search the binary search tree (*this) for a pair with key k.
// If such a pair is found, return a pointer to this pair; otherwise, return 0.
  return Get(root, k);
}

template <class K, class E>  // Workhorse
pair<K,E>* BST<K,E>::Get(TreeNode<pair<K,E> >* p, const K& k)
{
  if (!p) return 0;
  if (k < p->data.first) return Get(p->leftChild,k);
  if (k > p->data.first) return Get(p->rightChild,k);
  return &p->data;
}
===============================================





Program 5.19:Iterative search of a binary search tree
===============================================
template <class K, class E>  // Iterative version
pair<K,E>* BST<K,E>::Get(const K& k)
{
  TreeNode<pair<K,E> > *currentNode = root;
  while (currentNode)
    if (k < currentNode->data.first)
      currentNode = currentNode->leftChild;
    else if (k > currentNode->data.first)
      currentNode = currentNode->rightChild;
    else return &currentNode->data;
  }
  
  // no matching pair
  return 0;
}
===============================================






Program 5.20:Searching a binary search tree by rank
===============================================
template <class K, class E>  // search by rank
pair<K,~E>* BST<K,~E>::RankGet(int r)
{// Search the binary search tree for the rth smallest pair.
TreeNode<pair<K,E> > *currentNode = root;
while (currentNode)
  if (r < currentNode->leftSize) currentNode = currentNode->leftChild;
  else if (r > currentNode->leftSize)
  {
    r -= currentNode->leftSize;
    currentNode = currentNode->rightChild;
  }
  else return &currentNode->data;
return 0;
}
===============================================





Program 5.21:Insertion into a binary search tree
===============================================
template <class K, class E>
void BST<K,E>::Insert(const pair<K,E>& thePair)
{// Insert thePair into the binary search tree.
// search for thePair.first, pp is parent of p
   TreeNode<pair<K,E> > *p = root, *pp = 0;
   while (p) {
      pp = p;
      if (thePair.first < p->data.first) p = p->leftChild;
      else if (thePair.first > p->data.first) p = p->rightChild;
      else //  duplicate, update associated element
        {p->data.second = thePair.second; return;}
   }

   // perform insertion
   p = new TreeNode<pair<K,E> > (thePair);
   if (root)  // tree not empty
      if (thePair.first < pp->data.first) pp->leftChild = p;
      else pp->rightChild = p;
   else root = p;
}
===============================================





Program 5.22:Splitting a binary search tree
===============================================
template <class K, class E> 
void BST<K,E>::Split(const K& k, BST<K,E>& small,
pair<K,E>*& mid, BST<K,E>& big)
{// Split the binary search tree with respect to key k.
   if (!root) {small.root = big.root = 0; return;} // empty tree
   // create header nodes for small and big
   TreeNode<pair<K,E> > *sHead = new TreeNode<pair<K,E> >,
                        *s = sHead,
                        *bHead = new TreeNode<pair<K,E> >,
       			    *b = bHead,
                        *currentNode = root;
   while (currentNode)
      if (k < currentNode->data.first) {// add to big
         b->leftChild = currentNode;
         b = currentNode; currentNode = currentNode->leftChild;
      }
      else if (k > currentNode->data.first) {// add to small
         s->rightChild = currentNode;
         s = currentNode; currentNode = currentNode->rightChild;
      }
      else {// split at currentNode
         s->rightChild = currentNode->leftChild;
         b->leftChild = currentNode->rightChild;
         small.root = sHead->rightChild; delete sHead;
         big.root = bHead->leftChild; delete bHead;
         mid = new pair<K,E>(currentNode->data.first,
               currentNode->data.second);
         delete currentNode;
         return;
      }
      // no pair with key k
   s->rightChild = b->leftChild = 0;
   small.root = sHead->rightChild; delete sHead;
   big.root = bHead->leftChild; delete bHead;
   mid = 0;
   return;
}
===============================================






Program 5.23:Class definition and constructor for Sets
===============================================
class Sets {
public:
   // set operations follow
   .
   .
private:
   int *parent;
   int n; // number of set elements
};

Sets::Sets(int numberOfElements)
{
   if (numberOfElements < 2) throw "Must have at least 2 elements.";
   n = numberOfElements;
   parent = new int[n];
   fill(parent, parent+n, -1);
}
===============================================





Program 5.24:Simple functions for union and find
===============================================
void Sets::SimpleUnion(int i, int j)
{// Replace the disjoint sets with roots i and j, i != j with their union.
   parent[i] = j;
}

int Sets::SimpleFind(int i)
{// Find the root of the tree containing element i.
   while (parent[i] >= 0) i = parent[i];
      return i;
}
===============================================






Program 5.25:Union functions with weighting rule
===============================================
void Sets::WeightedUnion(int i, int j)
// Union sets with roots i and j, i != j, using the weighting rule.
// parent[i]=-count[i] and parent[j]=-count[j].
{
   int temp = parent[i] + parent[j];
   if (parent[i] > parent[j]) { // i has fewer nodes
      parent[i] = j;
      parent[j] = temp;
   }
   else { // j has fewer nodes (or i and j have the same number of nodes)
      parent[j] = i;
      parent[i] = temp;
   }
}
===============================================





Program 5.26:Collapsing rule
===============================================
int Sets::CollapsingFind(int i)
{// Find the root of the tree containing element i.
// Use the collapsing rule to collapse all nodes from i to the root.
   for (int r = i; parent[r] >= 0; r = parent[r]); // find root
   while (i != r) {// collapse
      int s = parent[i];
      parent[i] = r;
      i = s;
   }
   return r;
}
===============================================


