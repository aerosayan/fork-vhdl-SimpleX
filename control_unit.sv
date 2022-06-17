module control_unit
(
    input [31:0]      instruction,
       
    input             equ,
    input             nequ,
    input             biggerThan,
    input             lessThan,
    input             biggerEqual,
    input             lessEqual,

    input             halt,

    output reg        alu_in,
    output reg        dataMem_in,
    output reg        pc_in,

    output reg [4:0]  src1,
    output reg [4:0]  src2,
    output reg [4:0]  dest,

    output reg [31:0] alu_immediate_in,
    output reg        alu_imm,
    output reg [4:0]  func ,

    output reg        pc_loaded_immediate,
    output reg        pc_alu_immediate,

    output reg [31:0] pc_loaded_address,
       
    output reg        memrd,
    output reg        memwr
);

//000000 nop
//000001 lui R#, upper2Bytes
//000010 li  R#, lower2Bytes
//000011 add Rdest, Rsrc1, Rscrc2
//100011 sub Rdest, Rsrc1, Rscrc2
//000100 not Rdest, Rsrc1
//000101 and  Rdest, Rsrc1, Rscrc2
//000110 or Rdest, Rsrc1, Rscrc2
//000111 xor Rdest, Rsrc1, Rscrc2
//001000 xnor Rdest, Rsrc1, Rscrc2
//001001 nand Rdest, Rsrc1, Rscrc2
//001010 nor Rdest, Rsrc1, Rscrc2
//001011 shiftl Rdest, Rsrc1
//001100 shiftr Rdest, Rsrc1
//001101 Incr Rsrc
//001110 Decr Rsrc
//001111 load Rdest, [Raddress]
//010000 str Rsrc, [Raddress]
//010001 jmp @addr
//010010 jmp [R#]
//010011 jeq @addr
//010100 jeq [R#]
//010101 jneq @addr
//010110 jneq [R#]
//010111 jq @addr
//011000 jg [R#]
//011001 jge @addr
//011010 jgw [R#]
//011011 jl @addr
//011100 jl [R#]
//011101 jle @addr
//011110 jle [R#]
//011111 cmp

