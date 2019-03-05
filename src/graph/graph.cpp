#include "graph/graph.h"
#include "stdio.h"

namespace gns {

Graph::Graph()
	: m_size(0), m_container(GraphContainer())
{}

GraphList::GraphList() 
	: Graph()
{}

GraphList::GraphList(const GraphContainer &li)
{
	size_t size      = li.size();
	for(const auto & vert : li){
		
		for(const auto & ne : vert){
			
			if(ne >= size) {
				char buff[100];
				sprintf(buff, "The graph has no vertex '%u'", ne);
				GraphException(std::string(buff));
			}
			
		}
		
	}
	m_container = li;
}

size_t GraphList::AddVertex(const GraphVertex & neighbors)
{
	size_t size = neighbors.size();
	if(size > m_size)          {
		GraphException("Number of neighbors exceeds number of vertices");
	}
	for(const auto & ne : neighbors) {
		if(ne > m_size) {
			char buff[100];
			sprintf(buff, "The graph has no vertex '%u'", ne);
			GraphException(std::string(buff));
		}
	}
	
	m_container.push_back(neighbors);
	return m_size++;
}

}


