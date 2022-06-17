project compileall 
noview wave 
vsim -gui work.control_unit 

add wave -noupdate -group control_unit -radix hex {instruction}
add wave -noupdate -group control_unit -radix hex {equ}
add wave -noupdate -group control_unit -radix hex {nequ}
add wave -noupdate -group control_unit -radix hex {biggerThan}
add wave -noupdate -group control_unit -radix hex {lessThan}
add wave -noupdate -group control_unit -radix hex {biggerEqual}
add wave -noupdate -group control_unit -radix hex {lessEqual}
add wave -noupdate -group control_unit -radix hex {halt}
add wave -noupdate -group control_unit -radix hex {alu_in}
add wave -noupdate -group control_unit -radix hex {dataMem_in}
add wave -noupdate -group control_unit -radix hex {pc_in}
add wave -noupdate -group control_unit -radix hex {src1}
add wave -noupdate -group control_unit -radix hex {src2}
add wave -noupdate -group control_unit -radix hex {dest}
add wave -noupdate -group control_unit -radix hex {alu_immediate_in}
add wave -noupdate -group control_unit -radix hex {alu_imm}
add wave -noupdate -group control_unit -radix hex {func}
add wave -noupdate -group control_unit -radix hex {pc_loaded_immediate}
add wave -noupdate -group control_unit -radix hex {pc_alu_immediate}
add wave -noupdate -group control_unit -radix hex {pc_loaded_address}
add wave -noupdate -group control_unit -radix hex {memrd}
add wave -noupdate -group control_unit -radix hex {memwr}
 
restart -f 
view structure 
view signals 
view wave 

force equ 0 0
force nequ 0 0
force biggerThan 0 0
force lessThan 0 0
force biggerEqual 0 0
force lessEqual 0 0

#nop
force instruction 16#34200000 0



#force instruction 2#00000000000000000000000000000000 0 

#jneq @addr
#force nequ 0 500
#force nequ 1 550
#force nequ 0 600
#force instruction 2#01010100000000000000000000000100 500


#add R1, R2, R3 #R1 = R2 + R3
#force instruction 2#000011_00001_00010_00011_0000_0000_000 3200 

#add R1, R2, R3 #R1 = R2 - R3
#force instruction 2#100011_00001_00010_00011_0000_0000_000 3400 

#not R1, R2 # R1 = not(R2)
#force instruction 2#000100_00001_00010_00000_0000_0000_000 3600 

#and R1, R2, R3 #R1 = R2 + R3
#force instruction 2#000101_00001_00010_00011_0000_0000_000 3800 

#or R1, R2, R3 #R1 = R2 + R3
#force instruction 2#000110_00001_00010_00011_0000_0000_000 4000 

#xor R1, R2, R3 #R1 = R2 + R3
#force instruction 2#000111_00001_00010_00011_0000_0000_000 4200 

#xnor R1, R2, R3 #R1 = R2 + R3
#force instruction 2#001000_00001_00010_00011_0000_0000_000 4400 

#incr R1 # increment R1
#force instruction 2#001101_00001_00000_00000_0000_0000_000 4600 

#decr R1 # decrement R1
#force instruction 2#001110_00001_00000_00000_0000_0000_000 4800 

#jmp @address
#force instruction 2#010001_00_0110_0101_0100_0011_0010_0001 5000 

#jmp [R3]
#force instruction 2#010010_00011_001010100001100100001 5200



#jneq [R8]
#force nequ 0 5800
#force nequ 1 6000
#force nequ 0 6200
#force instruction 2#010110_01000_000000000000000000000  5800

#jeq @addr
#force equ 0 6000
#force equ 1 6200
#force equ 0 6400
#force instruction 2#010011_00_0110_0101_0100_0011_0010_0001 6000

#jeq [R9]
#force equ 0 6400
#force equ 1 6600
#force equ 0 6800
#force instruction 2#010100_01001_000000000000000000000  6400





