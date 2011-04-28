#!/usr/bin/expect -f

spawn ./main

expect "Boolean Functions interpeter"

send "expr funct = (x*y)+!a\r"

send "print /e funct\r"
expect "funct(axy) = ((x*y)+!a)"

# Table verite
send "print /t funct\r"
expect "funct(axy) = (11110001)"

# Dot
send "print /a funct\r"
# Don't know how to escape, so some very basic expectation
expect "label"

# test table and same funct name collision
send "table funct = (0001)\r"
send "print /e funct\r"
expect "funct(ab) = (b*a)"

send "table funct = (11110010)\r"
send "print /d funct\r"
expect "funct(abc) = (!a+(!c*(b*a)))"

send "print /k funct\r"
expect "ab  00 01 11 10"

send "print /b funct\r"
expect "label"

# test function imbrication
send "expr xor = a*!b+!a*b\r"
send "expr ff = xor(01)\r"
send "print ff\r"
expect "ff() = 1"

send "expr ff' = xor(01)*a\r"
send "print /d ff'\r"
expect "ff'(a) = a"

send "expr fun = a*b+c\r"
send "point ident = (***)\r"
send "eval fun ident\r"
expect "fun(0,1,1) = 1"

send "eval fun (111)\r"
expect "fun(1,1,1) = 1"

send "point ident = (111)\r"
expect "(1,1,1)"
send "point ident += (110)\r"
expect "(1,1,1), (1,1,0)"
send "point ident -= (111)\r"
expect "(1,1,0)"

interact

#send -- "print /t funct\r"

#send "\003\r"

# If we are here, then test is succesful

#interact
