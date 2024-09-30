#include "karatsuba_genarator.h"
#include <algorithm>
#include <cstdio>
#include <sstream>
#include <string>

std::string KaratsubaGenarator::helper(int n) {
  for (const RTLKaratsubaNode &el : mem)
    if (el.length == n)
      return el.name;

  std::string multiplier_x = helper(n / 2);
  std::string multiplier_y = helper(n / 2 + n % 2);
  std::string multiplier_z = helper(n / 2 + n % 2 + 1);

  char *formated_node = new char[2000];
  std::snprintf(formated_node, 2000, node.c_str(), n, n, multiplier_x.c_str(),
                multiplier_y.c_str(), multiplier_z.c_str());

  std::string module_description(formated_node);
  delete[] formated_node;

  char *formated_module_name = new char[200];
  std::snprintf(formated_module_name, 200, "karatsuba_node_%d", n);
  std::string module_name(formated_module_name);
  delete[] formated_module_name;

  mem.push_back(RTLKaratsubaNode{n, module_name, module_description});

  return module_name;
}

RTLModule KaratsubaGenarator::get_karatsuba_multiplier(int n) {
  std::string top_module_name = helper(n);
  std::sort(mem.begin(), mem.end(),
            [](const RTLKaratsubaNode &a, const RTLKaratsubaNode &b) {
              return a.length <= b.length;
            });
  std::stringstream ss;
  for (const RTLKaratsubaNode &node : mem)
    ss << node.verilog_description << "\n";
  return RTLModule{top_module_name, ss.str()};
}
