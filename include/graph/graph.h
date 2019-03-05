#ifndef GRAPH_H
#define GRAPH_H

#include <memory>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <iostream>

namespace gns {

enum class GraphErrors {OK, ID_MISSING};

typedef std::map<size_t, size_t> neighbour_t; //<id, weight>

struct GraphListVertex {
	neighbour_t incoming;
	neighbour_t outgoing;
};

typedef std::map<size_t, GraphListVertex> GraphContainer;

class GraphException : public std::runtime_error
{
public:
	GraphException(const std::string & text) : runtime_error(text) {}
};

class Graph
{
public:
	
	Graph();
	~Graph() {}
	Graph(const Graph & right)             = delete;
	Graph(Graph && right)                  = delete;
	Graph & operator=(const Graph & right) = delete;
	Graph & operator=(Graph && right)      = delete;
	virtual size_t GetSize() const = 0;
	
protected:
	GraphContainer m_container;
	size_t         m_size;
};

class GraphList : public Graph
{
public:
	GraphList();
	~GraphList() {}
	GraphList(const GraphList & right);
	GraphList(GraphList && right);
	GraphList & operator=(const GraphList & right);
	GraphList & operator=(GraphList && right);	
	GraphErrors AddVertex(const size_t id, const GraphListVertex & vertex);
	inline virtual size_t GetSize() const { return m_container.size(); }
};

class GraphMatrix : public Graph
{
public:
	GraphMatrix();
	~GraphMatrix() {}
	GraphMatrix(const GraphMatrix & right);
	GraphMatrix(GraphMatrix && right);
	GraphMatrix & operator=(const GraphMatrix & right);
	GraphMatrix & operator=(GraphMatrix && right);	
};

}



#endif
