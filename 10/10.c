#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int eval_cycle(int cycle, int x) {
	int xp;

	xp = (cycle - 1) % 40;
	if (!xp)
		printf("\n");
	if (abs(xp - x) < 2)
		printf("#");
	else
		printf(" ");
	
	if (cycle < 20)
		return 0;
	if (cycle == 20)
		return cycle * x;
	if (cycle > 220)
		return 0;
	cycle -= 20;
	if (cycle % 40 == 0)
		return (cycle + 20) * x;
	return 0;
}


int main(int argc, char **argv) {
	char buff[128], inst[128];
	int cycle = 1, x = 1, acc = 0, val;

	while (!feof(stdin)) {
		fgets(buff, 128, stdin);
		sscanf(buff, "%s %i", inst, &val);

		acc += eval_cycle(cycle, x);
		cycle++;

		if (!strcmp(inst, "noop"))
			continue;
		acc += eval_cycle(cycle, x);
		cycle++;
		x += val;
	}

	printf("sum: %i\n", acc);
	return 0;
}
