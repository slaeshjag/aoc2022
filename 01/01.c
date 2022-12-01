#include <stdio.h>
#include <stdlib.h>

#define	MAX_ELF		1024

static int _cal[MAX_ELF];


static int _cmp(const void *p1, const void *p2) {
	const int *i1 = p1, *i2 = p2;

	return *i2 - *i1;
}


int main(int argc, char **argv) {
	int i, n;
	char buff[128];

	for (i = 0; !feof(stdin) && i < MAX_ELF; i++)
		while (*buff = 0, fgets(buff, 128, stdin), sscanf(buff, "%i\n", &n) == 1)
			_cal[i] += n;
	if (i == MAX_ELF)
		return fprintf(stderr, "Too many elfs\n"), 1;
	
	qsort(&_cal, MAX_ELF, sizeof(int), _cmp);
	printf("%i\n", _cal[0]);
	printf("%i\n", _cal[0] + _cal[1] + _cal[2]);
	
	return 0;	
}
