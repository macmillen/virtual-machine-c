pushc 0
popg 1 //first fibo
pushc 1
popg 2 //scnd fibo


pushc 10
popg 0 //global 0 loop counter
while_loop:
//loop header
pushg 0
pushc 1
sub
popg 0

pushg 1
pushg 2
add
dup
pushg 2
popg 1
popg 2
wrint

//new line sequence
pushc 10
wrchr

//loop footer
pushg 0
pushc 0
eq
brf while_loop
halt
