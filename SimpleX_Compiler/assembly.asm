//Initialise Segments

//===================

//(Initialise_SP)
    li R1,  1024
    li R2, 0
    str R1, R2
    
//(Initialise_local)
    li R3, 20
    li R4, 1
    str R3, R4

//(Initialise_this)
    li R5, 200
    li R6, 3
    str R5, R6

//(Initialise_that)
    li R7, 300
    li R8, 4
    str R7, R8

//(Initialise_temp)
    li R9, 400
    li R10, 5
    str R9, R10

//(Initialise_argument)
    li R11, 100
    li R12, 2
    str R11, R12
       
//(Initialise_static
    li R13, 512
    li R14, 6
    str R13, R14
       
//(Initialise_pointer
    li R13, 1000
    li R14, 7
    str R13, R14

//function BootLoader.Init 1 1
(BootLoader.Init)
//push argument 0
     li R1, 0
     load R31, R1
     li R1, 2
     load R3, R1

     li R2, 0
     add R4, R3, R2
     load R30, R4
     str R30, R31
     Incr R31
     li R1, 0
     str R31, R1
//call Memory.init 1 1
     // push return address given as a number
     li R1, 0
     load R31, R1
     //replace the following li R2, return_address_
     li R2, _returnAddress0
     str R2, R31
     Incr R31
     str R31, R1

     // push local
     li R10, 1
     load R11, R10
     li R1, 0
     load R31, R1
     str R11, R31
     Incr R31
     str R31, R1
     
     // push argument
     li R10, 2
     load R11, R10
     li R1, 0
     load R31, R1
     str R11, R31
     Incr R31
     str R31, R1
     
     // push this
     li R10, 3
     load R11, R10
     li R1, 0
     load R31, R1
     str R11, R31
     Incr R31
     str R31, R1
     
     // push that
     li R10, 4
     load R11, R10
     li R1, 0
     load R31, R1
     str R11, R31
     Incr R31
     str R31, R1
     
     //New Arg = SP - 5 - nArgs -1
     li R2, 2
     li R1, 0
     load R31, R1
     li R4, 5
     // R3 = SP - 5- nArgs
     sub R3, R31, R4
     //R6 = nArgs
     li R6, 1
     sub R7, R3, R6
     // new Arg = SP - 5 - nArgs
     str R7, R2
     
     li R2, 1
     li R1, 0
     load R3, R1
     str R3, R2
     //push number of local variables
     // R2 = num_of_local_Variables
     li R2, 1
     li R3, 0
     li R1, 0
     load R31, R1
     (repeat_0)
     str R3, R31
     Incr R31
     str R31, R1
     Decr R2
     li R4, 0
     cmp R2, R4
     jneq repeat_0
     jmp Memory.init
(_returnAddress0)
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
//push argument 0
     li R1, 0
     load R31, R1
     li R1, 2
     load R3, R1

     li R2, 0
     add R4, R3, R2
     load R30, R4
     str R30, R31
     Incr R31
     li R1, 0
     str R31, R1
//call Main.main 2 1
     // push return address given as a number
     li R1, 0
     load R31, R1
     //replace the following li R2, return_address_
     li R2, _returnAddress1
     str R2, R31
     Incr R31
     str R31, R1

     // push local
     li R10, 1
     load R11, R10
     li R1, 0
     load R31, R1
     str R11, R31
     Incr R31
     str R31, R1
     
     // push argument
     li R10, 2
     load R11, R10
     li R1, 0
     load R31, R1
     str R11, R31
     Incr R31
     str R31, R1
     
     // push this
     li R10, 3
     load R11, R10
     li R1, 0
     load R31, R1
     str R11, R31
     Incr R31
     str R31, R1
     
     // push that
     li R10, 4
     load R11, R10
     li R1, 0
     load R31, R1
     str R11, R31
     Incr R31
     str R31, R1
     
     //New Arg = SP - 5 - nArgs -1
     li R2, 2
     li R1, 0
     load R31, R1
     li R4, 5
     // R3 = SP - 5- nArgs
     sub R3, R31, R4
     //R6 = nArgs
     li R6, 1
     sub R7, R3, R6
     // new Arg = SP - 5 - nArgs
     str R7, R2
     
     li R2, 1
     li R1, 0
     load R3, R1
     str R3, R2
     //push number of local variables
     // R2 = num_of_local_Variables
     li R2, 2
     li R3, 0
     li R1, 0
     load R31, R1
     (repeat_1)
     str R3, R31
     Incr R31
     str R31, R1
     Decr R2
     li R4, 0
     cmp R2, R4
     jneq repeat_1
     jmp Main.main
(_returnAddress1)
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
//function Main.main 2 1
(Main.main)
//push constant 40
     li R1, 0
     load R31, R1

     li R2, 40
     str R2, R31
     Incr R31
     str R31, R1
