
Page 173
===============================================
class ThreeLetterNode {
private:
 char data[3];
 ThreeLetterNode *link;
};
===============================================




Page 175
===============================================
class NodeA {
private:
  int data1;
  char data2;
  float data3;
  NodeA *linka;
  NodeB *linkb;
};

class NodeB {
private:
  int data;
  NodeB *link;
};
===============================================





Program 4.1:Composite classes
===============================================
class ThreeLetterChain; // forward declaration

class ThreeLetterNode {
friend class ThreeLetterChain;
private:
 char data[3];
 ThreeLetterNode *link;
};

class ThreeLetterChain {
public:
// Chain manipulation operations
 .
 .
private:
ThreeLetterNode *first;
};
===============================================





Program 4.2:Nested classes
===============================================
class ThreeLetterChain {
public:
 // Chain Manipulation operations
 .
 .
private:
 class ThreeLetterNode {  // nested class
 public:
 char data[3];
 ThreeLetterNode *link;
 };
 ThreeLetterNode *first;
};
===============================================







Page 180
===============================================
a = new NodeA;
b = new NodeB;
===============================================



Page 181
===============================================
class ChainNode {
friend class Chain;
public:
  ChainNode(int element = 0, ChainNode* next = 0)
     // 0 is the default value for element and next
    {data=element; link=next;}
private:
  int data;
  ChainNode *link;
};
===============================================






Program 4.3
===============================================
void Chain::Create2()
{
  // create and set fields of second node
  ChainNode* second = new ChainNode(20,0);
  
  // create and set fields of first node
  first = new ChainNode(10, second);
}
===============================================






Program 4.4:Inserting a node
===============================================
void Chain::Insert50(ChainNode *x)
{
  if (first)
    // insert after x
    x->link = new ChainNode(50,x->link); 
  else
    // insert into empty list
    first = new ChainNode(50); 
}
===============================================




Program 4.5:Deleting a node
===============================================
void Chain::Delete(ChainNode *x, ChainNode *y)
{
  if (x == first) first = first->link;
  else y->link = x->link;
  delete x;
}
===============================================





Page 187
===============================================
initialization step;
for each item in C
{
   currentItem = current item of C;
   do something with currentItem;
}
postprocessing step;
===============================================




Program 4.7:Pseudo-code for computing maximum element
===============================================
1 int x = std::numeric_limits<int>::min(); // initialization, must include <limits>
2 for each item in C
3 {
4    currentItem = current item of C; 
5    x = max(currentItem, x);              // do something
6 }
7 return x;                                // postprocessing step
===============================================




Program 4.6:Template definition of chains
===============================================
template <class T> class Chain; // forward declaration

template <class T>
class ChainNode {
friend class Chain<T>;
private:
  T data;
  ChainNode<T> *link;
};

template <class T>
class Chain {
public:
  Chain() {first = 0;}; // constructor initializing first to 0
  // Chain manipulation operations
   .
   .
private:
  ChainNode<T> *first;
};
===============================================





Page 187
===============================================
2 for (int i = 0; i < n; i++)
4 currentItem = a[i];
===============================================


Page 187
===============================================
2 for ( ChainNode<int> *ptr = first; ptr != 0; ptr = ptr ->link)
4 currentItem = ptr->data;
===============================================




Program 4.8:Using an array iterator
===============================================
void main()
{
  int x[3] = {0, 1, 2};
  
  // use a pointer y to iterate through the array x
  for (int* y = x; y != x + 3; y++)
    cout << *y << "  ";
  cout << endl;
}
===============================================





Page 189
===============================================
for (int i = 0; i != 3; i++)
  cout << x[i] << "  ";
===============================================



Page 189
===============================================
for (Iterator i = start; i != end; i++)
  cout << *i << "  ";
===============================================




Program 4.9: Possible code for STL copy function
===============================================
template <class Iterator>
void copy(Iterator start, Iterator end, Iterator to)
{// copy from [start, end) to [to, to ~+ end - start)
  while (start != end)
    {*to = *start; start++; to++;}
}
===============================================




Program 4.10:A forward iterator for chain
===============================================
class ChainIterator {
public:
  // typedefs required by C++ for a forward iterator omitted
  
  // constructor
  ChainIterator(ChainNode<T>* startNode = 0)
    {current = startNode;}
  
  // dereferencing operators
  T& operator*() const {return current->data;}
  T* operator->() const {return &current->data;}
  
