#include <iostream>
#include <fstream>
#include <limits.h>
#include <map>
#include <vector>
#include <string>
#include <stack>
#include <list>
#include <queue>
#include <sstream>

using namespace std;

int INFINITY = INT_MAX;

std::string ToString(int n)
{
  std::stringstream ss;
  ss << n;
  return ss.str();
}

class Vertex {
public:
  string           name;   // Vertex name
  vector<pair<int,Vertex *> > adj;    // Adjacent vertices
  int              dist;   // Cost
  Vertex          *path;   // Previous vertex on shortest path
  bool      visited; // visited

  int       l_path;

  vector<pair<int,Vertex *> > in_vertices;

  Vertex( const string & nm ) : name( nm )
    { reset( ); }

  void reset()
    { dist = INFINITY; path = NULL; visited = false; l_path = 0;}

  int getDist() const
    { return dist; }
};

class CompareVertex
{
public:
  bool operator() (const Vertex * node1, const Vertex * node2)
  {
    return node1->getDist() > node2->getDist(); // less than queue
  }
};

// Definitions
typedef map<string,Vertex *> vmap;
typedef pair<string,Vertex *> vpair;
typedef std::priority_queue<Vertex*, std::vector<Vertex*>, CompareVertex > PQ;

class Graph
{
  public:
    Graph( ) { undirected = false;}

  // Lab 6
  Graph(int x)
  {
    if (x==1)
      undirected = true;
    else
      undirected = false;
  }

  ~Graph( );
  void addEdge( const string & sourceName, const string & destName );
  void printPath( const string & destName ) const;
  void unweighted( const string & startName );

  // Lab 6
  void addEdge(const string & sourceName, const string & destName, int cost);

  // Lab 6
  void BFS( const string & startName );

  // Lab 6
  void ShortestPath (const string & startName, const string & endName);

  // Lab 6
  void MST();

  // For Prof. Moorthy
  int LongestSubsequence(std::vector<int> const & y_vec);
      
  private:
    Vertex * getVertex( const string & vertexName );
    void printPath( const Vertex & dest ) const;
    void clearAll( );

  // Lab 6
  void Dijkstra(const string & startName);

  vmap vertexMap;
  vector<Vertex *> allVertices;
  
  vector<Vertex *> LSRR_vertices;

  // Lab 6
  bool undirected;
};



void Graph::addEdge( const string & sourceName, const string & destName )
{
  Vertex * v = getVertex( sourceName );
  Vertex * w = getVertex( destName );
   
  // Lab 6
  v->adj.push_back( std::make_pair(0, w) );
  w->in_vertices.push_back( std::make_pair(0,v) );
  
  // Lab 6
  if (undirected)
  {
    w->adj.push_back( std::make_pair(0,v) );
    v->in_vertices.push_back( std::make_pair(0,w) );
  }
}

// Lab 6
void Graph::addEdge( const string & sourceName, const string & destName, int cost )
{
  Vertex * v = getVertex( sourceName );
  Vertex * w = getVertex( destName );

  v->adj.push_back( std::make_pair(cost,w) );
  w->in_vertices.push_back( std::make_pair(cost,v) );
  //

  if (undirected)
  {
    w->adj.push_back( std::make_pair(cost,v) );
    v->in_vertices.push_back( std::make_pair(cost,w) );
  }
}

void Graph::printPath( const string & destName ) const
{
    vmap::const_iterator itr = vertexMap.find( destName );

    if( itr == vertexMap.end( ) )
    {
        cout << "Destination vertex not found" << endl;
        return;
    }

    const Vertex & w = *(*itr).second;
    if( w.dist == INFINITY )
        cout << destName << " is unreachable";
    else
        printPath( w );
    cout << endl;
}

// If vertexName is not present, add it to vertexMap
// In either case, return the Vertex
Vertex * Graph::getVertex( const string & vertexName )
{
    vmap::iterator itr = vertexMap.find( vertexName );

    if( itr == vertexMap.end( ) )
    {
        Vertex *newv = new Vertex( vertexName );
        allVertices.push_back( newv );
        vertexMap.insert( vpair( vertexName, newv ) );
        return newv;
    }
    return (*itr).second;
}

void Graph::printPath( const Vertex & dest ) const
{
    if( dest.path != NULL )
    {
        printPath( *dest.path );
        cout << " to ";
    }
    cout << dest.name;
}

void Graph::clearAll( )
{
    for(unsigned int i = 0; i < allVertices.size( ); i++ )
        allVertices[ i ]->reset( );
}

Graph::~Graph( )
{
    for(unsigned int i = 0; i < allVertices.size( ); i++ )
        delete allVertices[ i ];
}


void Graph::unweighted( const string & startName )
{
    clearAll( );

    vmap::iterator itr = vertexMap.find( startName );

    if( itr == vertexMap.end( ) )
    {
        cout << startName << " is not a vertex in this graph" << endl;
        return;
    }

    Vertex *start = (*itr).second;
    list<Vertex *> q;
    q.push_back( start ); start->dist = 0;

    while( !q.empty( ) )
    {
        Vertex *v = q.front( ); q.pop_front( );

        for(unsigned int i = 0; i < v->adj.size( ); i++ )
        {
            Vertex *w = v->adj[ i ].second;
            
            if( w->dist == INFINITY )
            {
                w->dist = v->dist + 1;
                w->path = v;
                q.push_back( w );
            }
        }
    }
}

