from ctypes.wintypes import RGB
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

from matplotlib.font_manager import list_fonts

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

opcode = {'nop'    : '000000',
          'lui'    : '000001',
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
        
          
           'cmp'   :'011111'   
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

SP = "0"
local = "1"
argument = "2"
this = "3"
that = "4"
temp = "5"
static = "6"

SP_pointer = "10"
local_pointer = "40"
argument_pointer = "80"
this_pointer = "1000"
that_pointer = "2000"
temp_pointer = "3000"
static_pointer = "3500"
pointer_pointer = "4000"

label = 0
retAddress = 0

def InitialiseSegments(assemblyFile):
    f = open("assembly.asm", "a")
    f.write("//Initialise Segments\n")
    f.write("//===================\n")
    f.write("//(Initialise_SP)\n")
    f.write("    li R1,  " + SP_pointer + "\n")
    f.write("    li R2, " + SP + "\n")
    f.write("    str R1, R2\n")
    f.write("    \n")
    f.write("//(Initialise_local)\n")
    f.write("    li R3, " + local_pointer + "\n")
    f.write("    li R4, " + local + "\n")
    f.write("    str R3, R4\n")
    f.write("\n")
    f.write("//(Initialise_this)\n")
    f.write("    li R5, " + this_pointer + "\n")
    f.write("    li R6, " + this + "\n")
    f.write("    str R5, R6\n")
    f.write("\n")
    f.write("//(Initialise_that)\n")
    f.write("    li R7, " + that_pointer + "\n")
    f.write("    li R8, " + that + "\n")
    f.write("    str R7, R8\n")
    f.write("\n")
    f.write("//(Initialise_temp)\n")
    f.write("    li R9, " + temp_pointer + "\n")
    f.write("    li R10, " + temp + "\n")
    f.write("    str R9, R10\n")
    f.write("\n")
    f.write("//(Initialise_argument)\n")
    f.write("    li R11, " + argument_pointer + "\n")
    f.write("    li R12, " + argument + "\n")
    f.write("    str R11, R12\n")
    f.write("       \n")
    f.write("//(Initialise_static\n")
    f.write("    li R13, " + static_pointer + "\n")
    f.write("    li R14, " + static + "\n")
    f.write("    str R13, R14\n")
    f.write("       \n")
    f.write("//(Initialise_pointer\n")
    f.write("    li R13, " + pointer_pointer + "\n")
    f.write("    li R14, 7\n")
    f.write("    str R13, R14\n")
               

def VMTranslate(assemblyFile):
    lines = []
    with open(assemblyFile) as f:
        lines = f.readlines()
    f = open("assembly.asm", "w")

    f.write("//Initialise Segments\n")
    f.write("//===================\n")
    f.write("//(Initialise_SP)\n")
    f.write("    li R1,  " + SP_pointer + "\n")
    f.write("    li R2, " + SP + "\n")
    f.write("    str R1, R2\n")
    f.write("    \n")
    f.write("//(Initialise_local)\n")
    f.write("    li R3, " + local_pointer + "\n")
    f.write("    li R4, " + local + "\n")
    f.write("    str R3, R4\n")
    f.write("\n")
    f.write("//(Initialise_this)\n")
    f.write("    li R5, " + this_pointer + "\n")
    f.write("    li R6, " + this + "\n")
    f.write("    str R5, R6\n")
    f.write("\n")
    f.write("//(Initialise_that)\n")
    f.write("    li R7, " + that_pointer + "\n")
    f.write("    li R8, " + that + "\n")
    f.write("    str R7, R8\n")
    f.write("\n")
    f.write("//(Initialise_temp)\n")
    f.write("    li R9, " + temp_pointer + "\n")
    f.write("    li R10, " + temp + "\n")
    f.write("    str R9, R10\n")
    f.write("\n")
    f.write("//(Initialise_argument)\n")
    f.write("    li R11, " + argument_pointer + "\n")
    f.write("    li R12, " + argument + "\n")
    f.write("    str R11, R12\n")
    f.write("       \n")
    f.write("//(Initialise_static\n")
    f.write("    li R13, " + static_pointer + "\n")
    f.write("    li R14, " + static + "\n")
    f.write("    str R13, R14\n")
    f.write("       \n")
    f.write("//(Initialise_pointer\n")
    f.write("    li R13, " + pointer_pointer + "\n")
    f.write("    li R14, 7\n")
    f.write("    str R13, R14\n")

    f.write("//===========================\n\n\n")
    lineNumber = 1
    label = 0
    retAddress = 0
    repeat = 0
    for line in lines:
        line = line.replace('\n', '')
        line = line.lstrip()
        
        #if (line.startswith("#") == False and line !="" and line.startswith("//") == False and line.startswith("(") == False):
        if (line.startswith("#") == False and line !="" and line.startswith("//") == False):

            components = re.split(',?;?\s+', line)
            for elem in components:
               if(elem ==''):
                  components.remove('')
            if (line.startswith("(") == True):
                f.write(components[0] + "\n")
            #push operation
            if (components[0] == "push"):
                if (components[1] == "constant"):
                     f.write("//" + line + "\n")
                     f.write("     li R1, " + SP + "\n")# 0 here is  the SP pointer which is RAM{0]
                     f.write("     load R31, R1\n")
                     f.write("\n")
                     f.write("     li R2, " + components[2] + "\n")
                     f.write("     str R2, R31\n")
                     f.write("     Incr R31\n")
                     f.write("     str R31, R1\n")
                elif (components[1] == "local"):
                    f.write("//" + line + "\n")
                    f.write("     li R1, " + SP + "\n")
                    f.write("     load R31, R1\n")
                    f.write("     li R1, " + local + "\n")# 1 here is the local pointer which is RAM{1]
                    f.write("     load R3, R1\n")
                    f.write("\n")
                    f.write("     li R2, " + components[2] + "\n")
                    f.write("     add R4, R3, R2\n")
                    f.write("     load R30, R4\n")
                    f.write("     str R30, R31\n")
                    f.write("     Incr R31\n")
                    f.write("     li R1, " + SP + "\n")
                    f.write("     str R31, R1\n")
                elif (components[1] == "argument"):
                    f.write("//" + line + "\n")
                    f.write("     li R1, " + SP + "\n")
                    f.write("     load R31, R1\n")
                    f.write("     li R1, " + argument + "\n")# 1 here is the argument pointer which is RAM{5]
                    f.write("     load R3, R1\n")
                    f.write("\n")
                    f.write("     li R2, " + components[2] + "\n")
                    f.write("     add R4, R3, R2\n")
                    f.write("     load R30, R4\n")
                    f.write("     str R30, R31\n")
                    f.write("     Incr R31\n")
                    f.write("     li R1, " + SP + "\n")
                    f.write("     str R31, R1\n")

                elif (components[1] == "temp"):
                    f.write("//" + line + "\n")
                    f.write("     li R1, " + SP + "\n")
                    f.write("     load R31, R1\n")
                    f.write("     li R1, " + temp + "\n")
                    f.write("     load R3, R1\n")
                    f.write("\n")
                    f.write("     li R2, " + components[2] + "\n")
                    f.write("     add R4, R3, R2\n")
                    f.write("     load R30, R4\n")
                    f.write("     str R30, R31\n")
                    f.write("     Incr R31\n")
                    f.write("     li R1, " + SP + "\n")
                    f.write("     str R31, R1\n")

                elif (components[1] == "that"):
                    f.write("//" + line + "\n")
                    f.write("     li R1, " + SP + "\n")
                    f.write("     load R31, R1\n")
                    f.write("     li R1, " + that + "\n")# 1 here is the argument pointer which is RAM{5]
                    f.write("     load R3, R1\n")
                    f.write("\n")
                    f.write("     li R2, " + components[2] + "\n")
                    f.write("     add R4, R3, R2\n")
                    f.write("     load R30, R4\n")
                    f.write("     str R30, R31\n")
                    f.write("     Incr R31\n")
                    f.write("     li R1, " + SP + "\n")
                    f.write("     str R31, R1\n")
                else:
                    print("expexted constant/local/argument/static...etc at line " + str(lineNumber))
                    return
            elif (components[0] == "pop"):
                if (len(components) == 1):
                    f.write("//" + line + "\n")
                    f.write("// (pop_constant)\n")
                    f.write("     li R1, " + SP + "\n")
                    f.write("     load R31, R1\n")
                    f.write("     Decr R31\n")
                    f.write("     load R12, R31\n")
                    f.write("     str R31, " + SP + "\n")
                else:
                    if(len(components) == 3):
                        if (components[1] == "local"):
                            f.write("//" + line + "\n")
                            #f.write("(pop_local_index)\n")
                            f.write("     li R1, " + SP + "\n")
                            f.write("     load R31, R1\n")
                            f.write("     Decr R31\n")
                            f.write("     str R31, R1\n")
                            f.write("     load R2, R31\n")
                            f.write("     li R3, " + local + "\n")
                            f.write("     load R4, R3\n")
                            f.write("     li R5, " + components[2] + "\n")
                            f.write("     add R7, R4, R5\n")
                            f.write("     str R2, R7\n")
                        elif(components[1] == "argument"):
                            f.write("//" + line + "\n")
                            f.write("     li R1, " + SP + "\n")
                            f.write("     load R31, R1\n")
                            f.write("     Decr R31\n")
                            f.write("     str R31, R1\n")
                            f.write("     load R2, R31\n") #R2 contains the popped value
                            f.write("     li R3, " + argument + "\n") # 5 here is the address of the argument segment
                            f.write("     load R4, R3\n")
                            f.write("     li R5, " + components[2] + "\n")
                            f.write("     add R7, R4, R5\n")
                            f.write("     str R2, R7\n")
                        elif(components[1] == "this"):
                            f.write("//" + line + "\n")
                            f.write("     li R1, " + SP + "\n")
                            f.write("     load R31, R1\n")
                            f.write("     Decr R31\n")
                            f.write("     str R31, R1\n")
                            f.write("     load R2, R31\n") #R2 contains the popped value
                            f.write("     li R3, " + this + "\n") # 5 here is the address of the argument segment
                            f.write("     load R4, R3\n")
                            f.write("     li R5, " + components[2] + "\n")
                            f.write("     add R7, R4, R5\n")
                            f.write("     str R2, R7\n")
                        elif(components[1] == "that"):
                            f.write("//" + line + "\n")
                            f.write("     li R1, " + SP + "\n")
                            f.write("     load R31, R1\n")
                            f.write("     Decr R31\n")
                            f.write("     str R31, R1\n")
                            f.write("     load R2, R31\n") #R2 contains the popped value
                            f.write("     li R3, " + that + "\n") # 5 here is the address of the argument segment
                            f.write("     load R4, R3\n")
                            f.write("     li R5, " + components[2] + "\n")
                            f.write("     add R7, R4, R5\n")
                            f.write("     str R2, R7\n")

                        elif(components[1] == "temp"):
                            f.write("//" + line + "\n")
                            f.write("     li R1, " + SP + "\n")
                            f.write("     load R31, R1\n")
                            f.write("     Decr R31\n")
                            f.write("     str R31, R1\n")
                            f.write("     load R2, R31\n") #R2 contains the popped value
                            f.write("     li R3, " + temp + "\n") # 5 here is the address of the argument segment
                            f.write("     load R4, R3\n")
                            f.write("     li R5, " + components[2] + "\n")
                            f.write("     add R7, R4, R5\n")
                            f.write("     str R2, R7\n")

                        elif(components[1] == "pointer"):
                            f.write("//" + line + "\n")
                            f.write("     li R1, " + SP + "\n")
                            f.write("     load R31, R1\n")
                            f.write("     Decr R31\n")
                            f.write("     str R31, R1\n")
                            f.write("     load R2, R31\n") #R2 contains the popped value
                            thisTaht = this
                            if (components[2] == "0"):
                                thisTaht = this
                            else:
                                thisTaht = that
                            f.write("     li R3, " + thisTaht + "\n")
                            f.write("     str R2, R3\n")


            elif (components[0] == "add"):
                #pop second item
                f.write("//" + line + "\n")
                f.write("     li R1, " + SP + "\n")
                f.write("     load R31, R1\n")
                f.write("     Decr R31\n")
                f.write("     load R12, R31\n")
                f.write("     str R31, R1\n")
                #pop first item
                f.write("     li R1, " + SP + "\n")
                f.write("     load R31, R1\n")
                f.write("     Decr R31\n")
                f.write("     load R13, R31\n")
                f.write("     str R31, R1\n")
                #perform operation
                f.write("     add R14, R12, R13\n")
                #push the result
                f.write("     li R1, " + SP + "\n")
                f.write("     load R31, R1\n")
                f.write("     str R14, R31\n")
                f.write("     Incr R31\n")
                f.write("     str R31, R1\n")
            
            elif (components[0] == "sub"):
                #pop second item
                f.write("//" + line + "\n")
                f.write("     li R1, " + SP + "\n")
                f.write("     load R31, R1\n")
                f.write("     Decr R31\n")
                f.write("     load R12, R31\n")
                f.write("     str R31, R1\n")
                #pop first item
                f.write("     li R1, " + SP + "\n")
                f.write("     load R31, R1\n")
                f.write("     Decr R31\n")
                f.write("     load R13, R31\n")
                f.write("     str R31, R1\n")
                #perform operation
                f.write("     sub R14, R13, R12\n")
                #push the result
                f.write("     li R1, " + SP + "\n")
                f.write("     load R31, R1\n")
                f.write("     str R14, R31\n")
                f.write("     Incr R31\n")
                f.write("     str R31, R1\n")

            elif (components[0] == "and"):
                #pop second item
                f.write("//" + line + "\n")
                f.write("     li R1, " + SP + "\n")
                f.write("     load R31, R1\n")
                f.write("     Decr R31\n")
                f.write("     load R12, R31\n")
                f.write("     str R31, R1\n")
                #pop first item
                f.write("     li R1, " + SP + "\n")
                f.write("     load R31, R1\n")
                f.write("     Decr R31\n")
                f.write("     load R13, R31\n")
                f.write("     str R31, R1\n")
                #perform operation
                f.write("     and R14, R13, R12\n")
                #push the result
                f.write("     li R1, " + SP + "\n")
                f.write("     load R31, R1\n")
                f.write("     str R14, R31\n")
                f.write("     Incr R31\n")
                f.write("     str R31, R1\n")

            elif (components[0] == "or"):
                #pop second item
                f.write("//" + line + "\n")
                f.write("     li R1, " + SP + "\n")
                f.write("     load R31, R1\n")
                f.write("     Decr R31\n")
                f.write("     load R12, R31\n")
                f.write("     str R31, R1\n")
                #pop first item
                f.write("     li R1, " + SP + "\n")
                f.write("     load R31, R1\n")
                f.write("     Decr R31\n")
                f.write("     load R13, R31\n")
                f.write("     str R31, R1\n")
                #perform operation
                f.write("     or R14, R13, R12\n")
                #push the result
                f.write("     li R1, " + SP + "\n")
                f.write("     load R31, R1\n")
                f.write("     str R14, R31\n")
                f.write("     Incr R31\n")
                f.write("     str R31, R1\n")

            elif (components[0] == "incr"):
                #pop second item
                f.write("//" + line + "\n")
                f.write("     li R1, " + SP + "\n")
                f.write("     load R31, R1\n")
                f.write("     Decr R31\n")
                f.write("     load R12, R31\n")
                f.write("     str R31, R1\n")
                #perform operation
                f.write("     Incr R12\n")
                #push the result
                f.write("     li R1, " + SP + "\n")
                f.write("     load R31, R1\n")
                f.write("     str R12, R31\n")
                f.write("     Incr R31\n")
                f.write("     str R31, R1\n")

            elif (components[0] == "equ"):
                #pop second item
                f.write("//" + line + "\n")
                f.write("     li R1, " + SP + "\n")
                f.write("     load R31, R1\n")
                f.write("     Decr R31\n")
                f.write("     load R12, R31\n")
                f.write("     str R31, R1\n")
                #pop first item
                f.write("     li R1, " + SP + "\n")
                f.write("     load R31, R1\n")
                f.write("     Decr R31\n")
                f.write("     load R13, R31\n")
                f.write("     str R31, R1\n")
                #perform operation
                f.write("     li R15, 0\n")
                f.write("     cmp R12, R13\n")
                f.write("     jeq label" + str(label) + "\n")
                f.write("     cmp R12, R13\n")
                f.write("     jneq label" + str(label + 1) + "\n")
                f.write("  (label" + str(label) +")\n")
                f.write("     li R15, 1\n")
                f.write("  (label" + str(label+1)+")\n")
                label += 2
                #push the result
                f.write("     li R1, " + SP + "\n")
                f.write("     load R31, R1\n")
                f.write("     str R15, R31\n")
                f.write("     Incr R31\n")
                f.write("     str R31, R1\n")

            elif (components[0] == "nequ"):
                #pop second item
                f.write("//" + line + "\n")
                f.write("     li R1, " + SP + "\n")
                f.write("     load R31, R1\n")
                f.write("     Decr R31\n")
                f.write("     load R12, R31\n")
                f.write("     str R31, R1\n")
                #pop first item
                f.write("     li R1, " + SP + "\n")
                f.write("     load R31, R1\n")
                f.write("     Decr R31\n")
                f.write("     load R13, R31\n")
                f.write("     str R31, R1\n")
                #perform operation
                f.write("     li R15, 0\n")
                f.write("     cmp R12, R13\n")
                f.write("     jneq label" + str(label) + "\n")
                f.write("     cmp R12, R13\n")
                f.write("     jeq label" + str(label + 1) + "\n")
                f.write("  (label" + str(label) +")\n")
                f.write("     li R15, 1\n")
                f.write("  (label" + str(label+1)+")\n")
                label += 2
                #push the result
                f.write("     li R1, " + SP + "\n")
                f.write("     load R31, R1\n")
                f.write("     str R15, R31\n")
                f.write("     Incr R31\n")
                f.write("     str R31, R1\n")

            elif (components[0] == "gt"):
                #pop second item
                f.write("//" + line + "\n")
                f.write("     li R1, " + SP + "\n")
                f.write("     load R31, R1\n")
                f.write("     Decr R31\n")
                f.write("     load R12, R31\n")
                f.write("     str R31, R1\n")
                #pop first item
                ##f.write("     li R1, " + SP + "\n")
                f.write("     load R31, R1\n")
                f.write("     Decr R31\n")
                f.write("     load R13, R31\n")
                f.write("     str R31, R1\n")
                #perform operation
                f.write("     li R15, 0\n")
                f.write("     cmp R13, R12\n")
                f.write("     jg label" + str(label) + "\n")
                f.write("     cmp R13, R12\n")
                f.write("     jle label" + str(label + 1) + "\n")
                f.write("  (label" + str(label) +")\n")
                f.write("     li R15, 1\n")
                f.write("  (label" + str(label+1)+")\n")
                label += 2
                #push the result
                ##f.write("     li R1, " + SP + "\n")
                f.write("     load R31, R1\n")
                f.write("     str R15, R31\n")
                f.write("     Incr R31\n")
                f.write("     str R31, R1\n")

            elif (components[0] == "gte"):
                #pop second item
                f.write("//" + line + "\n")
                f.write("     li R1, " + SP + "\n")
                f.write("     load R31, R1\n")
                f.write("     Decr R31\n")
                f.write("     load R12, R31\n")
                f.write("     str R31, R1\n")
                #pop first item
                ##f.write("     li R1, " + SP + "\n")
                f.write("     load R31, R1\n")
                f.write("     Decr R31\n")
                f.write("     load R13, R31\n")
                f.write("     str R31, R1\n")
                #perform operation
                f.write("     li R15, 0\n")
                f.write("     cmp R13, R12\n")
                f.write("     jge label" + str(label) + "\n")
                f.write("     cmp R13, R12\n")
                f.write("     jl label" + str(label + 1) + "\n")
                f.write("  (label" + str(label) +")\n")
                f.write("     li R15, 1\n")
                f.write("  (label" + str(label+1)+")\n")
                label += 2
                #push the result
                ##f.write("     li R1, " + SP + "\n")
                f.write("     load R31, R1\n")
                f.write("     str R15, R31\n")
                f.write("     Incr R31\n")
                f.write("     str R31, R1\n")

            elif (components[0] == "lt"):
                #pop second item
                f.write("//" + line + "\n")
                f.write("     li R1, " + SP + "\n")
                f.write("     load R31, R1\n")
                f.write("     Decr R31\n")
                f.write("     load R12, R31\n")
                f.write("     str R31, R1\n")
                #pop first item
                f.write("     load R31, R1\n")
                f.write("     Decr R31\n")
                f.write("     load R13, R31\n")
                f.write("     str R31, R1\n")
                #perform operation
                f.write("     li R15, 0\n")
                f.write("     cmp R13, R12\n")
                f.write("     jl label" + str(label) + "\n")
                f.write("     cmp R13, R12\n")
                f.write("     jge label" + str(label + 1) + "\n")
                f.write("  (label" + str(label) +")\n")
                f.write("     li R15, 1\n")
                f.write("  (label" + str(label+1)+")\n")
                label += 2
                #push the result
                f.write("     load R31, R1\n")
                f.write("     str R15, R31\n")
                f.write("     Incr R31\n")
                f.write("     str R31, R1\n")

            elif (components[0] == "lte"):
                #pop second item
                f.write("//" + line + "\n")
                f.write("     li R1, " + SP + "\n")
                f.write("     load R31, R1\n")
                f.write("     Decr R31\n")
                f.write("     load R12, R31\n")
                f.write("     str R31, R1\n")
                #pop first item
                f.write("     load R31, R1\n")
                f.write("     Decr R31\n")
                f.write("     load R13, R31\n")
                f.write("     str R31, R1\n")
                #perform operation
                f.write("     li R15, 0\n")
                f.write("     cmp R13, R12\n")
                f.write("     jle label" + str(label) + "\n")
                f.write("     cmp R13, R12\n")
                f.write("     jg label" + str(label + 1) + "\n")
                f.write("  (label" + str(label) +")\n")
                f.write("     li R15, 1\n")
                f.write("  (label" + str(label+1)+")\n")
                label += 2
                #push the result
                f.write("     load R31, R1\n")
                f.write("     str R15, R31\n")
                f.write("     Incr R31\n")
                f.write("     str R31, R1\n")

            elif (components[0] == "not"):
                #pop second item
                f.write("//" + line + "\n")
                f.write("     li R1, " + SP + "\n")
                f.write("     load R31, R1\n")
                f.write("     Decr R31\n")
                f.write("     load R12, R31\n")
                f.write("     str R31, R1\n")
                #perform operation
                f.write("     not R12, R12\n")
                #push the result
                f.write("     load R31, R1\n")
                f.write("     str R12, R31\n")
                f.write("     Incr R31\n")
                f.write("     str R31, R1\n")

            elif (components[0] == "neg"):
                #pop second item
                f.write("//" + line + "\n")
                f.write("     li R1, " + SP + "\n")
                f.write("     load R31, R1\n")
                f.write("     Decr R31\n")
                f.write("     load R12, R31\n")
                f.write("     str R31, R1\n")
                #perform operation
                f.write("     li  R2, 0\n")
                f.write("     sub R12, R2, R12\n")
                #push the result
                ##f.write("     li R1, " + SP + "\n")
                f.write("     load R31, R1\n")
                f.write("     str R12, R31\n")
                f.write("     Incr R31\n")
                f.write("     str R31, R1\n")

            elif (components[0] == "if-goto"):
                f.write("//" + line + "\n")
                f.write("     li R1, " + SP + "\n")
                f.write("     load R31, R1\n")
                f.write("     Decr R31\n")
                f.write("     load R12, R31\n") #pop the last value on stack
                f.write("     str R31, R1\n") #save the stack pointer 
                #f.write("     li R1, 1\n")
                f.write("     li R1, 1\n")
                f.write("     cmp R12, R1\n")
                f.write("     jeq " + components[1] + "\n")

            elif (components[0] == "function"):
                f.write("//" + line + "\n")
                f.write("(" + components[1] + ")\n")

            elif (components[0] == "goto"):
                f.write("//" + line + "\n")
                f.write("     jmp " + components[1] + "\n")

            elif (components[0] == "call"):
                ##!!!!!!!!!!!!! We need to push a bunch of things on the stack here !!!!!!!!!!!
                numberOfLocalVariables = components[2]
                numberOfArgs = components[3]
                f.write("//" + line + "\n")
                f.write("     // push return address given as a number\n")
                f.write("     li R1, 0\n")
                f.write("     load R31, R1\n")
                f.write("     //replace the following li R2, return_address_\n")
                f.write("     li R2, _returnAddress" + str(retAddress) +"\n")
                f.write("     str R2, R31\n")
                f.write("     Incr R31\n")
                f.write("     str R31, R1\n\n")
                f.write("     // push local\n")
                f.write("     li R10, " + str(local) + "\n")
                f.write("     load R11, R10\n")
                f.write("     li R1, " + str(SP) + "\n")
                f.write("     load R31, R1\n")
                f.write("     str R11, R31\n")
                f.write("     Incr R31\n")
                f.write("     str R31, R1\n")
                f.write("     \n")
                f.write("     // push argument\n")
                f.write("     li R10, " + str(argument) + "\n")
                f.write("     load R11, R10\n")
                f.write("     li R1, " + str(SP) + "\n")
                f.write("     load R31, R1\n")
                f.write("     str R11, R31\n")
                f.write("     Incr R31\n")
                f.write("     str R31, R1\n")
                f.write("     \n")
                f.write("     // push this\n")
                f.write("     li R10, " + str(this) + "\n")
                f.write("     load R11, R10\n")
                f.write("     li R1, " + str(SP) + "\n")
                f.write("     load R31, R1\n")
                f.write("     str R11, R31\n")
                f.write("     Incr R31\n")
                f.write("     str R31, R1\n")
                f.write("     \n")
                f.write("     // push that\n")
                f.write("     li R10, " + str(that) + "\n")
                f.write("     load R11, R10\n")
                f.write("     li R1, " + str(SP) + "\n")
                f.write("     load R31, R1\n")
                f.write("     str R11, R31\n")
                f.write("     Incr R31\n")
                f.write("     str R31, R1\n")
                f.write("     \n")
                f.write("     //New Arg = SP - 5 - nArgs -1\n") 
                f.write("     li R2, " + str(argument) + "\n")
                f.write("     li R1, " + str(SP) + "\n")
                f.write("     load R31, R1\n")
                f.write("     li R4, 5\n")
                f.write("     // R3 = SP - 5- nArgs\n")
                f.write("     sub R3, R31, R4\n")
                f.write("     //R6 = nArgs\n")
                f.write("     li R6, " + components[3] + "\n")
                f.write("     sub R7, R3, R6\n")
                f.write("     // new Arg = SP - 5 - nArgs\n")
                f.write("     str R7, R2\n")
                f.write("     \n")
                f.write("     li R2, " + str(local) + "\n")
                f.write("     li R1, " + str(SP) + "\n")
                f.write("     load R3, R1\n")
                f.write("     str R3, R2\n")

                f.write("     //push number of local variables\n")
                f.write("     // R2 = num_of_local_Variables\n")
                f.write("     li R2, " + str(numberOfLocalVariables) + "\n")
                f.write("     li R3, 0\n")
                f.write("     li R1, " + str(SP) + "\n")
                f.write("     load R31, R1\n")
                f.write("     (repeat_" + str(repeat) +")\n")
                f.write("     str R3, R31\n")
                f.write("     Incr R31\n")
                f.write("     str R31, R1\n")
                f.write("     Decr R2\n")
                f.write("     li R4, 0\n")
                f.write("     cmp R2, R4\n")
                f.write("     jneq repeat_" + str(repeat) +"\n")
                repeat += 1
                f.write("     jmp " + components[1] + "\n")
                f.write("(_returnAddress" + str(retAddress) + ")\n")
                retAddress += 1

            elif (components[0] == "return"):
                f.write("//" + line + "\n")
                f.write("    li R2, " + str(argument) + "\n")
                f.write("    load R30, R2\n")
                f.write("    load R29, R2\n")
                f.write("    Incr R29\n") ## this is the SP value just before return (argumen0 + 1)
                f.write("    li R1, " + str(SP) + "\n")
                f.write("    load R31, R1\n")
                f.write("    Decr R31\n")
                f.write("    str R31, R1\n")
                f.write("    load R20, R31\n")
                f.write("    str R20, R30\n")
                f.write("    //SP = local0\n")
                f.write("    li R1, " + str(SP) + "\n")
                f.write("    load R31, R1\n")
                f.write("    li R2, " + str(local) + "\n")
                f.write("    load R31, R2\n")
                f.write("    str R31, R1\n")

                f.write("    //pop that(SP -1) 'that' pointer\n")
                f.write("    li R1, " + str(SP) + "\n")
                f.write("    load R31, R1\n")
                f.write("    li R2, 1\n")
                f.write("    sub R3, R31, R2\n")
                f.write("    load R4, R3\n")
                f.write("    li R5, " + str(that) + "\n")
                f.write("    str R4, R5\n")

                f.write("    //pop that(SP -2) 'this' pointer\n")
                f.write("    li R1, " + str(SP) + "\n")
                f.write("    load R31, R1\n")
                f.write("    li R2, 2\n")
                f.write("    sub R3, R31, R2\n")
                f.write("    load R4, R3\n")
                f.write("    li R5, " + str(this) + "\n")
                f.write("    str R4, R5\n")

                f.write("    //pop that(SP -3) 'argument' pointer\n")
                f.write("    li R1, " + str(SP) + "\n")
                f.write("    load R31, R1\n")
                f.write("    li R2, 3\n")
                f.write("    sub R3, R31, R2\n")
                f.write("    load R4, R3\n")
                f.write("    li R5, " + str(argument) + "\n")
                f.write("    str R4, R5\n")

                f.write("    //pop that(SP -4) 'local' pointer\n")
                f.write("    li R1, " + str(SP) + "\n")
                f.write("    load R31, R1\n")
                f.write("    li R2, 4\n")
                f.write("    sub R3, R31, R2\n")
                f.write("    load R4, R3\n")
                f.write("    li R5, " + str(local) + "\n")
                f.write("    str R4, R5\n")

                f.write("    //pop that(SP -5) 'return address'\n")
                f.write("    li R1, " + str(SP) + "\n")
                f.write("    load R31, R1\n")
                f.write("    li R2, 5\n")
                f.write("    sub R3, R31, R2\n")
                f.write("    load R26, R3\n")
                f.write("    mov R31, R29\n")
                f.write("    str R31, R1\n")
                f.write("    return\n")

            elif (line.startswith("(")):
                s = 0

            else:
                print("unknown command at line  " + str(lineNumber) + "\n")
                return

        lineNumber += 1           
    f.close()
  
def main():
    arguments = len(sys.argv)
    if (arguments >= 2):
        print("generating machine code for " + sys.argv[1])
        list_of_files = sys.argv[1:]
        for file in list_of_files:
            print(file)
            InitialiseSegments("assembly.asm")
            VMTranslate(file)
    else:
        print("Please provide a VM code source")


if __name__ == "__main__":
    main() 