  // increment
  ChainIterator& operator++()   // preincrement
    {current = current->link; return *this;}
  ChainIterator operator++(int) // postincrement
    {
      ChainIterator old = *this;
      current = current->link;
      return old;
    }
  
  // equality testing
  bool operator!=(const ChainIterator right) const
    {return current != right.current;}
  bool operator==(const ChainIterator right) const
    {return current == right.current;}
  private:
    ChainNode<T>* current;
};
===============================================





Page 190
===============================================
ChainIterator begin() {return ChainIterator(first);}
ChainIterator end() {return ChainIterator(0);}
===============================================




Page 190
===============================================
Chain<int>::ChainIterator yi = y.begin();
===============================================



Page 190
===============================================
sum = accumulate(y.begin(), y.end(), 0);
===============================================





Program 4.11:Inserting at the back of a list
===============================================
template <class T>
void Chain<T>::InsertBack(const T& e)
{
  if (first) {// nonempty chain
    last->link = new ChainNode<T>(e);
    last = last->link;
  }
  else first = last = new ChainNode<T>(e);
}
===============================================





Program 4.12:Concatenating two chains
===============================================
template <class T>
void Chain<T>::Concatenate(Chain<T>& b)
{// b is concatenated to the end of *this.
  if (first) (last->link = b.first; last = b.last;}
  else { first = b.first; last = b.last;}
  b.first = b.last = 0;
}
===============================================





Program 4.13:Reversing a list
===============================================
template <class T>
void Chain<T>::Reverse()
{// A chain is reversed so that (a sub 1 , ... , a sub n) becomes (a sub n ,  ... ,a sub 1).
  ChainNode<T> *current = first, 
  *previous = 0;  // previous trails current
  while (current) {
    ChainNode<T> *r = previous; 
    previous = current;               // r trails previous
    current = current->link;  // current moves to next node
    previous->link = r;  // link previous to preceding node
  }
  first = previous;
}
===============================================




Program 4.14:Inserting at the front of a circular list
===============================================
template <class T>
void CircularList<T>::InsertFront(const T& e)
{// Insert the element e at the front of the circular
// list *this, where last points to the last node in the list.
  ChainNode<T> *newNode = new ChainNode<T>(e);
  if (last) { // nonempty list
    newNode->link = last -> link; 
    last->link = newNode;
  }
  else { // empty list
    last = newNode;
    newNode->link = newNode;
  }
}
===============================================





Program 4.15:Getting a node
===============================================
template <class T>
ChainNode<T>* CircularList<T>::GetNode()
{//  Provide a node for use.
  ChainNode<T>* x;
  if (av) {x = av; av = av->link;}
  else x = new ChainNode<T>;
  return x;
}
===============================================






Program 4.16:Returning a node
===============================================
template <class T>
void CircularList<T>::RetNode(ChainNode<T>*&  x)
{//  Free the node pointed to by x.
  x->link = av;
  av = x;
  x = 0;
}
===============================================






Program 4.17:Deleting a circular list
===============================================
template <class KeyT>
void CircularList<T>::~CircularList()
{// Delete the circular list.
  if (last) {
      ChainNode<T>* first = last->link;
      last->link = av;    // last node linked to av
      av = first;         // first node of list becomes front of av list
      last = 0;
  }
}
===============================================






Page 199
===============================================
last->link = av;
av = first;
===============================================





Program 4.19:Adding to a linked stack
===============================================
template <class T>
void LinkedStack<T>::Push(const T& e) {
  top = new ChainNode<T>(e, top);
}
===============================================





Program 4.20:Deleting from a linked stack
===============================================
template <class T>
void LinkedStack<T>::Pop()
{// Delete top node from the stack.
  if (IsEmpty()) throw "Stack is empty. Cannot delete.";
  ChainNode<T> *delNode = top;
  top = top->link;      // remove top node
  delete delNode;     // free the node
}
===============================================






Program 4.21:Adding to a linked queue
===============================================
template <class T>
void LinkedQueue<T>::Push(const T& e)
{
  if (IsEmpty()) front = rear = new ChainNode(e, 0); // empty queue
  else rear = rear->link = new ChainNode(e, 0); // attach node and update rear
}
===============================================





Program 4.22:Deleting from a linked queue
===============================================
template <class T>
void LinkedQueue<T>::Pop()
{// Delete first element in queue.
  if (IsEmpty()) throw "Queue is empty. Cannot delete.";
  ChainNode<T> *delNode = front;
  front = front->link;      // remove first node from chain
  delete delNode;           // free the node
}
===============================================




