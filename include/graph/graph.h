#ifndef GRAPH_H
#define GRAPH_H

#include <memory>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <ostream>

namespace gns {

enum class GraphErrors {OK, ID_MISSING, WEIGHT_NOT_MATCH};

typedef std::map<size_t, size_t> neighbour_t; //<id, weight>

struct GraphVertexData {
	neighbour_t incoming;
	neighbour_t outgoing;
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
	size_t         m_size;
	GraphErrors CheckVertexNeighbors(const size_t id, const neighbour_t & neigh) const;
public:
	Graph();
	~Graph() {}
	Graph(const Graph & right);
	Graph(Graph && right);
	Graph & operator=(const Graph & right);
	Graph & operator=(Graph && right);	
	GraphContainer::const_iterator begin();
	GraphContainer::const_iterator end();
	GraphContainer::const_iterator FindVertex(const size_t id) const;
	GraphErrors InsertVertex(const size_t id, const GraphVertexData & vertex);
	GraphErrors EraseVertex(const size_t id);
	GraphErrors MergeVertices(const size_t dest, const size_t source);
	inline size_t GetSize() const { return m_container.size(); }
};

}

#endif
