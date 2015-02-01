#include <stdlib.h>
#include <stdio.h>
#include "trie.h"

size_t trie_add_string(trienode *t, const char *str, void *data)
{
    unsigned char c;
    trienode *node, *leaf;
    int nodesadded = 0;
    if (!t || !str || !data) {
        return -1;
    }
    node = t;
    while ((c = *str++)) {
        if (c > 127) {
            return -1;
        }
        if (!node->leaves[c]) {
            leaf = (trienode *)calloc(1, trienodesize);
            if (!leaf) {
                return -1;
            }
            node->leaves[c] = leaf;
            nodesadded++;
        }
        node = node->leaves[c];
    }
    if (node->data) {
        // Perhaps a function passed in to dealloc the data
        // if (!dealloc) { return -1 };
    }
    node->data = (void *)data;
    return nodesadded * trienodesize;
}

void *trie_match_string(trienode *t, const char *str)
{
    unsigned char c;
    trienode *node;
    if (!t || !str) {
        return NULL;
    }
    node = t;
    while ((c = *str++)) {
        if (c > 127) {
            return NULL;
        }
        if (!node->leaves[c]) {
            return NULL;
        }
        node = node->leaves[c];
    }
    return node->data;
}

