module karatsuba_leaf (
  input        u, v,

  output [1:0] r
);

  assign r = u & v;

endmodule