//call Array.new 1 1
     // push return address given as a number
     li R1, 0
     load R31, R1
     //replace the following li R2, return_address_
     li R2, _returnAddress2
     str R2, R31
     Incr R31
     str R31, R1

     // push local
     li R10, 1
     load R11, R10
     li R1, 0
     load R31, R1
     str R11, R31
     Incr R31
     str R31, R1
     
     // push argument
     li R10, 2
     load R11, R10
     li R1, 0
     load R31, R1
     str R11, R31
     Incr R31
     str R31, R1
     
     // push this
     li R10, 3
     load R11, R10
     li R1, 0
     load R31, R1
     str R11, R31
     Incr R31
     str R31, R1
     
     // push that
     li R10, 4
     load R11, R10
     li R1, 0
     load R31, R1
     str R11, R31
     Incr R31
     str R31, R1
     
     //New Arg = SP - 5 - nArgs -1
     li R2, 2
     li R1, 0
     load R31, R1
     li R4, 5
     // R3 = SP - 5- nArgs
     sub R3, R31, R4
     //R6 = nArgs
     li R6, 1
     sub R7, R3, R6
     // new Arg = SP - 5 - nArgs
     str R7, R2
     
     li R2, 1
     li R1, 0
     load R3, R1
     str R3, R2
     //push number of local variables
     // R2 = num_of_local_Variables
     li R2, 1
     li R3, 0
     li R1, 0
     load R31, R1
     (repeat_2)
     str R3, R31
     Incr R31
     str R31, R1
     Decr R2
     li R4, 0
     cmp R2, R4
     jneq repeat_2
     jmp Array.new
(_returnAddress2)
//pop static 0
     li R1, 0
     load R31, R1
     Decr R31
     str R31, R1
     load R2, R31
     li R3, 6
     load R4, R3
     li R5, 0
     add R7, R4, R5
     str R2, R7
//push constant 2000
     li R1, 0
     load R31, R1

     li R2, 2000
     str R2, R31
     Incr R31
     str R31, R1
//push constant 6
     li R1, 0
     load R31, R1

     li R2, 6
     str R2, R31
     Incr R31
     str R31, R1
//call Memory.poke 1 2
     // push return address given as a number
     li R1, 0
     load R31, R1
     //replace the following li R2, return_address_
     li R2, _returnAddress3
     str R2, R31
     Incr R31
     str R31, R1

     // push local
     li R10, 1
     load R11, R10
     li R1, 0
     load R31, R1
     str R11, R31
     Incr R31
     str R31, R1
     
     // push argument
     li R10, 2
     load R11, R10
     li R1, 0
     load R31, R1
     str R11, R31
     Incr R31
     str R31, R1
     
     // push this
     li R10, 3
     load R11, R10
     li R1, 0
     load R31, R1
     str R11, R31
     Incr R31
     str R31, R1
     
     // push that
     li R10, 4
     load R11, R10
     li R1, 0
     load R31, R1
     str R11, R31
     Incr R31
     str R31, R1
     
     //New Arg = SP - 5 - nArgs -1
     li R2, 2
     li R1, 0
     load R31, R1
     li R4, 5
     // R3 = SP - 5- nArgs
     sub R3, R31, R4
     //R6 = nArgs
     li R6, 2
     sub R7, R3, R6
     // new Arg = SP - 5 - nArgs
     str R7, R2
     
     li R2, 1
     li R1, 0
     load R3, R1
     str R3, R2
     //push number of local variables
     // R2 = num_of_local_Variables
     li R2, 1
     li R3, 0
     li R1, 0
     load R31, R1
     (repeat_3)
     str R3, R31
     Incr R31
     str R31, R1
     Decr R2
     li R4, 0
     cmp R2, R4
     jneq repeat_3
     jmp Memory.poke
(_returnAddress3)
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
//push constant 10
     li R1, 0
     load R31, R1

     li R2, 10
     str R2, R31
     Incr R31
     str R31, R1
//push constant 20
     li R1, 0
     load R31, R1

     li R2, 20
     str R2, R31
     Incr R31
     str R31, R1
//call Main.createSeries 1 3
     // push return address given as a number
     li R1, 0
     load R31, R1
     //replace the following li R2, return_address_
     li R2, _returnAddress4
     str R2, R31
     Incr R31
     str R31, R1

     // push local
     li R10, 1
     load R11, R10
     li R1, 0
     load R31, R1
     str R11, R31
     Incr R31
     str R31, R1
     
     // push argument
     li R10, 2
     load R11, R10
     li R1, 0
     load R31, R1
     str R11, R31
     Incr R31
     str R31, R1
     
     // push this
     li R10, 3
     load R11, R10
     li R1, 0
     load R31, R1
     str R11, R31
     Incr R31
     str R31, R1
     
     // push that
     li R10, 4
     load R11, R10
     li R1, 0
     load R31, R1
     str R11, R31
     Incr R31
     str R31, R1
     
     //New Arg = SP - 5 - nArgs -1
     li R2, 2
     li R1, 0
     load R31, R1
     li R4, 5
     // R3 = SP - 5- nArgs
     sub R3, R31, R4
     //R6 = nArgs
     li R6, 3
     sub R7, R3, R6
     // new Arg = SP - 5 - nArgs
     str R7, R2
     
     li R2, 1
     li R1, 0
     load R3, R1
     str R3, R2
     //push number of local variables
     // R2 = num_of_local_Variables
     li R2, 1
     li R3, 0
     li R1, 0
     load R31, R1
     (repeat_4)
     str R3, R31
     Incr R31
     str R31, R1
     Decr R2
     li R4, 0
     cmp R2, R4
     jneq repeat_4
     jmp Main.createSeries
