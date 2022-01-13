module alu_test_bench;
    reg [7:0] A;
    reg [7:0] B;
    reg [1:0] op_code;
  reg c_in ;
  wire [7:0] y;
  wire c_out ;
 ALU alu_tb(.A(A),.B(B),.op_code(op_code),.c_in(c_in), .y(y),.c_out(c_out));
    initial 
      begin
        $dumpfile("dump.vcd");
  	$dumpvars(0);
        A = 8'b11111100 ;
        B = 8'b01100101 ;
        c_in = 1'b1 ;
        $display("Carry In : %b",c_in);
        op_code = 2'b00; #100;$display("Result : %b Carry Out :  %b",y,c_out);
        op_code = 2'b01; #100;$display("Result : %b Carry Out :  %b",y,c_out);
        op_code = 2'b10; #100;$display("Result for OR gate : %b ",y);
        op_code = 2'b11; #100;$display("Result for AND gate : %b ",y);
        c_in = 1'b0 ;
        $display("Carry In : %b",c_in);
        op_code = 2'b00; #100;$display("Result : %b Carry Out :  %b",y,c_out);
        op_code = 2'b01; #100;$display("Result : %b Carry Out :  %b",y,c_out);
        op_code = 2'b10; #100;$display("Result for OR gate : %b ",y);
        op_code = 2'b11; #300;$display("Result for AND gate : %b ",y);     
    end
endmodule