Program 4.23:Polynomial class definition
===============================================
struct Term
{// All members of Term are public by default.
  int coef;       // coefficient
  int exp;  // exponent
  Term Set(int c, int e) {coef = c;
  exp = e; return *this;};
};

class Polynomial {
public:
  // public functions defined here
private:
  Chain<Term> poly;
};
===============================================




Program 4.24:Adding two polynomials
===============================================
 1 Polynomial Polynomial::operator+(const Polynomial& b) const
 2 {// Polynomials *this (a) and b are added and the sum returned.
 3 Term temp;
 4 Chain<Term>::ChainIterator ai ~=~ poly.begin(),
 5 bi = b.poly.begin();
 6 Polynomial c;
 7 while (ai && bi) { // current nodes are not null
 8    if (ai->exp == bi->exp)) {  //둘의 지수가 같으면(동차면)
 9       int sum = ai->coef + bi->coef;
10       if (sum) c.poly.InsertBack(temp.Set(sum, ai->exp));  //InserBack : 가장 뒤에다 노드 하나 붙여주는 함수
11       ai++; bi++;  // advance to next term
12    }
13    else if (ai->exp < bi->exp) {
14       c.poly.InsertBack(temp.Set(bi->coef,bi->exp));
15       bi++; // next term of b
16    }
17    else {
18       c.poly.InsertBack(temp.Set(ai->coef,ai->exp));
19       ai++; // next term of a
20    }
21 }
22 while (ai) {// copy rest of a  b다 끝내고 a항 떨거지들 붙여주기
23    c.poly.InsertBack(temp.Set(ai->coef,ai->exp));
24    ai++;
25 }
26 while (bi) {// copy rest of b  얘도 마찬가지
27    c.poly.InsertBack(temp.Set(bi->coef,bi->exp));
28    bi++;
29 }
30 return c;
31 }
===============================================







Program 4.25:Adding two polynomials represented as circular...
===============================================
 1 Polynomial Polynomial::operator+(const Polynomial& b) const 
 2 {// Polynomials *this (a) and b are added and the sum returned.
 3   Term temp;
 4   CircularListWithHeader<Term>::Iterator ai = poly.begin(),
 5                                          bi = b.poly.begin();
 6   Polynomial c; // assume constructor sets head->exp = -1
 7   while (1) {
 8      if (ai->exp == bi->exp) {
 9         if (ai->exp == - 1) return c;  //모조노드가 지수값을 -1값을 가진다고 가정하면 모든 항을 다 더했다는 뜻. (둘 다 연산을 마치고 모조 head노드로 돌아왔다는 뜻이니까)
10         int sum = ai->coef + bi->coef;
11         if (sum) c.poly.InsertBack(temp.Set(sum, ai->exp));
12         ai++; bi++;  // advance to next term
13      }
14      else if (ai->exp < bi->exp) { //4.24에서는 항이 남았을 때를 생각해서 while문을 한 번 더 돌렸는데, 이 코드들이 while(1)에 걸려서 다 처리해줌.
15         c.poly.InsertBack(temp.Set(bi->coef, bi->exp));
16         bi++; // next term of b
17      }
18      else {  //얘도 마찬가지.
19         c.poly.InsertBack(temp.Set(ai->coef, ai->exp));  
20         ai++; // next term of a
21      }
22   }
23 }
===============================================






Program 4.26:First version of equivalence algorithm
===============================================
void Equivalence()
{
  initialize;
  while more pairs
  {
    input the next pair (i,j);
    process this pair;
  }
  initialize for output;
  for (each object not yet output)
    output the equivalence class that contains this object;
}
===============================================







Program 4.27:A more detailed version of equivalence algorithm
===============================================
void Equivalence()
{
  read n;                  // read in number of objects
  initialize first[0:n - 1] to 0 and out[0:n - 1] to false;
  while more pairs // input pairs
  {
    read the next pair (i,j);
    put j on the chain first[i];
    put i on the chain first[j];
  }
  for (i = 0; i < n; i++)
    if (!out[i]) {
      out[i] = true;
      output the equivalence class that contains object i;
    }
}
===============================================








Program 4.28:C++ function to find equivalence classes
===============================================
class ENode {
friend void Equivalence();
public:
  ENode(int d = 0) // constructor
    {data = d; link = 0;}
private:
  int data;
  ENode *link;
};

