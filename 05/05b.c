#include <ctype.h>
#include <stdio.h>
#include <string.h>

static char _stack[9][100];

void insert_below(char c, int stack) {
	memmove(&_stack[stack][1], &_stack[stack][0], 99);
	_stack[stack][0] = c;
}


int top_of_stack(int stack) {
	return strlen(_stack[stack]);
}


char crate_at_top(int stack) {
	int top = top_of_stack(stack) - 1;
	if (top < 0)
		return ' ';
	return _stack[stack][top];
}


void insert_above(char c, int stack) {
	_stack[stack][top_of_stack(stack)] = c;
}


char pop_from_stack(int stack) {
	char c;

	c = _stack[stack][top_of_stack(stack) - 1];
	_stack[stack][top_of_stack(stack) - 1] = 0;
	return c;
}


int main(int argc, char **argv) {
	char buff[128];
	int mode = 0, cnt, to, from, i;

	while (!feof(stdin)) {
		*buff = 0;
		fgets(buff, 128, stdin);
		if (!mode) {
			if (isdigit(buff[1])) {
				mode = 1;
				continue;
			}

			for (i = 0; i < 9; i++) {
				if (buff[i*4 + 1] == ' ')
					continue;
				insert_below(buff[i*4+1], i);
			}
		} else {
			char pull_stack[100];
		
			if (sscanf(buff, "move %i from %i to %i\n", &cnt, &from, &to) != 3)
				continue;
			to -= 1, from -= 1;

			for (i = 0; i < cnt; i++)
				pull_stack[i] = pop_from_stack(from);
				
			for (i = cnt - 1; i >= 0; i--)
				insert_above(pull_stack[i], to);
		}
	}

	for (i = 0; i < 9; i++)
		printf("%c", crate_at_top(i));
	printf("\n");

	return 0;
}
