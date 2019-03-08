#include "graph/graph.h"
#include "stdio.h"

namespace gns {

Graph::Graph() 
	: m_size(0), m_container(GraphContainer())
{}

GraphContainer::const_iterator Graph::begin()
{
	return m_container.cbegin();
}

GraphContainer::const_iterator Graph::end()
{
	return m_container.cend();
}

GraphContainer::const_iterator Graph::FindVertex(const size_t id) const
{
	return m_container.find(id);
}

GraphErrors Graph::InsertVertex(const size_t id, const GraphVertexData & vertex)
{
	GraphErrors result = CheckVertexNeighbors(id, vertex.incoming);
	if(result != GraphErrors::OK){
		return result;
	}
	result = CheckVertexNeighbors(id, vertex.outgoing);
	if(result != GraphErrors::OK){
		return result;
	}
	
	for(const auto & in : vertex.incoming){
		const auto & out_val = vertex.outgoing.find(in.first);
		if(out_val != vertex.outgoing.end() && in.second != out_val->second){ // Для 1 ребра может быть только 1 вес
			fprintf(stderr, "\nincoming vertex weight does not match outgoing weight: %u <-> %u [%u != %u]\n",
				in.first, id, in.second, out_val->second);
			return GraphErrors::WEIGHT_NOT_MATCH;
		}
	}
	
	for(const auto & in : vertex.incoming) {
		m_container[in.first].outgoing[id] = in.second;
	}
	
	for(const auto & in : vertex.outgoing) {
		m_container[in.first].incoming[id] = in.second;
	}

	m_container[id] = vertex;
	return GraphErrors::OK;
}

GraphErrors Graph::EraseVertex(const size_t id)
{
	auto vert = m_container.find(id);
	if(vert == m_container.end()) {
		return GraphErrors::ID_MISSING;
	}
	for(const auto & in : vert->second.incoming){
		m_container[in.first].outgoing.erase(id);
	}
	for(const auto & out : vert->second.outgoing){
		m_container[out.first].incoming.erase(id);
	}
	m_container.erase(id);
	return GraphErrors::OK;
}

GraphErrors Graph::MergeVertices(const size_t dest, const size_t source)
{
	const auto & vdest = m_container.find(dest);
	if(vdest == m_container.end()){
		return GraphErrors::ID_MISSING;
	}
	const auto & vsource = m_container.find(source);
	if(vsource == m_container.end()){
		return GraphErrors::ID_MISSING;
	}
	for(const auto & vd : vsource->second.incoming){
		auto & incoming  = vdest->second.incoming;
		auto neighbour = m_container.find(vd.first);
		if(neighbour == m_container.end()){
			return GraphErrors::ID_MISSING;
		}
		neighbour->second.outgoing.erase(source);
		if(incoming.find(vd.first) == incoming.end()){
			incoming[vd.first] = vd.second;
		}
	}
	for(const auto & vd : vsource->second.outgoing){
		auto & outgoing = vdest->second.outgoing;
		if(outgoing.find(vd.first) == outgoing.end()){
			outgoing[vd.first] = vd.second;
		}
	}
	EraseVertex(source);
}

std::ostream & operator<<(std::ostream &out, const Graph &graph)
{
	for(const auto & vert : graph.m_container) {
		
		out << "\n" << vert.first;
		
		neighbour_t in_refs  = vert.second.incoming;
		out << " in( ";
		for(const auto & in : in_refs) {
			out << "{" << in.first << "," << in.second << "} ";
		}
		out << ")";
		
		neighbour_t out_refs = vert.second.outgoing;
		out << " out( ";
		for(const auto & o : out_refs) {
			out << "{" << o.first << "," << o.second << "} ";
		}
		out << ")";
		
	}
	return out;
}

GraphErrors Graph::CheckVertexNeighbors(const size_t id, const neighbour_t &neigh) const
{
	for(const auto & in : neigh) {
		if(in.first == id) { // Петля
			continue;
		}
		auto vit = m_container.find(in.first);
		if(vit == m_container.end()) {
			fprintf(stderr, "\nthe vector has no vertex '%u'\n", in.first);
			return GraphErrors::ID_MISSING;
		}
	}
	return GraphErrors::OK;
}

}