void Equivalence()
{// Input the equivalence pairs and output the equivalence classes.
ifstream inFile( "equiv.in", ios::in); // "equiv.in" is the input file
if (!inFile) throw "Cannot open input file.";
int i, j, n;
inFile >> n;  // read number of objects
// initialize first and out
ENode **first = new ENode*[n];
bool *out = new bool [n];
// use STL function fill to initialize
fill(first,~first~+~n,~0);
fill(out,out+n, false);

// Phase 1: input equivalence pairs
inFile >> i >> j;
while (inFile.good()) {  // check end of file
first[i]  = new ENode(j, first[i]);
first[j]  = new ENode(i, first[j]);
inFile  >> i >> j;
}

// Phase 2: output equivalence classes
for (i = 0; i < n; i++)
if (!out[i]) { // needs to be output
   cout << endl << "A new class: " << i;
   out[i] = true ;
   ENode *x = first[i]; ENode *top = 0; // initialize stack
   while (1) { // find rest of class
      while (x) { // process the list
         j = x->data;
         if (!out[j]) {
            cout << ", " << j;
            out[j] = true;
            ENode *y = x->link;
            x->link = top;
            top = x;
            x = y;
         }
         else x = x->link;
      } // end of while(x)
      if (!top) break;
         x = first[top->data];
         top = top->link; // unstack
   } // end of while(1)
} // end of if (!out[i])
for (i = 0; i < n; i++)
   while (first[i]) {
      ENode *delnode = first[i];
      first[i] = delnode->link;
      delete delnode;
   }
   delete [ ] first; delete [ ] out;
} 
===============================================









Program 4.29:Class definition for sparse matrices
===============================================
struct Triple {int row, col, value;};
class Matrix; // forward declaration
class MatrixNode {
friend class Matrix;
friend istream& operator>>(istream&, Matrix&); // for reading in a matrix
private:
  MatrixNode *down , *right;
  bool head;
  union {   // anonymous union
    MatrixNode *next;
    Triple triple;
  };
  MatrixNode(bool, Triple*); // constructor
};

MatrixNode::MatrixNode(bool b, Triple* t) // constructor
{
  head = b;
  if (b) {right = down = this;} // row/column header node
  else triple = *t;  // element node or header node for list of header nodes
}

class Matrix {
friend istream& operator>>(istream&, Matrix&);
public:
  ~Matrix();  // destructor
private:
  MatrixNode *headnode;
};
===============================================







Program 4.30:Reading in a sparse matrix
===============================================
 1 istream& operator>>(istream& is, Matrix& matrix)
 2 {// Read in a matrix and set up its linked representation.
 3    Triple  s;
 4    is >> s.row >> s.col >> s.value;   // matrix dimensions
 5    int p = max(s.row, s.col);
 6    // set up header node for list of header nodes.
 7    matrix.headnode = new MatrixNode(false, &s);
 8    if (p == 0) { matrix.headnode->right = matrix.headnode; return is;}
 9    // at least one row or column
10    MatrixNode **head = new MatrixNode*[p];
11    for (int i = 0; i < p; i++)
12       head[i]  = new MatrixNode(true, 0);
13    int currentRow = 0;
14    int MatrixNode *last = head[0]; // last node in current row

15    for (i = 0; i < s.value; i++)  // input triples
16    {
17       Triple t;
18       is >> t.row >> t.col >> t.value;
19       if (t.row > currentRow) {  // close current row
20          last->right = head[currentRow];
21          currentRow = t.row;
22          last = head[currentRow];
23       } // end of if
24       last = last->right = new MatrixNode(false, &t);  // link new node into row list
25       head[t.col]->next = head[t.col]->next->down = last; // link into column list
26    } // end of for

27    last->right = head[currentRow]; // close last row
28    for (i = 0; i < s.col; i++) head[i]->next->down = head[i]; // close all column lists
29    // link the header nodes together
30    for (i = 0; i < p-1; i++) head[i]->next = head[i+1];
31       head[p-1]->next = matrix.headnode;
32    matrix.headnode->right =  head[0];
33    delete [ ] head;
34    return is;
35 }
===============================================






Program 4.31:Deleting a sparse matrix
===============================================
Matrix::~Matrix()
{// Return all nodes to the av list. This list is a chain linked via the right
// field. av is a static variable that points to the first node of the av list.
  if (!headnode) return; // no nodes to delete
  MatrixNode *x = headnode->right;
  headnode->right = av; av = headnode; // return headnode
  while (x != headnode) { // erase by rows
    MatrixNode *y = x->right;
    x->right = av;
    av = y;
    x = x->next; // next row
  }
  headnode = 0;
}
===============================================







