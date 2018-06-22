pushc 20
popg 1
pushc 1
popg 2
pushc 1
popg 3

pushc 1
wrint
pushc ' '
wrchr

fib:
pushg 3
wrint
pushc ' '
wrchr
pushg 3
pushg 2
pushg 3
add
popg 3
popg 2
pushg 1
pushc 1
sub
dup
popg 1
brt fib
