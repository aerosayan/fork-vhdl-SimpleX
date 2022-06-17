project compileall 
noview wave 
vsim -gui work.rom 

add wave -noupdate -divider {ROM} 
add wave -noupdate -expand  -group ROM 
add wave -noupdate -group ROM -radix hex {address} 
add wave -noupdate -group ROM -radix hex {rom_out} 
add wave -noupdate -group ROM -radix hex {myrom} 
 
restart -f 
view structure 
view signals 
view wave 
#clock of 5 ns period 

force address 16#0000 0
force address 16#0001 100
force address 16#0002 200
force address 16#0003 300
 
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
run 1300  
 
wave zoom full 