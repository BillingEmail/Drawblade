#include <stdio.h>
#include <stdlib.h>
#include "../world.h"

int main(int argc, char **argv) {
	World *w = NewWorld_FromFile(argv[1]);

	free(w);
	return 0;
}
