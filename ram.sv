module ram
(
    input        clk,
    input [31:0] address,
    input        memrd,
    input        memwr,
    input [31:0] ram_in,
    output reg [31:0] ram_out
);

reg [31:0] myramm[16384]; 

always @(*) begin
   if (memrd) begin
       ram_out <= myramm[address];
   end

end

always @(posedge clk)
begin 
    if (memwr == 1'b1) begin
       myramm[address] <= ram_in;
    end    
end

endmodule