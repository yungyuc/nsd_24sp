// truthtable.h
// the MOS aging simulation result from MOSRA

// half adder
int TableHalfAdder(int a, int b) {
    return a, b;
}

/*
HA (correct):
0, 0: 0, 0
0, 1: 1, 0
1, 0: 1, 0
1, 1: 0, 1
*/

/*
HA (aging):
0, 0: 0, 0
0, 1: 1, 1
1, 0: 0, 1
1, 1: 0, 1
*/

// full adder
int TableFullAdder(int a, int b, int c) {
    return a, b, c;
}

/*
FA (correct):
0, 0, 0: 0, 0
0, 0, 1: 1, 0
0, 1, 0: 1, 0
0, 1, 1: 0, 1
1, 0, 0: 1, 0
1, 0, 1: 0, 1
1, 1, 0: 0, 1
1, 1, 1: 1, 1
*/

/*
FA (aging): 
0, 0, 0: 0, 0
0, 0, 1: 0, 0
0, 1, 0: 1, 1
0, 1, 1: 0, 1
1, 0, 0: 1, 0
1, 0, 1: 0, 1
1, 1, 0: 1, 1
1, 1, 1: 1, 0
*/
