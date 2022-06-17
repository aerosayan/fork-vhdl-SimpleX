project compileall 
noview wave 
vsim -gui work.bidir 

add wave -noupdate -group bidir -radix hex {data_memory_wr}
add wave -noupdate -group bidir -radix hex {data_memory_rd}
add wave -noupdate -group bidir -radix hex {data_bus}
add wave -noupdate -group bidir -radix hex {memrd}
add wave -noupdate -group bidir -radix hex {memwr}

restart -f 
view structure 
view signals 
view wave 

force memrd 0 0
force memwr 0 0
force data_bus 16#zzzzzzzz 0

force data_memory_wr 16#12 0

force memwr 1 100
force memwr 0 104


force data_bus 16#23 200
force data_bus 16#zz 204
force memrd 1 200
force memrd 0 204


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
run 400  
 
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