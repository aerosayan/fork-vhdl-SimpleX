project compileall 
noview wave 
vsim -gui work.register_file 

add wave -noupdate -divider {register_file} 
add wave -noupdate -expand  -group register_file 
add wave -noupdate -group register_file -radix hex {clk}  
add wave -noupdate -group register_file -radix hex {sel_src1}
add wave -noupdate -group register_file -radix hex {sel_src2} 
add wave -noupdate -group register_file -radix hex {sel_dest} 
add wave -noupdate -group register_file -radix hex {outp_src1}     
add wave -noupdate -group register_file -radix hex {outp_src2}
add wave -noupdate -group register_file -radix hex {alu_in}
add wave -noupdate -group register_file -radix hex {alu_data_in}
add wave -noupdate -group register_file -radix hex {regFile}

add wave -noupdate -group register_file -radix hex {pc_addr_in}
add wave -noupdate -group register_file -radix hex {pc_in}

add wave -noupdate -group register_file -radix hex {memrd}
add wave -noupdate -group register_file -radix hex {data_mem_in}
#add wave -noupdate -group register_file -radix hex {pc_in}
#add wave -noupdate -group register_file -radix hex {save_pc}

add wave -noupdate -group register_file -radix hex {debug_in}
add wave -noupdate -group register_file -radix hex {sel_debug}
add wave -noupdate -group register_file -radix hex {debug_out}
 
restart -f 
view structure 
view signals 
view wave 
#clock of 5 ns period 
force -freeze clk 1 0, 0 {2 ps} -r 4 

force memrd 16#0 0
force alu_in  16#0 0
#force save_pc 0 0

force alu_data_in  16#11112222 200 
force alu_data_in  16#00000000 204  
force alu_in 1 200
force alu_in 0 204
force sel_dest 16#3 200
force sel_dest 16#0 204

force alu_data_in  16#33334444 300 
force alu_data_in  16#00000000 304  
force alu_in 1 300
force alu_in 0 304
force sel_dest 16#6 300
force sel_dest 16#0 304

force debug_in 16#1 4000
force sel_debug 16#0 4000

force debug_in 16#1 4020
force sel_debug 16#1 4020

force debug_in 16#1 4040
force sel_debug 16#2 4040

force debug_in 16#1 4060
force sel_debug 16#3 4060

force debug_in 16#1 4080
force sel_debug 16#4 4080

force debug_in 16#1 4100
force sel_debug 16#5 4100

force debug_in 16#1 4120
force sel_debug 16#6 4120

force debug_in 16#1 4140
force sel_debug 16#7 4140

force debug_in 16#1 4160
force sel_debug 16#8 4160

force debug_in 16#1 4180
force sel_debug 16#9 4180

force debug_in 16#1 4200
force debug_in 16#10 4200

force debug_in 16#1 4220
force debug_in 16#11 4220

force debug_in 16#1 4240
force debug_in 16#12 4240

force debug_in 16#1 4260
force debug_in 16#13 4260

force debug_in 16#1 4280
force debug_in 16#14 4280

force debug_in 16#1 4300
force debug_in 16#15 4300


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
#Run for 130 ns 
run 5000 
 
wave zoom full 