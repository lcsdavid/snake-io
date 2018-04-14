#include "dlnode.h"

const dlnode_t dlnode_default = { (void*)0, (void*)0, (void*)0 };

dlnode_t* dlnode_create(void* data, dlnode_t* next, dlnode_t* previous);

void dlnode_delete(dlnode_t* node);