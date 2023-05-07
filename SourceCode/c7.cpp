Program 7.1:Sequential search
====================================
template <class E, class K>
int SeqSearch (E *a, const int n, const K& k)
{// Search a[1:n] from left to right.  Return least i such that
// the key of a[i] equals k.  If there is no such i, return 0.
  int i;
  for (i = 1; i <= n && a[i] ! =  k; i+ +);
  if (i > n) return 0;
  return i;
}
====================================






Program 7.2:Verifying two lists using a sequencial search
====================================
void Verify1(Element *l1, Element *l2, const int n, const int m)
{// Compare two unordered lists l1 and l2 of size n and m, respectively.
  bool *marked = new bool [m+1];
  fill(marked + 1,marked+m+1, false);
  
  for (i = 1; i <= n; i++)
  {
    int j = SeqSearch(l2, m, l1[i]);
    if (j == 0) cout << l1[i] << " not in l2 " << endl; // satisfies (1)
    else
    {
      if (!Compare(l1[i], l2[j]) // satisfies (3)
        cout << "Discrepancy in " << l1[i] << endl;
      marked[j] = true; // mark l2[j] as being seen
    }
  }
  for (i = 1; i <= m; i++)
    if (! marked[i]) cout << l2[i] << " not in l1. " << endl; // satisfies (2)
  delete [ ] marked ;
}
====================================







Program 7.3:Fast verification of two lists
====================================
void Verify2(Element *l1, Element *l2, const int n, const int m)
{// Same task as Verify1. However, this time we first sort l1 and l2.
  Sort(l1, n);   // sort into increasing order of key
  Sort(l2, m);
  int i = 1, j = 1;
  while (( i <= n) && (j <= m))
    if (l[i] < l[j])
    {
      cout << l1[i] << " not in l2" << endl;
      i++;
    }
    else if (l[i] > l[j])
    {
      cout << l2[j] << " not in l1" << endl;
      j++;
    }
    else
    {// equal keys
      if (!Compare(l1[i], l2[j]))
        cout << "Discrepancy in " << l1[i] <<endl;
      i++; j++;
    }
  if (i <= n) OutputRest(l1, i, n, 1);             // output records i through n of l1
  else if (j <= m) OutputRest(l2, j, m, 2); // output records j through m of l2
}
====================================






Program 7.4:Insertion into a sorted list
====================================
template <class T>
void Insert(const T& e, T *a, int i)
{// Insert e into the ordered sequence a[1:i] such that the
// resulting sequence a[1:i+1] is also ordered.
// The array a must have space allocated for at least i+2 elements.
  a[0] = e;
  while (e < a[i])
  {
    a[i+1] = a[i];
    i--;
  }
  a[i+1] = e;
}
====================================






Program 7.5:Insertion sort
====================================
template <class T>
void InsertionSort(T *a, const int n)
{// Sort a[1:n] into nondecreasing order.
  for (int j = 2; j <= n; j++) {
    T temp = a[j];
    Insert(temp, a, j-1);
  }
}
====================================






Program 7.6:Quick Sort
====================================
template <class T>
void QuickSort(T *a, const int left, const int right)
{// Sort a[left:right] into nondecreasing order.
// a[left] is arbitrarily chosen as the pivot. Variables i and j
// are used to partition the subarray so that at any time a[m] < =pivot, m < i,
// and a[m] >= pivot, m > j.  It is assumed that a[left] <= a[right+ 1].
  if (left < right) {
    int i = left,
    j = right + 1,
    pivot = a[left];
    do {
      do i++; while (a[i] < pivot);
      do j--; while (a[j] > pivot);
      if (i < j) swap(a[i], a[j]);
    } while (i < j);
    swap(a[left], a[j]);
    
    QuickSort(a, left, j-1);
    QuickSort(a, j+1, right);
  }
}
====================================





Program 7.7:Merging two sorted lists
====================================
template <class T>
void Merge(T *initList, T *mergedList, const int l, const int m, const int n)
{// initList[l:m] and initList[m+1:n] are sorted lists.  They are merged to obtain
// the sorted list mergedList[l:n].
  for (int i1 = l, iResult = l, i2 = m+1;  // i1, i2, and iResult are list positions
   i1 <= m && i2 <= n; // neither input list is exhausted
   iResult++)
    if (initList[i1] <= initList[i2])
    {
      mergedList[iResult] = initList[i1];
      i1++;
    }
    else
    {
      mergedList[iResult] = initList[i2];
      i2++;
    }
  // copy remaining records, if any, of first list
  copy(initList+i1, initList+m+1, mergedList+iResult);
  
  // copy remaining records, if any, of second list
  copy(initList + i2, initList + n + 1, mergedList + iResult);
}
====================================





Program 7.8:Merge pass
====================================
template <class T>
void MergePass(T *initList, T *resultList, const int n, const int s)
{// Adjacent pairs of sublists of size s are merged from
// initList to resultList. n is the number of records in initList.
  for (int i = 1; // i is first position in first of the sublists being merged
  i <= n mi 2*s + 1; // enough elements for two sublists of length s?
  i += 2*s)
    Merge(initList, resultList, i, i + s - 1, i + 2 * s - 1);
  
  // merge remaining list of size < 2 * s
  if ((i + s - 1) < n) Merge(initList, resultList, i, i + s - 1, n);
  else copy(initList + i, initList + n + 1, resultList + i);
}
====================================







Program 7.9:Merge Sort
====================================
template <class T>
void MergeSort(T *a, const int n)
{// Sort a[1:n] into nondecreasing order.
  T *tempList = new T[n+1];
  // l is the length of the sublist currently being merged
  for (int l = 1; l < n; l *= 2)
  {
    MergePass(a, tempList, n, l);
    l *= 2;
    MergePass(tempList, a, n, l); // interchange role of a and tempList
  }
  delete [ ] tempList;
}
====================================







Program 7.10:Recursive Merge Sort
====================================
template <class T>
int rMergeSort(T* a, int* link, const int left, const int right)
{// a[left:right] is to be sorted. link[i] is initially 0 for all i.
// rMergeSort returns the index of the first element in the sorted chain.
  if (left >= right) return left;
  int mid = (left + right) / 2;
  return ListMerge(a, link,
  rMergeSort(a, link, left, mid),            // sort left half
  rMergeSort(a, link, mid + 1, right)); // sort right half
}
====================================






Program 7.11:Merging sorted chains
====================================
template <class T>
int ListMerge(T* a, int* link, const int start1, const int start2)
{// The sorted chains beginning at start1 and start2, respectively, are merged.
// link[0] is used as a temporary header.  Return start of merged chain.
  int iResult = 0; // last record of result chain
  for (int i1 = start1, i2 = start2; i1 && i2; )
    if (a[i1] <= a[i2]) {
      link[iResult] = i1;
      iResult = i1; i1 = link[i1];
    }
    else {
      link[iResult] = i2;
      iResult = i2; i2 = link[i2];
    }
  
  // attach remaining records to result chain
  if (i1 == 0) link[iResult] = i2;
  else link[iResult] = i1;
  return link[0];
}
====================================




Program 7.13:Adjusting a max heap
====================================
template <class T>
void Adjust(T *a, const int root, const int n)
{// Adjust binary tree with root root to satisfy heap property. The left and right
// subtrees of root already satisfy the heap property.  No node index is > n.
  T e = a[root];
  // find proper place for e
  for (int j = 2*root; j <= n; j *= 2) {
    if (j < n && a[j] < a[j+1]) j++;  // j is max child of its parent
    if (e >= a[j]) break; // e may be inserted as parent of j
    a[j/2] = a[j]; // move jth record up the tree
  }
  a[j/2] = e;
}
====================================




Program 7.14:Heap Sort
====================================
template <class T>
void HeapSort(T *a, const int n)
{// Sort a[1:n]) into nondecreasing order.
  for (int i = n/2; i >= 1; i--) // heapify
    Adjust(a, i, n);
  
  for (i = n-1; i >= 1; i--)  // sort
  {
    swap(a[1], a[i+1]);            // swap first and last of current heap
    Adjust(a, 1, i);  // heapify
  }
}
====================================





Program 7.15:LSD Radix Sort
====================================
template <class T>
int RadixSort(T *a, int *link, const int d, const int r, const int n)
{// Sort a[1:n]) using a d-digit radix-r sort. digit(a[i],j,r) returns the jth radix-r
// digit (from the left) of a[i]'s key. Each digit is in the range is [0,r).
// Sorting within a digit is done using a bin sort.
  int e[r], f[r]; // queue front and end pointers
  // create initial chain of records starting at first
  int first = 1;
  for (int i = 1; i < n; i++) link[i] = i + 1; // link into a chain
  link[n] = 0;
  
  for (i = d-1; i >= 0; i--)
  {// sort on digit i
    fill(f, f + r, 0); // initialize bins to empty queues
    for ( int current = first; current; current = link[current])
    {// put records into queues/bins
      int k = digit(a[current], i, r);
      if (f[k] == 0) f[k] = current;
      else link[e[k]] = current;
      e[k] = current;
    }
    for (j = 0; !f[j]; j++); // find first nonempty queue/bin
    first = f[j];
    int last = e[j];
    for (int k = j + 1; k < r; k++) // concatenate remaining queues
      if (f[k]) {
        link[last] = f[k];
        last = e[k];
      }
    link[last] = 0;
  }
  return first;
}
====================================





Program 7.16:Rearranged records using a doubly linked list
====================================
template <class T>
void List1(T *a, int *linka, const int n, int first)
{// Rearrange the sorted chain beginning at first so that the records a[1:n]
// are in sorted order.
  int *linkb = new int [n]; // array for backward links
  int prev = 0;
  for (int current = first; current; current = linka[current])
  {// convert chain into a doubly linked list
    linkb[current] = prev;
    prev = current;
  }
  
  for (int i = 1; i < n ; i++) // move a[first] to position i while
  { // maintaining the list
    if (first != i) {
      if (linka[i]) linkb[linka[i]] = first;
      linka[linkb[i]] = first;
      swap(a[first], a[i]);
      swap(linka[first], linka[i]);
      swap(linkb[first], linkb[i]);
    }
    first = linka[i];
  }
}
====================================






Program 7.17:Rearranged records using only one link field
====================================
template <class T>
void List2(T *a, int *link, const int n, int first)
{// Same function as List1 except that a second link array linkb is not required.
  for (int i = 1; i < n; i++)
  {// Find correct record for ith position.  Its index is >= i as
  // records in positions 1, 2, ..., i - 1 are already correctly positioned.
    while (first < i) first = link[first];
    int q = link[first]; // a[q] is next record in sorted order
    if (first != i)
    {// a[first] has ith smallest key. Move record to ith position.
    // Also set link from old position of a[i] to new one.
      swap(a[i], a[first]);
      link[first] = link[i];
      link[i] = first;
    }
    first = q;
  }
}
====================================





Program 7.18:Table Sort
====================================
template <class T>
void Table(T *a, const int n, int *t)
{// Rearrange a[1:n] to correspond to the sequence a[t[1]], ... , a[t[n]], n >= 1.
  for (int i = 1; i < n; i++)
    if (t[i] != i)  {// there is a non-trivial cycle starting at i
      T p = a[i];
      int j = i;
      do {
        int k = t[j]; a[j] = a[k]; t[j] = j;
        j = k;
      } while (t[j] != i);
      a[j] = p; // j is position for record p
      t[j] = j;
    }
}
====================================






Figure 7.16:Average times for sort methods
====================================
if (left < right) {
  code to partition and make recursive calls
}
Code segment ending ...

Code segment starting ...
if (left + nBreak < right) {
  code to partition and make recursive calls
}
else {
     sort a[left:right] using Insertion Sort;
     return;
}
====================================





Program 7.20:Random permutation generator
====================================
template <class T>
void Permute(T *a, int n)
{// Random permutation generator.
  for (int i = n; i >= 2; i--)
  {
    int j = rand() % i + 1; // j = random integer in the range [1, i]
    swap(a[j], a[i]);
  }
}
====================================




Program 7.22:Run generation using a loser tree
====================================
template <class T>
 1 void Runs(T *r)
 2 {
 3   r = new T[k];
 4   int *rn = new int[k], *l = new int[k];
 5   for (int i = 0; i < k; i++) {// input records
 6      InputRecord(r[i]); rn[i] = 1;
 7   }
 8   InitializeLoserTree();
 9   T q = l[0]; // tournament winner
10   int rq = 1, rc = 1, rmax = 1; T lastRec = MAXREC;
11   while(1) {// output runs
12     if (rq != rc) {// end of run
13       output end of run marker;
14       if (rq > rmax) return;
15       else rc = rq;
16     }
17     WriteRecord(r[q]); lastRec = r[q]; // output record r[q]
18     // input new record into tree
19     if (end of input) rn[q] = rmax + 1;
20     else {
21       ReadRecord(r[q]);
22       if (r[q] < lastRec)  // new record belongs to next run
23         rn[q] = rmax = rq + 1;
24       else rn[q] = rc;
25     }
26     rq = rn[q];
27     // adjust losers
28     for (t = (k+q)/2; t; t /= 2;) // t is initialized to be parent of q
29     if ((rn[l[t]] < rq) || ((rn[l[t]] == rq) && (r[l[t]] < r[q])))
30     {// t is the winner
31       swap(q, l[t]);
32       rq = rn[q];
33     }
34   }
35   delete [ ] r ; delete [ ] rn ; delete [ ] l;
36 }
====================================






Program 7.23:Finding a binary tree with minimum weighted...
====================================
template <class T>
void Huffman(MinHeap<TreeNode<T>*> heap, int n)
{// heap is initially a min heap of n single-node binary trees as described above.
  for (int i = 0; i < n-1; i++)
  {// combine two minimum-weight trees
    TreeNode<T> *first = heap.Pop();
    TreeNode<T> *second = heap.Pop();
    TreeNode<T> *bt = new BinaryTreeNode<T>(first, second,
    first.data + second.data);
    heap.Push(bt);
  }
}
====================================




