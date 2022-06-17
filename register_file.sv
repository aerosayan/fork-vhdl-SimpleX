module register_file
(
    input clk,
    input rst,
    input [4:0]  sel_src1,
    input [4:0]  sel_src2,
    input [4:0]  sel_dest,

    input [31:0] alu_data_in,
    input        alu_in,
        
    input [31:0] data_mem_in,

    input        pc_in,
    input [31:0] pc_addr_in,

    input        memrd,

    //debug ports
    input              debug_in,
    input [4:0]        sel_debug,
    output reg [31:0]  debug_out,

    output reg [31:0] outp_src1,
    output reg [31:0] outp_src2
);

reg [31:0] regFile [0:31];

always @(*) begin 
   outp_src1 = regFile[sel_src1];
end

always @(*) begin 
   outp_src2 = regFile[sel_src2];
end


always @(posedge clk)
begin 
    if (alu_in == 1'b1) begin
    regFile[sel_dest] <= alu_data_in; 
    end    
    else if(memrd == 1'b1) begin
    regFile[sel_dest] <= data_mem_in;
    end
    else if(pc_in == 1'b1) begin
        regFile[sel_dest] <= pc_addr_in;
    end

end

always @(*) begin 
    if (debug_in == 1'b1) begin 
       debug_out = regFile[sel_debug];
    end
end

endmodule 