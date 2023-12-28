/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <cstddef>
#include <vector>
#include <queue>
#include <stack>
#include <list>

using namespace std;

template <class T, class U> class Edge;
template <class T, class U> class Graph;
template <class T, class U> class Vertex;


/****************** Provided structures  ********************/

template <class T, class U>
class Vertex {
    T info;                // contents
    vector<Edge<T,U>> adj;  // list of outgoing edges
    bool visited;          // auxiliary field
    bool processing;       // auxiliary field
    int indegree;          // auxiliary field
    int num;               // auxiliary field
    int low;               // auxiliary field

    void addEdge(Vertex<T,U> *dest, double w, U info);
    bool removeEdgeTo(Vertex<T,U> *d);
public:
    explicit Vertex(T in);
    T getInfo() const;
    void setInfo(T in);
    bool isVisited() const;
    void setVisited(bool v);
    bool isProcessing() const;
    void setProcessing(bool p);
    const vector<Edge<T,U>> &getAdj() const;
    void setAdj(const vector<Edge<T,U>> &edges);

    int getIndegree() const;

    int getNum() const;

    void setNum(int num);

    int getLow() const;

    void setLow(int low);

    friend class Graph<T,U>;
};

template <class T,class U>
class Edge {
    Vertex<T,U> * dest;      // destination vertex
    double weight;         // edge weight
    U info;
public:
    Edge(Vertex<T,U> *d, double w, U i);
    Vertex<T,U> *getDest() const;
    void setDest(Vertex<T,U> *dest);
    double getWeight() const;
    void setWeight(double weight);
    U getInfo() const;
    void setInfo(U info);
    friend class Graph<T,U>;
    friend class Vertex<T,U>;
};

template <class T, class U>
struct CmpVertexPtr {
};

template <class T, class U>
class Graph {
    vector<Vertex<T,U> *> vertexSet;      // vertex set
    int _index_;                        // auxiliary field
    stack<Vertex<T,U>> _stack_;           // auxiliary field
    list<list<T>> _list_sccs_;        // auxiliary field

    void dfsVisit(Vertex<T,U> *v,  vector<T> & res) const;
    bool dfsIsDAG(Vertex<T,U> *v) const;
public:
    Vertex<T,U> *findVertex(const T &in) const;
    int getNumVertex() const;
    Vertex<T,U>* addVertex(const T &in);
    bool removeVertex(const T &in);
    bool addEdge(const T &sourc, const T &dest, double w, U info);
    bool addEdge(Vertex<T, U> *sourc, Vertex<T, U> *dest, double w, U info);
    bool removeEdge(const T &sourc, const T &dest);
    vector<Vertex<T,U> * > getVertexSet() const;
    vector<T> dfs() const;
    vector<T> dfs(const T & source) const;
    vector<T> bfs(const T &source) const;
    vector<T> topsort() const;
    bool isDAG() const;

};

/****************** Provided constructors and functions ********************/

template <class T,class U>
Vertex<T,U>::Vertex(T in): info(in) {}

template <class T, class U>
Edge<T,U>::Edge(Vertex<T,U> *d, double w, U i): dest(d), weight(w), info(i) {}


template <class T, class U>
int Graph<T,U>::getNumVertex() const {
    return vertexSet.size();
}

template <class T, class U>
vector<Vertex<T,U>*> Graph<T,U>::getVertexSet() const {
    return vertexSet;
}

template<class T, class U>
T Vertex<T,U>::getInfo() const {
    return info;
}

template<class T,class U>
void Vertex<T,U>::setInfo(T in) {
    Vertex::info = in;
}

template<class T,class U>
bool Vertex<T,U>::isProcessing() const {
    return processing;
}

template<class T,class U>
void Vertex<T,U>::setProcessing(bool p) {
    Vertex::processing = p;
}

template<class T, class U>
Vertex<T,U> *Edge<T,U>::getDest() const {
    return dest;
}

template<class T, class U>
void Edge<T,U>::setDest(Vertex<T,U> *d) {
    Edge::dest = d;
}

template<class T, class U>
double Edge<T,U>::getWeight() const {
    return weight;
}

template<class T, class U>
void Edge<T,U>::setWeight(double w) {
    Edge::weight = w;
}

template<class T, class U>
U Edge<T,U>::getInfo() const {
    return info;
}
template<class T, class U>
void Edge<T,U>::setInfo(U info) {
    this->info = info;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T, class U>
Vertex<T,U> * Graph<T,U>::findVertex(const T &in) const {
    for (auto v : vertexSet)
        if (v->info == in)
            return v;
    return NULL;
}

template <class T, class U>
bool Vertex<T,U>::isVisited() const {
    return visited;
}

template<class T, class U>
int Vertex<T,U>::getIndegree() const {
    return indegree;
}

template<class T, class U>
int Vertex<T,U>::getNum() const {
    return num;
}

template<class T, class U>
void Vertex<T,U>::setNum(int n) {
    Vertex::num = n;
}

template<class T, class U>
int Vertex<T,U>::getLow() const {
    return low;
}

template<class T, class U>
void Vertex<T,U>::setLow(int l) {
    Vertex::low = l;
}

template <class T, class U>
void Vertex<T,U>::setVisited(bool v) {
    Vertex::visited = v;
}

template<class T, class U>
const vector<Edge<T,U>> &Vertex<T,U>::getAdj() const {
    return adj;
}

template <class T, class U>
void Vertex<T,U>::setAdj(const vector<Edge<T,U>> &edges) {
    Vertex::adj = edges;
}


/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T, class U>
Vertex<T,U>* Graph<T,U>::addVertex(const T &in) {
    if (findVertex(in) != NULL)
        return nullptr;
    vertexSet.push_back(new Vertex<T,U>(in));
    return vertexSet.back();
}


/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T, class U>
bool Graph<T,U>::addEdge(const T &sourc, const T &dest, double w, U i) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    v1->addEdge(v2,w,i);
    v2->indegree++;
    return true;
}

