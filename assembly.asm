//Initialise Segments
//===================
//(Initialise_SP)
    li R1,  10
    li R2, 0
    str R1, R2
    
//(Initialise_local)
    li R3, 40
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
    li R11, 80
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
//===========================


//function Main.test  1
(Main.test)
//push constant 9
     li R1, 0
     load R31, R1

     li R2, 9
     str R2, R31
     Incr R31
     str R31, R1
//push constant 4
     li R1, 0
     load R31, R1

     li R2, 4
     str R2, R31
     Incr R31
     str R31, R1
//call Math.mul 2 2
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
     li R2, 2
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
     jmp Math.mul
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
//push constant 9
     li R1, 0
     load R31, R1

     li R2, 9
     str R2, R31
     Incr R31
     str R31, R1
//push constant 4
     li R1, 0
     load R31, R1

     li R2, 4
     str R2, R31
     Incr R31
     str R31, R1
//call Math.max 1 2
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
     (repeat_1)
     str R3, R31
     Incr R31
     str R31, R1
     Decr R2
     li R4, 0
     cmp R2, R4
     jneq repeat_1
     jmp Math.max
(_returnAddress1)
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
//push constant 4
     li R1, 0
     load R31, R1

     li R2, 4
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
//call Math.min 1 2
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
     (repeat_2)
     str R3, R31
     Incr R31
     str R31, R1
     Decr R2
     li R4, 0
     cmp R2, R4
     jneq repeat_2
     jmp Math.min
(_returnAddress2)
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
//push constant 19
     li R1, 0
     load R31, R1

     li R2, 19
     str R2, R31
     Incr R31
     str R31, R1
//call Math.sqrt 3 1
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
     li R2, 3
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
     jmp Math.sqrt
(_returnAddress3)
//pop local 3
     li R1, 0
     load R31, R1
     Decr R31
     str R31, R1
     load R2, R31
     li R3, 1
     load R4, R3
     li R5, 3
     add R7, R4, R5
     str R2, R7
//push constant a
     li R1, 0
     load R31, R1

     li R2, a
     str R2, R31
     Incr R31
     str R31, R1
//push constant 5
     li R1, 0
     load R31, R1

     li R2, 5
     str R2, R31
     Incr R31
     str R31, R1
//call Math.div 3 2
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
     (repeat_4)
     str R3, R31
     Incr R31
     str R31, R1
     Decr R2
     li R4, 0
     cmp R2, R4
     jneq repeat_4
     jmp Math.div
(_returnAddress4)
//pop local 4
     li R1, 0
     load R31, R1
     Decr R31
     str R31, R1
     load R2, R31
     li R3, 1
     load R4, R3
     li R5, 4
     add R7, R4, R5
     str R2, R7
(whileForever)
//goto whileForever
     jmp whileForever
//function Math.mul 2 2
(Math.mul)
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
//push constant 0
     li R1, 0
     load R31, R1

     li R2, 0
     str R2, R31
     Incr R31
     str R31, R1
//nequ
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
     li R15, 0
     cmp R12, R13
     jneq label0
     cmp R12, R13
     jeq label1
  (label0)
     li R15, 1
  (label1)
     li R1, 0
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
//function Math.max 1 2
(Math.max)
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
//gt
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
     jg label2
     cmp R13, R12
     jle label3
  (label2)
     li R15, 1
  (label3)
     load R31, R1
     str R15, R31
     Incr R31
     str R31, R1
     li R1, 0
     load R31, R1
     str R15, R31
     Incr R31
     str R31, R1
//if-goto ifTrueStatement_2
     li R1, 0
     load R31, R1
     Decr R31
     load R12, R31
     str R31, R1
     li R1, 1
     cmp R12, R1
     jeq ifTrueStatement_2
//goto ifFalseStatement_2
     jmp ifFalseStatement_2
(ifTrueStatement_2)
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
//goto ifEndStatement_2
     jmp ifEndStatement_2
(ifFalseStatement_2)
(ifEndStatement_2)
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
//function Math.min 1 2
(Math.min)
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
     jl label6
     cmp R13, R12
     jge label7
  (label6)
     li R15, 1
  (label7)
     load R31, R1
     str R15, R31
     Incr R31
     str R31, R1
     li R1, 0
     load R31, R1
     str R15, R31
     Incr R31
     str R31, R1
//if-goto ifTrueStatement_3
     li R1, 0
     load R31, R1
     Decr R31
     load R12, R31
     str R31, R1
     li R1, 1
     cmp R12, R1
     jeq ifTrueStatement_3
//goto ifFalseStatement_3
     jmp ifFalseStatement_3
(ifTrueStatement_3)
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
//goto ifEndStatement_3
     jmp ifEndStatement_3
(ifFalseStatement_3)
(ifEndStatement_3)
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
//function Math.sqrt 3 1
(Math.sqrt)
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
(whileStatementStart_3)
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
     jge label10
     cmp R13, R12
     jl label11
  (label10)
     li R15, 1
  (label11)
     load R31, R1
     str R15, R31
     Incr R31
     str R31, R1
     li R1, 0
     load R31, R1
     str R15, R31
     Incr R31
     str R31, R1
//if-goto whileTrueStatement_3
     li R1, 0
     load R31, R1
     Decr R31
     load R12, R31
     str R31, R1
     li R1, 1
     cmp R12, R1
     jeq whileTrueStatement_3
//goto whileEndStatement_3
     jmp whileEndStatement_3
(whileTrueStatement_3)
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
//push constant 2
     li R1, 0
     load R31, R1

     li R2, 2
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
//goto whileStatementStart_3
     jmp whileStatementStart_3
(whileEndStatement_3)
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
//function Math.div 3 2
(Math.div)
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
(whileStatementStart_5)
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
     jge label14
     cmp R13, R12
     jl label15
  (label14)
     li R15, 1
  (label15)
     load R31, R1
     str R15, R31
     Incr R31
     str R31, R1
     li R1, 0
     load R31, R1
     str R15, R31
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
//goto whileStatementStart_5
     jmp whileStatementStart_5
(whileEndStatement_5)
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
