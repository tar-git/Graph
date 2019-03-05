#include "gtest/gtest.h"
#include "graph/graph.h"

using namespace gns;

TEST(GraphListTestSuit, DefaultConstructorSuccess) {
   
//	GraphList graph;
//	ASSERT_TRUE(graph.GetSize() == 0);
	
}

TEST(GraphListTestSuit, AddVertexSuccess) {
   
	GraphListVertex vertex;
	
	GraphList        graph;

	GraphErrors err = graph.AddVertex(size_t(5), vertex);
	
}

