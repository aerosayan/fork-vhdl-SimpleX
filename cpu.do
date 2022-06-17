project compileall 
noview wave 
vsim -gui work.cpu 

add wave -noupdate  -radix hex {clk}
add wave -noupdate -group cpu -radix hex {reset}
add wave -noupdate -group cpu -radix hex {equ_sig}
add wave -noupdate -group cpu -radix hex {nequ_sig}
add wave -noupdate -group cpu -radix hex {halt}
add wave -noupdate -group cpu -radix hex {instruction}
add wave -noupdate -group cpu -radix hex {instr_addr_out}
add wave -noupdate -group cpu -radix hex {next_pc}
add wave -noupdate -group cpu -radix hex {pc_load_imm}
add wave -noupdate -group cpu -radix hex {pc_loaded_address}


add wave -noupdate -group dataMem -radix hex {data_mem_in}
add wave -noupdate -group dataMem -radix hex {data_mem_out}
add wave -noupdate -group dataMem -radix hex {mem_addr}
add wave -noupdate -group dataMem -radix hex {memIn}
add wave -noupdate -group dataMem -radix hex {memrd}
add wave -noupdate -group dataMem -radix hex {memwr}


add wave -noupdate -group alu -radix hex {alu_in1}
add wave -noupdate -group alu -radix hex {alu_in2}
add wave -noupdate -group alu -radix hex {alu_outp}

add wave -noupdate -group alu -radix hex {func}
add wave -noupdate -group alu -radix hex {sel_src1}
add wave -noupdate -group alu -radix hex {sel_src2}
add wave -noupdate -group alu -radix hex {sel_dest}
add wave -noupdate -group alu -radix hex {alu_in}
add wave -noupdate -group alu -radix hex {pc_in}
add wave -noupdate -group alu -radix hex {alu_imm}
   
add wave -noupdate -group alu -radix hex {ctrl_unit_memrd}
add wave -noupdate -group alu -radix hex {equ}
add wave -noupdate -group alu -radix hex {nequ}
add wave -noupdate -group alu -radix hex {biggerThan}
add wave -noupdate -group alu -radix hex {lessThan}
add wave -noupdate -group alu -radix hex {biggerEqual}
add wave -noupdate -group alu -radix hex {lessThanEqual}

         #for debugging
add wave -noupdate -group debug -radix hex {debug_in}
add wave -noupdate -group debug -radix hex {sel_debug}
add wave -noupdate -group debug -radix hex {debug_out}

 
restart -f 
view structure 
view signals 
view wave 

#clock of 4 ns period 
force -freeze clk 1 0, 0 {10 ps} -r 20

force reset 1 0
force reset 0 50

force instruction 16#04200000 200
force instruction 16#08200001 220
force instruction 16#04400000 240
force instruction 16#08400002 260
force instruction 16#0c611000 280



#force instruction 2#00000100001000000000000000000000 200
#force instruction 2#00001000001000000000000000010001 220
#force instruction 2#01000000010000010000000000000000 240



#debug all registers
force debug_in 16#1  1400
force sel_debug 16#0 1400
force sel_debug 16#1 1420
force sel_debug 16#2 1440
force sel_debug 16#3 1460
force sel_debug 16#4 1480
force sel_debug 16#5 1500
force sel_debug 16#6 1520
force sel_debug 16#7 1540
force sel_debug 16#8 1560
force sel_debug 16#9 1580
force sel_debug 16#a 1600
force sel_debug 16#b 1620
force sel_debug 16#c 1640
force sel_debug 16#d 1660
force sel_debug 16#e 1680
force sel_debug 16#f 1700
force sel_debug 16#10 1720
force sel_debug 16#11 1720
force sel_debug 16#12 1720
force sel_debug 16#13 1720
force sel_debug 16#14 1740
force sel_debug 16#15 1720
force sel_debug 16#16 1760
force sel_debug 16#17 1780
force sel_debug 16#18 1800
force sel_debug 16#19 1820
force sel_debug 16#1a 1840
force sel_debug 16#1b 1860
force sel_debug 16#1c 1880
force sel_debug 16#1d 1900
force sel_debug 16#1e 1920
force sel_debug 16#1f 1940


WaveRestoreZoom {0 ns} {1000 ps} 
TreeUpdate [SetDefaultTree] 
WaveRestoreCursors {130 ns} 
configure wave -namecolwidth 212 
configure wave -valuecolwidth 140 
configure wave -justifyvalue left 
configure wave -signalnamewidth 0 
configure wave -snapdistance 10 
configure wave -datasetprefix 0 
configure wave -rowmargin 4 
configure wave -childrowmargin 2    
run 2000  
 
wave zoom full 