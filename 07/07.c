#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	SEPARATOR " \t\n\r"

static int total_size;
static int small_size;
static int size_buff[1024];
static int size_buff_cur;

int parse_directory(FILE *fp) {
	char buff[128], *tok;
	int cur_size = 0;

	for (; !feof(fp); ) {
		*buff = 0;
		fgets(buff, 128, fp);
		tok = strtok(buff, SEPARATOR);
		if (!tok)
			break;

		if (*tok == '$') {
			tok = strtok(NULL, SEPARATOR);
			if (!strcmp(tok, "cd")) {
				tok = strtok(NULL, SEPARATOR);
				if (!strcmp(tok, ".."))
					break;
				cur_size += parse_directory(fp);
			} else if (!strcmp(tok, "ls"));
		} else if (!strcmp(tok, "dir"));
		else
			cur_size += atoi(tok);
	}

	if (cur_size < 100000)
		small_size += cur_size;
	total_size = cur_size;
	size_buff[size_buff_cur++] = cur_size;

	return cur_size;
}


int main(int argc, char **argv) {
	int i, best, best_index;

	parse_directory(stdin);

	printf("total size: %i\n", total_size);
	printf("small size: %i\n", small_size);
	for (i = best_index = 0, best = 99999999; i < size_buff_cur; i++) {
		if (70000000 - total_size + size_buff[i] < 30000000)
			continue;
		if (size_buff[i] < best)
			best = size_buff[i], best_index = i;
	}

	printf("smallest to delete: %i\n", best);

	return 0;
}
