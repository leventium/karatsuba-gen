module karatsuba_leaf3 (
  input      [2:0] u, v,

  output reg [5:0] r
);

reg [2:0] op1;
reg [3:0] op2;
reg [4:0] op3;

always @* begin
  op1 = u & { 3 { v[0] } };

  op2 = u & { 3 { v[1] } };
  op2 = { op2, { 1'b0 } };

  op3 = u & { 3 { v[2] } };
  op3 = { op3, { 2'b00 } };

  r = op1 + op2 + op3;
end

endmodule
