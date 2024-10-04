module karatsuba_leaf2 (
  input      [1:0] u, v,

  output reg [3:0] r
);

reg [1:0] op1;
reg [2:0] op2;

always @* begin
  op1 = u & { 2 {v[0]} };
  op2 = u & { 2 {v[1]} };
  op2 = { op2, { 1'b0 } };
  r = op1 + op2;
end

endmodule
