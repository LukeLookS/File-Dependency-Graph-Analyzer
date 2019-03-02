/////////////////////////////////////////////////////////////////////
// Graph.h                                                         //
// Mengjie Shi                                                     //
// SUID: 457056896                                                 //
/////////////////////////////////////////////////////////////////////

#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
#include <sstream>
#include <stack>

#include "Key_Value_Table.h"


// Vertex class
template<typename V, typename E>
class Vertex
{
public:
	typedef std::pair<size_t, E> Edge;  // graph index of target vertex, edge type
	typename typedef std::vector<Edge>::iterator iterator;
	iterator begin();
	iterator end();
	Vertex(V v, size_t id);
	Vertex(V v);
	void add(Edge& edge);
	Edge& operator[](size_t i);
	Edge operator[](size_t i) const;
	V& value();
	size_t& id();
	size_t size();
	bool& mark();
	bool operator==(const Vertex &t1)const;
	bool operator!=(const Vertex &t1)const;
private:
	std::vector<Edge> _edges;
	V _v;
	size_t _id;
	static size_t count;
	bool _mark;
};
//----< reserve memory for, and initialize, static count >-----
template<typename V, typename E>
size_t Vertex<V, E>::count = 0;

//----< set and return boolean mark, used for traversal >------
template<typename V, typename E>
bool& Vertex<V, E>::mark() { return _mark; }

//----< return iterator pointing to first edge >---------------
template<typename V, typename E>
typename Vertex<V, E>::iterator Vertex<V, E>::begin() { return _edges.begin(); }

//----< return iterator pointing to one past last edge >-------
template<typename V, typename E>
typename Vertex<V, E>::iterator Vertex<V, E>::end() { return _edges.end(); }

//-----------< overload the operator== >-------------
template<typename V, typename E>
bool Vertex<V, E>::operator==(const Vertex &t1)const
{
	if (_v == t1._v)
		return true;
	else
		return false;
}

//-----------< overload the operator!= >-------------
template<typename V, typename E>
bool Vertex<V, E>::operator!=(const Vertex &t1)const
{
	if (_v == t1._v)
		return false;
	else
		return true;
}

//----< construct instance, specifying id - must be unique >---
template<typename V, typename E>
Vertex<V, E>::Vertex(V v, size_t id) : _v(v), _id(id), _mark(false) {}

//----< construct instance - creates id sequentially >-------
template<typename V, typename E>
Vertex<V, E>::Vertex(V v) : _v(v), _id(count++), _mark(false) {}

//----< add edge to vertex edge collection >-------------------
template<typename V, typename E>
void Vertex<V, E>::add(Edge& edge) { _edges.push_back(edge); }

//----< index non-const vertex's edges >-----------------------
template<typename V, typename E>
typename Vertex<V, E>::Edge& Vertex<V, E>::operator[](size_t i) { return _edges[i]; }

//----< index const vertex's edges >---------------------------
template<typename V, typename E>
typename Vertex<V, E>::Edge Vertex<V, E>::operator[](size_t i) const { return _edges[i]; }

//----< set and read value of vertex's held type, V >----------
template<typename V, typename E>
V& Vertex<V, E>::value() { return _v; }

//----< return vertex's id >-----------------------------------
template<typename V, typename E>
size_t& Vertex<V, E>::id() { return _id; }

//----< return number of edges >-------------------------------
template<typename V, typename E>
size_t Vertex<V, E>::size() { return _edges.size(); }


// Graph class
template<typename V, typename E>
class Graph
{
public:
	typedef std::pair<size_t, E> Edge;  // graph index of target vertex, edge type
	typename typedef std::vector<Edge>::iterator Iterator;
	typename typedef std::vector< Vertex<V, E> >::iterator iterator;
	iterator begin();
	iterator end();
	Vertex<V, E>& operator[](size_t i);
	Vertex<V, E> operator[](size_t i) const;
	void addVertex(Vertex<V, E> v);
	void addEdge(E eval, Vertex<V, E>& parent, Vertex<V, E>& child);
	unsigned findmember(std::vector<Vertex<V, E>> v, Vertex<V, E> target);
	void DeletVertex(std::vector<Vertex<V, E>> pvs);
	size_t size();

