module karatsuba_leaf1 (
  input        u, v,

  output [1:0] r
);

assign r = u & v;

endmodule
