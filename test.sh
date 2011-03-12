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

interact

#send -- "print /t funct\r"

#send "\003\r"

# If we are here, then test is succesful

#interact
