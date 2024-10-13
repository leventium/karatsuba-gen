#ifndef INCLUDE_SRC_KARATSUBA_GENARATOR_H_
#define INCLUDE_SRC_KARATSUBA_GENARATOR_H_

#include <random>
#include <string>
#include <vector>

struct RTLModule {
  std::string name;
  std::string verilog_description;
};

class KaratsubaGenarator {
private:
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
  static const std::string tb_loop;

  static std::mt19937 mt_rand;

  std::vector<RTLKaratsubaNode> mem;

  std::string helper(int n);
  std::string gen_rand_literal(int width);

public:
  KaratsubaGenarator();
  int generate_multiplier(RTLModule &res, int n);
  int generate_testbench(RTLModule &res, int n, const std::string &top_name);
};

#endif // INCLUDE_SRC_KARATSUBA_GENARATOR_H_
