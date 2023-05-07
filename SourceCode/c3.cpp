Program 3.1:Selection sort using templates
===============================================
 1 template <class T>
 2 void SelectionSort (T *a, const int n)
 3 {// Sort a[0] to a[n-1] into nondecreasing order.
 4   for ( int i = 0; i < n ; i++ )
 5   {
 6      int j = i;
 7      // find smallest integer in a[i] to a[n-1]
 8      for ( int k = i + 1 ; k < n ; k++ )
 9        if (a[k] < a[j]) j = k ;
10      swap(a[i],a[j]);
11   }
12 }
===============================================




Program 3.2:Code fragment illustrating template instantiation
===============================================
float farray[100];
int intarray[250];
 .
 .
// assume that the arrays are initialized at this point
SelectionSort(farray, 100);
SelectionSort(intarray, 250);
===============================================




Program 3.3:Template function to change the size of a 1-dimenaional array
===============================================
template <class T>
void ChangeSize1D(T*& a, const int oldSize, const int newSize)
{
  if (newSize < 0) throw "New length must be >= 0";
  
  T* temp = new T[newSize];                                  // new array
  int number = min(oldSize, newSize);  // number to copy
  copy(a, a + number, temp);
  delete [] a;                             // deallocate old memory
  a = temp;
}
===============================================






Program 3.4:Definition of the class Bag containing integers
===============================================
class Bag
{
public:
  Bag (int bagCapacity = 10); // constructor
  ~Bag(); // destructor
  
  int Size() const;  // return number of elements in bag
  bool IsEmpty() const; // return true if the bag is empty; false otherwise
  int Element() const;  // return an element that is in the bag
  
  void Push(const int);    // insert an integer into the bag
  void Pop(); // delete an integer from the bag

private:
  int *array;
  int capacity; // capacity of array
  int top; // array position of top element
};
===============================================






Program 3.5:Implementation of operations of Bag
===============================================
Bag::Bag (int bagCapacity): capacity ( bagCapacity ) {
  if (capacity < 1) throw "Capacity must be > 0";
  array = new int[capacity];
  top = -1;
}

Bag::~Bag() { delete [ ] array;}

inline int Bag::Size() const {return top+1;}

inline bool Bag::IsEmpty() const {return size == 0;}

inline int Bag::Element() const {
  if (IsEmpty()) throw "Bag is empty";
  return array[0];
}

void Bag::Push(const int x) {
  if (capacity ==top+1) ChangeSize1D(array, capacity, 2 * capacity);
  capacity *=2;
  array[++top] = x;
}

void Bag::Pop() {
  if (IsEmpty()) throw "Bag is empty, cannot delete";
  int deletePos = "top" / 2;
  copy(array+deletePos+1,array+top+1,array+deletePos);
      // compact array
  top--;
}
===============================================






Program 3.6:Definition of template class Bag
===============================================
template <class T>
class Bag
{
public:
  Bag (int bagCapacity = 10);
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
===============================================





Program 3.7:Implementation of some operations of Bag
===============================================
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
===============================================





ADT 3.1:Abstract data type Stack
===============================================
template <class T>
class Stack
{ // A finite ordered list with zero or more elements.
public:
  Stack (int stackCapacity = 10);
  // Create an empty stack whose initial capacity is stackCapacity.
  
  bool IsEmpty() const;
  // If number of elements in the stack is 0, return true else return false.
  
  T& Top() const;
  // Return top element of stack.
  
  void Push (const T& item);
  // Insert item into the top of the stack.
  
  void Pop();
  // Delete the top element of the stack.
};
===============================================





Page 136
===============================================
private:
  T *stack;                // array for stack elements
  int top;    // array position of top element
  int capacity;    // capacity of stack array

template <class T>
Stack<T>::Stack (int stackCapacity) : capacity (stackCapacity)
{
  if (capacity < 1) throw "Stack capacity must be > 0";
  stack = new T[capacity];
  top = -1;
}
===============================================




Page 137
===============================================
template <class T>
inline bool  Stack<T>::IsEmpty() const { return top == -1;}

template <class T>
inline T&  Stack<T>::Top() const
{
  if (IsEmpty()) throw "Stack is empty";
  return stack[top];
}
===============================================







Program 3.8:Adding to a stack
===============================================
template <class T>
void Stack<T>::Push (const T& x)
{// Add x to the stack.
  if (top ==capacity-1)
  {
    ChangeSize1D(stack, capacity,2 * capacity);
    capacity*=2;
  }
  stack[++top] = x;
}
===============================================




Program 3.9:Deleting from a stack
===============================================
template <class T>
void Stack<T>::Pop()
{// Delete top element from the stack.
  if (IsEmpty()) throw "Stack is empty. Cannot delete.";
  stack[top--].~T();   // destructor for T
}
===============================================






ADT 3.2:Abstract data type Queue
===============================================
template <class T>
class Queue
{ // A finite ordered list with zero or more elements.
public:
  Queue(int queueCapacity = 10);
  // Create an empty queue whose initial capacity is queueCapacity
  
