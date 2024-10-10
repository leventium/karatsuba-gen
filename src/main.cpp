#include "karatsuba_genarator.h"
#include <cstdlib>
#include <fstream>
#include <iostream>

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cout << "N must be specified.\nDone.\n";
  }

  int n = std::atoi(argv[1]);
  KaratsubaGenarator gen;
  RTLModule multiplier;

  int err = gen.generate_multiplier(multiplier, n);
  if (err) {
    std::cout << "N must be integer greater than 0.\nDone.\n";
    return 1;
  }

  std::ofstream file;
  file.open(multiplier.name + ".v");
  file << multiplier.verilog_description;
  file.close();

  RTLModule testbench;
  err = gen.generate_testbench(testbench, n, multiplier.name);

  file.open("tb.v");
  file << testbench.verilog_description;
  file.close();

  std::cout << "Top-level module: " << multiplier.name << std::endl;
  std::cout << "Testbench: tb.v" << std::endl;
  std::cout << "Done." << std::endl;

  return 0;
}
