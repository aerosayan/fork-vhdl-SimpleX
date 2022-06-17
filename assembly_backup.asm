//Initialise Segments
//===================
//(Initialise_SP)
    li R1, 100
    li R2, 0
    str R1, R2
    
//(Initialise_local)
    li R3, 200
    li R4, 1
    str R3, R4

//(Initialise_this)
    li R5, 300
    li R6, 2
    str R5, R6

//(Initialise_that)
    li R7, 400
    li R8, 3
    str R7, R8

//(Initialise_temp)
    li R9, 500
    li R10, 4
    str R9, R10

//(Initialise_argument)
    li R11, 600
    li R12, 5
    str R11, R12
       
     li R1, 0
     load R31, R1
     li R2, 5
     str R2, R31
     Incr R31
     str R31, R1

     li R1, 0
     load R31, R1
     li R2, 7
     str R2, R31
     Incr R31
     str R31, R1

//(push_local_index(index = 9))
    li R1, 0
    load R31, R1
    //replace the 1 with the pointer to local
    li R1, 1
    load R3, R1
    //replace the 9 with the index
    li R2, 9
    add R3, R3, R2
    load R30, R3
    str R30, R31
    Incr R31
    li R1, 0
    str R31, R1

//(pop_local_index)
//    li R1, 0
//    load R31, R1
//    Decr R31
//    str R31, R1
//    load R2, R31
//    li R3, 1
//    load R4, R3
//    li R5, 9
//    add R4, R4, R5
//    str R2, R4

