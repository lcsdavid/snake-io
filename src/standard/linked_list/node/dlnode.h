#ifndef DLNODE_H
#define DLNODE_H

typedef struct DoublyLinkedNode node_t;

typedef struct DoublyLinkedNode {
    node_t* next;
    node_t* previous;
    void* data;
} node_t;

const node_t dlnode_default;

node_t* dlnode_create(void* data, node_t* next, node_t* previous);

void dlnode_delete(node_t* node);


#endif
