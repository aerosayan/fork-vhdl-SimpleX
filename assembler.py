from datetime import date
import os
import getpass
from datetime import datetime
import sys
from os.path import expanduser
import subprocess 
import getopt
import argparse
import time
import os.path
import re
from typing import NamedTuple

##000000 nop
##000001 lui R#, upper2Bytes
##000010 li  R#, lower2Bytes
##000011 add Rdest, Rsrc1, Rscrc2
##100011 sub Rdest, Rsrc1, Rscrc2
##000100 not Rdest, Rsrc1
##000101 and  Rdest, Rsrc1, Rscrc2
##000110 or Rdest, Rsrc1, Rscrc2
##000111 xor Rdest, Rsrc1, Rscrc2
##001000 xnor Rdest, Rsrc1, Rscrc2
##001001 nand Rdest, Rsrc1, Rscrc2
##001010 nor Rdest, Rsrc1, Rscrc2
##001011 shiftl Rdest, Rsrc1
##001100 shiftr Rdest, Rsrc1
##001101 Incr Rsrc
##001110 Decr Rsrc
##001111 load Rdest, [Raddress]
##010000 str Rsrc, [Raddress]
##010001 jmp @addr
##010010 jmp [R#]
##010011 jeq @addr
##010100 jeq [R#]
##010101 jneq @addr
##010110 jneq [R#]
##010111 jg @addr
##011000 jg [R#]
##011001 jge @addr
##011010 jgw [R#]
##011011 jl @addr
##011100 jl [R#]
##011101 jle @addr
##011110 jle [R#]
##011111 cmp
##100010 mov

opcode = {'nop'    :'000000',
          'lui'    :'000001',
          'li'     :'000010',
          'add'    :'000011',
          'sub'    :'100011', 
          'not'    :'000100', 
          'and'    :'000101',
          'or'     :'000110', 
          'xor'    :'000111', 
          'xnor'   :'001000',
          'nand'   :'001001',
          'nor'    :'001010',
          'shiftl' :'001011',
          'shiftr' :'001100',
          'Incr'   :'001101',
          'Decr'   :'001110',
          'load'   :'001111',
          'str'    :'010000',
          'jmp'    :'010001',
          'jeq'    :'010011',
          'jneq'   :'010101',
          'jg'     :'010111',
          'jge'    :'011001',
          'jl'     :'011011',
          'jle'    :'011101',
          'cmp'    :'011111',
          'call'   :'100000',
          'return' :'100001',  
          'mov'    :'100010',
          'jmpa'   :'010100'
          }
           
registers = {'R0':"00000", 
             'R1':"00001",
             'R2':'00010',
             'R3':'00011',
             'R4':'00100',
             'R5':'00101',
             'R6':'00110',
             'R7':'00111',
             'R8':'01000',
             'R9':'01001',
             'R10':'01010',
             'R11':"01011", 
             'R12':"01100",
             'R13':'01101',
             'R14':'01110',
             'R15':'01111',
             'R16':'10000',
             'R17':'10001',
             'R18':'10010',
             'R19':'10011',
             'R20':'10100',
             'R21':'10101',
             'R22':'10110',
             'R23':'10111',
             'R24':'11000',
             'R25':'11001',
             'R26':'11010',
             'R27':'11011',
             'R28':'11100',
             'R29':'11101',
             'R30':'11110',
             'R31':'11111'}

symbol_table = {}
program = []

def pass1(assemblyFile) :
    lines = []
    identifierAddress = 16
    with open(assemblyFile) as f:
        lines = f.readlines()
    pc = 0
    for line in lines:
        line = line.lstrip()
        line = line.replace('\n', '')
       
        if (line.startswith("#") == False and line !="" and line.startswith("//") == False):
            
            components = re.split(',?;?\s+', line)
            print(components)


            if (line.startswith('(') == True):
                labelName = line.replace('(','')
                labelName = labelName.replace(')','')
                symbol_table[labelName] = pc
            elif(components[0] == "li" and components[2].isnumeric() == False):
                symbol_table[components[2]] = identifierAddress
                identifierAddress += 1
                pc = pc + 2
            elif(components[0] == "li" and components[2].isnumeric() == True):
                pc = pc + 2
            else:
                pc = pc + 1
    print(symbol_table)
    print("number of instructions = " + str(pc))

def generate_memory_list():
    f = open("memory.list", "w")
    for assemCode in program:
        if (assemCode.startswith("--")== False):
            decimal = int(assemCode, 2)
            hex_string = hex(decimal)
            hex_string = hex_string.replace('0x', '')
            hex_string = hex_string.zfill(8)
            print(hex_string) 
            f.write(hex_string + '\n')


def generate_rom_vhdl():
    f = open("rom.vhd", "w")
    f.write("-------------------------------------------\n")
    f.write("---- ROM example\n")
    f.write("-------------------------------------------\n")
    f.write("library ieee;\n")
    f.write("use ieee.std_logic_1164.all;\n")
    f.write("use ieee.numeric_std.all;\n")
    f.write("-------------------------------------------\n")
    f.write("entity rom is\n")
    f.write("   port(\n")
    f.write("         address: in std_logic_vector(31 downto 0);--integer range 0 to 31;\n")
    f.write("         rom_out: out std_logic_vector(31 downto 0)\n")
    f.write("       );\n")
    f.write("end entity;\n")
    f.write("--------------------------------------------\n")
    f.write("architecture rtl of rom is\n")
    f.write("   signal address_reg : std_logic_vector(31 downto 0);\n")
    f.write("   type memory is array (0 to 1024) of std_logic_vector(31 downto 0);\n")
    f.write("   \n")
    f.write("   constant myrom :memory :=\n")
    f.write("   (\n")
    pc = 0
    for assemCode in program:
        if (assemCode.startswith("--")):
            f.write('      '  + assemCode)
        else:
            f.write('      '  + str(pc) + '=>"' + assemCode + '",\n')
            pc += 1
    f.write("\n")
    f.write("      others=>\"00000000000000000000000000000000\"\n")
    f.write("   );\n")
    f.write("   \n")
    f.write("begin\n")
    f.write("   process (address)\n")
    f.write("   begin\n")
    f.write("         rom_out <= myrom(to_integer(unsigned(address)));\n")
    f.write("   end process;\n")
    f.write("   \n")
    f.write("end rtl;\n")
    

