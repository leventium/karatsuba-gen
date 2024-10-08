module karatsuba_node_%d #(
  parameter N = %d
)(
  input      [  N-1 : 0] u, v,

  output reg [N*2-1 : 0] r
);

  reg [N-N/2-N%%2-1 : 0] a, c;
  reg [  N/2+N%%2-1 : 0] b, d;
  reg [    N/2+N%%2 : 0] z_op1, z_op2;

  always @* begin
    a = u[      N-1 : N/2+N%%2];
    b = u[N/2+N%%2-1 :       0];
    c = v[      N-1 : N/2+N%%2];
    d = v[N/2+N%%2-1 :       0];

    z_op1 = a + b;
    z_op2 = c + d;
  end

  wire [N-N%%2-1 : 0] x;
  wire [N+N%%2-1 : 0] y;
  wire [N+N%%2+1 : 0] z;

  %s multiplier_x (.u(a), .v(c), .r(x));
  %s multiplier_y (.u(b), .v(d), .r(y));
  %s multiplier_z (.u(z_op1), .v(z_op2), .r(z));

  reg [          2*N-1 : 0] x_shifted;
  reg [        N+N%%2+1 : 0] z_minx_miny;
  reg [N+N/2+2*(N%%2)+1 : 0] z_minx_miny_shifted;

  always @* begin
    x_shifted           = { x, { N+N%%2 {1'b0} } };
    z_minx_miny         = z - x - y;
    z_minx_miny_shifted = { z_minx_miny, { N/2+N%%2 {1'b0} } };
    r                   = x_shifted + z_minx_miny_shifted + y;
  end

endmodule