(_returnAddress4)
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
//push constant 2001
     li R1, 0
     load R31, R1

     li R2, 2001
     str R2, R31
     Incr R31
     str R31, R1
//push constant 7
     li R1, 0
     load R31, R1

     li R2, 7
     str R2, R31
     Incr R31
     str R31, R1
//call Memory.poke 1 2
     // push return address given as a number
     li R1, 0
     load R31, R1
     //replace the following li R2, return_address_
     li R2, _returnAddress5
     str R2, R31
     Incr R31
     str R31, R1

     // push local
     li R10, 1
     load R11, R10
     li R1, 0
     load R31, R1
     str R11, R31
     Incr R31
     str R31, R1
     
     // push argument
     li R10, 2
     load R11, R10
     li R1, 0
     load R31, R1
     str R11, R31
     Incr R31
     str R31, R1
     
     // push this
     li R10, 3
     load R11, R10
     li R1, 0
     load R31, R1
     str R11, R31
     Incr R31
     str R31, R1
     
     // push that
     li R10, 4
     load R11, R10
     li R1, 0
     load R31, R1
     str R11, R31
     Incr R31
     str R31, R1
     
     //New Arg = SP - 5 - nArgs -1
     li R2, 2
     li R1, 0
     load R31, R1
     li R4, 5
     // R3 = SP - 5- nArgs
     sub R3, R31, R4
     //R6 = nArgs
     li R6, 2
     sub R7, R3, R6
     // new Arg = SP - 5 - nArgs
     str R7, R2
     
     li R2, 1
     li R1, 0
     load R3, R1
     str R3, R2
     //push number of local variables
     // R2 = num_of_local_Variables
     li R2, 1
     li R3, 0
     li R1, 0
     load R31, R1
     (repeat_5)
     str R3, R31
     Incr R31
     str R31, R1
     Decr R2
     li R4, 0
     cmp R2, R4
     jneq repeat_5
     jmp Memory.poke
(_returnAddress5)
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
(whileStatementStart_5)
//push constant 1
     li R1, 0
     load R31, R1

     li R2, 1
     str R2, R31
     Incr R31
     str R31, R1
//if-goto whileTrueStatement_5
     li R1, 0
     load R31, R1
     Decr R31
     load R12, R31
     str R31, R1
     li R1, 1
     cmp R12, R1
     jeq whileTrueStatement_5
//goto whileEndStatement_5
     jmp whileEndStatement_5
(whileTrueStatement_5)
//goto whileStatementStart_5
     jmp whileStatementStart_5
(whileEndStatement_5)
//push constant 0
     li R1, 0
     load R31, R1

     li R2, 0
     str R2, R31
     Incr R31
     str R31, R1
//return
    li R2, 2
    load R30, R2
    load R29, R2
    Incr R29
    li R1, 0
    load R31, R1
    Decr R31
    str R31, R1
    load R20, R31
    str R20, R30
    //SP = local0
    li R1, 0
    load R31, R1
    li R2, 1
    load R31, R2
    str R31, R1
    //pop that(SP -1) 'that' pointer
    li R1, 0
    load R31, R1
    li R2, 1
    sub R3, R31, R2
    load R4, R3
    li R5, 4
    str R4, R5
    //pop that(SP -2) 'this' pointer
    li R1, 0
    load R31, R1
    li R2, 2
    sub R3, R31, R2
    load R4, R3
    li R5, 3
    str R4, R5
    //pop that(SP -3) 'argument' pointer
    li R1, 0
    load R31, R1
    li R2, 3
    sub R3, R31, R2
    load R4, R3
    li R5, 2
    str R4, R5
    //pop that(SP -4) 'local' pointer
    li R1, 0
    load R31, R1
    li R2, 4
    sub R3, R31, R2
    load R4, R3
    li R5, 1
    str R4, R5
    //pop that(SP -5) 'return address'
    li R1, 0
    load R31, R1
    li R2, 5
    sub R3, R31, R2
    load R26, R3
    mov R31, R29
    str R31, R1
    return
//function Main.average 3 1
(Main.average)
//push constant 0
     li R1, 0
     load R31, R1

     li R2, 0
     str R2, R31
     Incr R31
     str R31, R1
//pop local 2
     li R1, 0
     load R31, R1
     Decr R31
     str R31, R1
     load R2, R31
     li R3, 1
     load R4, R3
     li R5, 2
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
//push constant 0
     li R1, 0
     load R31, R1

     li R2, 0
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
(whileStatementStart_6)
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
//push argument 0
     li R1, 0
     load R31, R1
     li R1, 2
     load R3, R1

     li R2, 0
     add R4, R3, R2
     load R30, R4
     str R30, R31
     Incr R31
     li R1, 0
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
//if-goto whileTrueStatement_6
     li R1, 0
     load R31, R1
     Decr R31
     load R12, R31
     str R31, R1
     li R1, 1
     cmp R12, R1
     jeq whileTrueStatement_6
//goto whileEndStatement_6
     jmp whileEndStatement_6
