//Initialise Segments

//===================

//(Initialise_SP)
    li R1,  100
    li R2, 0
    str R1, R2
    
//(Initialise_local)
    li R3, 200
    li R4, 1
    str R3, R4

//(Initialise_this)
    li R5, 400
    li R6, 3
    str R5, R6

//(Initialise_that)
    li R7, 500
    li R8, 4
    str R7, R8

//(Initialise_temp)
    li R9, 600
    li R10, 5
    str R9, R10

//(Initialise_argument)
    li R11, 300
    li R12, 2
    str R11, R12
       
//(Initialise_static
    li R13, 700
    li R14, 6
    str R13, R14
       
//(Initialise_pointer
    li R13, 800
    li R14, 7
    str R13, R14

//function Math.main 2 0
(Math.main)
//push constant 1
     li R1, 0
     load R31, R1

     li R2, 1
     str R2, R31
     Incr R31
     str R31, R1
//pop local 0
     li R1, 0
     load R31, R1
     Decr R31
     str R31, R1
     load R2, R31
     li R3, 1
     load R4, R3
     li R5, 0
     add R7, R4, R5
     str R2, R7
//push constant 0
     li R1, 0
     load R31, R1

     li R2, 0
     str R2, R31
     Incr R31
     str R31, R1
//pop local 1
     li R1, 0
     load R31, R1
     Decr R31
     str R31, R1
     load R2, R31
     li R3, 1
     load R4, R3
     li R5, 1
     add R7, R4, R5
     str R2, R7
(whileStatementStart_1)
//push local 1
     li R1, 0
     load R31, R1
     li R1, 1
     load R3, R1

     li R2, 1
     add R4, R3, R2
     load R30, R4
     str R30, R31
     Incr R31
     li R1, 0
     str R31, R1
//push constant 35
     li R1, 0
     load R31, R1

     li R2, 35
     str R2, R31
     Incr R31
     str R31, R1
//lt
     li R1, 0
     load R31, R1
     Decr R31
     load R12, R31
     str R31, R1
     load R31, R1
     Decr R31
     load R13, R31
     str R31, R1
     li R15, 0
     cmp R13, R12
     jl label0
     cmp R13, R12
     jge label1
  (label0)
     li R15, 1
  (label1)
     load R31, R1
     str R15, R31
     Incr R31
     str R31, R1
//if-goto whileTrueStatement_1
     li R1, 0
     load R31, R1
     Decr R31
     load R12, R31
     str R31, R1
     li R1, 1
     cmp R12, R1
     jeq whileTrueStatement_1
//goto whileEndStatement_1
     jmp whileEndStatement_1
(whileTrueStatement_1)
//push constant 500
     li R1, 0
     load R31, R1

     li R2, 500
     str R2, R31
     Incr R31
     str R31, R1
//push local 1
     li R1, 0
     load R31, R1
     li R1, 1
     load R3, R1

     li R2, 1
     add R4, R3, R2
     load R30, R4
     str R30, R31
     Incr R31
     li R1, 0
     str R31, R1
//add
     li R1, 0
     load R31, R1
     Decr R31
     load R12, R31
     str R31, R1
     li R1, 0
     load R31, R1
     Decr R31
     load R13, R31
     str R31, R1
     add R14, R12, R13
     li R1, 0
     load R31, R1
     str R14, R31
     Incr R31
     str R31, R1
//push local 0
     li R1, 0
     load R31, R1
     li R1, 1
     load R3, R1

     li R2, 0
     add R4, R3, R2
     load R30, R4
     str R30, R31
     Incr R31
     li R1, 0
     str R31, R1
//pop temp 0
     li R1, 0
     load R31, R1
     Decr R31
     str R31, R1
     load R2, R31
     li R3, 5
     load R4, R3
     li R5, 0
     add R7, R4, R5
     str R2, R7
//pop pointer 1
     li R1, 0
     load R31, R1
     Decr R31
     str R31, R1
     load R2, R31
     li R3, 4
     str R2, R3
//push temp 0
     li R1, 0
     load R31, R1
     li R1, 5
     load R3, R1

     li R2, 0
     add R4, R3, R2
     load R30, R4
     str R30, R31
     Incr R31
     li R1, 0
     str R31, R1
//pop that 0
     li R1, 0
     load R31, R1
     Decr R31
     str R31, R1
     load R2, R31
     li R3, 4
     load R4, R3
     li R5, 0
     add R7, R4, R5
     str R2, R7
//push local 0
     li R1, 0
     load R31, R1
     li R1, 1
     load R3, R1

     li R2, 0
     add R4, R3, R2
     load R30, R4
     str R30, R31
     Incr R31
     li R1, 0
     str R31, R1
//push constant 1
     li R1, 0
     load R31, R1

     li R2, 1
     str R2, R31
     Incr R31
     str R31, R1
//add
     li R1, 0
     load R31, R1
     Decr R31
     load R12, R31
     str R31, R1
     li R1, 0
     load R31, R1
     Decr R31
     load R13, R31
     str R31, R1
     add R14, R12, R13
     li R1, 0
     load R31, R1
     str R14, R31
     Incr R31
     str R31, R1
//pop local 0
     li R1, 0
     load R31, R1
     Decr R31
     str R31, R1
     load R2, R31
     li R3, 1
     load R4, R3
     li R5, 0
     add R7, R4, R5
     str R2, R7
//push local 1
     li R1, 0
     load R31, R1
     li R1, 1
     load R3, R1

     li R2, 1
     add R4, R3, R2
     load R30, R4
     str R30, R31
     Incr R31
     li R1, 0
     str R31, R1
//push constant 1
     li R1, 0
     load R31, R1

     li R2, 1
     str R2, R31
     Incr R31
     str R31, R1
//add
     li R1, 0
     load R31, R1
     Decr R31
     load R12, R31
     str R31, R1
     li R1, 0
     load R31, R1
     Decr R31
     load R13, R31
     str R31, R1
     add R14, R12, R13
     li R1, 0
     load R31, R1
     str R14, R31
     Incr R31
     str R31, R1
//pop local 1
     li R1, 0
     load R31, R1
     Decr R31
     str R31, R1
     load R2, R31
     li R3, 1
     load R4, R3
     li R5, 1
     add R7, R4, R5
     str R2, R7
//goto whileStatementStart_1
     jmp whileStatementStart_1
(whileEndStatement_1)
