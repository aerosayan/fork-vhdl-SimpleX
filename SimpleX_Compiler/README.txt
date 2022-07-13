To Add a new micro-operation to the processor(w.g. multiplication HW support)
==============================================================================

1- Add the new operation to the Veriog in the ALU (alu.sv), for example:
      5'b01111:
            begin
                outp_temp <= alu_mux_out * in2;
            end
2- Add the instruction into the control_unit.sv, for example:
    6'b100100: begin //mul  dest, src1, src2
        alu_in <= 1'b1;
        dataMem_in <= 1'b0;
        pc_in <= 1'b0;    
        src1 <= instruction[20:16];
        src2 <= instruction[15:11];
        est <= instruction[25:21];    
        func <= 15;
        alu_immediate_in <= 0;
        alu_imm <= 1'b0; 
        pc_loaded_immediate <= 1'b0;
        pc_alu_immediate <= 1'b0;
        pc_loaded_address <= 0;
        memwr <= 1'b0;
        memrd <= 1'b0;
    end
3- Add the new mneomic instruction into the assembler, for example in the assembler.cpp:
   opcode_["mul"]    = "100100";
   .
   .
   if(components[0] == "add" or components[0] == "sub" ......if(components[0] == "mul")

4- Add the VM translator bit into the VMTranslator.cpp, for example:
   else if  (components[0] == "mul") 
   { 
      // pop second item
      asm_ << "//" << line << "\n";
      asm_ << "     li R1, " << SP_ << "\n";
      asm_ << "     load R31, R1\n";
      asm_ << "     Decr R31\n";
      asm_ << "     load R12, R31\n";
      asm_ << "     str R31, R1\n";
      // pop first item
      asm_ << "     li R1, " << SP_ << "\n";
      asm_ << "     load R31, R1\n";
      asm_ << "     Decr R31\n";
      asm_ << "     load R13, R31\n";
      asm_ << "     str R31, R1\n";
      // perform operation
      asm_ << "     mul R14, R13, R12\n";
      // push the result
      asm_ << "     li R1, " << SP_ << "\n";
      asm_ << "     load R31, R1\n";
      asm_ << "     str R14, R31\n";
      asm_ << "     Incr R31\n";
      asm_ << "     str R31, R1\n";
   }
