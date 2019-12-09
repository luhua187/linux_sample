#ifndef _HASH_H_H___
#define _HASH_H_H___

#define HASH_MAX 89977

typedef unsigned int u_int32;

typedef struct _hash_node
{
    u_int32 key;
    void *data;

    struct _hash_table *next;
    
}hash_node;



int get_hash_key(u_int32 key);

int hash_table_init();

int add_data_node(u_int32 key, void *node);

void del_date_node(u_int32 key);

void *del_data_node_ret(u_int32 key);

const void* find_node_by_key(u_int32 key);

int free_hash_table();


#endif