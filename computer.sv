
module computer
(
    input             clk,
    input             rese0,
    input             halt,

    //for debugging
    input             debug_in,
    input [4:0]       sel_debug,
    output reg [31:0] debug_out
);
    logic [31:0]      instr_addr_out;
    logic [31:0]      instruction;

    logic [31:0]      data_mem_in;
    logic [31:0]      data_mem_out;
    logic [31:0]      mem_addr;
    logic             memrd;
    logic             memwr;

    rom rom0(
        .address(instr_addr_out),
        .rom_out(instruction)
    );

    ram ram0(
        .clk(clk),
        .address(mem_addr),
        .memrd(memrd),
        .memwr(memwr),
        .ram_in(data_mem_in),
        .ram_out(data_mem_out)
    );

    cpu cpu0(
        .clk(clk),
        .reset(reset),
        .halt(halt),
        .debug_in(debug_in),
        .sel_debug(sel_debug),
        .debug_out(debug_out),
        .data_mem_in(data_mem_out),
        .data_mem_out(data_mem_in),
        .mem_addr(mem_addr),
        .instruction(instruction),
        .instr_addr_out(instr_addr_out),
        .memrd(memrd),
        .memwr(memwr)
    ); 


endmodule
