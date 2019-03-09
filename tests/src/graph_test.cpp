#include "gtest/gtest.h"
#include "graph/graph.h"

using namespace gns;

void CheckConnections(const Graph & graph) {
	for(auto & vert : graph){
		size_t id = vert.first;
		for(const auto & ref : vert.second.incoming){
			auto vit = graph.FindVertex(ref.first);
			ASSERT_TRUE(vit != graph.end());
			ASSERT_FALSE(vit->second.outgoing.find(id) == vit->second.outgoing.end());
		}
		for(const auto & ref : vert.second.outgoing){
			auto vit = graph.FindVertex(ref.first);
			ASSERT_TRUE(vit != graph.end());
			ASSERT_FALSE(vit->second.incoming.find(id) == vit->second.incoming.end());
		}
	}
}

#define GRAPH_ASSERT_TRUE(err) \
	ASSERT_TRUE(err == GraphErrors::OK);

#define GRAPH_ASSERT_FALSE(err) \
	ASSERT_TRUE(err != GraphErrors::OK);

TEST(GraphTestSuit, DefaultConstructorSuccess) {
   
	Graph graph;
	ASSERT_TRUE(graph.GetSize() == 0);
	
}

TEST(GraphTestSuit, CopyConstructor){
	Graph graph;
	GraphVertexData vertex;
	
	GRAPH_ASSERT_TRUE(graph.InsertVertex(1, vertex));
	GRAPH_ASSERT_TRUE(graph.InsertVertex(2, vertex));
	
	vertex.incoming[1] = 11;
	GRAPH_ASSERT_TRUE(graph.InsertVertex(2, vertex));
	
	vertex.outgoing[2] = 4;
	GRAPH_ASSERT_TRUE(graph.InsertVertex(3, vertex));
	
	Graph g2(graph);
	
	ASSERT_FALSE(&graph == &g2);
	
	for(const auto & v1 : graph){
		auto vd = g2.FindVertex(v1.first);
		ASSERT_FALSE(vd == g2.end());
		for(const auto & in : v1.second.incoming){
			ASSERT_FALSE(vd->second.incoming.find(in.first) == vd->second.incoming.end());
		}
		for(const auto & out : v1.second.outgoing){
			ASSERT_FALSE(vd->second.outgoing.find(out.first) == vd->second.outgoing.end());
		}
	}
	for(const auto & v2 : g2){
		auto vd = graph.FindVertex(v2.first);
		ASSERT_FALSE(vd == graph.end());
		for(const auto & in : v2.second.incoming){
			ASSERT_FALSE(vd->second.incoming.find(in.first) == vd->second.incoming.end());
		}
		for(const auto & out : v2.second.outgoing){
			ASSERT_FALSE(vd->second.outgoing.find(out.first) == vd->second.outgoing.end());
		}
	}
}

TEST(GraphTestSuit, MoveConstructor){
	Graph graph;
	GraphVertexData vertex;
	
	GRAPH_ASSERT_TRUE(graph.InsertVertex(1, vertex));
	GRAPH_ASSERT_TRUE(graph.InsertVertex(2, vertex));
	
	vertex.incoming[1] = 11;
	GRAPH_ASSERT_TRUE(graph.InsertVertex(2, vertex));
	
	vertex.outgoing[2] = 4;
	GRAPH_ASSERT_TRUE(graph.InsertVertex(3, vertex));
	
	Graph g2(std::move(graph));
	
	ASSERT_FALSE(&graph == &g2);
	ASSERT_TRUE(graph.GetSize() == 0);
	ASSERT_FALSE(g2.GetSize() == 0);
	ASSERT_FALSE(g2.FindVertex(1) == g2.end());
	ASSERT_FALSE(g2.FindVertex(2) == g2.end());
	ASSERT_FALSE(g2.FindVertex(3) == g2.end());
}