	template<typename F>
	void dfs(Vertex<V, E>& v, F f);

	std::vector<std::vector<int>> initMatrix(size_t s);
	void setMatrix(int x, int y);
	int getMatrix(int x, int y);
	std::vector<std::vector<int>> addToMatrix(Graph<V, E>&_g);

	std::vector< std::vector<std::string> > Scc();
	void searchScc(size_t u, int disc[], int low[], std::stack<size_t> *st, bool flag[]);

private:
	std::vector< Vertex<V, E> > adj;
	std::vector< std::vector<std::string> > sccVe;
	std::unordered_map<size_t, size_t> idMap; // id maps to graph index
	template<typename F>
	void dfsCore(Vertex<V, E>& v, F f);
	std::vector<std::vector<int>> matrix;
};
//----< return iterator pointing to first vertex >-------------
template<typename V, typename E>
typename Graph<V, E>::iterator Graph<V, E>::begin() { return adj.begin(); }

//----< return iterator pointing one past last vertex >--------
template<typename V, typename E>
typename Graph<V, E>::iterator Graph<V, E>::end() { return adj.end(); }

//----< index non-const graph's vertex collection >------------
template<typename V, typename E>
typename Vertex<V, E>& Graph<V, E>::operator[](size_t i) { return adj[i]; }

//----< index const graph's vertex collection >----------------
template<typename V, typename E>
typename Vertex<V, E> Graph<V, E>::operator[](size_t i) const { return adj[i]; }

//----< add vertex to graph's vertex collection >--------------
template<typename V, typename E>
void Graph<V, E>::addVertex(Vertex<V, E> v)
{
	Vertex<V, E> _v(v.value(), adj.size());
	if (findmember(adj, _v) == 0)
	{
		adj.push_back(_v);
		idMap[_v.id()] = adj.size() - 1;
	}
}

//----< delete vertex of graph >--------------
template<typename V, typename E>
void Graph<V, E>::DeletVertex(std::vector<Vertex<V, E>> vvs)
{
	for (unsigned i = 0; i < vvs.size(); i++)
	{
		for (std::vector<Vertex<std::string, std::string>>::iterator iter = adj.begin(); iter != adj.end();)
		{
			if ((*iter).id() == vvs[i].id())
			{
				adj.erase(iter);  //  delete parent from vector adj
				break;
			}
			iter++;
		}
	}
}

//----< utility function, if exist, return the location, else return '0' >------
template<typename V, typename E>
unsigned Graph<V, E>::findmember(std::vector<Vertex<V, E>> v, Vertex<V, E> target)
{
	if (v.size() == 0)  //  vector is empty
		return 0;
	unsigned c;
	for (c = 0; c < v.size(); c++)
	{
		if (v[c] == target)
		{
			c++;  //  in order to make a judgement
			break;
		}
	}
	if (v[c - 1] != target)
		return 0;  //  target does not exsit in v
	return c;  //  return the result
}

//-------< return number of vertices in graph >---------
template<typename V, typename E>
size_t Graph<V, E>::size() { return adj.size(); }

//----< add edge from specified parent to child vertices >-----
template<typename V, typename E>
void Graph<V, E>::addEdge(E eVal, Vertex<V, E>& parent, Vertex<V, E>& child)
{
	size_t childIndex;
	if (findmember(adj, child) != 0)  //  vertex does not exist in graph
	{
		Vertex<V, E> tempchild = adj[findmember(adj, child) - 1];
		childIndex = idMap[tempchild.id()];
	}
	else
		childIndex = idMap[child.id()];  //  find the vertex

	size_t parentIndex;
	if (childIndex == adj.size())
		throw std::exception("no edge child");
	if (findmember(adj, parent) != 0)  //  parent does not exist in graph
	{
		Vertex<V, E> temp = adj[findmember(adj, parent) - 1];
		parentIndex = idMap[temp.id()];
	}
	else
		parentIndex = idMap[parent.id()];

	if (parentIndex == adj.size())
		throw std::exception("no edge parent");
	Vertex<V, E>::Edge e;
	e.first = childIndex;
	e.second = eVal;
	adj[parentIndex].add(e);  //  add edge to graph	
}

