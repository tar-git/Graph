#ifndef GRAPH_H
#define GRAPH_H

#include <memory>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <ostream>

#define IF_GRAPH_ERROR(exp) \
	if(exp != GraphErrors::OK) \
	    return exp;

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

typedef std::map<size_t, GraphVertexData> GraphContainer;

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
	inline size_t GetSize() const { return m_container.size(); }
};

}

#endif
