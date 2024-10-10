#include "karatsuba_genarator.h"
#include <algorithm>
#include <cstdio>
#include <sstream>
#include <string>

const std::string KaratsubaGenarator::leaf1("module karatsuba_leaf1 (\n"
                                            "  input        u, v,\n"
                                            "\n"
                                            "  output [1:0] r\n"
                                            ");\n"
                                            "\n"
                                            "assign r = u & v;\n"
                                            "\n"
                                            "endmodule\n");
const std::string KaratsubaGenarator::leaf2("module karatsuba_leaf2 (\n"
                                            "  input      [1:0] u, v,\n"
                                            "\n"
                                            "  output reg [3:0] r\n"
                                            ");\n"
                                            "\n"
                                            "reg [1:0] op1;\n"
                                            "reg [2:0] op2;\n"
                                            "\n"
                                            "always @* begin\n"
                                            "  op1 = u & { 2 {v[0]} };\n"
                                            "  op2 = u & { 2 {v[1]} };\n"
                                            "  op2 = { op2, { 1'b0 } };\n"
                                            "  r = op1 + op2;\n"
                                            "end\n"
                                            "\n"
                                            "endmodule\n");
const std::string KaratsubaGenarator::leaf3("module karatsuba_leaf3 (\n"
                                            "  input      [2:0] u, v,\n"
                                            "\n"
                                            "  output reg [5:0] r\n"
                                            ");\n"
                                            "\n"
                                            "reg [2:0] op1;\n"
                                            "reg [3:0] op2;\n"
                                            "reg [4:0] op3;\n"
                                            "\n"
                                            "always @* begin\n"
                                            "  op1 = u & { 3 { v[0] } };\n"
                                            "\n"
                                            "  op2 = u & { 3 { v[1] } };\n"
                                            "  op2 = { op2, { 1'b0 } };\n"
                                            "\n"
                                            "  op3 = u & { 3 { v[2] } };\n"
                                            "  op3 = { op3, { 2'b00 } };\n"
                                            "\n"
                                            "  r = op1 + op2 + op3;\n"
                                            "end\n"
                                            "\n"
                                            "endmodule\n");
const std::string KaratsubaGenarator::node(
    "module karatsuba_node_%d #(\n"
    "  parameter N = %d\n"
    ")(\n"
    "  input      [  N-1 : 0] u, v,\n"
    "\n"
    "  output reg [N*2-1 : 0] r\n"
    ");\n"
    "\n"
    "  reg [N-N/2-N%%2-1 : 0] a, c;\n"
    "  reg [  N/2+N%%2-1 : 0] b, d;\n"
    "  reg [    N/2+N%%2 : 0] z_op1, z_op2;\n"
    "\n"
    "  always @* begin\n"
    "    a = u[      N-1 : N/2+N%%2];\n"
    "    b = u[N/2+N%%2-1 :       0];\n"
    "    c = v[      N-1 : N/2+N%%2];\n"
    "    d = v[N/2+N%%2-1 :       0];\n"
    "\n"
    "    z_op1 = a + b;\n"
    "    z_op2 = c + d;\n"
    "  end\n"
    "\n"
    "  wire [N-N%%2-1 : 0] x;\n"
    "  wire [N+N%%2-1 : 0] y;\n"
    "  wire [N+N%%2+1 : 0] z;\n"
    "\n"
    "  %s multiplier_x (.u(a), .v(c), .r(x));\n"
    "  %s multiplier_y (.u(b), .v(d), .r(y));\n"
    "  %s multiplier_z (.u(z_op1), .v(z_op2), .r(z));\n"
    "\n"
    "  reg [          2*N-1 : 0] x_shifted;\n"
    "  reg [        N+N%%2+1 : 0] z_minx_miny;\n"
    "  reg [N+N/2+2*(N%%2)+1 : 0] z_minx_miny_shifted;\n"
    "\n"
    "  always @* begin\n"
    "    x_shifted           = { x, { N+N%%2 {1'b0} } };\n"
    "    z_minx_miny         = z - x - y;\n"
    "    z_minx_miny_shifted = { z_minx_miny, { N/2+N%%2 {1'b0} } };\n"
    "    r                   = x_shifted + z_minx_miny_shifted + y;\n"
    "  end\n"
    "\n"
    "endmodule\n");

const std::string KaratsubaGenarator::tb(
    "`timescale 1ns/1ps\n"
    "module tb #(\n"
    "  parameter N = %d\n"
    ");\n"
    "\n"
    "reg  [  N-1:0] a, b;\n"
    "wire [N*2-1:0] c;\n"
    "reg  [N*2-1:0] expected;\n"
    "\n"
    "%s mult (.u(a), .v(b), .r(c));\n"
    "\n"
    "initial begin\n"
    "  for (integer i = 0; i < 3; i = i + 1) begin\n"
    "    a = $unsigned($random) %% (2**N);\n"
    "    b = $unsigned($random) %% (2**N);\n"
    "    #10;\n"
    "    expected = a * b;\n"
    "    if (c == expected)\n"
    "      $display(\"%%d * %%d = %%d  --  Ok.\", a, b, c);\n"
    "    else\n"
    "      $display(\"%%d * %%d = %%d ($d)  --  Fail.\", a, b, c, expected);\n"
    "  end\n"
    "end\n"
    "\n"
    "endmodule\n");

KaratsubaGenarator::KaratsubaGenarator() {
  mem.push_back({1, "karatsuba_leaf1", leaf1});
  mem.push_back({2, "karatsuba_leaf2", leaf2});
  mem.push_back({3, "karatsuba_leaf3", leaf3});
}

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

int KaratsubaGenarator::generate_multiplier(RTLModule &res, int n) {
  if (n < 1)
    return 1;
  std::string top_module_name = helper(n);
  std::sort(mem.begin(), mem.end(),
            [](const RTLKaratsubaNode &a, const RTLKaratsubaNode &b) {
              return a.length <= b.length;
            });
  std::stringstream ss;
  for (const RTLKaratsubaNode &node : mem)
    ss << node.verilog_description << "\n";

  res.name = top_module_name;
  res.verilog_description = ss.str();
  return 0;
}

int KaratsubaGenarator::generate_testbench(RTLModule &res, int n,
                                           const std::string &top_name) {
  if (n < 1)
    return 1;

  char buff[700];
  std::snprintf(buff, 700, tb.c_str(), n, top_name.c_str());

  res.name = "tb";
  res.verilog_description = buff;
  return 0;
}
