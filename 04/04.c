#include <stdio.h>


int main(int argc, char **argv) {
	int a, b, c, d, o, o2, overlap = 0, overlap2 = 0;
	

	while (!feof(stdin)) {
		o = 0;
		o2 = 0;

		if (fscanf(stdin, "%i-%i,%i-%i\n", &a, &b, &c, &d) != 4)
			break;
		if (a <= c) {
			if (b >= c)
				o2 = 1;
			if (b >= d) {
				o2 = 1;
				o = 1;
			}
		} 

		if (c <= a) {
			if (d >= a)
				o2 = 1;
			if (d >= b) {
				o2 = 1;
				o = 1;
			}
		}

		overlap += o;
		overlap2 += o2;
	}

	printf("Overlaps: %i\n", overlap);
	printf("Overlaps 2: %i\n", overlap2);
}
