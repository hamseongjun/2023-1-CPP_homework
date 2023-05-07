
ADT 6.1
===============================================
class Graph
{// objects: A nonempty set of vertices and a set of undirected edges,
// where each edge is a pair of vertices.
public:
  virtual ~Graph() {}
    // virtual destructor
  bool IsEmpty() const {return n == 0};
    // return true iff graph has no vertices
  int NumberOfVertices() const {return n};
    // return number of vertices in the graph
  int NumberOfEdges() const {return e};
    // return number of edges in the graph
  virtual int Degree(int u) const = 0;
    // return number of edges incident to vertex u
  virtual bool ExistsEdge(int u, int v) const = 0;
    // return true iff graph has the edge (u,v)
  virtual void InsertVertex(int v) = 0;
    // insert vertex v into graph; v has no incident edges
  virtual void InsertEdge(int u, int v) = 0;
    // insert edge (u, v) into graph
  virtual void DeleteVertex(int v) = 0;
    // delete v and all edges incident to it
  virtual void DeleteEdge(int u, int v) = 0;
    // delete edge (u, v) from the graph
  private:
    int n;           // number of vertices
    int e;     // number of edges
};
===============================================





Page 334
===============================================
LinkedGraph(const int vertices = 0) : n(vertices), e(0)
  {adjLists = new Chain<int>[n];}
===============================================





Program 6.1:Depth-first search
===============================================
virtual void Graph::DFS()  // Driver
{
  visited = new bool [n];
    // visited is declared as a bool* data member of Graph
  fill(visited,visited+n,false);
  DFS(0); // start search at vertex 0
  delete [] visited; 
}

virtual void Graph::DFS(const int v) // Workhorse
{// Visit all previously unvisited vertices that are reachable from vertex v.
  visited[v] = true;
  for (each vertex w adjacent to v) // actual code uses an iterator
    if (!visited[w]) DFS(w);
}
===============================================






Program 6.2:Breath-first search
===============================================
virtual void Graph::BFS(int v)
{// A breadth first search of the graph is carried out beginning at vertex v.
// visited[i] is set to true when v is visited. The function uses a queue.
  visited = new bool [n];
  fill(visited,visited+n,false);
  visited[v] = true;
  Queue<int> q;
  q.Push(v);
  while (!q.IsEmpty()) {
    v = q.Front();
    q.Pop();
    for (all vertices w adjacent to v) // actual code uses an iterator
      if (!visited[w]) {
        q.Push(w);
        visited[w] = true;
      }
  } // end of while loop
  delete [] visited;
}
===============================================






Program 6.3:Determining connected components
===============================================
virtual void Graph::Components()
{//  Determine the connected components of the graph.
  // visited is assumed to be declared as a bool* data member of Graph
  visited = new bool [n];
  fill(visited,visited+n,false);
  for (i = 0; i < n; i++)
    if (!visited[i]) {
      DFS(i); // find a component
      OutputNewComponent();
    }
  delete [] visited;
}
===============================================






Program 6.4:Computing dfn and low
===============================================
virtual void Graph::DfnLow(const int x) // begin DFS at vertex x
{
  num = 1;                      // num is an int data member of Graph
  dfn = new int[n];  // dfn is declared as int* in Graph
  low = new int[n];  // low is declared as int* in Graph
  fill(dfn,dfn+n,0);
  fill(low,low+n,0);
  DfnLow(x, -1); // start at vertex x
  delete [] dfn;
  delete [] low;
}

void Graph::DfnLow (const int u, const int v)
{// Compute dfn and low while performing a depth first search beginning at vertex
// u. v is the parent (if any) of u in the resulting spanning tree.
  dfn[u] = low[u] = num++;
  for (each vertex w adjacent from u)  // actual code uses an iterator
    if (dfn[w] == 0) { // w is an unvisited vertex
      DfnLow(w, u);
      low[u] = min(low[u], low[w]);
    }
    else if (w != v) low[u] = min(low[u], dfn[w]); // back edge
}
===============================================






Program 6.5:Outputting biconnected components when n>1
===============================================
virtual void Graph::Biconnected()
{
  num = 1;                       // num is an int data member of Graph
  dfn = new int[n];  // dfn is declared as int* in Graph
  low = new int[n];  // low is declared as int* in Graph
  fill(dfn,dfn+n,0);
  fill(low,low+n,0);
  Biconnected(0, -1); // start at vertex 0
  delete [] dfn;
  delete [] low;
}

