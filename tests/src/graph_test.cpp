#include "gtest/gtest.h"
#include "graph/graph.h"

using namespace gns;

TEST(GraphTestSuit, DefaultConstructorSuccess) {
   
	Graph graph;
	ASSERT_TRUE(graph.GetSize() == 0);
	
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
}

TEST(GraphTestSuit, InsertVertexFail) {
   
	Graph graph;
	GraphVertexData vertex;
	GraphErrors first_vertex = graph.InsertVertex(5, vertex);
	ASSERT_TRUE(first_vertex == GraphErrors::OK);
	
	vertex.incoming[4] = 11;
	GraphErrors id_missing = graph.InsertVertex(7, vertex);
	
	ASSERT_TRUE(id_missing == GraphErrors::ID_MISSING);
	
	vertex.incoming.clear();
	
	vertex.incoming[5] = 15;
	vertex.outgoing[5] = 14;
	
	GraphErrors weight_not_match = graph.InsertVertex(3, vertex);
	ASSERT_TRUE(weight_not_match == GraphErrors::WEIGHT_NOT_MATCH);
	
}

TEST(GraphTestSuit, EraseVertexSuccess){
	
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
	
	std::cout << "\n\n" << graph << "\n\n";
	
	for(auto & g : graph){
		size_t id = g.first;
		graph.EraseVertex(id);
		for(auto & gv : graph){
			ASSERT_TRUE(gv.second.incoming.find(id) == gv.second.incoming.end());
			ASSERT_TRUE(gv.second.outgoing.find(id) == gv.second.outgoing.end());
		}
		std::cout << "\n\n" << graph << "\n\n";
	}
	
}

TEST(GraphTestSuit, FindVertexSuccess){
	
	Graph graph;
	GraphVertexData vertex;
	GraphErrors insert_first = graph.InsertVertex(1, vertex);
	ASSERT_TRUE(insert_first == GraphErrors::OK);
	
	GraphErrors unlinked_vertex = graph.InsertVertex(5, vertex);
	ASSERT_TRUE(unlinked_vertex == GraphErrors::OK);
	
	ASSERT_TRUE(graph.FindVertex(1) == graph.begin());
	ASSERT_TRUE(graph.FindVertex(2) == graph.end());
	
}

TEST(GraphTestSuit, FindVertexFail){
	
	Graph graph;
	GraphVertexData vertex;
	GraphErrors insert_first = graph.InsertVertex(1, vertex);
	ASSERT_TRUE(insert_first == GraphErrors::OK);
	
	GraphErrors unlinked_vertex = graph.InsertVertex(5, vertex);
	ASSERT_TRUE(unlinked_vertex == GraphErrors::OK);
	
	ASSERT_FALSE(graph.FindVertex(5) == graph.begin());
}

TEST(GraphTestSuit, TEST){
	
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
	
	graph.MergeVertices(3, 4);
}
