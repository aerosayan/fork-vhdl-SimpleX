module cpu
(
    input clk, 
    input reset,  

    input halt,

    //for debugging
    input             debug_in,
    input [4:0]       sel_debug,
    output reg [31:0] debug_out,

    input [31:0]      data_mem_in, 
    output reg [31:0] data_mem_out,
    output reg [31:0] mem_addr,
  
    input [31:0]      instruction,
    output reg [31:0] instr_addr_out,

    output reg        memrd ,
    output reg        memwr
);

    logic [31:0]  alu_in1;
    logic [31:0]  alu_in2;
    logic [31:0]  alu_outp;

    logic  [31:0] next_pc;
    logic  ctrl_unit_memrd;
    logic  ctrl_unit_memwr;

    //Register file controls ------------------------
    logic   alu_in;
    logic   memIn;  
    logic   pc_in;

    logic   [4:0] sel_src1;
    logic   [4:0] sel_src2;
    logic   [4:0] sel_dest;
    
    logic  [31:0] alu_immediate_in;
    logic  alu_imm;

    logic  [4:0] func;

    logic  equ_sig;
    logic  nequ_sig;
    logic  biggerThan_sig;
    logic  lessThan_sig;
    logic  biggerEqual_sig;
    logic  lessThanEqual_sig;

    //program counter controls -------------------------
    logic   pc_load_imm;
    logic   alu_load_imm;
    logic   [31:0] pc_loaded_address;
   
    //alu status
    logic   equ;
    logic   nequ;
    logic   biggerThan;
    logic   lessThan;
    logic   biggerEqual;
    logic   lessThanEqual;


   alu alu0(    
    .func(func),
    .in1(alu_in1),
    .in2(alu_in2),
    .alu_imm_in(alu_immediate_in),
    .alu_imm(alu_imm),
    .equ(equ),
    .nequ(nequ),
    .biggerThan(biggerThan),
    .lessThan(lessThan),
    .biggerEqual(biggerEqual),
    .lessThanEqual(lessThanEqual),
    .outp(alu_outp)
);

register_file register_file0(
    .clk(clk),
    .rst(reset),
    .sel_src1(sel_src1),
    .sel_src2(sel_src2),
    .sel_dest(sel_dest),
    .alu_data_in(alu_outp),
    .alu_in(alu_in),
    .data_mem_in(data_mem_in),
    .pc_in(pc_in),
    .pc_addr_in(next_pc),
    .memrd(ctrl_unit_memrd),
    .debug_in(debug_in),
    .sel_debug(sel_debug),
    .debug_out(debug_out),
    .outp_src1(alu_in1),
    .outp_src2(alu_in2)
); 

pc  pc0( 
    .clk(clk),
    .rst(reset),
    .pc_loaded_address(pc_loaded_address),
    .pc_alu_address(alu_outp),
    .pc_load_imm_ctrl(pc_load_imm),
    .pc_load_alu_ctrl(alu_load_imm),
    .halt(halt),
    .instr_address(instr_addr_out),
    .instr_address_plus1(next_pc)
);


control_unit control_unit0(
    .instruction(instruction),
    .equ(equ_sig),
    .nequ(nequ_sig),
    .biggerThan(biggerThan_sig),
    .lessThan(lessThan_sig),
    .biggerEqual(biggerEqual_sig),
    .lessEqual(lessThanEqual_sig),
    .halt(halt),
    .alu_in(alu_in),
    .dataMem_in(memIn),
    .pc_in(pc_in),
    .src1(sel_src1),
    .src2(sel_src2),
    .dest(sel_dest),
    .alu_immediate_in(alu_immediate_in),
    .alu_imm(alu_imm),
    .func (func),
    .pc_loaded_immediate(pc_load_imm),
    .pc_alu_immediate(alu_load_imm),
    .pc_loaded_address(pc_loaded_address),
    .memrd(ctrl_unit_memrd),
    .memwr(ctrl_unit_memwr)
);

always @(posedge clk) begin
    equ_sig <=equ;
    nequ_sig <= nequ;
    biggerThan_sig <= biggerThan;
    lessThan_sig  <= lessThan;
    biggerEqual_sig <= biggerEqual;
    lessThanEqual_sig <= lessThanEqual;
end ;

always @(*) begin
   memrd <= ctrl_unit_memrd;
   memwr <= ctrl_unit_memwr;
   data_mem_out<=alu_in2;
   mem_addr<=alu_outp;
end;

endmodule 