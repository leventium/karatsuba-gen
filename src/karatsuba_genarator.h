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

  const std::string leaf{"module karatsuba_leaf_%d #(\n"
                         "  parameter N = %d\n"
                         ") (\n"
                         "  input  [  N-1:0] u, v,\n"
                         "\n"
                         "  output [2*N-1:0] r\n"
                         ");\n"
                         "\n"
                         "  assign r = u * v;\n"
                         "\n"
                         "endmodule\n"};

  const std::string node{
      "module karatsuba_node_%d #(\n"
      "  parameter N = %d\n"
      ")(\n"
      "  input      [  N-1 : 0] u, v,\n"
      "\n"
      "  output reg [N*2-1 : 0] r\n"
      ");\n"
      "\n"
      "  reg [N-N/2-N%2-1 : 0] a, c;\n"
      "  reg [  N/2+N%2-1 : 0] b, d;\n"
      "  reg [  N/2+N%2+1 : 0] z_op1, z_op2;\n"
      "\n"
      "  always @* begin\n"
      "    a = u[      N-1 : N/2+N%2];\n"
      "    b = u[N/2+N%2-1 :       0];\n"
      "    c = v[      N-1 : N/2+N%2];\n"
      "    d = v[N/2+N%2-1 :       0];\n"
      "\n"
      "    z_op1 = a + b;\n"
      "    z_op2 = c + d;\n"
      "  end\n"
      "\n"
      "  wire [N-N%2-1 : 0] x;\n"
      "  wire [N+N%2-1 : 0] y;\n"
      "  wire [N+N%2+1 : 0] z;\n"
      "\n"
      "  %s multiplier_x (.u(a), .v(c), .r(x));\n"
      "  %s multiplier_y (.u(b), .v(d), .r(y));\n"
      "  %s multiplier_z (.u(z_op1), .v(z_op2), .r(z));\n"
      "\n"
      "  reg [        N-N%2-1 : 0] x_neg;\n"
      "  reg [        N+N%2-1 : 0] y_neg;\n"
      "  reg [          2*N-1 : 0] x_shifted;\n"
      "  reg [        N+N%2+1 : 0] z_minx_miny;\n"
      "  reg [N+N/2+2*(N%2)+1 : 0] z_minx_miny_shifted;\n"
      "\n"
      "  always @* begin\n"
      "    x_shifted           = { x, N+N%2 {1'b0} };\n"
      "    x_neg               = ~x + 1;\n"
      "    y_neg               = ~y + 1;\n"
      "    z_minx_miny         = z + x_neg + y_neg;\n"
      "    z_minx_miny_shifted = { z_minx_miny, N/2+N%2 {1'b0} };\n"
      "    r                   = x_shifted + z_minx_miny_shifted + y;\n"
      "  end\n"
      "\n"
      "endmodule\n"};

  std::vector<RTLKaratsubaNode> mem;

  std::string helper(int n);

public:
  KaratsubaGenarator();
  RTLModule get_karatsuba_multiplier(int n);
};

#endif // INCLUDE_SRC_KARATSUBA_GENARATOR_H_
