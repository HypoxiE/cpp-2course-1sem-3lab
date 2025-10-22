#include <cstdlib>

int random(size_t min, size_t max) {
	int range = max - min + 1;
    return (rand() % range) + min;
}