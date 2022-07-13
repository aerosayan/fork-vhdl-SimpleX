#exec python3 assembler.py &
project compileall 
noview wave 
vsim -gui work.computer

add wave -noupdate -group computer -radix hex {clk}
add wave -noupdate -group computer -radix hex {reset}
add wave -noupdate -group computer -radix hex {halt}
#for debugging
add wave -noupdate -group computer -radix hex {debug_in}
add wave -noupdate -group computer -radix dec {sel_debug}
add wave -noupdate -group computer -radix hex {debug_out}

add wave -noupdate -group computer -radix hex {data_mem_in}
add wave -noupdate -group computer -radix hex {data_mem_out}
add wave -noupdate -group computer -radix hex {mem_addr}
       
add wave -noupdate -group computer -radix hex {memrd}
add wave -noupdate -group computer -radix hex {memwr}
add wave -noupdate -group Instruction -radix dec {instr_addr_out}
add wave -noupdate -group Instruction -radix hex {instruction}

 
restart -f 
view structure 
view signals 
view wave 

#clock of 4 ns period 
force -freeze clk 1 0, 0 {10 ps} -r 20

force reset 1 0
force reset 0 70
#force halt 1 0
force halt 0 0
force debug_in 0 0


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
run 2004100  
 
wave zoom full