Program 4.32:Class definition of a doubly linked list
===============================================
class DblList;

class DblListNode {
   friend class DblList;
   private:
   int data;
   DblListNode *left, *right;
};

class DblList {
public:
   // List manipulation operations
   .
   .
private:
   DblListNode *first;  // points to header node
};
===============================================








Program 4.33:Deletion from a doubly linked circular list
===============================================
void DblList::Delete(DblListNode *x)
{
   if (x == first) throw "Deletion of header node not permitted";
   else {
      x->left->right = x->right;
      x->right->left = x->left;
      delete x;
   }
}
===============================================







Program 4.34:Insertion into a doubly linked circular list
===============================================
void DblList::Insert(DblListNode *p, DblListNode *x)
{// insert node p to the right of node x
  p->left = x; p->right = x->right;
  x->right->left = p; x->right = p;
}
===============================================







Page 230
===============================================
enum Triple {var, ptr, no};
class PolyNode
{
  PolyNode *next;                  // link field
  int exp;
  Triple trio;
  union {
    char vble;
    PolyNode *down;       // link field
    int coef;
  };
};
===============================================







Page 231
===============================================
template <class T> class GenList; // forward declaration

template <class T>
class GenListNode {
friend class GenList<T>;
private:
  GenListNode<T> *next;
  bool tag;
  union {
    T data;
    GenListNode<T> *down;
  };
};

template <class T>
class GenList {
public:
  // List manipulation operations
   
private:
  GenListNode<T> *first;
};
===============================================







Program 4.35:Copying a list
===============================================
// Driver
void GenList<T>::Copy(const GenList<T>& l) const
{// Make a copy of l.
  first = Copy(l.first);
}

// Workhorse
GenListNode<T>* GenList<T>::Copy(GenListNode<T>* p)
{// Copy the nonrecursive list with no shared sublists pointed at by p.
  GenListNode<T> *q = 0;
  if (p) {
    q = new GenListNode<T>;
    q->tag = p->tag;
    if (p->tag) q->down = Copy(p->down);
    else q->data = p->data;
    q->next = Copy(p->next);
  }
  return q;
}
===============================================







Program 4.36:Determining if two lists are identical
===============================================
// Driver
template <class T>
bool operator==(const GenList<T>& l) const
{// *this and l are non-recursive lists.
// The function returns true iff the two lists are identical.
  return Equal(first, l.first);
}

// Workhorse 
bool Equal(GenListNode<T>* s, GenListNode<T> *t)
{
  if ((!s) && (!t)) return true;
  if (s && t && (s->tag == t->tag))
    if (s->tag)
      return Equal(s->down, t->down) && Equal(s->next, t->next);
    else return (s->data == t->data) && Equal(s->next, t->next);
  return false;
}
===============================================







Program 4.37:Computing the depth of a list
===============================================
// Driver
template <class T>
int GenList<T>::Depth()
{// Compute the depth of a non-recursive list.
  return Depth(first);
}

// Workhorse
template <class T>
int GenList<T>::Depth(GenListNode<T> *s)
{
  if (!s) return 0;   // empty list
  GenListNode<T> *current = s;
  int m = 0;
  while (current) {
    if (current->tag) m = max(m,~Depth(current->down));
    current = current->next;
  }
  return m+1;
}
===============================================






Page 238
===============================================
template <class T>
class GenListNode<T>
{
friend class GenList<T>;
private:
  GenListNode<T> *next;
  int tag; // 0 for data, 1 for down, 2 for ref
  union {
    T data;
    GenListNode<T> *down;
    int ref;
  };
};
===============================================








Program 4.38:Deleting a list recursively
===============================================
// Driver
template <class T>
GenList<T>::~GenList()
{// Each header node has a reference count.
  if (first)
  {
    Delete(first);
    first = 0;
  }
}

// Workhorse
void GenList<T>::Delete(GenListNode<T>* x)
{
  x->ref--;  // decrement reference count of header node.
  if (!x->ref)
  {
    GenListNode<T> *y = x; // y traverses top level of x.
    while (y->next) { y = y->next; if (y->tag == 1) Delete(y->down);}
    y->next = av;   // attach top-level nodes to av list
    av = x;
  }
}
===============================================