  bool IsEmpty( ) const;
  // If number of elements in the queue is 0, return true else return false.
  
  T& Front() const;
  // Return the element at the front of the queue.
  
  T& Rear() const;
  // Return the element at the rear of the queue.
  
  void Push (const T& item);
  // Insert item at the rear of the queue.
  
  void Pop();
  // Delete the front element of the queue.
};
===============================================






Page 143
===============================================
if (rear == capacity - 1) rear = 0;
else rear++;
===============================================






Page 143
===============================================
private:
  T *queue;           // array for queue elements
  int front,          // one counterclockwise from front
  rear,               // array position of rear element
  capacity;           // capacity of queue array

template <class T>
Queue<T>::Queue (int queueCapacity) : capacity (queueCapacity)
{
  if (capacity < 1) throw "Queue capacity must be > 0";
  queue = new T[capacity];
  front = rear = 0;
}
===============================================






Page 143
===============================================
template <class T>
inline bool Queue<T>::IsEmpty() {return front == rear;}

template <class T>
inline T& Queue<T>::Front()
{
  if (IsEmpty()) throw "Queue is empty. No front element";
  return queue[(front+1)%capacity];
}

template <class T>
inline T& Queue<T>::Rear()
{
  if (IsEmpty()) throw "Queue is empty. No rear element";
  return queue[rear];
}
===============================================





Program 3.10:Adding to a queue
===============================================
template <class T>
void Queue<T>::Push(const& x)
{// Add x at rear of queue.
  if ((rear+1) % capacity == front)
  {// queue full, double capacity
    // code to double queue capacity comes here
  }
  
  rear = (rear + 1) % capacity;
  queue[rear] = x;
}
===============================================






Program 3.11:Doubling queue capacity
===============================================
// allocate an array with twice the capacity
T* newQueue = new T[ 2 * capacity];

// copy from queue to newQueue
int start = (front +1) %capacity;
if (start < 2)
  // no wrap around
  copy(queue+start, queue+start+capacity-1, newQueue);
else
{// queue wraps around
  copy(queue+start, queue+capacity, newQueue);
  copy(queue, queue+rear+1, newQueue+capacity-start);
}

// switch to newQueue
front = 2 * capacity-1;   //2배 늘렸으니까 배열은 0부터 시작이니까
rear = capacity-2;        
capacity *= 2;
delete [] queue;
queue = newQueue;
===============================================






Program 3.12:Deleting from a queue
===============================================
template <class T>
void Queue<T>::Pop()
{// Delete front element from queue.
  if (IsEmpty()) throw "Queue is empty. Cannot delete.";
  front = (front + 1) % capacity;
  queue[front].~T();   // destructor for T
}
===============================================





Program 3.13:Definition of Bag and Stack
===============================================
class Bag
{
public:
  Bag (int bagCapacity = 10);
  virtual ~Bag();
  
  virtual int Size() const; 
  virtual bool IsEmpty() const; 
  virtual int Element() const; 
  