virtual void Graph::Biconnected (const int u, const int v)
{// Compute dfn and low, and output the edges of G by their biconnected
// components. v is the parent (if any) of u in the resulting spanning tree.
// s is an initially empty stack declared as a data member of Graph.
  dfn[u] =  low[u] =  num++;
  for ( each vertex w adjacent from u) { // actual code uses an iterator
    if ((v != w) && (dfn[w] < dfn[u])) add (u, w) to stack s;
    if (dfn[w] == 0) { // w is an unvisited vertex
      Biconnected(w, u);
      low[u] = min(low[u], low[w]);
      if (low[w] >= dfn[u]) {
        cout << "New Biconnected Component: " << endl;
        do {
          delete an edge from the stack s;
          let this edge be (x, y);
          cout << x << ", " << y << endl;
        } while ( (x, y) and (u, w) are not the same edge)
      } 
    }
    else if (w != v) low[u] = min(low[u], dfn[w]); // back edge
}
===============================================





Program 6.6:Kruskal's algorithm
===============================================
1  T=es;
2  while ((T contains less than n-1 edges) && (E not empty)) {
3  choose an edge (v,w) from E of lowest cost;
4  delete (v,w) from E;
5  if ((v,w) does not create a cycle in T) add (v,w) to T;
6  else discard (v,w);
7  }
8  if (T contains fewer than n-1 edges) cout << "no spanning tree" << endl;
===============================================





Program 6.7:Prim's algorithm
===============================================
// Assume that G has at least one vertex.
TV = {0}; // start with vertex 0 and no edges
for (T=es; T contains fewer than n-1 edges;  add (u,v) to T)
{
  Let (u,v) be a least-cost edge such that u mo TV and v  TV;
  if (there is no such edge) break;
  add v to TV;
}
if (T contains fewer than n-1 edges) cout << "no spanning tree" << endl;
===============================================





Program 6.8:Determining the length of the shortest paths
===============================================
 1 void MatrixWDigraph::ShortestPath(const int n, const int v)
 2 {// dist[j],0<=j<n, is set to the length of the shortest path from v to j
 3 // in a digraph G with n vertices and edge lengths given by length[i][j].
 4    for (int i = 0; i < n; i++) {s[i] = false; dist[i] = length[v][i];} // initialize
 5    s[v] = true;
 6    dist[v] = 0;

 7    for (i = 0; i < n-2; i++) { // determine n-1 paths from vertex v
 8       int u = Choose(n);  // choose returns a value u such that:
 9       // dist[u] = minimum dist[w], where s[w] = false
10       s[u] = true;
11       for (int w = 0; w < n; w++)
12          if (! s[w] && dist[u] + length[u][w] < dist[w])
13             dist[w] = dist[u] + length[u][w];
14          } // end of for (i = 0; ...)
15  }
===============================================





Program 6.9:Bellman and Ford algorithm to compute shortest paths
===============================================
 1 void MatrixWDigraph::BellmanFord(const int n, const int v)
 2 {// Single source all destination shortest paths with negative edge lengths.
 3    for (int i = 0; i < n; i++) dist[i] = length[v][i]; // initialize dist

 4    for (int k = 2; k <= n-1; k++)
 5    for (each u such that u != v and u has at least one incoming edge)
 6       for (each <i, u> in the graph)
 7          if (dist[u] > dist[i] + length[i][u]) dist[u] = dist[i] + length[i][u];
8 }
===============================================




Program 6.10:All-pairs shortest paths
===============================================
 1 void MatrixWDigraph::AllLengths(const int n)
 2 {// length[n][n] is the adjacency matrix of a graph with n vertices.
 3 // a[i][j] is the length of the shortest path between i and j.
 4 for (int i = 0; i < n; i++)
 5    for (int j = 0; j < n; j++)
 6       a[i][j] = length[i][j];     // copy length into a
 7 for (int k = 0; k < n; k++)   // for a path with highest vertex index k
 8    for (i = 0; i < n; i++)  // for all possible pairs of vertices
 9       for (int j = 0; j < n; j++)
10          if ((a[i][k] + a[k][j]) < a[i][j]) a[i][j] = a[i][k] + a[k][j];
11 }
===============================================





Program 6.11:Design of a topological sorting algorithm
===============================================
 1  Input the AOV network.  Let n be the number of vertices.
 2  for (int i=0; i < n; i++) // output the vertices
 3  {
 4     if (every vertex has a predecessor) return;
 5     // network has a cycle and is infeasible.
 6     pick a vertex v that has no predecessors;
 7     cout << v;
 8     delete v and all edges leading out of v from the network;
 9  }
===============================================






Program 6.12:Topological order
===============================================
 1 void LinkedDigraph::TopologicalOrder()
 2 {// The n vertices of a network are listed in topological order.
 3    int top = -1;
 4    for (int i = 0; i < n; i++) // create a linked stack of vertices with
 5       if (count[i] == 0) { count[i] = top; top = i;} // no predecessors

 6    for (i = 0; i < n; i++)
 7       if (top == -1) throw " Network has a cycle.";
 8       int j = top; top = count[top]; // unstack a vertex
 9       cout << j << endl;
10       Chain<int>::ChainIterator ji = adjLists[j].begin();
11       while (ji) { // decrease the count of the successor vertices of j
12          count[*ji]--;
13          if (count[*ji] == 0) { count[*ji] = top; top = *ji;} // add *ji to stack
14          ji++;
15      }
16 }
===============================================






Program 6.13:Finding an Eulerian walk
===============================================
   virtual Path Graph::Euler(int v)
 1  {
 2     Path path = { };
 3     for ((all vertices w  adjacent to v) && (edge (v,w) not yet used)) {
 4        mark edge (v, w) as used;
 5        path =  roman "{" (v,w) roman "}" ~cu~euler(w)~cu~path;
 6  }
 7  return path;
 8  }
===============================================


