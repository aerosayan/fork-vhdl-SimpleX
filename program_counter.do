project compileall 
noview wave 
vsim -gui work.pc 
 
add wave -noupdate -group pc -radix hex {clk} 
add wave -noupdate -group pc -radix hex {rst}       
add wave -noupdate -group pc -radix hex {pc_loaded_address}
add wave -noupdate -group pc -radix hex {pc_alu_address}
add wave -noupdate -group pc -radix hex {pc_load_imm_ctrl}     
add wave -noupdate -group pc -radix hex {pc_load_alu_ctrl}       
add wave -noupdate -group pc -radix hex {halt}         
add wave -noupdate -group pc -radix hex {instr_address}
add wave -noupdate -group pc -radix hex {instr_address_plus1}

restart -f 
view structure 
view signals 
view wave 
#clock of 5 ns period 
#force -freeze clk 1 0, 0 {2 ps} -r 4 
force clk 0,1 2 ps -r 4 ps

force rst 1 0
force rst 0 100

force pc_load_imm_ctrl 0 0 
force pc_load_alu_ctrl 0 0 
force halt 0 0

force halt 1 800
force halt 0 1200

force pc_load_imm_ctrl 1 1400
force pc_load_imm_ctrl 0 1404
force pc_loaded_address 16#00000010 1400
force pc_loaded_address 16#00000000 1404

force halt 1 1600
force halt 0 1800

force pc_load_alu_ctrl 1 2400
force pc_load_alu_ctrl 0 2404
force pc_alu_address 16#12345678 2400
force pc_alu_address 16#00000000 2404


WaveRestoreZoom {0 ns} {1000 ps} 
TreeUpdate [SetDefaultTree] 
WaveRestoreCursors {130 ns} 
configure wave -namecolwidth 212 
configure wave -valuecolwidth 40 
configure wave -justifyvalue left 
configure wave -signalnamewidth 0 
configure wave -snapdistance 10 
configure wave -datasetprefix 0 
configure wave -rowmargin 4 
configure wave -childrowmargin 2     
#Run for 130 ns 
run 5500  
 
wave zoom full 