  virtual void Push(const int);
  virtual void Pop();
protected:
  int *array;
  int capacity;
  int top;
};

class Stack : public Bag
{
public:
  Stack (int stackCapacity = 10);
  ~Stack();
  int Top() const;
  void Pop();
};
===============================================







Program 3.14:Implementation of Stack operations
===============================================
Stack::Stack (int stackCapacity) : Bag(stackCapacity) { }
// Constructor for Stack calls constructor for Bag.

Stack::~Stack() { }
// Destructor for Bag is automatically called when Stack
// is destroyed. This ensures that array is deleted.

int Stack::Top() const
{
  if (IsEmpty()) throw "Stack is empty.";
  return array[top];
}

void Stack::Pop()
{
  if (IsEmpty()) throw "Stack is empty. Cannot delete.";
  top--;
}
===============================================







Page 150
===============================================
Bag b(3); // uses Bag constructor to create array of capacity 3
Stack s(3); // uses Stack constructor to create array of capacity 3

b.Push(1); b.Push(2); b.Push(3);
// use Bag::Push.

s.Push(1); s.Push(2) ; s.Push(3);
// Stack::Push not defined, so use Bag::Push.

b.Pop(); // uses Bag::Pop, which calls Bag::IsEmpty
s.Pop();
// uses Stack::Pop, which calls Bag::IsEmpty because IsEmpty
// has not been redefined in Stack.
===============================================






Page 154
===============================================
struct offsets
{
  int a, b ;
};

enum directions { N, NE, E, SE, S, SW, W, NW };
offsets move[8] ;
===============================================






Program 3.15:First pass at finding a path through a maze
===============================================
initialize list to the maze entrance coordinates and direction east;
while (list is not empty)
{
  (i,j,dir) = coordinates and direction from end of list;
  delete last element of list;
  while (there are more moves from (i,j))
  {
    (g,h) = coordinates of next move;
    if (( g == m ) && ( h == p )) success;
    if ( (!maze[g][h])  // legal move
       && (!mark[g][h])  // haven't been here before
    {
      mark[g][h] = 1;
      dir = next direction to try;
      add (i,j, dir) to end of list;
      (i,j,dir) = (g,h,N);
    }
  }
}
cout << "No path in maze." << endl;
===============================================




Program 3.16:Finding a path through a maze
===============================================
void Path(const int m, const int p)
{// Output a path (if any) in the maze; maze[0][i] = maze[m+1][i] =
// maze[j][0] = maze[j][p+1] = 1, 0 <= i <= p+1, 0 <= j <= m+1.
  
  // start at (1,1)
  mark[1][1] = 1;
  Stack<Items> stack(m*p);
  Items temp(1, 1, E);
    // set temp.x, temp.y, and temp.dir
  stack.Push(temp);
  
  while (!stack.IsEmpty())
  {// stack not empty
    temp = stack.Top();
    stack.Pop(); // unstack
    int i = temp.x; int j = temp.y; int d = temp.dir; //처음에 d = 2 (E == 2이므로)가 저장.
    while (d < 8) // move forward
    {
      int g = i + move[d].a; int h = j + move[d].b;
      if ((g == m) && (h == p)) { // reached exit, 종점에 도착했다면
        // output path
        cout << stack;  //stack은 자료형이 stack이라서 그냥 출력이 안 됨. 연산자 오버로딩 해줘야 됨.
        cout << i << " " << j << endl; // last two squares on the path
        cout << m << " " << p << endl;
        return;
      }
      if ((!maze[g][h]) && (!mark[g][h])) { // new position (!길이없거나 && !방문했던 곳이거나) (부정문인 거 주의!!)
        mark[g][h] = 1;
        temp.x = i;  temp.y = j; temp.dir = d+1;
        stack.Push(temp); // stack it
        i = g; j = h; d = N; // move to (g,h)
      }
      else d++; // try next direction
    }
  }
  cout << "No path in maze." << endl;
}
===============================================





Page 155
===============================================
struct Items {
  int x, y, dir ;
};
===============================================






Program 3.17:Overloading <<
===============================================
template <class T>
ostream& operator<<(ostream& os, Stack<T>& s)
{
  os << "top = " << s.top << endl;
  for (int i = 0 ; i <= s.top; i++)
    os << i << ":" << s.stack[i] << endl;
  return os;
}

ostream& operator<<(ostream& os, Items& item)
{
  return os << item.x << "," << item.y << ","  << item.dir;
}
===============================================






Program 3.18:Evaluating postfix expressions
===============================================
void Eval(Expression e)
{// Evaluate the postfix expression e. It is assumed that the last token (a token
// is either an operator, operand, or '#') in e is '#.' A function NextToken is
// used to get the next token from e. The function uses the stack stack
  Stack<Token> stack;   // initialize stack
  for (Token x = NextToken(e) ; x != '#'; x = NextToken(e))
    if (x is an operand) stack.Push(x)  // add to stack
    else {// operator

       remove the correct number of operands for operator
       x from stack; perform the operation x and store the
       result (if any) onto the stack;
    }
}
===============================================






Program 3.19:Converting from infix to postfix form
===============================================
void Postfix (Expression e)
{// Output the postfix form of the infix expression e. NextToken
// is as in function Eval (?P{9}). It is assumed that
// the last token in e is `#.' Also, `#' is used at the bottom of the stack
  Stack<Token> stack; // initialize stack
  stack.Push('#');
  for (Token x = NextToken(e); x != '#'; x = NextToken(e))
    if (x is an operand)  cout << x;
    else if (x == ')')
      {// unstack until '('
        for (; stack.Top() != '('; stack.Pop())
          cout << stack.Top();
        stack.Pop(); // unstack '('
      }
    else { // x is an operator
      for (; isp(stack.Top()) <= icp(x); stack.Pop())
        cout << stack.Top();
      stack.Push(x);
    }
  
  // end of expression; empty the stack
  for (; !stack.IsEmpty(); cout << stack.Top(), stack.Pop());
  cout << endl;
}
===============================================