TEST(GraphTestSuit, AssignmentOperator){
	Graph graph;
	GraphVertexData vertex;
	
	GRAPH_ASSERT_TRUE(graph.InsertVertex(1, vertex));
	GRAPH_ASSERT_TRUE(graph.InsertVertex(2, vertex));
	
	vertex.incoming[1] = 11;
	GRAPH_ASSERT_TRUE(graph.InsertVertex(2, vertex));
	
	vertex.outgoing[2] = 4;
	GRAPH_ASSERT_TRUE(graph.InsertVertex(3, vertex));
	
	Graph g2 = graph;
	
	ASSERT_FALSE(&graph == &g2);
	
	for(const auto & v1 : graph){
		auto vd = g2.FindVertex(v1.first);
		ASSERT_FALSE(vd == g2.end());
		for(const auto & in : v1.second.incoming){
			ASSERT_FALSE(vd->second.incoming.find(in.first) == vd->second.incoming.end());
		}
		for(const auto & out : v1.second.outgoing){
			ASSERT_FALSE(vd->second.outgoing.find(out.first) == vd->second.outgoing.end());
		}
	}
	for(const auto & v2 : g2){
		auto vd = graph.FindVertex(v2.first);
		ASSERT_FALSE(vd == graph.end());
		for(const auto & in : v2.second.incoming){
			ASSERT_FALSE(vd->second.incoming.find(in.first) == vd->second.incoming.end());
		}
		for(const auto & out : v2.second.outgoing){
			ASSERT_FALSE(vd->second.outgoing.find(out.first) == vd->second.outgoing.end());
		}
	}
}

TEST(GraphTestSuit, MoveOperator){
	Graph graph;
	GraphVertexData vertex;
	
	GRAPH_ASSERT_TRUE(graph.InsertVertex(1, vertex));
	GRAPH_ASSERT_TRUE(graph.InsertVertex(2, vertex));
	
	vertex.incoming[1] = 11;
	GRAPH_ASSERT_TRUE(graph.InsertVertex(2, vertex));
	
	vertex.outgoing[2] = 4;
	GRAPH_ASSERT_TRUE(graph.InsertVertex(3, vertex));
	
	Graph g2;
	g2 = std::move(graph);
	
	ASSERT_FALSE(&graph == &g2);
	ASSERT_TRUE(graph.GetSize() == 0);
	ASSERT_FALSE(g2.GetSize() == 0);
	ASSERT_FALSE(g2.FindVertex(1) == g2.end());
	ASSERT_FALSE(g2.FindVertex(2) == g2.end());
	ASSERT_FALSE(g2.FindVertex(3) == g2.end());
}

TEST(GraphTestSuit, InsertVertexSuccess) {
   
	Graph graph;
	GraphVertexData vertex;
	GraphErrors insert_first = graph.InsertVertex(1, vertex);
	ASSERT_TRUE(insert_first == GraphErrors::OK);
	
	GraphErrors unlinked_vertex = graph.InsertVertex(5, vertex);
	ASSERT_TRUE(unlinked_vertex == GraphErrors::OK);
	
	vertex.incoming[1] = 11;
	GraphErrors single_linked_in_vertex = graph.InsertVertex(2, vertex);
	ASSERT_TRUE(single_linked_in_vertex == GraphErrors::OK);
	
	vertex.incoming.clear();
	vertex.outgoing[2] = 4;
	GraphErrors single_linked_out_vertex = graph.InsertVertex(3, vertex);
	ASSERT_TRUE(single_linked_out_vertex == GraphErrors::OK);
	
	vertex.incoming.clear();
	vertex.outgoing.clear();
	vertex.incoming[3] = 5;
	vertex.outgoing[3] = 5;
	GraphErrors double_linked_vertex = graph.InsertVertex(4, vertex);
	ASSERT_TRUE(double_linked_vertex == GraphErrors::OK);
	
//	std::cout << graph << "\n\n";
	
	vertex.incoming.clear();
	vertex.outgoing.clear();
	vertex.outgoing[3] = 1;
	
	GraphErrors insert_existing_vertex = graph.InsertVertex(1, vertex);
	ASSERT_TRUE(insert_existing_vertex == GraphErrors::OK);
	
//	std::cout << graph << "\n\n";
	
	CheckConnections(graph);
}

TEST(GraphTestSuit, InsertVertexFail) {
   
	Graph graph;
	GraphVertexData vertex;
	
	GRAPH_ASSERT_TRUE(graph.InsertVertex(5));
	
	vertex.incoming[4] = 11;
	GraphErrors id_missing = graph.InsertVertex(7, vertex);
	
	ASSERT_TRUE(id_missing == GraphErrors::ID_MISSING);
	
	vertex.incoming.clear();
	
	vertex.incoming[5] = 15;
	vertex.outgoing[5] = 14;
	
	GraphErrors weight_not_match = graph.InsertVertex(3, vertex);
	ASSERT_TRUE(weight_not_match == GraphErrors::WEIGHT_NOT_MATCH);
	
}

