module add_1bit_tb();

reg clock, a, b, cin;
wire sum, cout;

add_1bit add_1bit_0(a, b, cin, sum, cout);

initial begin
    clock = 1;
    a = 0;
    b = 0;
    cin = 0;
    #5 a = 1;
    #10 a = 0;
    #10 b = 1;
    #15 a = 1;
    #15 b = 1;
    #500 $finish;
    $dumpfile("add.vcd");
    $dumpvars;
end

always #5 begin
    clock = ~clock;
    $display("a %d, b %d, cin %d, sum %d, cout %d", a, b, cin, sum, cout);
end

endmodule
