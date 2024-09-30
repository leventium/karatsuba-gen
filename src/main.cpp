#include "karatsuba_genarator.h"
#include <cstdlib>
#include <fstream>
#include <iostream>

int main(int argc, char **argv) {
  int n = std::atoi(argv[1]);
  KaratsubaGenarator gen;
  RTLModule res = gen.get_karatsuba_multiplier(n);

  std::ofstream file;
  file.open(res.name + ".v");
  file << res.verilog_description;
  file.close();

  std::cout << "Top-level module: " << res.name << std::endl;

  return 0;
}
