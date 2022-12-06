#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
	int i, j, len;
	char freq[256], window[14] = { 0 };
	
	if (argc < 2 || atoi(argv[1]) < 2 || atoi(argv[1]) > 14)
		return fprintf(stderr, "Pattern length required (4 or 14)\n"), 1;
	
	len = atoi(argv[1]);

	for (i = 0; !feof(stdin); i++) {
		memset(freq, 0, 256);
		window[13] = fgetc(stdin);
		

		for (j = 14 - len; j < 14; j++)
			if (++freq[(unsigned) window[j]] != 1 || !window[j])
				break;
		
		if (j == 14)
			break;
		memmove(&window[0], &window[1], 13);
	}
	
	while(!feof(stdin))
		fgetc(stdin);

	printf("Position: %i\n", i+1);
	return 0;
}