def assemble(assemblyFile):
    lines = []
    with open(assemblyFile) as f:
        lines = f.readlines()
    f = open("assembly.txt", "w")
       
    for line in lines:
        line = line.replace('\n', '')
        line = line.lstrip()
        
        if (line.startswith("#") == False and line !="" and line.startswith("//") == False and line.startswith("(") == False):
            components = re.split(',?;?\s+', line)
            for elem in components:
               if(elem ==''):
                  components.remove('')
            #no operation
            if (components[0] == "nop"):
                program.append("--" + line + "\n")
                program.append(components["return"] + "00000000000000000000000000")

            if (components[0] == "call"):
                if (components[1].isnumeric()):
                    hexBinary = bin(int(components[1], 10))[2:].zfill(26)
                    program.append("--" + line + "\n")
                    program.append(opcode["call"] + hexBinary)
                else:
                    address = str(symbol_table[components[1]])
                    hexBinary = bin(int(address, 10))[2:].zfill(26)
                    program.append("--" + line + "\n")
                    program.append(opcode["call"] + hexBinary)

            if (components[0] == "return"):
                program.append("--" + line + "\n")
                program.append(opcode["return"] + "00000000000000000000000000")

            #lui or li operation
            elif (components[0] == "li"):
                if (components[2].startswith("_") == False):
                    literalVal = components[2].replace('0x','')
                 
                    literalVal = bin(int(literalVal))
                    literalVal = literalVal.replace('b','')
                    upperHex = literalVal[16:31].zfill(21)
                    lowerHex = literalVal[0:15].zfill(21)
                    program.append("--" + line + "\n")
                    program.append(opcode["lui"] + registers[components[1]] + str(upperHex))
                    program.append(opcode["li"] + registers[components[1]] + str(lowerHex))
                else:
                    literalVal = str(symbol_table[components[2]])
                    #if (literalVal.isnumeric()):
                    literalVal = literalVal.zfill(8)
                    upperHex = literalVal[0:4]
                    lowerHex = literalVal[4:9] 
                    upperHexBinary = bin(int(upperHex, 10))[2:].zfill(21)
                    lowerHexBinary = bin(int(lowerHex, 10))[2:].zfill(21)
                    program.append("--" + line + "\n")
                    program.append(opcode["lui"] + registers[components[1]] + upperHexBinary)
                    program.append(opcode["li"] + registers[components[1]] + lowerHexBinary)


            if(components[0] == "jmp" or components[0] == "jeq" or components[0] == "jneq" or components[0] == "jg" or components[0] == "jge" or components[0] == "jl" or components[0] == "jle"):
                if (components[1].isnumeric()):
                    hexBinary = bin(int(components[1], 10))[2:].zfill(26)
                    program.append("--" + line + "\n")
                    program.append(opcode[components[0]] + hexBinary)
                else:
                    address = str(symbol_table[components[1]])
                    hexBinary = bin(int(address, 10))[2:].zfill(26)
                    program.append("--" + line + "\n")
                    program.append(opcode[components[0]] + hexBinary)

            if(components[0] == "add" or components[0] == "sub" or components[0] == "and" or components[0] == "or" or components[0] == "xor" or components[0] == "xnor" or components[0] == "nand" or components[0] == "nor"):
                program.append("--" + line + "\n")
                program.append(opcode[components[0]] + registers[components[1]] + registers[components[2]] +  registers[components[3]] +'00000000000')

            if(components[0] == "shiftl" or components[0] == "shiftr"):
                program.append("--" + line + "\n")
                program.append(opcode[components[0]] + registers[components[1]] + registers[components[2]] + "0000000000000000")
            
            if(components[0] == "Incr" or components[0] == "Decr"):
                program.append("--" + line + "\n")
                program.append(opcode[components[0]] + registers[components[1]] + "000000000000000000000")

            if(components[0] == "not"):
                 program.append("--" + line + "\n")
                 program.append(opcode[components[0]] + registers[components[1]] + registers[components[2]] + "0000000000000000")

            if(components[0] == "load" or components[0] == "str" or components[0] == "cmp"):
                program.append("--" + line + "\n")
                program.append(opcode[components[0]] + registers[components[1]] + registers[components[2]] + "0000000000000000")

            if(components[0] == "mov"):
                program.append("--" + line + "\n")
                program.append(opcode[components[0]] + registers[components[1]] + registers[components[2]] + "0000000000000000")

            if(components[0] == "jmpa"):
                 program.append("--" + line + "\n")
                 program.append(opcode[components[0]] + registers[components[1]] + "000000000000000000000")


    #generate_rom_vhdl()
    generate_memory_list()
    f.close()


def main():
    arguments = len(sys.argv)
    pass1("assembly.asm")
    assemble("assembly.asm")


if __name__ == "__main__":
    main() 