(whileTrueStatement_6)
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
//push static 0
     li R1, 0
     load R31, R1
     li R1, 6
     load R3, R1

     li R2, 0
     add R4, R3, R2
     load R30, R4
     str R30, R31
     Incr R31
     li R1, 0
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
//pop pointer 1
     li R1, 0
     load R31, R1
     Decr R31
     str R31, R1
     load R2, R31
     li R3, 4
     str R2, R3
//push that 0
     li R1, 0
     load R31, R1
     li R1, 4
     load R3, R1

     li R2, 0
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
//goto whileStatementStart_6
     jmp whileStatementStart_6
(whileEndStatement_6)
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
//push argument 0
     li R1, 0
     load R31, R1
     li R1, 2
     load R3, R1

     li R2, 0
     add R4, R3, R2
     load R30, R4
     str R30, R31
     Incr R31
     li R1, 0
     str R31, R1
//call Main.div 3 2
     // push return address given as a number
     li R1, 0
     load R31, R1
     //replace the following li R2, return_address_
     li R2, _returnAddress6
     str R2, R31
     Incr R31
     str R31, R1

     // push local
     li R10, 1
     load R11, R10
     li R1, 0
     load R31, R1
     str R11, R31
     Incr R31
     str R31, R1
     
     // push argument
     li R10, 2
     load R11, R10
     li R1, 0
     load R31, R1
     str R11, R31
     Incr R31
     str R31, R1
     
     // push this
     li R10, 3
     load R11, R10
     li R1, 0
     load R31, R1
     str R11, R31
     Incr R31
     str R31, R1
     
     // push that
     li R10, 4
     load R11, R10
     li R1, 0
     load R31, R1
     str R11, R31
     Incr R31
     str R31, R1
     
     //New Arg = SP - 5 - nArgs -1
     li R2, 2
     li R1, 0
     load R31, R1
     li R4, 5
     // R3 = SP - 5- nArgs
     sub R3, R31, R4
     //R6 = nArgs
     li R6, 2
     sub R7, R3, R6
     // new Arg = SP - 5 - nArgs
     str R7, R2
     
     li R2, 1
     li R1, 0
     load R3, R1
     str R3, R2
     //push number of local variables
     // R2 = num_of_local_Variables
     li R2, 3
     li R3, 0
     li R1, 0
     load R31, R1
     (repeat_6)
     str R3, R31
     Incr R31
     str R31, R1
     Decr R2
     li R4, 0
     cmp R2, R4
     jneq repeat_6
     jmp Main.div
(_returnAddress6)
//pop local 2
     li R1, 0
     load R31, R1
     Decr R31
     str R31, R1
     load R2, R31
     li R3, 1
     load R4, R3
     li R5, 2
     add R7, R4, R5
     str R2, R7
//push local 2
     li R1, 0
     load R31, R1
     li R1, 1
     load R3, R1

     li R2, 2
     add R4, R3, R2
     load R30, R4
     str R30, R31
     Incr R31
     li R1, 0
     str R31, R1
//return
    li R2, 2
    load R30, R2
    load R29, R2
    Incr R29
    li R1, 0
    load R31, R1
    Decr R31
    str R31, R1
    load R20, R31
    str R20, R30
    //SP = local0
    li R1, 0
    load R31, R1
    li R2, 1
    load R31, R2
    str R31, R1
    //pop that(SP -1) 'that' pointer
    li R1, 0
    load R31, R1
    li R2, 1
    sub R3, R31, R2
    load R4, R3
    li R5, 4
    str R4, R5
    //pop that(SP -2) 'this' pointer
    li R1, 0
    load R31, R1
    li R2, 2
    sub R3, R31, R2
    load R4, R3
    li R5, 3
    str R4, R5
    //pop that(SP -3) 'argument' pointer
    li R1, 0
    load R31, R1
    li R2, 3
    sub R3, R31, R2
    load R4, R3
    li R5, 2
    str R4, R5
    //pop that(SP -4) 'local' pointer
    li R1, 0
    load R31, R1
    li R2, 4
    sub R3, R31, R2
    load R4, R3
    li R5, 1
    str R4, R5
    //pop that(SP -5) 'return address'
    li R1, 0
    load R31, R1
    li R2, 5
    sub R3, R31, R2
    load R26, R3
    mov R31, R29
    str R31, R1
    return
//function Main.sumSeries 2 1
(Main.sumSeries)
//push constant 0
     li R1, 0
     load R31, R1

     li R2, 0
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
(whileStatementStart_7)
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
//push argument 0
     li R1, 0
     load R31, R1
     li R1, 2
     load R3, R1

     li R2, 0
     add R4, R3, R2
     load R30, R4
     str R30, R31
     Incr R31
     li R1, 0
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
     jl label2
     cmp R13, R12
     jge label3
  (label2)
     li R15, 1
  (label3)
     load R31, R1
     str R15, R31
     Incr R31
     str R31, R1
//if-goto whileTrueStatement_7
     li R1, 0
     load R31, R1
     Decr R31
     load R12, R31
     str R31, R1
     li R1, 1
     cmp R12, R1
     jeq whileTrueStatement_7
//goto whileEndStatement_7
     jmp whileEndStatement_7
