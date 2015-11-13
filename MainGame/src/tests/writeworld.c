#include <stdio.h>
#include <stdlib.h>
#include "../world.h"

int main(int argc, char **argv) {
	int test[5][5] = {
		{1, 2, 3, 4, 5},
		{5, 4, 1, 2, 3},
		{7, 8, 9, 8, 1},
		{3, 5, 4, 7, 6},
		{0, 8, 7, 4, 5}
	};

	int width = 5;
	int height = 5;

	FILE *fug = fopen(argv[1], "wb");
	fwrite(&width, sizeof(int), 1, fug);
	fwrite(&height, sizeof(int), 1, fug);
	fwrite(test, sizeof(int), 25, fug);

	fclose(fug);
	return 0;
}
