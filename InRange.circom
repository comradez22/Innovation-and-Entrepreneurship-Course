pragma circom 2.0.0;
include "./circomlib/circuits/comparators.circom";
include "./circomlib/circuits/bitify.circom";
template InAuthorizedRange()
{
	signal input min_grade;
	signal input your_grade;
	signal output out;
	component gt=GreaterEqThan(9);
	gt.in[0] <== your_grade;
	gt.in[1] <== min_grade;
	gt.out === 1;
	out <--gt.out;
	out === 1;
}

component main = InAuthorizedRange();
