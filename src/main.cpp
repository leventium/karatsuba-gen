#include "karatsuba_genarator.h"
#include "result.h"
#include <cstdlib>
#include <fstream>
#include <iostream>

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cout << "N must be specified.\nDone.\n";
  }

  int n = std::atoi(argv[1]);
  KaratsubaGenarator gen;
  Result<RTLModule, GenerateError> res = gen.get_karatsuba_multiplier(n);
  if (res.is_error()) {
    std::cout << "N must be integer greater than 0.\nDone.\n";
    return 1;
  }

  std::ofstream file;
  file.open((*res).name + ".v");
  file << (*res).verilog_description;
  file.close();

  std::cout << "Top-level module: " << (*res).name << std::endl;

  return 0;
}