(whileTrueStatement_7)
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
//push static 0
     li R1, 0
     load R31, R1
     li R1, 6
     load R3, R1

     li R2, 0
     add R4, R3, R2
     load R30, R4
     str R30, R31
     Incr R31
     li R1, 0
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
//pop pointer 1
     li R1, 0
     load R31, R1
     Decr R31
     str R31, R1
     load R2, R31
     li R3, 4
     str R2, R3
//push that 0
     li R1, 0
     load R31, R1
     li R1, 4
     load R3, R1

     li R2, 0
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
//goto whileStatementStart_7
     jmp whileStatementStart_7
(whileEndStatement_7)
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
//return
    li R2, 2
    load R30, R2
    load R29, R2
    Incr R29
    li R1, 0
    load R31, R1
    Decr R31
    str R31, R1
    load R20, R31
    str R20, R30
    //SP = local0
    li R1, 0
    load R31, R1
    li R2, 1
    load R31, R2
    str R31, R1
    //pop that(SP -1) 'that' pointer
    li R1, 0
    load R31, R1
    li R2, 1
    sub R3, R31, R2
    load R4, R3
    li R5, 4
    str R4, R5
    //pop that(SP -2) 'this' pointer
    li R1, 0
    load R31, R1
    li R2, 2
    sub R3, R31, R2
    load R4, R3
    li R5, 3
    str R4, R5
    //pop that(SP -3) 'argument' pointer
    li R1, 0
    load R31, R1
    li R2, 3
    sub R3, R31, R2
    load R4, R3
    li R5, 2
    str R4, R5
    //pop that(SP -4) 'local' pointer
    li R1, 0
    load R31, R1
    li R2, 4
    sub R3, R31, R2
    load R4, R3
    li R5, 1
    str R4, R5
    //pop that(SP -5) 'return address'
    li R1, 0
    load R31, R1
    li R2, 5
    sub R3, R31, R2
    load R26, R3
    mov R31, R29
    str R31, R1
    return
//function Main.createSeries 1 3
(Main.createSeries)
//push constant 0
     li R1, 0
     load R31, R1

     li R2, 0
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
(whileStatementStart_8)
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
//push argument 2
     li R1, 0
     load R31, R1
     li R1, 2
     load R3, R1

     li R2, 2
     add R4, R3, R2
     load R30, R4
     str R30, R31
     Incr R31
     li R1, 0
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
     jl label4
     cmp R13, R12
     jge label5
  (label4)
     li R15, 1
  (label5)
     load R31, R1
     str R15, R31
     Incr R31
     str R31, R1
//if-goto whileTrueStatement_8
     li R1, 0
     load R31, R1
     Decr R31
     load R12, R31
     str R31, R1
     li R1, 1
     cmp R12, R1
     jeq whileTrueStatement_8
//goto whileEndStatement_8
     jmp whileEndStatement_8
(whileTrueStatement_8)
//push static 0
     li R1, 0
     load R31, R1
     li R1, 6
     load R3, R1

     li R2, 0
     add R4, R3, R2
     load R30, R4
     str R30, R31
     Incr R31
     li R1, 0
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
//push argument 0
     li R1, 0
     load R31, R1
     li R1, 2
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
//push argument 0
     li R1, 0
     load R31, R1
     li R1, 2
     load R3, R1

     li R2, 0
     add R4, R3, R2
     load R30, R4
     str R30, R31
     Incr R31
     li R1, 0
     str R31, R1
//push argument 1
     li R1, 0
     load R31, R1
     li R1, 2
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
//pop argument 0
     li R1, 0
     load R31, R1
     Decr R31
     str R31, R1
     load R2, R31
     li R3, 2
     load R4, R3
     li R5, 0
     add R7, R4, R5
     str R2, R7
//goto whileStatementStart_8
     jmp whileStatementStart_8
(whileEndStatement_8)
//push constant 0
     li R1, 0
     load R31, R1

     li R2, 0
     str R2, R31
     Incr R31
     str R31, R1
//return
    li R2, 2
    load R30, R2
    load R29, R2
    Incr R29
    li R1, 0
    load R31, R1
    Decr R31
    str R31, R1
    load R20, R31
    str R20, R30
    //SP = local0
    li R1, 0
    load R31, R1
    li R2, 1
    load R31, R2
    str R31, R1
    //pop that(SP -1) 'that' pointer
    li R1, 0
    load R31, R1
    li R2, 1
    sub R3, R31, R2
    load R4, R3
    li R5, 4
    str R4, R5
    //pop that(SP -2) 'this' pointer
    li R1, 0
    load R31, R1
    li R2, 2
    sub R3, R31, R2
    load R4, R3
    li R5, 3
    str R4, R5
    //pop that(SP -3) 'argument' pointer
    li R1, 0
    load R31, R1
    li R2, 3
    sub R3, R31, R2
    load R4, R3
    li R5, 2
    str R4, R5
    //pop that(SP -4) 'local' pointer
    li R1, 0
    load R31, R1
    li R2, 4
    sub R3, R31, R2
    load R4, R3
    li R5, 1
    str R4, R5
    //pop that(SP -5) 'return address'
    li R1, 0
    load R31, R1
    li R2, 5
    sub R3, R31, R2
    load R26, R3
    mov R31, R29
    str R31, R1
    return
