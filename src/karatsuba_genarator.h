#ifndef INCLUDE_SRC_KARATSUBA_GENARATOR_H_
#define INCLUDE_SRC_KARATSUBA_GENARATOR_H_

#include "result.h"
#include <string>
#include <vector>

struct RTLModule {
  std::string name;
  std::string verilog_description;
};

enum class GenerateError { BelowOne };

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

  std::vector<RTLKaratsubaNode> mem;

  std::string helper(int n);

public:
  KaratsubaGenarator();
  Result<RTLModule, GenerateError> get_karatsuba_multiplier(int n);
};

#endif // INCLUDE_SRC_KARATSUBA_GENARATOR_H_