TEST(GraphTestSuit, EraseVertexSuccess) {
	
	Graph graph;
	GraphVertexData vertex;
	GraphErrors insert_first = graph.InsertVertex(1, vertex);
	ASSERT_TRUE(insert_first == GraphErrors::OK);
	
	GraphErrors unlinked_vertex = graph.InsertVertex(5, vertex);
	ASSERT_TRUE(unlinked_vertex == GraphErrors::OK);
	
	vertex.incoming[1] = 11;
	GraphErrors single_linked_in_vertex = graph.InsertVertex(2, vertex);
	ASSERT_TRUE(single_linked_in_vertex == GraphErrors::OK);
	
	vertex.incoming.clear();
	vertex.outgoing[2] = 4;
	GraphErrors single_linked_out_vertex = graph.InsertVertex(3, vertex);
	ASSERT_TRUE(single_linked_out_vertex == GraphErrors::OK);
	
	vertex.incoming.clear();
	vertex.outgoing.clear();
	vertex.incoming[3] = 5;
	vertex.outgoing[3] = 5;
	GraphErrors double_linked_vertex = graph.InsertVertex(4, vertex);
	ASSERT_TRUE(double_linked_vertex == GraphErrors::OK);
	
//	std::cout << graph << "\n";
	
	for(auto & g : graph){
		size_t id = g.first;
		graph.EraseVertex(id);
		for(auto & gv : graph){
			ASSERT_TRUE(gv.second.incoming.find(id) == gv.second.incoming.end());
			ASSERT_TRUE(gv.second.outgoing.find(id) == gv.second.outgoing.end());
		}
//		std::cout << graph << "\n";
	}
	
}

TEST(GraphTestSuit, FindVertexSuccess) {
	
	Graph graph;
	GraphVertexData vertex;
	GraphErrors insert_first = graph.InsertVertex(1, vertex);
	ASSERT_TRUE(insert_first == GraphErrors::OK);
	
	GraphErrors unlinked_vertex = graph.InsertVertex(5, vertex);
	ASSERT_TRUE(unlinked_vertex == GraphErrors::OK);
	
	ASSERT_TRUE(graph.FindVertex(1) == graph.begin());
	ASSERT_TRUE(graph.FindVertex(2) == graph.end());
	
}

TEST(GraphTestSuit, FindVertexFail) {
	
	Graph graph;
	GraphVertexData vertex;
	GraphErrors insert_first = graph.InsertVertex(1, vertex);
	ASSERT_TRUE(insert_first == GraphErrors::OK);
	
	GraphErrors unlinked_vertex = graph.InsertVertex(5, vertex);
	ASSERT_TRUE(unlinked_vertex == GraphErrors::OK);
	
	ASSERT_FALSE(graph.FindVertex(5) == graph.begin());
}

TEST(GraphTestSuit, MergeVerticesSuccess) {
	
	Graph graph;
	GraphVertexData vertex;
	GraphErrors result;
	for(int i = 1; i <= 10; ++i){
		result = graph.InsertVertex(i, vertex);
		ASSERT_TRUE(result == GraphErrors::OK);
	}

	vertex.outgoing[1] = 11;
	vertex.outgoing[3] = 5;
	vertex.outgoing[4] = 16;
	vertex.outgoing[5] = 8;
	vertex.outgoing[8] = 12;
	vertex.incoming[4] = 16;
	vertex.incoming[5] = 8;
	
	result = graph.InsertVertex(2, vertex);
	ASSERT_TRUE(result == GraphErrors::OK);
	
//	std::cout << graph << "\n";
	
	vertex.incoming.clear();
	vertex.outgoing.clear();
	
	vertex.outgoing[6]  = 18;
	vertex.outgoing[7]  = 4;
	vertex.outgoing[9]  = 13;
	vertex.outgoing[10] = 9;
	vertex.outgoing[2]  = 72;
	vertex.incoming[9]  = 13;
	vertex.incoming[10] = 9;	
	
	result = graph.InsertVertex(8, vertex);
	ASSERT_TRUE(result == GraphErrors::OK);
	
//	std::cout << graph << "\n";
	GraphErrors merge_success = graph.MergeVertices(2, 8);
	ASSERT_TRUE(merge_success == GraphErrors::OK);
//	std::cout << graph << "\n\n";
	
	CheckConnections(graph);
}

