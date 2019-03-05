#ifndef GRAPH_H
#define GRAPH_H

#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <cassert>

namespace gns {

typedef std::vector<std::vector<size_t>> GraphContainer;
typedef std::vector<size_t>              GraphVertex;

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
	inline  size_t GetSize() const { return m_size; }
	virtual size_t AddVertex(const std::vector<size_t> & neighbors) = 0;

	
protected:
	GraphContainer m_container;
	size_t         m_size;
};

class GraphList : public Graph
{
public:
	GraphList();
	GraphList(const GraphContainer & li);
	~GraphList() {}
	GraphList(const GraphList & right);
	GraphList(GraphList && right);
	GraphList & operator=(const GraphList & right);
	GraphList & operator=(GraphList && right);	
	virtual size_t AddVertex(const GraphVertex & neighbors);
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