//function Main.div 3 2
(Main.div)
//push argument 0
     li R1, 0
     load R31, R1
     li R1, 2
     load R3, R1

     li R2, 0
     add R4, R3, R2
     load R30, R4
     str R30, R31
     Incr R31
     li R1, 0
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
//pop local 2
     li R1, 0
     load R31, R1
     Decr R31
     str R31, R1
     load R2, R31
     li R3, 1
     load R4, R3
     li R5, 2
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
(whileStatementStart_9)
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
//push argument 1
     li R1, 0
     load R31, R1
     li R1, 2
     load R3, R1

     li R2, 1
     add R4, R3, R2
     load R30, R4
     str R30, R31
     Incr R31
     li R1, 0
     str R31, R1
//gte
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
     jge label6
     cmp R13, R12
     jl label7
  (label6)
     li R15, 1
  (label7)
     load R31, R1
     str R15, R31
     Incr R31
     str R31, R1
//if-goto whileTrueStatement_9
     li R1, 0
     load R31, R1
     Decr R31
     load R12, R31
     str R31, R1
     li R1, 1
     cmp R12, R1
     jeq whileTrueStatement_9
//goto whileEndStatement_9
     jmp whileEndStatement_9
(whileTrueStatement_9)
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
//push argument 1
     li R1, 0
     load R31, R1
     li R1, 2
     load R3, R1

     li R2, 1
     add R4, R3, R2
     load R30, R4
     str R30, R31
     Incr R31
     li R1, 0
     str R31, R1
//sub
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
     sub R14, R13, R12
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
//push local 2
     li R1, 0
     load R31, R1
     li R1, 1
     load R3, R1

     li R2, 2
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
//pop local 2
     li R1, 0
     load R31, R1
     Decr R31
     str R31, R1
     load R2, R31
     li R3, 1
     load R4, R3
     li R5, 2
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
//goto whileStatementStart_9
     jmp whileStatementStart_9
(whileEndStatement_9)
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
//return
    li R2, 2
    load R30, R2
    load R29, R2
    Incr R29
    li R1, 0
    load R31, R1
    Decr R31
    str R31, R1
    load R20, R31
    str R20, R30
    //SP = local0
    li R1, 0
    load R31, R1
    li R2, 1
    load R31, R2
    str R31, R1
    //pop that(SP -1) 'that' pointer
    li R1, 0
    load R31, R1
    li R2, 1
    sub R3, R31, R2
    load R4, R3
    li R5, 4
    str R4, R5
    //pop that(SP -2) 'this' pointer
    li R1, 0
    load R31, R1
    li R2, 2
    sub R3, R31, R2
    load R4, R3
    li R5, 3
    str R4, R5
    //pop that(SP -3) 'argument' pointer
    li R1, 0
    load R31, R1
    li R2, 3
    sub R3, R31, R2
    load R4, R3
    li R5, 2
    str R4, R5
    //pop that(SP -4) 'local' pointer
    li R1, 0
    load R31, R1
    li R2, 4
    sub R3, R31, R2
    load R4, R3
    li R5, 1
    str R4, R5
    //pop that(SP -5) 'return address'
    li R1, 0
    load R31, R1
    li R2, 5
    sub R3, R31, R2
    load R26, R3
    mov R31, R29
    str R31, R1
    return
//function Memory.init 1 1
(Memory.init)
//push constant 4096
     li R1, 0
     load R31, R1

     li R2, 4096
     str R2, R31
     Incr R31
     str R31, R1
//pop static 1
     li R1, 0
     load R31, R1
     Decr R31
     str R31, R1
     load R2, R31
     li R3, 6
     load R4, R3
     li R5, 1
     add R7, R4, R5
     str R2, R7
//push constant 0
     li R1, 0
     load R31, R1

     li R2, 0
     str R2, R31
     Incr R31
     str R31, R1
//pop static 2
     li R1, 0
     load R31, R1
     Decr R31
     str R31, R1
     load R2, R31
     li R3, 6
     load R4, R3
     li R5, 2
     add R7, R4, R5
     str R2, R7
//push static 1
     li R1, 0
     load R31, R1
     li R1, 6
     load R3, R1

     li R2, 1
     add R4, R3, R2
     load R30, R4
     str R30, R31
     Incr R31
     li R1, 0
     str R31, R1
//return
    li R2, 2
    load R30, R2
    load R29, R2
    Incr R29
    li R1, 0
    load R31, R1
    Decr R31
    str R31, R1
    load R20, R31
    str R20, R30
    //SP = local0
    li R1, 0
    load R31, R1
    li R2, 1
    load R31, R2
    str R31, R1
    //pop that(SP -1) 'that' pointer
    li R1, 0
    load R31, R1
    li R2, 1
    sub R3, R31, R2
    load R4, R3
    li R5, 4
    str R4, R5
    //pop that(SP -2) 'this' pointer
    li R1, 0
    load R31, R1
    li R2, 2
    sub R3, R31, R2
    load R4, R3
    li R5, 3
    str R4, R5
    //pop that(SP -3) 'argument' pointer
    li R1, 0
    load R31, R1
    li R2, 3
    sub R3, R31, R2
    load R4, R3
    li R5, 2
    str R4, R5
    //pop that(SP -4) 'local' pointer
    li R1, 0
    load R31, R1
    li R2, 4
    sub R3, R31, R2
    load R4, R3
    li R5, 1
    str R4, R5
    //pop that(SP -5) 'return address'
    li R1, 0
    load R31, R1
    li R2, 5
    sub R3, R31, R2
    load R26, R3
    mov R31, R29
    str R31, R1
    return
