project compileall 
noview wave 
vsim -gui work.alu 

add wave -noupdate -divider {alu} 
add wave -noupdate -expand  -group alu 
add wave -noupdate -group alu -radix hex {in1}
add wave -noupdate -group alu -radix hex {in2} 
add wave -noupdate -group alu -radix hex {outp} 
add wave -noupdate -group alu -radix hex {alu_mux_out}
add wave -noupdate -group alu -radix hex {equ}        
add wave -noupdate -group alu -radix hex {nequ}
add wave -noupdate -group alu -radix hex {biggerThan}   
add wave -noupdate -group alu -radix hex {lessThan}    
add wave -noupdate -group alu -radix hex {biggerEqual}  
add wave -noupdate -group alu -radix hex {lessThanEqual}
add wave -noupdate -group alu -radix dec {func}  
add wave -noupdate -group alu -radix hex {alu_imm_in}
add wave -noupdate -group alu -radix dec {alu_imm}  
 
restart -f 
view structure 
view signals 
view wave 


force in1 16#00000001 0 
force in2 16#00000002 0
force alu_imm 0 0
force func 1

#force in1 16#00000001 200 
#force in2 16#00000002 200
#force func 16#4 200

#force in1 16#00000001 250 
#force in2 16#00000002 250
#force func 16#1 250

#force in1 16#00000001 300 
#force in2 16#00000002 300
#force func 16#2 300

#force in1 16#00000001 350 
#force in2 16#00000002 350
#force func 16#3 350

#force in1 16#00000001 400 
#force in2 16#00000002 400
#force func 16#4 400

#force in1 16#00000001 450 
#force in2 16#00000002 450
#force func 16#5 450

force in1 16#00000001 500 
force in2 16#00000002 500
force func 16#6 500

#force in1 16#00000001 550 
#force in2 16#00000002 550
#force func 16#7 550

#force in1 16#00000001 600 
#force in2 16#00000002 600
#force func 16#8 600

#force in1 16#0000000a 650 
#force in2 16#00000002 650
#force func 16#9 650

#force in1 16#0000000a 750 
#force in2 16#00000002 750
#force func 13 750

#force in1 16#0000000a 800 
#force in2 16#00000002 800
#force func 14 800

#force in1 16#0000000a 860 
#force in2 16#00000002 860
#force func 15 860




force alu_imm 0 1000
force in1 16#12340000 1000 
force alu_imm_in 16#00005678 1000
force func 16#0 1000

force alu_imm 1 1200
force in1 16#00000002 1200 
force alu_imm_in 16#00000005 1200
force func 16#0 1200

#force in1 16#0000000a 1500 
#force in2 16#00000005 1500
#force func 16 1500

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
run 5000  
 
wave zoom full 