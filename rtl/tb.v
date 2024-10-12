`timescale 1ns/1ps
module tb #(
  parameter N = %d
);

reg  [  N-1:0] a, b;
wire [N*2-1:0] c;
reg  [N*2-1:0] expected;

%s mult (.u(a), .v(b), .r(c));

reg [1:0] i;

initial begin
  for (i = 0; i < 3; i = i + 1) begin
    a = $unsigned($random) %% (2**N);
    b = $unsigned($random) %% (2**N);
    #10;
    expected = a * b;
    if (c == expected)
      $display("%%d * %%d = %%d  --  Ok.", a, b, c);
    else
      $display("%%d * %%d = %%d ($d)  --  Fail.", a, b, c, expected);
  end
end

endmodule
