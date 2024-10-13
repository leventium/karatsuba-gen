  a = %s;
  b = %s;
  #10;
  expected = a * b;
  if (c == expected)
    $display("%%d * %%d = %%d  --  Ok.", a, b, c);
  else
    $display("%%d * %%d = %%d (%%d)  --  Fail.", a, b, c, expected);
