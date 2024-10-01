module karatsuba_leaf_%d #(
  parameter N = %d
) (
  input  [  N-1:0] u, v,

  output [2*N-1:0] r
);

  assign r = u * v;

endmodule
