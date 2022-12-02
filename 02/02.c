#include <stdio.h>

static const int _win[9] = {
/*	X	Y	Z */
	3,	6,	0,	// A
	0,	3,	6,	// B
	6,	0,	3	// C
};



int main(int argc, char **argv) {
	char buff[128];
	unsigned char i, j, y;
	int score = 0, score2 = 0, end, res;

	while (!feof(stdin)) {
		*buff = 0, fgets(buff, 128, stdin);
		if (sscanf(buff, "%c %c", (char *) &i, (char *) &j) != 2)
			break;
		y = j;
		i -= 'A';
		j -= 'X';
		score += (j + 1);
		score += _win[i*3 + j];
		
		end = ((int) y) - 'Y';
		res = (i + end);
		if (res < 0)
			res += 3;
		res %= 3;
		score2 += res + 1;
		score2 += _win[i*3 + res];
	}

	printf("Score: %i\n", score);
	printf("Score 2: %i\n", score2);
	return 0;
}