WaveRestoreZoom {0 ns} {1000 ps} 
TreeUpdate [SetDefaultTree] 
WaveRestoreCursors {130 ns} 
configure wave -namecolwidth 272 
configure wave -valuecolwidth 140 
configure wave -justifyvalue left 
configure wave -signalnamewidth 0 
configure wave -snapdistance 10 
configure wave -datasetprefix 0 
configure wave -rowmargin 4 
configure wave -childrowmargin 2     
#Run for 130 ns 
run 10000  
 
wave zoom full 

set LogicStyleTable(LOGIC_0) {Solid #39ff14 0}
set LogicStyleTable(LOGIC_1) {Solid #39ff14 2}
set LogicStyleTable(LOGIC_DC) {DoubleDash blue 1}
set LogicStyleTable(LOGIC_U) {Solid red 1}
set LogicStyleTable(LOGIC_W) {DoubleDash red 1}
set LogicStyleTable(LOGIC_X) {Solid red 1}
set LogicStyleTable(LOGIC_Z) {Solid blue 1}
set PrefDefault(dark1_bg) #999999999999
set PrefDefault(dark1_fg) #3fff3fff3fff
set PrefDefault(disabled_fg) #7fff7fff7fff
set PrefDefault(fixedFontV2) {{Courier 10 Pitch} 16}
set PrefDefault(footerFont) {{Liberation Sans Narrow} 12 normal roman}
set PrefDefault(footerFontV2) {{Liberation Sans Narrow} 16}
set PrefDefault(inactive_bg) #e0e0e0
set PrefDefault(light1_bg) #e665e665e665
set PrefDefault(light1_fg) #7fff7fff7fff
set PrefDefault(menuFont) {{Liberation Sans Narrow} 12 normal roman}
set PrefDefault(menuFontV2) {{Liberation Sans Narrow} 16}
set PrefDefault(sb_width) 11
set PrefDefault(textFontV2) {{Courier 10 Pitch} 16}
set PrefDefault(treeFont) {{Liberation Sans Narrow} 12 normal roman}
set PrefDefault(treeFontV2) {{Liberation Sans Narrow} 16}
set PrefDefault(troughcolor) #bfffbfffbfff
set PrefDefault(waveFont) {{Liberation Sans Narrow} 12 normal roman}
set PrefDefault(waveFontV2) {{Liberation Sans Narrow} 16}
set PrefDragDrop(Project) {{Verilog {Add to Project} {}} {SystemVerilog {Add to Project} {}} {VHDL {Add to Project} {}} {PSL {Add to Project} {}} {Text {Add to Project} {}} {SystemC {Add to Project} {}} {TCL {Add to Project} {}} {Macro {Add to Project} {}} {VCD {Add to Project} {}} {SDF {Add to Project} {}} {XML {Add to Project} {}} {Logfile {Add to Project} {}} {UCDB {Add to Project} {}} {TDB {Add to Project} {}} {UPF {Add to Project} {}} {PCF {Add to Project} {}} {Project {Add to Project} {}} {VRM {Add to Project} {}} {DebugDatabase {Add to Project} {}} {DebugArchive {Add to Project} {}}}
set PrefDragDrop(Transcript) {{Verilog Open {}} {SystemVerilog Open {}} {VHDL Open {}} {PSL Open {}} {Text Open {}} {SystemC Open {}} {TCL Open {}} {Macro Open {}} {VCD Open {}} {SDF Open {}} {XML Open {}} {Logfile Open {}} {UCDB Open {}} {TDB Open {}} {UPF Open {}} {PCF Open {}} {Project Open {}} {VRM Open {}} {DebugDatabase Open {}} {DebugArchive Open {}}}
set PrefDragDrop(Wave) {{Verilog Open {}} {SystemVerilog Open {}} {VHDL Open {}} {PSL Open {}} {Text Open {}} {SystemC Open {}} {TCL Open {}} {Macro Open {}} {VCD Open {}} {SDF Open {}} {XML Open {}} {Logfile Open {}} {UCDB Open {}} {TDB Open {}} {UPF Open {}} {PCF Open {}} {Project Open {}} {VRM Open {}} {DebugDatabase Open {}} {DebugArchive Open {}}}
set PrefMain(pdfViewer) {}
set PrefWave(displaycommas) 0
set PrefWave(displayfreq) 0
