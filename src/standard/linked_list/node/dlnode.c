#include "dlnode.h"

const node_t dlnode_default = { (void*)0, (void*)0, (void*)0 };

node_t* dlnode_create(void* data, node_t* next, node_t* previous);

void dlnode_delete(node_t* node);