TEST(GraphTestSuit, MergeVerticesFail) {
	Graph graph;
	GraphVertexData vertex;
	GraphErrors result;
	for(int i = 1; i <= 10; ++i){
		result = graph.InsertVertex(i);
		ASSERT_TRUE(result == GraphErrors::OK);
	}

	vertex.outgoing[1] = 11;
	vertex.outgoing[3] = 5;
	vertex.outgoing[4] = 16;
	vertex.outgoing[5] = 8;
	vertex.outgoing[8] = 12;
	vertex.incoming[4] = 16;
	vertex.incoming[5] = 8;
	
	result = graph.InsertVertex(2, vertex);
	
	GraphErrors bad_merge = graph.MergeVertices(1, 11);
	ASSERT_TRUE(bad_merge == GraphErrors::ID_MISSING);
	
	bad_merge = graph.MergeVertices(13, 2);
	ASSERT_TRUE(bad_merge == GraphErrors::ID_MISSING);
}

TEST(GraphTestSuit, GraphUnion) {
	Graph graph1, graph2;
	for(int i = 1; i < 10; i+=2){
		graph1.InsertVertex(i);
		graph2.InsertVertex(i+1);
	}
	graph1.InsertVertex(11);
	graph2.InsertVertex(11);
	
	GraphVertexData vertex;
	vertex.outgoing[1]  = 1;
	vertex.incoming[3]  = 3;
	GRAPH_ASSERT_TRUE(graph1.InsertVertex(5, vertex));
	
	vertex.clear();
	vertex.outgoing[7]  = 7;
	vertex.incoming[7]  = 7;
	vertex.incoming[9]  = 9;
	GRAPH_ASSERT_TRUE(graph1.InsertVertex(11, vertex));
	
	vertex.clear();
	vertex.outgoing[2]  = 2;
	vertex.incoming[2]  = 2;
	vertex.incoming[4]  = 4;
	GRAPH_ASSERT_TRUE(graph2.InsertVertex(6, vertex));
	
	vertex.clear();
	vertex.outgoing[8]   = 8;
	vertex.incoming[10]  = 10;
	GRAPH_ASSERT_TRUE(graph2.InsertVertex(11, vertex));
	
//	std::cout << "Befor union:\n"
//			  << "graph1:\n" << graph1 << "\n\n"
//			  << "graph2:\n" << graph2 << "\n\n";
	
	GraphPtr gptr = graph1.GraphUnion(graph2);
	
//	std::cout << "After union:\n"
//			  << "graph3:\n" << *gptr << "\n\n";
	
	CheckConnections(*gptr);
}

TEST(GraphTestSuit, PlusOperator) {
	Graph graph1, graph2;
	for(int i = 1; i < 10; i+=2){
		graph1.InsertVertex(i);
		graph2.InsertVertex(i+1);
	}
	graph1.InsertVertex(11);
	graph2.InsertVertex(11);
	
	GraphVertexData vertex;
	vertex.outgoing[1]  = 1;
	vertex.incoming[3]  = 3;
	GRAPH_ASSERT_TRUE(graph1.InsertVertex(5, vertex));
	
	vertex.clear();
	vertex.outgoing[7]  = 7;
	vertex.incoming[7]  = 7;
	vertex.incoming[9]  = 9;
	GRAPH_ASSERT_TRUE(graph1.InsertVertex(11, vertex));
	
	vertex.clear();
	vertex.outgoing[2]  = 2;
	vertex.incoming[2]  = 2;
	vertex.incoming[4]  = 4;
	GRAPH_ASSERT_TRUE(graph2.InsertVertex(6, vertex));
	
	vertex.clear();
	vertex.outgoing[8]   = 8;
	vertex.incoming[10]  = 10;
	GRAPH_ASSERT_TRUE(graph2.InsertVertex(11, vertex));
	
//	std::cout << "Befor union:\n"
//			  << "graph1:\n" << graph1 << "\n\n"
//			  << "graph2:\n" << graph2 << "\n\n";
	
	Graph graph3 = graph1 + graph2;
	
//	std::cout << "After union:\n"
//			  << "graph3:\n" << graph3 << "\n\n";
	
	CheckConnections(graph3);
}
