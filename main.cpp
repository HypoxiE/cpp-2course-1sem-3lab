#include <iostream>
#include "hash/hash.h"

using namespace std;

int main() {
	HashTable<int, char> h;
	h[10] = '1';
	return 0;
}