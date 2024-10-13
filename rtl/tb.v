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
%s
end

endmodule
