

module alu
(
    input [4:0]  func,
    input [31:0] in1,
    input [31:0] in2,

    input [31:0] alu_imm_in,
    input        alu_imm,

    output reg equ,
    output reg nequ,
    output reg biggerThan,
    output reg lessThan,
    output reg biggerEqual,
    output reg lessThanEqual,

    output reg [31:0] outp 
);

logic [31:0] outp_temp;
logic [31:0] alu_mux_out;

always @(*) begin
   case(func)
        5'b00000:
                begin
                outp_temp <= alu_mux_out;
                end
        5'b00001:
                begin
                outp_temp <= alu_mux_out + in2;
                end
        5'b00010:
                begin
                outp_temp <= alu_mux_out - in2;
                end   
        5'b00011:
                begin
                outp_temp <= alu_mux_out - in2;
                end  
        5'b00100:
                begin
                outp_temp <= ~alu_mux_out;
                end   
        5'b00101:
                begin
                outp_temp <= alu_mux_out & in2;
                end  
        5'b00110:
                begin
                outp_temp <= alu_mux_out | in2;
                end  
        5'b00111:
                begin
                outp_temp <= alu_mux_out ^ in2;
                end  
        5'b01000:
                begin
                outp_temp <= alu_mux_out ~^ in2;
                end  
        5'b01001:
                begin
                //outp_temp <= alu_mux_out ~| in2;
                end
        5'b01010:
                begin
                outp_temp <= alu_mux_out & in2;
                end
        5'b01011:
                begin
                outp_temp <= alu_mux_out << in2;
                end
        5'b01100:
                begin
                outp_temp <= alu_mux_out >> in2;
                end
        5'b01101:
                begin
                outp_temp <= alu_mux_out + 1;
                end
        5'b01110:
                begin
                outp_temp <= alu_mux_out - 1;
                end
        5'b01111:
                begin
                outp_temp <= alu_mux_out * in2;
                end
   endcase;
end

always @(*) begin
      if(alu_imm == 1'b1) begin 
         alu_mux_out <= alu_imm_in;
      end
      else begin 
         alu_mux_out <= in1;
      end
end 

always @(*)
begin
  equ <= (outp_temp == 0);
  nequ <= !equ;
  biggerThan <= (alu_mux_out > in2);
  biggerEqual <= (biggerThan | equ);
  lessThan <= (alu_mux_out < in2);
  lessThanEqual <= (lessThan | equ);
end

assign outp = outp_temp;

endmodule;
   
