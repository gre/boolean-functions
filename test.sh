#!/usr/bin/expect -f

spawn ./main

expect "Boolean Functions interpeter"

send "expr funct = (x*y)+!a\r"

send "print /e funct\r"
expect "funct = ((x*y)+!a)"

# Table verite
send "print /t funct\r"
expect "funct = (11110001)"

# Dot
send "print /a funct\r"
# Don't know how to escape, so some very basic expectation
expect "label"
expect "n6 *"

# test table and same funct name collision
send "table funct = (0001)\r"
send "print /e funct\r"
expect "funct = (b*a)"

send "table funct = (11110010)\r"
send "print /d funct\r"
expect "funct(abc) = (!a+(!c*(b*a)))"

# test function imbrication
send "expr xor = a*!b+!a*b\r"
send "expr ff = xor(01)\r"
send "print ff\r"
expect "ff() = 1"

send "expr ff' = xor(01)*a\r"
send "print /d ff'\r"
expect "ff'(a) = a"


interact

#send -- "print /t funct\r"

#send "\003\r"

# If we are here, then test is succesful

#interact
