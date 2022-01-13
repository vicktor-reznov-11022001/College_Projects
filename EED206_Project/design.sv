module ALU(A,B,op_code,c_in,y,c_out);
  input [7:0] A,B;
  input [1:0] op_code;
  input c_in ; 
  output [7:0] y;
  output c_out ;
  reg [8:0] Reg1;
  reg Reg2 ;
    
  assign y = Reg1 ;
  assign c_out = Reg2 ;

  always @(op_code or A or B or c_in)
    begin
        case (op_code)
         2'b00 : Reg1 = A + B + c_in ;
         2'b01 : Reg1 = A - B - c_in ;
         2'b10 : Reg1 = A | B;  
         2'b11 : Reg1 = A & B;  
        endcase 
      Reg2 = Reg1[8];
    end
endmodule