template <class T, class U>
bool Graph<T,U>::addEdge(Vertex<T,U> *sourc, Vertex<T,U> *dest, double w, U i) {
    if (sourc == NULL || dest == NULL)
        return false;
    sourc->addEdge(dest, w, i);
    dest->indegree++;
    return true;
}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T, class U>
void Vertex<T,U>::addEdge(Vertex<T,U> *d, double w, U i) {
    adj.push_back(Edge<T,U>(d, w, i));
}


/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T, class U>
bool Graph<T,U>::removeEdge(const T &sourc, const T &dest) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    return v1->removeEdgeTo(v2);
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T, class U>
bool Vertex<T,U>::removeEdgeTo(Vertex<T,U> *d) {
    for (auto it = adj.begin(); it != adj.end(); it++)
        if (it->dest  == d) {
            adj.erase(it);
            return true;
        }
    return false;
}

/*
 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 */
template <class T, class U>
bool Graph<T,U>::removeVertex(const T &in) {
    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++)
        if ((*it)->info  == in) {
            auto v = *it;
            vertexSet.erase(it);
            for (auto u : vertexSet)
                u->removeEdgeTo(v);
            delete v;
            return true;
        }
    return false;
}


/****************** DFS ********************/
/*
 * Performs a depth-first search (dfs) traversal in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template <class T, class U>
vector<T> Graph<T,U>::dfs() const {
    vector<T> res;
    for (auto v : vertexSet)
        v->visited = false;
    for (auto v : vertexSet)
        if (! v->visited)
            dfsVisit(v, res);
    return res;
}

/*
 * Auxiliary function that visits a vertex (v) and its adjacent, recursively.
 * Updates a parameter with the list of visited node contents.
 */
template <class T, class U>
void Graph<T,U>::dfsVisit(Vertex<T,U> *v, vector<T> & res) const {
    v->visited = true;
    res.push_back(v->info);
    for (auto & e : v->adj) {
        auto w = e.dest;
        if ( ! w->visited)
            dfsVisit(w, res);
    }
}


/****************** DFS ********************/
/*
 * Performs a depth-first search (dfs) in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order,
 * from the source node.
 */
template <class T, class U>
vector<T> Graph<T,U>::dfs(const T & source) const {
    vector<T> res;
    auto s = findVertex(source);
    if (s == nullptr)
        return res;

    for (auto v : vertexSet)
        v->visited = false;

    dfsVisit(s, res);
    return res;
}


/****************** BFS ********************/
/*
 * Performs a breadth-first search (bfs) in a graph (this), starting
 * from the vertex with the given source contents (source).
 * Returns a vector with the contents of the vertices by bfs order.
 */
template <class T, class U>
vector<T> Graph<T,U>::bfs(const T & source) const {
    vector<T> res;
    auto s = findVertex(source);
    if (s == NULL)
        return res;
    queue<Vertex<T,U> *> q;
    for (auto v : vertexSet)
        v->visited = false;
    q.push(s);
    s->visited = true;
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        res.push_back(v->info);
        for (auto & e : v->adj) {
            auto w = e.dest;
            if ( ! w->visited ) {
                q.push(w);
                w->visited = true;
            }
        }
    }
    return res;
}


/****************** isDAG  ********************/
/*
 * Performs a depth-first search in a graph (this), to determine if the graph
 * is acyclic (acyclic directed graph or DAG).
 * During the search, a cycle is found if an edge connects to a vertex
 * that is being processed in the stack of recursive calls (see theoretical classes).
 * Returns true if the graph is acyclic, and false otherwise.
 */

template <class T, class U>
bool Graph<T,U>::isDAG() const {
    for (auto v : vertexSet) {
        v->visited = false;
        v->processing = false;
    }
    for (auto v : vertexSet)
        if (! v->visited)
            if ( ! dfsIsDAG(v) )
                return false;
    return true;
}

/**
 * Auxiliary function that visits a vertex (v) and its adjacent, recursively.
 * Returns false (not acyclic) if an edge to a vertex in the stack is found.
 */
template <class T, class U>
bool Graph<T,U>::dfsIsDAG(Vertex<T,U> *v) const {
    v->visited = true;
    v->processing = true;
    for (auto & e : v->adj) {
        auto w = e.dest;
        if (w->processing)
            return false;
        if (! w->visited)
            if (! dfsIsDAG(w))
                return false;
    }
    v->processing = false;
    return true;
}


/****************** toposort ********************/
/*
 * Performs a topological sorting of the vertices of a graph (this).
 * Returns a vector with the contents of the vertices by topological order.
 * If the graph has cycles, returns an empty vector.
 * Follows the algorithm described in theoretical classes.
 */

template<class T, class U>
vector<T> Graph<T,U>::topsort() const {
    if (!isDAG()) return {};
    vector<T> order;
    for (Vertex<T,U>* v: this->getVertexSet()) v->setVisited(false);

    for (Vertex<T,U>* v: this->getVertexSet()) {
        if (v->isVisited()) continue;
        dfsTopSort(v, order);
    }

    reverse(order.begin(), order.end());
    return order;
}

template<class T, class U>
void dfsTopSort(Vertex<T,U> *v, vector<T> &order) {
    v->setVisited(true);
    for (Edge<T,U> e: v->getAdj()) {
        Vertex<T,U>* w = e.getDest();
        if (w->isVisited()) continue;
        dfsTopSort(w, order);
    }
    order.push_back(v->getInfo());
}

#endif /* GRAPH_H_ */
