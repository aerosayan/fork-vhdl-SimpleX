module rom
(
    input [31:0] address,
    output reg [31:0] rom_out
);
 
reg [31:0] myrom[8192]; 
	   
always @(*)
begin
    rom_out <= myrom[address];
end


 initial 
 begin
  $readmemh("memory.list", myrom);
 end
	  
endmodule 