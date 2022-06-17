exec python3 assembler.py &
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
force sel_debug 16#11 1740
force sel_debug 16#12 1760
force sel_debug 16#13 1780
force sel_debug 16#14 1800
force sel_debug 16#15 1820
force sel_debug 16#16 1840
force sel_debug 16#17 1860
force sel_debug 16#18 1880
force sel_debug 16#19 1900
force sel_debug 16#1a 1920
force sel_debug 16#1b 1940
force sel_debug 16#1c 1960
force sel_debug 16#1d 1980
force sel_debug 16#1e 2000
force sel_debug 16#1f 2020



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
run 954100  
 
wave zoom full 