always @(*) begin 
    case (instruction[31:26]) 
        6'b000000: begin ////nop
                alu_in <= 1'b0;
                dataMem_in <= 1'b0;
                pc_in <= 1'b0;    
                src1 <= 0;
                src2 <= 0;
                dest <= 0;    
                func <= 0;
                alu_immediate_in <= 0;
                alu_imm <= 1'b0; 
                pc_loaded_immediate <= 1'b0;
                pc_alu_immediate <= 1'b0;
                pc_loaded_address <= 0;              
                memwr <= 1'b0;
                memrd <= 1'b0;
        end
           6'b000001: begin //lui dest,literal ; load the upper 16 bit to R[dest]
                 alu_in <= 1'b1;
                 dataMem_in <= 1'b0;
                 pc_in <= 1'b0;    
                 src1 <= 0;
                 src2 <= 0;
                 dest <= instruction[25: 21];    
                 func <= 0;
                 alu_immediate_in <= {instruction[15: 0] , 16'h0000};
                 alu_imm <= 1'b1; 
                 pc_loaded_immediate <= 1'b0;
                 pc_alu_immediate <= 1'b0;
                 pc_loaded_address <= 0;
                 memwr <= 1'b0;
                 memrd <= 1'b0;
           end 
           6'b000010: begin //li dest,literal ; load the lower 16 bit to R[dest]
                 alu_in <= 1'b1;
                 dataMem_in <= 1'b0;
                 pc_in <= 1'b0;    
                 src1 <= 0;  
                 src2 <= instruction[25: 21]; 
                 dest <= instruction[25:21];    
                 func <= 6;
                 alu_immediate_in <= {16'h0000, instruction[15:0]};
                 alu_imm <= 1'b1; 
                 pc_loaded_immediate <= 1'b0;
                 pc_alu_immediate <= 1'b0;
                 pc_loaded_address <= 0;
                 memwr <= 1'b0;
                 memrd <= 1'b0;
           end
           6'b000011: begin //add  dest, src1, src2
                 alu_in <= 1'b1;
                 dataMem_in <= 1'b0;
                 pc_in <= 1'b0;    
                 src1 <= instruction[20: 16];
                 src2 <= instruction[15:11];
                 dest <= instruction[25:21];    
                 func <= 1;
                 alu_immediate_in <= 0;
                 alu_imm <= 1'b0; 
                 pc_loaded_immediate <= 1'b0;
                 pc_alu_immediate <= 1'b0;
                 pc_loaded_address <= 0;
                 memwr <= 1'b0;
                 memrd <= 1'b0;
            end
           6'b100011: begin //sub  dest, src1, src2
                 alu_in <= 1'b1;
                 dataMem_in <= 1'b0;
                 pc_in <= 1'b0;    
                 src1 <= instruction[20:16];
                 src2 <= instruction[15:11];
                 dest <= instruction[25:21];    
                 func <= 2;
                 alu_immediate_in <= 0;
                 alu_imm <= 1'b0; 
                 pc_loaded_immediate <= 1'b0;
                 pc_alu_immediate <= 1'b0;
                 pc_loaded_address <= 0;
                 memwr <= 1'b0;
                 memrd <= 1'b0;
                 end
           6'b000100: begin //not dest, src1
                 alu_in <= 1'b1;
                 dataMem_in <= 1'b0;
                 pc_in <= 1'b0;    
                 src1 <= instruction[20: 16];
                 src2 <= 0;
                 dest <= instruction[25:21];    
                 func <= 4;
                 alu_immediate_in <= 0;
                 alu_imm <= 1'b0; 
                 pc_loaded_immediate <= 1'b0;
                 pc_alu_immediate <= 1'b0;
                 pc_loaded_address <= 0;
                 memwr <= 1'b0;
                 memrd <= 1'b0;
            end
           6'b000101: begin //and  dest, src1, src2
                 alu_in <= 1'b1;
                 dataMem_in <= 1'b0;
                 pc_in <= 1'b0;    
                 src1 <= instruction[20:16];
                 src2 <= instruction[15:11];
                 dest <= instruction[25:21];    
                 func <= 5;
                 alu_immediate_in <= 0;
                 alu_imm <= 1'b0; 
                 pc_loaded_immediate <= 1'b0;
                 pc_alu_immediate <= 1'b0;
                 pc_loaded_address <= 0;
                 memwr <= 1'b0;
                 memrd <= 1'b0;
            end
           6'b000110: begin //or  dest, src1, src2
                 alu_in <= 1'b1;
                 dataMem_in <= 1'b0;
                 pc_in <= 1'b0;    
                 src1 <= instruction[20:16];
                 src2 <= instruction[15:11];
                 dest <= instruction[25:21];    
                 func <= 6;
                 alu_immediate_in <= 0;
                 alu_imm <= 1'b0; 
                 pc_loaded_immediate <= 1'b0;
                 pc_alu_immediate <= 1'b0;
                 pc_loaded_address <= 0;
                 memwr <= 1'b0;
                 memrd <= 1'b0;
            end
           6'b000111: begin //xor  dest, src1, src2
                 alu_in <= 1'b1;
                 dataMem_in <= 1'b0;
                 pc_in <= 1'b0;    
                 src1 <= instruction[20:16];
                 src2 <= instruction[15:11];
                 dest <= instruction[25:21];    
                 func <= 7;
                 alu_immediate_in <= 0;
                 alu_imm <= 1'b0; 
                 pc_loaded_immediate <= 1'b0;
                 pc_alu_immediate <= 1'b0;
                 pc_loaded_address <= 0;
                 memwr <= 1'b0;
                 memrd <= 1'b0;
            end
           6'b001000: begin //xnor  dest, src1, src2
                 alu_in <= 1'b1;
                 dataMem_in <= 1'b0;
                 pc_in <= 1'b0;    
                 src1 <= instruction[20:16];
                 src2 <= instruction[15:11];
                 dest <= instruction[25:21];    
                 func <= 8;
                 alu_immediate_in <= 0;
                 alu_imm <= 1'b0; 
                 pc_loaded_immediate <= 1'b0;
                 pc_alu_immediate <= 1'b0;
                 pc_loaded_address <= 0;
                 memwr <= 1'b0;
                 memrd <= 1'b0;
            end
           6'b001001: begin //nand  dest, src1, src2
                 alu_in <= 1'b1;
                 dataMem_in <= 1'b0;
                 pc_in <= 1'b0;    
                 src1 <= instruction[20:16];
                 src2 <= instruction[15:11];
                 dest <= instruction[25:21];    
                 func <= 9;
                 alu_immediate_in <= 0;
                 alu_imm <= 1'b0; 
                 pc_loaded_immediate <= 1'b0;
                 pc_alu_immediate <= 1'b0;
                 pc_loaded_address <= 0;
                 memwr <= 1'b0;
                 memrd <= 1'b0;
            end               
           6'b001010: begin //nor  dest, src1, src2
                 alu_in <= 1'b1;
                 dataMem_in <= 1'b0;
                 pc_in <= 1'b0;    
                 src1 <= instruction[20:16];;
                 src2 <= instruction[15:11];
                 dest <= instruction[25:21];    
                 func <= 10;
                 alu_immediate_in <= 0;
                 alu_imm <= 1'b0; 
                 pc_loaded_immediate <= 1'b0;
                 pc_alu_immediate <= 1'b0;
                 pc_loaded_address <= 0;
                 memwr <= 1'b0;
                 memrd <= 1'b0;
            end
           6'b001011: begin //shiftl  dest, src1, src2
                 alu_in <= 1'b1;
                 dataMem_in <= 1'b0;
                 pc_in <= 1'b0;    
                 src1 <= instruction[20:16];;
                 src2 <= instruction[15:11];
                 dest <= instruction[25:21];    
                 func <= 11;
                 alu_immediate_in <= 0;
                 alu_imm <= 1'b0; 
                 pc_loaded_immediate <= 1'b0;
                 pc_alu_immediate <= 1'b0;
                 pc_loaded_address <= 0;
                 memwr <= 1'b0;
                 memrd <= 1'b0;
            end
           6'b001100: begin //shiftl  dest, src1, src2
                 alu_in <= 1'b1;
                 dataMem_in <= 1'b0;
                 pc_in <= 1'b0;    
                 src1 <= instruction[20:16];;
                 src2 <= instruction[15:11];
                 dest <= instruction[25:21];    
                 func <= 12;
                 alu_immediate_in <= 0;
                 alu_imm <= 1'b0; 
                 pc_loaded_immediate <= 1'b0;
                 pc_alu_immediate <= 1'b0;
                 pc_loaded_address <= 0;
                 memwr <= 1'b0;
                 memrd <= 1'b0;
            end
           6'b001101: begin //Incr  R#
                 alu_in <= 1'b1;
                 dataMem_in <= 1'b0;
                 pc_in <= 1'b0;    
                 src1 <= instruction[25:21];
                 src2 <= 0;
                 dest <= instruction[25:21];    
                 func <= 13;
                 alu_immediate_in <= 0;
                 alu_imm <= 1'b0; 
                 pc_loaded_immediate <= 1'b0;
                 pc_alu_immediate <= 1'b0;
                 pc_loaded_address <= 0;
                 memwr <= 1'b0;
                 memrd <= 1'b0;
            end
           6'b001110: begin //Decr  R#
                 alu_in <= 1'b1;
                 dataMem_in <= 1'b0;
                 pc_in <= 1'b0;    
                 src1 <= instruction[25:21];
                 src2 <= 0;
                 dest <= instruction[25:21];    
                 func <= 14;
                 alu_immediate_in <= 0;
                 alu_imm <= 1'b0; 
                 pc_loaded_immediate <= 1'b0;
                 pc_alu_immediate <= 1'b0;
                 pc_loaded_address <= 0;
                 memwr <= 1'b0;
                 memrd <= 1'b0;
            end
           6'b001111: begin //load R7, [R5] load R7 with the contents of memory address in R5
                 alu_in <= 1'b0;
                 dataMem_in <= 1'b1;
                 pc_in <= 1'b0;    
                 src1 <= instruction[20:16];;
                 src2 <= 0;
                 dest <= instruction[25:21];    
                 func <= 0;
                 alu_immediate_in <= 0;
                 alu_imm <= 1'b0; 
                 pc_loaded_immediate <= 1'b0;
                 pc_alu_immediate <= 1'b0;
                 pc_loaded_address <= 0;
                 memwr <= 1'b0;
                 memrd <= 1'b1;
            end
           6'b010000: begin //str R7, [R10] store R7 to memory addressed in R10
                 alu_in <= 1'b0;
                 dataMem_in <= 1'b0;
                 pc_in <= 1'b0;    
                 src1 <= instruction[20:16];;
                 src2 <= instruction[25: 21];
                 dest <= 0;    
                 func <= 0;
                 alu_immediate_in <= 0;
                 alu_imm <= 1'b0; 
                 pc_loaded_immediate <= 1'b0;
                 pc_alu_immediate <= 1'b0;
                 pc_loaded_address <= 0;
                 memwr <= 1'b1;
                 memrd <= 1'b0;
            end
           6'b010001: begin //jump #address
                 alu_in <= 1'b0;
                 dataMem_in <= 1'b0;
                 pc_in <= 1'b0;    
                 src1 <= 0;
                 src2 <= 0;
                 dest <= 0;    
                 func <= 0;
                 alu_immediate_in <= 0;
                 alu_imm <= 1'b0; 
                 pc_loaded_immediate <= 1'b1;
                 pc_alu_immediate <= 1'b0;
                 pc_loaded_address[16:0] <=  instruction[16:0];
                 memwr <= 1'b0;
                 memrd <= 1'b0;
            end
           6'b010010: begin //jump [R3]]
                 alu_in <= 1'b0;
                 dataMem_in <= 1'b0;
                 pc_in <= 1'b0;    
                 src1 <= instruction[25:21];
                 src2 <= 0;
                 dest <= 0;    
                 func <= 0;
                 alu_immediate_in <= 0;
                 alu_imm <= 1'b0; 
                 pc_loaded_immediate <= 1'b0;
                 pc_alu_immediate <= 1'b1;
                 pc_loaded_address <=  0;
                 memwr <= 1'b0;
                 memrd <= 1'b0;
            end
           6'b010011: begin //jeq #addr
                 alu_in <= 1'b0;
                 dataMem_in <= 1'b0;
                 pc_in <= 1'b0;    
                 src1 <= instruction[25:21];
                 src2 <= instruction[20:16]; 
                 dest <= 0;    
                 func <= 2;
                 alu_immediate_in <= 0;
                 alu_imm <= 1'b0; 
                 pc_loaded_immediate <= 1'b0;
                 pc_alu_immediate <= 1'b0;
                 pc_loaded_immediate <= equ;
                 if(equ == 1'b1) begin
                    pc_loaded_address <= {6'b000000 , instruction[25:0]}; 
                 end
                 else begin
                    pc_loaded_address <= 0;
                 end
                 memwr <= 1'b0;
                 memrd <= 1'b0;
            end
           6'b010100: begin //jeq [R3]]
                 alu_in <= 1'b0;
                 dataMem_in <= 1'b0;
                 pc_in <= 1'b0;    
                 src1 <= instruction[25:21]; // address;
                 src2 <= 0;
                 dest <= 0;    
                 func <= 0;
                 alu_immediate_in <= 0;
                 alu_imm <= 1'b0; 
                 pc_loaded_immediate <= 1'b0;
                 if(equ  == 1'b1) begin
                     pc_alu_immediate <= 1'b1;
                 end
                 else begin
                     pc_alu_immediate <= 1'b0;
                 end
                 pc_loaded_address <=  0;
                 memwr <= 1'b0;
                 memrd <= 1'b0;
            end
           6'b010101: begin //jneq #addr
                 alu_in <= 1'b0;
                 dataMem_in <= 1'b0;
                 pc_in <= 1'b0;    
                 src1 <= instruction[25:21];
                 src2 <= instruction[20:16]; 
                 dest <= 0;    
                 func <= 2;
                 alu_immediate_in <= 0;
                 alu_imm <= 1'b0; 
                 pc_alu_immediate <= 1'b0;
                 pc_loaded_immediate <= nequ;
                 if(nequ == 1'b1) begin
                    pc_loaded_address <= {6'b000000 , instruction[25:0]}; 
                 end
                 else begin
                    pc_loaded_address <= 0;
                 end
                 memwr <= 1'b0;
                 memrd <= 1'b0;
            end
           6'b010110: begin //jneq [R3]]
                 alu_in <= 1'b0;
                 dataMem_in <= 1'b0;
                 pc_in <= 1'b0;    
                 src1 <= instruction[25:21]; // address;
                 src2 <= 0;
                 dest <= 0;    
                 func <= 0;
                 alu_immediate_in <= 0;
                 alu_imm <= 1'b0; 
                 pc_loaded_immediate <= 1'b0;
                 if(nequ  == 1'b1) begin
                    pc_alu_immediate <= 1'b1;
                 end
                 else begin
                    pc_alu_immediate <= 1'b0;
                 end
                 pc_loaded_address <=  0;
                 memwr <= 1'b0;
                 memrd <= 1'b0;
            end            
           6'b010111: begin //jg #addr
                 alu_in <= 1'b0;
                 dataMem_in <= 1'b0;
                 pc_in <= 1'b0;    
                 src1 <= instruction[25:21];
                 src2 <= instruction[20:16]; 
                 dest <= 0;    
                 func <= 2;
                 alu_immediate_in <= 0;
                 alu_imm <= 1'b0; 
                 pc_alu_immediate <= 1'b0;
                 pc_loaded_immediate <= biggerThan;
                 if(biggerThan == 1'b1) begin
                    pc_loaded_address <= {6'b000000 , instruction[25:0]}; 
                 end
                 else begin
                    pc_loaded_address <= 0;
                 end
                
                 memwr <= 1'b0;
                 memrd <= 1'b0;
            end
           6'b011000: begin //jg [R3]]
                 alu_in <= 1'b0;
                 dataMem_in <= 1'b0;
                 pc_in <= 1'b0;    
                 src1 <= instruction[25:21]; // address;
                 src2 <= 0;
                 dest <= 0;    
                 func <= 0;
                 alu_immediate_in <= 0;
                 alu_imm <= 1'b0; 
                 pc_loaded_immediate <= 1'b0;
                 if(biggerThan  == 1'b1) begin
                    pc_alu_immediate <= 1'b1;
                 end
                 else begin
                    pc_alu_immediate <= 1'b0;
                 end
                 pc_loaded_address <=  0;
                 memwr <= 1'b0;
                 memrd <= 1'b0;
            end
           6'b011001: begin //jge #addr
                 alu_in <= 1'b0;
                 dataMem_in <= 1'b0;
                 pc_in <= 1'b0;    
                 src1 <= instruction[25:21];
                 src2 <= instruction[20:16]; 
                 dest <= 0;    
                 func <= 2;
                 alu_immediate_in <= 0;
                 alu_imm <= 1'b0; 
                 pc_alu_immediate <= 1'b0;
                 pc_loaded_immediate <= biggerEqual;
                 if(biggerEqual == 1'b1) begin
                    pc_loaded_address <= {6'b000000 , instruction[25:0]};  
                 end
                 else begin
                    pc_loaded_address <= 0;
                 end
                 memwr <= 1'b0;
                 memrd <= 1'b0;
            end
           6'b011010: begin //jge [R3]]
                 alu_in <= 1'b0;
                 dataMem_in <= 1'b0;
                 pc_in <= 1'b0;    
                 src1 <= instruction[25:21]; // address;
                 src2 <= 0;
                 dest <= 0;    
                 func <= 0;
                 alu_immediate_in <= 0;
                 alu_imm <= 1'b0; 
                 pc_loaded_immediate <= 1'b0;
                 if(biggerEqual == 1'b1) begin
                    pc_alu_immediate <= 1'b1;
                 end
                 else begin
                    pc_alu_immediate <= 1'b0;
                  end
                  pc_loaded_address <=  0;
                  memwr <= 1'b0;
                  memrd <= 1'b0;
            end
           6'b011011: begin //jl #addr
                 alu_in <= 1'b0;
                 dataMem_in <= 1'b0;
                 pc_in <= 1'b0;    
                 src1 <= instruction[25:21];
                 src2 <= instruction[20:16]; 
                 dest <= 0;    
                 func <= 2;
                 alu_immediate_in <= 0;
                 alu_imm <= 1'b0; 
                 pc_alu_immediate <= 1'b0;
                 pc_loaded_immediate <= lessThan;
                 if(lessThan == 1'b1) begin
                    pc_loaded_address <= {6'b000000 , instruction[25:0]}; 
                 end
                 else begin
                    pc_loaded_address <= 0;
                 end
                 memwr <= 1'b0;
                 memrd <= 1'b0;
            end
           6'b011100: begin //jl [R3]
                 alu_in <= 1'b0;
                 dataMem_in <= 1'b0;
                 pc_in <= 1'b0;    
                 src1 <= instruction[25:21]; // address;
                 src2 <= 0;
                 dest <= 0;    
                 func <= 0;
                 alu_immediate_in <= 0;
                 alu_imm <= 1'b0; 
                 pc_loaded_immediate <= 1'b0;
                 if(lessThan == 1'b1) begin
                    pc_alu_immediate <= 1'b1;
                 end
                 else begin
                    pc_alu_immediate <= 1'b0;
                 end
                 pc_loaded_address <=  0;
                 memwr <= 1'b0;
                 memrd <= 1'b0;
            end
           6'b011101: begin//jle #addr
                 alu_in <= 1'b0;
                 dataMem_in <= 1'b0;
                 pc_in <= 1'b0;    
                 src1 <= instruction[25:21];
                 src2 <= instruction[20:16]; 
                 dest <= 0;    
                 func <= 2;
                 alu_immediate_in <= 0;
                 alu_imm <= 1'b0; 
                 pc_alu_immediate <= 1'b0;
                 pc_loaded_immediate <= lessEqual;
                 if(lessEqual == 1'b1) begin
                    pc_loaded_address <= {6'b000000 , instruction[25:0]}; 
                 end
                 else begin
                    pc_loaded_address <= 0;
                 end
                 memwr <= 1'b0;
                 memrd <= 1'b0;
            end
           6'b011110: begin //jle [R3]
                 alu_in <= 1'b0;
                 dataMem_in <= 1'b0;
                 pc_in <= 1'b0;    
                 src1 <= instruction[25:21]; // address;
                 src2 <= 0;
                 dest <= 0;    
                 func <= 0;
                 alu_immediate_in <= 0;
                 alu_imm <= 1'b0; 
                 pc_loaded_immediate <= 1'b0;
                 if(lessEqual == 1'b1) begin
                    pc_alu_immediate <= 1'b1;
                 end 
                 else begin
                    pc_alu_immediate <= 1'b0;
                 end
                 pc_loaded_address <=  0;
                 memwr <= 1'b0;
                 memrd <= 1'b0;
            end
           6'b011111: begin //cmp R1, R2
                 alu_in <= 1'b0;
                 dataMem_in <= 1'b0;
                 pc_in <= 1'b0;    
                 src1 <= instruction[25:21];
                 src2 <= instruction[20:16]; 
                 dest <= 0;    
                 func <= 2;
                 alu_immediate_in <= 0;
                 alu_imm <= 1'b0; 
                 pc_loaded_immediate <= 1'b0;
                 pc_alu_immediate <= 1'b0;
                 pc_loaded_address <=  0;
                 memwr <= 1'b0;
                 memrd <= 1'b0;
            end
           6'b100000: begin //call @addr
                 alu_in <= 1'b0;
                 dataMem_in <= 1'b0;
                 pc_in <= 1'b1;    
                 src1 <= 0;
                 src2 <= 0; 
                 dest <= 26;  // return from a call   
                 func <= 0;
                 alu_immediate_in <= instruction[25:0];
                 alu_imm <= 1'b1; 
                 pc_loaded_immediate <= 1'b0;
                 pc_alu_immediate <= 1'b1;
                 pc_loaded_address <=  0;
                 memwr <= 1'b0;
                 memrd <= 1'b0;
            end
           6'b100001: begin //return
                 alu_in <= 1'b0;
                 dataMem_in <= 1'b0;
                 pc_in <= 1'b0;    
                 src1 <= 26;
                 src2 <= 0; 
                 dest <= 0;    
                 func <= 0;
                 alu_immediate_in <= 0;
                 alu_imm <= 1'b0; 
                 pc_loaded_immediate <= 1'b0;
                 pc_alu_immediate <= 1'b1;
                 pc_loaded_address <=  0;
                 memwr <= 1'b0;
                 memrd <= 1'b0;
            end

            6'b100010: begin //Mov R2, R1
                 alu_in <= 1'b1;
                 dataMem_in <= 1'b0;
                 pc_in <= 1'b0;    
                 src1 <= instruction[20:16];;
                 src2 <= 0;
                 dest <= instruction[25:21];    
                 func <= 0;
                 alu_immediate_in <= 0;
                 alu_imm <= 1'b0; 
                 pc_loaded_immediate <= 1'b0;
                 pc_alu_immediate <= 1'b0;
                 pc_loaded_address <= 0;
                 memwr <= 1'b0;
                 memrd <= 1'b10;
            end
    endcase
end

endmodule 