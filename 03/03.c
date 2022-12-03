#include <ctype.h>
#include <stdio.h>
#include <string.h>

int prio3;
char flags2[256];

int get_prio(char c) {
	int p = 0;
	if (isupper(c))
		p = 26;
	p += tolower(c) - 'a' + 1;
	return p;
}


void do_group() {
	int i;
	for (i = 0; i < 256; i++)
		if (flags2[i] == 7)
			prio3 += get_prio(i);
	memset(flags2, 0, 256);
}


int main(int argc, char **argv) {
	char data[1024], comp1[1024], comp2[1024], flags[256];
	int n, n2, i, j, prio = 0, g, g3;
		
	for (g = 0; !feof(stdin); g++) {
		g3 = g % 3;
		*data = 0;
		if (fscanf(stdin, "%s\n", data) != 1)
			break;
		n = strlen(data);
		n2 = n/2;
		strcpy(comp1, data);
		comp1[n2] = 0;
		strcpy(comp2, &data[n2]);
		
		memset(flags, 0, 256);
		if (!(g % 3)) {
			do_group();
		}

		for (i = 0; i < n2; i++) {
			flags2[(unsigned) comp1[i]] |= (1 << g3);
			for (j = 0; j < n2; j++) {
				flags2[(unsigned) comp2[j]] |= (1 << g3);
				if (comp1[i] == comp2[j]) {
					if (flags[(unsigned) comp1[i]])
						continue;
					flags[(unsigned) comp1[i]] = 1;
					prio += get_prio(comp1[i]);
				}
			}
		}
	}

	do_group();
	
	printf("priority: %i\n", prio);
	printf("badge prio: %i\n", prio3);

	return 0;
}
