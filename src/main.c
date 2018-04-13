#include <stdio.h>

#include "standard/linked_list/node/node.h"

int main(void) {
	dlnode_t node = dlnode_default;
	int a = 5;
	dlnode_t node2 = { (void*)0, (void*)0, &a };

	printf("1: %p %p %p\n2: %p %p %p", node.next, node.previous, node.data,
		node2.next, node2.previous, node2.data);

	return 0;
}