module pc
(
    input               clk,
    input               rst,          
    input [31:0]        pc_loaded_address,
    input [31:0]        pc_alu_address,
    input               pc_load_imm_ctrl,
    input               pc_load_alu_ctrl,
    input               halt,
    output reg [31:0]  instr_address,
    output reg [31:0]  instr_address_plus1
);
reg [31:0] prog_counter;


always @(posedge clk) begin
    if (rst == 1'b1) begin
       prog_counter <= 0;
    end
    else begin
          if (pc_load_imm_ctrl == 1'b1) begin 
            prog_counter <= pc_loaded_address;
          end 
          
          else if (pc_load_alu_ctrl == 1'b1) begin 
            prog_counter <= pc_alu_address;
          end 

          else if (halt == 1'b1) begin 
            prog_counter <= prog_counter;
          end

          else begin 
            prog_counter <= prog_counter + 1;
          end;
    end;   
end

 always @(*) begin 
    instr_address <= prog_counter;
    instr_address_plus1 <= prog_counter + 1;
end 

endmodule
