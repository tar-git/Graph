#include <sstream>

#include "gtest/gtest.h"

#include "cpp_school/example_folder/sample.h"


TEST(TestSuite2, SampleTest) {
  std::stringstream buffer;
  std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
  sample_ns::sayHello();
  std::string text = buffer.str();
  EXPECT_EQ("Hello, World!\n", text);
  std::cout.rdbuf(old);
}
