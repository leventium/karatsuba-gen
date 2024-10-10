#ifndef INCLUDE_SRC_KARATSUBA_GENARATOR_H_
#define INCLUDE_SRC_KARATSUBA_GENARATOR_H_

#include <string>
#include <vector>

struct RTLModule {
  std::string name;
  std::string verilog_description;
};

class KaratsubaGenarator {
  struct RTLKaratsubaNode {
    int length;
    std::string name;
    std::string verilog_description;
  };

  static const std::string leaf1;
  static const std::string leaf2;
  static const std::string leaf3;
  static const std::string node;
  static const std::string tb;

  std::vector<RTLKaratsubaNode> mem;

  std::string helper(int n);

public:
  KaratsubaGenarator();
  int generate_multiplier(RTLModule &res, int n);
  int generate_testbench(RTLModule &res, int n, const std::string &top_name);
};

#endif // INCLUDE_SRC_KARATSUBA_GENARATOR_H_
