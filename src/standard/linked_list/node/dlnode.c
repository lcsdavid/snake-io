#include "dlnode.h"

dlnode_t* dlnode_create(void* data, dlnode_t* next, dlnode_t* previous);

void dlnode_delete(dlnode_t* node);