

bytecode format



// opcode ! (seperator) operand1 : (seperator) operand2, 
1F!0:1
//  for variable addresses use * example

1!*0:*0

// for constant integers just use the value

1!*0:1000

complety original bytecode and instruction set
is not based on the x86 instruction set or any of its rules
much simpler and easyier to use


mov [ax][bx]
first operand must contain variable
second operand must contain constant value or variable

01!*variable:10,thename


code label is what the name they picked, with no space lower cased


// note inheritance, and multiple inheritance
// when the code blocks are loaded, 
// load those other ones in to

; fix the invalid data outside of blocks
; fix if they put " " as theres string constant
; remove multiple traces of \n outside of { }, remove them
; change the way constant variables are handled (check)
; remove them, and replace them with there respective names (check)
; space characters inside constants are replaced with . and ; (check)
; this is so that they can be trimed up and compared with(check)
; constants in the variable look up table(check)
; do not trim comments inside of quotes
; fix it so that invalid blocks are not allowed 
; incoerperate type checking
; add udt
; change & to a unsigned long
; change # to a double 

variables code block contains {
var& - unsigned long (long integer)
var# - double ( real )
var$ - character array }



types processed in its own block
the types block
udt type [$x,&y,#f] 


MAS BYTECODE - written by jared bruni


OPCODE           REGISTERS              MNEMOIC         EXAMPLE (& FOR INTEGER $ FOR STRING)
1                   2                     ADD           ADD X&,Y&     ; add 2 numerics
2                   2                     SUB           SUB X&,Y&     ; subtract 2 numerics
3                   2                     DIV           DIV X&,Y&     ; divide 2 numerics
4                   2                     MUL           MUL X&,Y&     ; multiply 2 numerics
5                   2                     OR            OR  X&,Y&     ; or 2 numerics
6                   2                     XOR           XOR X&,Y&     ; xor 2 numerics
7                   2                     AND           AND X&,Y&     ; and 2 numerics
8                   2                     MOV           MOV X&,Y&     ; mov numeric

; left room to add

20                   1                     INC           INC X&       ; increment numeric
21                   1                     DEC           DEC X&       ; decerment numeric
22                   1                     NOT           NOT X&       ; not numeric



40                    2                    SMOV          SMOV AX$,BX$ ; string move



60                    1                    PRINTLN      PRINTLN VAR$   ; std out w/ a \n
61                    1                    MINPUT       INPUT VAR$   ; std in
62                    1                    MILINE       ILINE VAR$   ; std in by line
63                    1                    PRINT        PRINT  VAR$   ; std out with no \n



;; new

trigger or object

; create all your codes as objects, and then when your ready to make the program
; compile them into there respective .mas formats
; and use the uses (owns) clause with the names of the mas objects


mas trigger { ; application trigger for objects

owns {

jared
jason
josh

}

begin  {


}

end {


}


}



.masasm
.trigger