//----< recursive depth first search with action f >-----------
template<typename V, typename E>
template<typename F>
void Graph<V, E>::dfsCore(Vertex<V, E>& v, F f)
{
	f(v);
	v.mark() = true;
	for (auto e : v)
	{
		if (adj[e.first].mark() == false)
			dfsCore(adj[e.first], f);
	}
	for (auto& vert : adj)
	{
		if (vert.mark() == false)
			dfsCore(vert, f);
	}
}

//-------< depth first search, clears marks for next search >--------
template<typename V, typename E>
template<typename F>
void Graph<V, E>::dfs(Vertex<V, E>& v, F f)
{
	dfsCore(v, f);
	for (auto& vert : adj)
		vert.mark() = false;
}

//---------< strong componenet detect >----------
template<typename V, typename E>
std::vector< std::vector<std::string> > Graph<V, E>::Scc()
{
	size_t size = adj.size();
	int *disc = new int[size];
	int *low = new int[size];
	bool *s = new bool[size];
	std::stack<size_t> *sta = new std::stack<size_t>();
	for (unsigned i = 0; i < size; i++)
	{
		disc[i] = -1;
		low[i] = -1;
		s[i] = false;
	}
	for (unsigned i = 0; i < size; i++)
	{
		if (disc[i] == -1)
			searchScc(i, disc, low, sta, s);
	}
	return sccVe;
}

template<typename V, typename E>
void Graph<V, E>::searchScc(size_t u, int disc[], int low[], std::stack<size_t> *st, bool flag[])
{
	static int t = 0;
	disc[u] = low[u] = ++t;
	st->push(u);
	flag[u] = true;
	Vertex<V, E> vt = adj[u];
	Iterator iter;
	for (iter = vt.begin(); iter != vt.end(); ++iter)
	{
		Edge edge = *iter;
		size_t v = edge.first;
		if (disc[v] == -1)
		{
			searchScc(v, disc, low, st, flag);
			if (low[u] > low[v])
				low[u] = low[v];
		}
		else if (flag[v] == true)
			if (low[u] > disc[v])
				low[u] = low[v];
	}
	int w = 0;
	if (low[u] == disc[u])
	{
		std::cout << "  ";
		std::vector<std::string> presult;
		while (st->top() != u)
		{
			w = (int)st->top();
			Vertex<V, E> tmpv = adj[w];
			std::cout << tmpv.value() << "---";
			presult.push_back(tmpv.value());
			flag[w] = false;
			st->pop();
		}
		w = (int)st->top();
		Vertex<V, E> tmpv = adj[w];
		presult.push_back(tmpv.value());
		if (presult.size() > 1)
			sccVe.push_back(presult);
		std::cout << tmpv.value() << "\n";
		flag[w] = false;
		st->pop();
	}
}

//---------< construct a 2-D matrix with a given graph>----------
template<typename V, typename E>
std::vector<std::vector<int>> Graph<V, E>::addToMatrix(Graph<V, E> &_g)
{
	_g.initMatrix(_g.size());  //  initial the matrix with '0'
	iterator iter = _g.begin();
	while (iter != _g.end())
	{
		Vertex<V, E> v = *iter;
		for (size_t i = 0; i < v.size(); ++i)  //  search for entire metrix row by row
		{
			Vertex<V, E>::Edge edge = v[i];
			_g.setMatrix(v.id(), _g[edge.first].id());  //  there is an Edge of vertex v
		}
		++iter;
	}
	return _g.matrix;
}

//------------< initial a 2-D s*s matrix>-------------
template<typename V, typename E>
std::vector<std::vector<int>> Graph<V, E>::initMatrix(size_t s)
{
	std::vector<std::vector<int>> temp;
	std::vector<int> row;
	for (unsigned j = 0; j < s; j++)  //  build a row
		row.push_back(0);
	for (unsigned i = 0; i < s; i++)  //  build a matrix
		temp.push_back(row);
	matrix = temp;
	return temp;
}