//function Memory.allocate 1 1
(Memory.allocate)
//push static 1
     li R1, 0
     load R31, R1
     li R1, 6
     load R3, R1

     li R2, 1
     add R4, R3, R2
     load R30, R4
     str R30, R31
     Incr R31
     li R1, 0
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
//push static 1
     li R1, 0
     load R31, R1
     li R1, 6
     load R3, R1

     li R2, 1
     add R4, R3, R2
     load R30, R4
     str R30, R31
     Incr R31
     li R1, 0
     str R31, R1
//push argument 0
     li R1, 0
     load R31, R1
     li R1, 2
     load R3, R1

     li R2, 0
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
//pop static 1
     li R1, 0
     load R31, R1
     Decr R31
     str R31, R1
     load R2, R31
     li R3, 6
     load R4, R3
     li R5, 1
     add R7, R4, R5
     str R2, R7
//push static 2
     li R1, 0
     load R31, R1
     li R1, 6
     load R3, R1

     li R2, 2
     add R4, R3, R2
     load R30, R4
     str R30, R31
     Incr R31
     li R1, 0
     str R31, R1
//push argument 0
     li R1, 0
     load R31, R1
     li R1, 2
     load R3, R1

     li R2, 0
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
//pop static 2
     li R1, 0
     load R31, R1
     Decr R31
     str R31, R1
     load R2, R31
     li R3, 6
     load R4, R3
     li R5, 2
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
//return
    li R2, 2
    load R30, R2
    load R29, R2
    Incr R29
    li R1, 0
    load R31, R1
    Decr R31
    str R31, R1
    load R20, R31
    str R20, R30
    //SP = local0
    li R1, 0
    load R31, R1
    li R2, 1
    load R31, R2
    str R31, R1
    //pop that(SP -1) 'that' pointer
    li R1, 0
    load R31, R1
    li R2, 1
    sub R3, R31, R2
    load R4, R3
    li R5, 4
    str R4, R5
    //pop that(SP -2) 'this' pointer
    li R1, 0
    load R31, R1
    li R2, 2
    sub R3, R31, R2
    load R4, R3
    li R5, 3
    str R4, R5
    //pop that(SP -3) 'argument' pointer
    li R1, 0
    load R31, R1
    li R2, 3
    sub R3, R31, R2
    load R4, R3
    li R5, 2
    str R4, R5
    //pop that(SP -4) 'local' pointer
    li R1, 0
    load R31, R1
    li R2, 4
    sub R3, R31, R2
    load R4, R3
    li R5, 1
    str R4, R5
    //pop that(SP -5) 'return address'
    li R1, 0
    load R31, R1
    li R2, 5
    sub R3, R31, R2
    load R26, R3
    mov R31, R29
    str R31, R1
    return
//function Memory.poke 1 2
(Memory.poke)
//push constant 0
     li R1, 0
     load R31, R1

     li R2, 0
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
//push argument 0
     li R1, 0
     load R31, R1
     li R1, 2
     load R3, R1

     li R2, 0
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
//push argument 1
     li R1, 0
     load R31, R1
     li R1, 2
     load R3, R1

     li R2, 1
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
//push constant 1
     li R1, 0
     load R31, R1

     li R2, 1
     str R2, R31
     Incr R31
     str R31, R1
//return
    li R2, 2
    load R30, R2
    load R29, R2
    Incr R29
    li R1, 0
    load R31, R1
    Decr R31
    str R31, R1
    load R20, R31
    str R20, R30
    //SP = local0
    li R1, 0
    load R31, R1
    li R2, 1
    load R31, R2
    str R31, R1
    //pop that(SP -1) 'that' pointer
    li R1, 0
    load R31, R1
    li R2, 1
    sub R3, R31, R2
    load R4, R3
    li R5, 4
    str R4, R5
    //pop that(SP -2) 'this' pointer
    li R1, 0
    load R31, R1
    li R2, 2
    sub R3, R31, R2
    load R4, R3
    li R5, 3
    str R4, R5
    //pop that(SP -3) 'argument' pointer
    li R1, 0
    load R31, R1
    li R2, 3
    sub R3, R31, R2
    load R4, R3
    li R5, 2
    str R4, R5
    //pop that(SP -4) 'local' pointer
    li R1, 0
    load R31, R1
    li R2, 4
    sub R3, R31, R2
    load R4, R3
    li R5, 1
    str R4, R5
    //pop that(SP -5) 'return address'
    li R1, 0
    load R31, R1
    li R2, 5
    sub R3, R31, R2
    load R26, R3
    mov R31, R29
    str R31, R1
    return
