#include <ctype.h>
#include <stdio.h>


static int map[1024*1024];


int check_visible(int x, int y) {
	int i, h, flag = 0;

	h = map[x + y * 1024];
	if (h < 0)
		return -1;

	// From left
	for (i = 0; i < x; i++)
		if (map[i + y*1024] >= h)
			flag |= 1;
	
	// From right
	for (i = x + 1; map[i + y*1024] != -1; i++)
		if (map[i + y*1024] >= h)
			flag |= 2;
	
	// From above
	for (i = 0; i < y; i++)
		if (map[i*1024 + x] >= h)
			flag |= 4;
	
	// From below
	for (i = y + 1; map[i*1024 + x] != -1; i++)
		if (map[i*1024 + x] >= h)
			flag |= 8;
	if (flag == 0xF)
		return 0;
	return 1;
}


int check_score(int x, int y) {
	int i, h, s1, s2, s3, s4;

	h = map[x + y * 1024];
	if (h < 0)
		return 0;

	// From left
	for (i = x - 1, s1 = 0; i >= 0; i--) {
		s1++;
		if (map[i + y*1024] >= h)
			break;
	}
	
	// From right
	for (i = x + 1, s2 = 0; map[i + y*1024] != -1; i++) {
		s2++;
		if (map[i + y*1024] >= h)
			break;
	}
	
	// From above
	for (i = y - 1, s3 = 0; i >= 0; i--) {
		s3++;
		if (map[x + i*1024] >= h)
			break;
	}
	
	// From below
	for (i = y + 1, s4 = 0; map[i*1024 + x] != -1; i++) {
		s4++;
		if (map[x + i*1024] >= h)
			break;
	}

	return s1 * s2 * s3 * s4;
}


int main(int argc, char **argv) {
	int i, j, invisible = 0, visible = 0, hiscore = 0, n, v;
	char buff[128];

	for (i = 0; i < 1024*1024; i++)
		map[i] = -1;

	for (i = 0; !feof(stdin); i++) {
		*buff = 0;
		fgets(buff, 128, stdin);
		for (j = 0; j < 128 && isdigit(buff[j]); j++) {
			n = buff[j] - '0';
			map[i*1024 + j] = n;
		}

	}

	for (i = 0; i < 1024; i++)
		for (j = 0; j < 1024; j++) {
			v = check_visible(i, j);
			if (!v)
				invisible++;
			else if (v == 1)
				visible++;
			if ((n = check_score(i, j)) > hiscore)
				hiscore = n;
		}

	printf("Visible: %i\n", visible);
	printf("Invisible: %i\n", invisible);
	printf("High score: %i\n", hiscore);
	return 0;
}
