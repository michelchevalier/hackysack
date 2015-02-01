/*
 * An ASCII trie
 */

#ifndef TRIE_H
#define TRIE_H

typedef struct _trienode {
    struct _trienode *leaves[128];
    void *data;
} trienode;

extern size_t trienodesize;

size_t trie_add_string(trienode *t, const char *str, void *data);

void *trie_match_string(trienode *t, const char *str);

#endif
