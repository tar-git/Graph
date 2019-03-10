#ifndef GRAPH_H
#define GRAPH_H

#include <memory>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <ostream>
#include <algorithm>

#define IF_GRAPH_ERROR(exp, err) \
	(err) = (exp); \
	if((err) != GraphErrors::OK) { \
	    return (err); \
	}

namespace gns {

class Graph;

typedef std::shared_ptr<Graph> GraphPtr;

enum class GraphErrors {OK, ID_MISSING, WEIGHT_NOT_MATCH};

typedef std::map<size_t, size_t> neighbour_t; //<id, weight>

struct GraphVertexData {
	neighbour_t incoming;
	neighbour_t outgoing;
	inline void clear() {incoming.clear(); outgoing.clear();}
};

typedef std::pair<size_t, GraphVertexData> GraphVertex;

typedef std::pair<size_t, neighbour_t> AdjacencyListNode;

typedef std::map<size_t, GraphVertexData> GraphContainer;

typedef std::map<size_t, neighbour_t> AdjacencyList;

typedef std::vector<std::vector<size_t>> AdjacencyMatrix;

class GraphException : public std::runtime_error
{
public:
	GraphException(const std::string & text) : runtime_error(text) {}
};

class Graph
{
	friend std::ostream & operator<<(std::ostream & out, const Graph & graph);
	GraphContainer m_container;
	GraphErrors CheckVertexNeighbors(const size_t id, const neighbour_t & neigh) const;
	void ClearVertexConnections(const size_t id);
public:
	Graph();
	Graph(const AdjacencyList & alist);
	Graph(const AdjacencyMatrix & matrix);
	Graph(const std::initializer_list<AdjacencyListNode> & inlist);
	~Graph() {}
	Graph(const Graph & right);
	Graph(Graph && right);
	Graph & operator=(const Graph & right);
	Graph & operator=(Graph && right);	
	Graph operator+(const Graph & right);
	GraphContainer::const_iterator begin() const;
	GraphContainer::const_iterator end() const;
	GraphContainer::const_iterator FindVertex(const size_t id) const;
	GraphErrors InsertVertex(const size_t id, const GraphVertexData & vertex = GraphVertexData());
	GraphErrors AddVertex(const GraphVertex & vertex);
	GraphErrors EraseVertex(const size_t id);
	GraphErrors MergeVertices(const size_t dest, const size_t source);
	GraphPtr GraphUnion(const Graph & right);
	void SetAdjacencyList(const AdjacencyList & alist);
	void SetAdjacencyMatrix(const AdjacencyMatrix & matrix);
	inline size_t GetSize() const { return m_container.size(); }
};

}

#endif