//------------< set value to given axis>-------------
template<typename V, typename E>
void Graph<V, E>::setMatrix(int x, int y)
{
	matrix[x][y] = 1;
}

//------------< get value to given axis>-------------
template<typename V, typename E>
int Graph<V, E>::getMatrix(int x, int y)
{
	return matrix[x][y];
}

// Display class
// provide some means to output the graph, sort result, matrix and so on.
template<typename V, typename E>
class Display
{
public:
	typedef Graph<V, E> graph;
	typedef Vertex<V, E> vertex;

	static void showVert(Vertex<std::string, std::string> &v)
	{
		std::cout << "\n  id " << v.id() << ": " << (v.value()).c_str();
	}

	static void show(graph& g)
	{
		std::cout << "\n\n  Dependency in Graph";
		std::cout << "\n ---------------------";
		graph::iterator iter = g.begin();
		while (iter != g.end())
		{
			vertex v = *iter;
			std::cout << "\n  vertex id = " << v.id() << ", value = " << (v.value()).c_str();
			for (size_t i = 0; i < v.size(); ++i)
			{
				vertex::Edge edge = v[i];
				std::cout << "\n    edge points to vertex with id = " << g[edge.first].id();
				std::cout << " and value = " << g[edge.first].value().c_str();
				std::cout << ", edge value = " << (edge.second).c_str();
			}
			++iter;
		}
		std::cout << "\n";
	}

	static void showDFS(graph &g)
	{
		std::cout << "\n\n  Names of Vertices with DFS";
		std::cout << "\n ----------------------------";
		g.dfs(g[0], showVert);
		std::cout << "\n";
	}

	static std::vector<Vertex<V, E>> topologicalSort(graph g)
	{
		std::vector< Vertex<V, E> > reV;
		graph _g = g;
		int count = 0;
		while (_g.size() != 0)  //  if finished the sort, we would delete all vertex 
		{
			std::vector< Vertex<V, E> > tempVe = vertsWithoutParents(_g, count);
			count++;
			for (unsigned i = 0; i < tempVe.size(); i++)
				reV.push_back(tempVe[i]);
		}
		return reV;
	}

	static std::vector< Vertex<V, E> > vertsWithoutParents(graph& g, int count)
	{
		std::vector<vertex> noParents;
		std::vector<size_t> parentCount;
		graph::iterator iter = g.begin();
		unsigned i = 0;
		while (i < g.size() + count)
		{
			parentCount.push_back(0);
			i++;
		}
		iter = g.begin();
		while (iter != g.end())
		{
			vertex v = *iter;
			for (size_t i = 0; i<v.size(); i++)
			{
				std::pair<int, E> e = v[i];
				parentCount[e.first]++;
			}
			++iter;
		}
		for (size_t j = 0; j < g.size(); j++)
		{
			if (parentCount[j] == 0)
				noParents.push_back(g[j]);
		}
		g.DeletVertex(noParents);
		return noParents;
	}

	static void showMatrix(std::vector<std::vector<int>> matrix)
	{
		for (unsigned i = 0; i < matrix.size(); i++)
		{
			for (unsigned j = 0; j < matrix.size(); j++)
			{
				std::cout << "  " << matrix[i][j];
			}
			std::cout << "\n";
		}
	}

	static void showTopoSortResult(std::vector<Vertex<V, E>> vvss)
	{
		for (unsigned vc = 0; vc < vvss.size(); vc++)
			Display<std::string, std::string>::showVert(vvss[vc]);
		std::cout << "\n";
	}
};

//----< convert integer to string >--------------------------
inline std::string ToString(size_t i)
{
	std::ostringstream in;
	in << i;
	return in.str();
}

//----< convert string to integer >--------------------------
inline int ToInt(const std::string& str)
{
	std::istringstream in(str);
	int retn;
	in >> retn;
	return retn;
}