//function Memory.peek 2 1
(Memory.peek)
//push constant 0
     li R1, 0
     load R31, R1

     li R2, 0
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
//push argument 0
     li R1, 0
     load R31, R1
     li R1, 2
     load R3, R1

     li R2, 0
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
//pop pointer 1
     li R1, 0
     load R31, R1
     Decr R31
     str R31, R1
     load R2, R31
     li R3, 4
     str R2, R3
//push that 0
     li R1, 0
     load R31, R1
     li R1, 4
     load R3, R1

     li R2, 0
     add R4, R3, R2
     load R30, R4
     str R30, R31
     Incr R31
     li R1, 0
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
//return
    li R2, 2
    load R30, R2
    load R29, R2
    Incr R29
    li R1, 0
    load R31, R1
    Decr R31
    str R31, R1
    load R20, R31
    str R20, R30
    //SP = local0
    li R1, 0
    load R31, R1
    li R2, 1
    load R31, R2
    str R31, R1
    //pop that(SP -1) 'that' pointer
    li R1, 0
    load R31, R1
    li R2, 1
    sub R3, R31, R2
    load R4, R3
    li R5, 4
    str R4, R5
    //pop that(SP -2) 'this' pointer
    li R1, 0
    load R31, R1
    li R2, 2
    sub R3, R31, R2
    load R4, R3
    li R5, 3
    str R4, R5
    //pop that(SP -3) 'argument' pointer
    li R1, 0
    load R31, R1
    li R2, 3
    sub R3, R31, R2
    load R4, R3
    li R5, 2
    str R4, R5
    //pop that(SP -4) 'local' pointer
    li R1, 0
    load R31, R1
    li R2, 4
    sub R3, R31, R2
    load R4, R3
    li R5, 1
    str R4, R5
    //pop that(SP -5) 'return address'
    li R1, 0
    load R31, R1
    li R2, 5
    sub R3, R31, R2
    load R26, R3
    mov R31, R29
    str R31, R1
    return
//function Array.new 1 1
(Array.new)
//push argument 0
     li R1, 0
     load R31, R1
     li R1, 2
     load R3, R1

     li R2, 0
     add R4, R3, R2
     load R30, R4
     str R30, R31
     Incr R31
     li R1, 0
     str R31, R1
//call Memory.allocate 1 1
     // push return address given as a number
     li R1, 0
     load R31, R1
     //replace the following li R2, return_address_
     li R2, _returnAddress7
     str R2, R31
     Incr R31
     str R31, R1

     // push local
     li R10, 1
     load R11, R10
     li R1, 0
     load R31, R1
     str R11, R31
     Incr R31
     str R31, R1
     
     // push argument
     li R10, 2
     load R11, R10
     li R1, 0
     load R31, R1
     str R11, R31
     Incr R31
     str R31, R1
     
     // push this
     li R10, 3
     load R11, R10
     li R1, 0
     load R31, R1
     str R11, R31
     Incr R31
     str R31, R1
     
     // push that
     li R10, 4
     load R11, R10
     li R1, 0
     load R31, R1
     str R11, R31
     Incr R31
     str R31, R1
     
     //New Arg = SP - 5 - nArgs -1
     li R2, 2
     li R1, 0
     load R31, R1
     li R4, 5
     // R3 = SP - 5- nArgs
     sub R3, R31, R4
     //R6 = nArgs
     li R6, 1
     sub R7, R3, R6
     // new Arg = SP - 5 - nArgs
     str R7, R2
     
     li R2, 1
     li R1, 0
     load R3, R1
     str R3, R2
     //push number of local variables
     // R2 = num_of_local_Variables
     li R2, 1
     li R3, 0
     li R1, 0
     load R31, R1
     (repeat_7)
     str R3, R31
     Incr R31
     str R31, R1
     Decr R2
     li R4, 0
     cmp R2, R4
     jneq repeat_7
     jmp Memory.allocate
(_returnAddress7)
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
//return
    li R2, 2
    load R30, R2
    load R29, R2
    Incr R29
    li R1, 0
    load R31, R1
    Decr R31
    str R31, R1
    load R20, R31
    str R20, R30
    //SP = local0
    li R1, 0
    load R31, R1
    li R2, 1
    load R31, R2
    str R31, R1
    //pop that(SP -1) 'that' pointer
    li R1, 0
    load R31, R1
    li R2, 1
    sub R3, R31, R2
    load R4, R3
    li R5, 4
    str R4, R5
    //pop that(SP -2) 'this' pointer
    li R1, 0
    load R31, R1
    li R2, 2
    sub R3, R31, R2
    load R4, R3
    li R5, 3
    str R4, R5
    //pop that(SP -3) 'argument' pointer
    li R1, 0
    load R31, R1
    li R2, 3
    sub R3, R31, R2
    load R4, R3
    li R5, 2
    str R4, R5
    //pop that(SP -4) 'local' pointer
    li R1, 0
    load R31, R1
    li R2, 4
    sub R3, R31, R2
    load R4, R3
    li R5, 1
    str R4, R5
    //pop that(SP -5) 'return address'
    li R1, 0
    load R31, R1
    li R2, 5
    sub R3, R31, R2
    load R26, R3
    mov R31, R29
    str R31, R1
    return
