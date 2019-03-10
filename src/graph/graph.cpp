#include "graph/graph.h"
#include "stdio.h"

namespace gns {

Graph::Graph() 
	: m_container(GraphContainer())
{}

Graph::Graph(const AdjacencyList & alist){
	SetAdjacencyList(alist);
}

Graph::Graph(const AdjacencyMatrix &matrix)
{
	SetAdjacencyMatrix(matrix);
}

Graph::Graph(const std::initializer_list<AdjacencyListNode> &inlist)
{
	std::set<size_t> duplicates;
	m_container.clear();
	for(const auto & node : inlist){
		size_t id = node.first;
		if(duplicates.find(id) != duplicates.end()){
			continue;
		}
		duplicates.insert(id);
		m_container[id].outgoing = node.second;
		for(const auto & ref : node.second){
			m_container[ref.first].incoming[id] = ref.second;
		}
	}
}

Graph::Graph(const Graph &right)
	: m_container(right.m_container)
{}

Graph::Graph(Graph &&right)
	: m_container(std::move(right.m_container))
{}

Graph & Graph::operator=(const Graph &right)
{
	if(this != &right){
		m_container = right.m_container;
	}
	return *this;
}

Graph & Graph::operator=(Graph && right){
	if(this != &right){
		m_container = std::move(right.m_container);
	}
	return *this;
}

Graph Graph::operator+(const Graph &right)
{
	return *GraphUnion(right);
}

GraphContainer::const_iterator Graph::begin() const
{
	return m_container.cbegin();
}

GraphContainer::const_iterator Graph::end() const
{
	return m_container.cend();
}

GraphContainer::const_iterator Graph::FindVertex(const size_t id) const
{
	return m_container.find(id);
}

GraphErrors Graph::InsertVertex(const size_t id, const GraphVertexData & vertex)
{
	GraphErrors result;
	IF_GRAPH_ERROR(CheckVertexNeighbors(id, vertex.incoming), result);
	IF_GRAPH_ERROR(CheckVertexNeighbors(id, vertex.incoming), result);
	
	for(const auto & in : vertex.incoming){
		const auto & out_val = vertex.outgoing.find(in.first);
		if(out_val != vertex.outgoing.end() && in.second != out_val->second){ // for 1 edge there can be only 1 weight
			fprintf(stderr, "\nincoming vertex weight does not match outgoing weight: %u <-> %u [%u != %u]\n",
				in.first, id, in.second, out_val->second);
			return GraphErrors::WEIGHT_NOT_MATCH;
		}
	}
	
	ClearVertexConnections(id);
	
	for(const auto & in : vertex.incoming) {
		m_container[in.first].outgoing[id] = in.second;
	}
	
	for(const auto & in : vertex.outgoing) {
		m_container[in.first].incoming[id] = in.second;
	}

	m_container[id] = vertex;
	return GraphErrors::OK;
}

GraphErrors Graph::AddVertex(const GraphVertex &vertex)
{
	return InsertVertex(vertex.first, vertex.second);
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
	auto & incoming  = vdest->second.incoming;
	auto & outgoing  = vdest->second.outgoing;
	for(const auto & vd : vsource->second.incoming){
		auto neighbour   = m_container.find(vd.first);
		if(neighbour == m_container.end()){ //Отсутствует узел, указывающий на source
			continue;
		}
		neighbour->second.outgoing.erase(source);
		if(vd.first != dest && incoming.find(vd.first) == incoming.end()){
			incoming[vd.first] = vd.second;
			neighbour->second.outgoing[dest] = vd.second;
		}
	}
	for(const auto & vd : vsource->second.outgoing){
		auto neighbour   = m_container.find(vd.first);
		if(neighbour == m_container.end()){ //Отсутствует узел, на который указывает source
			continue;
		}
		neighbour->second.incoming.erase(source);
		if(vd.first != dest && outgoing.find(vd.first) == outgoing.end()){
			outgoing[vd.first] = vd.second;
			neighbour->second.incoming[dest] = vd.second;
		}
	}
	return EraseVertex(source);
}

GraphPtr Graph::GraphUnion(const Graph &right)
{
	GraphPtr graph(new Graph);
	GraphVertex vertex;
	for(const auto & vert : *this) {
		auto rv = right.FindVertex(vert.first);
		if(rv == right.end()){      // add vertex of this graph
			graph->m_container.insert(vert);
		}
		else{                       // add crossing vertex
			vertex.second.clear();
			vertex.first = vert.first;
			vertex.second.incoming = vert.second.incoming;
			vertex.second.outgoing = vert.second.outgoing;
			for(const auto & neigh : rv->second.incoming){
				vertex.second.incoming.insert(neigh);
			}
			for(const auto & neigh : rv->second.outgoing){
				vertex.second.outgoing.insert(neigh);
			}
			graph->m_container.insert(vertex);
		}
		
	}
	
	for(const auto & vert : right) { // add vertex of right graph
		if(graph->FindVertex(vert.first) == graph->end()){
			graph->m_container.insert(vert);
		}
	}

	return graph;
}

void Graph::SetAdjacencyList(const AdjacencyList &alist)
{
	for(const auto & node : alist){
		m_container[node.first].outgoing = node.second;
		for(const auto & ref : node.second){
			m_container[ref.first].incoming[node.first] = ref.second;
		}
	}
}

void Graph::SetAdjacencyMatrix(const AdjacencyMatrix &matrix)
{
	size_t size = matrix.size();
	for(int i = 0; i < size; ++i){
		if(matrix[i].size() != size){
			m_container.clear();
			fprintf(stderr, "the matrix should be square!");
			return;
		}
		for(int j = 0; j < matrix[i].size(); ++j){
			
			if(matrix[i][j] != 0){
				m_container[i].outgoing[j] = matrix[i][j];
			}
			if(matrix[j][i] != 0){
				m_container[i].incoming[j] = matrix[j][i];
			}
			
		}
	}
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

void Graph::ClearVertexConnections(const size_t id)
{
	auto vit = m_container.find(id);
	if(vit == m_container.end()) {
		return;
	}
	for(const auto & vd : vit->second.incoming){
		auto neit = m_container.find(vd.first);
		if(neit != m_container.end()){
			neit->second.outgoing.erase(id);
		}
	}
	for(const auto & vd : vit->second.outgoing){
		auto neit = m_container.find(vd.first);
		if(neit != m_container.end()){
			neit->second.incoming.erase(id);
		}
	}
}

}


