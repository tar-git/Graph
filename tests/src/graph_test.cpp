#include "gtest/gtest.h"
#include "graph/graph.h"

using namespace gns;

TEST(GraphListTestSuite, DefaultConstructor) {
   
	GraphList graph;
	ASSERT_TRUE(graph.GetSize() == 0);
	
}

TEST(GraphListTestSuite, Constructor) {
   
	GraphContainer con;
	con.push_back(GraphVertex {10, 13});
	con.push_back(GraphVertex {0 , 14});
	
	GraphList graph(con);
	ASSERT_TRUE(graph.GetSize() != 0);
	
}

