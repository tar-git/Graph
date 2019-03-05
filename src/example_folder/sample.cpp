#include "cpp_school/example_folder/sample.h"

#include <iostream>

namespace sample_ns {
void sayHello(void) noexcept {
  std::cout << "Hello, World!" << std::endl;
}
}  // namespace sample_ns