/**
 * Process a request; return false if end of file.
 */
bool processRequest( istream & in, Graph & g )
{
    string startName;
    string destName;

    cout << "Enter start node: ";
    if( !( in >> startName ) )
        return false;
    cout << "Enter destination node: ";
    if( !( in >> destName ) )
        return false;

    g.unweighted( startName );
    g.printPath( destName );

    return true;
}

// Lab 6
void Graph::BFS( const string & startName)
{
  Graph::clearAll();

  Vertex * s = getVertex( startName );
  s->dist = 0;
  PQ myqueue;
  myqueue.push(s);

  while (!myqueue.empty())
  {
    Vertex * u = myqueue.top();
    myqueue.pop();

    cout << "Name: " << u->name << "  Dist: " << u->dist << "\n";

    for (unsigned int i=0; i < u->adj.size(); ++i)
    {
      if (u->adj[i].second->dist == INFINITY)
      {
        u->adj[i].second->dist = u->dist + 1;
        myqueue.push( u->adj[i].second );
      }
    }
  }
}

// Lab 6 - Dijkstra's Algorithm
void Graph::ShortestPath (const string & startName, const string & endName)
{
  Graph::Dijkstra(startName);
  Graph::printPath( *(getVertex(endName)) );
}

void Graph::Dijkstra(const string & startName)
{
  Graph::clearAll();
  Vertex * s = getVertex(startName);
  s->dist = 0;

  PQ myqueue;
  for (unsigned int i=0; i<allVertices.size(); i++)
  {
    myqueue.push( allVertices[i] );
  }

  while (!myqueue.empty())
  {
    Vertex * u = myqueue.top();
    myqueue.pop();
    for (unsigned int i=0; i<u->adj.size(); i++)
    {
      // cout << "u: " << u->name << " v: " << u->adj[i].second->name << "\n";
      // cout << "dist(v): " << u->adj[i].second->dist << " dist(u): " << u->dist << " l(u,v): " << u->adj[i].first << "\n";
      if (u->adj[i].second->dist > u->dist + u->adj[i].first)
      {
        u->adj[i].second->dist = u->dist + u->adj[i].first;
        u->adj[i].second->path = u;
      }
    }
  }
  return;
}

// Lab 6 - Prim's Algorithm
void Graph::MST()
{
  Graph::clearAll();
  if (allVertices.size()==0) return;
  Vertex * uo = allVertices[0];
  uo->dist = 0;

  PQ myqueue;
  for (unsigned int i=0; i<allVertices.size(); i++)
  {
    myqueue.push( allVertices[i] );
  }

  while (!myqueue.empty())
  {
    Vertex * u = myqueue.top();
    myqueue.pop();
    u->visited = true;
    for (unsigned int i=0; i<u->adj.size(); i++)
    {
      //cout << "u: " << u->name << " v: " << u->adj[i].second->name << "\n";
      //cout << "dist(u): " << u->dist << " dist(v): " << u->adj[i].second->dist << " l(u,v): " << u->adj[i].first << "\n";
      if (u->path != u->adj[i].second && u->adj[i].second->dist > u->adj[i].first)
      {
        u->adj[i].second->dist = u->adj[i].first;
        u->adj[i].second->path = u;
      }
    }
  }

  // Print edges of Minimum Spanning Tree
  int count=0;
  cout << "Minimum Spanning Tree's Edges:\n";
  for (unsigned int i=0; i<allVertices.size(); i++)
  {
    if (allVertices[i]->path != NULL)
    {
      cout << "Edge: " << allVertices[i]->path->name << " to " << allVertices[i]->name;
      cout << "\n";
      count++;
    }
  }

  if (count!= allVertices.size()-1)
  {
    cout << "\nThis graph is disconnected. MST does not exist.\n\n";
  }
}


// Added for Prof. Moorthy
int Graph::LongestSubsequence(std::vector<int> const & y_vec)
{
  // clear memory
  for(unsigned int i = 0; i < allVertices.size( ); i++ )
  {
        delete allVertices[ i ];
  }

  // reset graph
  vertexMap.clear();
  allVertices.clear();

  // set up vector
  std::vector<Vertex *> mylist;

  // add adjacency relations
  for (unsigned int i=0; i<y_vec.size(); i++)
  {
    mylist.push_back( Graph::getVertex( ToString(y_vec[i]) ));
    for (unsigned int j=0; j<i; j++)
    {
      if (y_vec[j] < y_vec[i])
      {
        addEdge( ToString( y_vec[j] ), ToString( y_vec[i] ));
      }
    }
  }

  // main "Dynamic" Algorithm, pg.158 (DG)
  int max = 0;
  for (unsigned int j=0; j<mylist.size(); j++)
  {
    int localmax = 0;
    unsigned int k = 0;
    for (; k<mylist[j]->in_vertices.size(); k++)
    {
      localmax = std::max(localmax, mylist[j]->in_vertices[k].second->l_path);
    }
    localmax = localmax + 1;
    mylist[j]->l_path = localmax;
    max = std::max(max,localmax);
  }

  return max;
}

