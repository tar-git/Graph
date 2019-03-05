#include "graph/graph.h"
#include "stdio.h"

namespace gns {

Graph::Graph()
	: m_size(0), m_container(GraphContainer())
{}

GraphList::GraphList() 
	: Graph()
{}

GraphErrors GraphList::AddVertex(const size_t id, const GraphListVertex & vertex)
{
	for(const auto & in : vertex.incoming){
		auto vit = m_container.find(in.first);
		if(vit == m_container.end()){
			return GraphErrors::ID_MISSING;
		}
		else{
			vit->second.outgoing[id] = in.second;
		}
	}
	for(const auto & out : vertex.outgoing){
		auto vit = m_container.find(out.first);
		if(vit == m_container.end()){
			return GraphErrors::ID_MISSING;
		}
		else{
			vit->second.incoming[id] = out.second;
		}
	}
	m_container[id] = vertex;
	return GraphErrors::OK;
}

}


