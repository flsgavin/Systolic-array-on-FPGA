#include "sa.h"
#include "instr.h"

struct Pos{
	int x;
	int y;
	Pos(int i, int j){
		x = i; y = j;
	}
	Pos(){
		x = -1; y = -1;
	}
};
