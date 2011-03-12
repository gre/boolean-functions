#!/usr/bin/expect -f

spawn ./main

expect "Boolean Functions interpeter"

send -- "expr funct = (x*y)+!a\r"
send -- "print /e funct\r"

expect "funct = ((x*y)+!a)"

send "\003\r"

# If we are here, then test is succesful

#interact
