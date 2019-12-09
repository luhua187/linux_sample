#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <pthread.h>

#include "hash.h"

static hash_node *node_head == NULL;
static pthread_rwlock_t *lock_head = NULL;


static inline hash_node* get_hash_node_head()
{
    return node_head ? node_head:NULL;
}

static inline pthread_rwlock_t* get_lock_head()
{
    return lock_head ? lock_head : NULL;
}

inline u_int32 get_hash_key(int value)
{
    return (value % EP_HASH_MAX) & 0x7fffffff;
}


int hash_table_init()

{
    int i;
    pthread_rwattr_t rwattr;
    
    node_head = (hash_node *)malloc(sizeof(hash_node) * EP_HASH_MAX);
    if(node_head == NULL)
       return -1;

    memset(node_head, 0, sizeof(hash_node)*EP_HASH_MAX);


    lock_head = (pthread_rwlock_t *)malloc(sizeof(pthread_rwlock_t) * EP_HASH_MAX);
    if(lock_head == NULL)
        return -1;

    memset(lock_head, 0, sizeof(sizeof(pthread_rwlock_t) * EP_HASH_MAX));


    memset(&rwattr, 0, sizeof(pthread_rwattr_t));
    
    for(i = 0; i < EP_HASH_MAX; i++)
        pthread_rwlock_init(lock_head[i], &rwattr);


    return 0;
}

int add_data_node(u_int32 key, void *node)
{
    int hash = get_hash_key(key);
    pthread_rwlock_t *lock = &(lock_head[hash]);

    hash_node *p = &(node_head[hash]), 
    hash_node *p_next_node = NULL;

    pthread_rwlock_wrlock(lock);
    if(p->key == 0)
    {
        p->key  = key;
        p->node = node;
        p->next = NULL;
    }
    else
    {    
        p_next_node = (hash_node *)malloc(sizeof(hash_node));
        if(p_next_node == NULL)
        {
            pthread_rwlock_unlock(lock);
            return -1;
        }
        p_next_node->key    = key;
        p_next_node->node   = node;     
    }
    pthread_rwlock_unlock(lock);


    return 0;
}

void del_date_node(u_int32 key)
{
    int hash = get_hash_key(key);
    pthread_rwlock_t *lock = &(lock_head[hash]);

    hash_node *p = &(node_head[hash]), 
    hash_node *p_node = NULL;
    
    pthread_rwlock_wrlock(lock);
    if(p->key == key)
    {
        free(p->data);
        p->key = 0;
        
        if(p->next != NULL)
        {
            p_node  = p->next;
            p->key  = p_node->key;
            p->data = p_node->data;          
            free(p_node); 
        }

        pthread_rwlock_unlock(lock);
        return;
    }

    p_node = p;
    p = p->next;
    while(p)
    {
        if(p->key == key)
        {
            free(p->data);
            p_node->next = p->next;
            pthread_rwlock_unlock(lock);
            
            free(p);
            return;
        }
        else
        {
            p_node = p;
            p = p->next;           
        }
    }

    pthread_rwlock_unlock(lock);
    return ;
}



void* del_data_node_ret(u_int32 key)
{
    int hash = get_hash_key(key);
    pthread_rwlock_t *lock = &(lock_head[hash]);

    hash_node *p = &(node_head[hash]), 
    hash_node *p_node = NULL;
    void *data = NULL;
    
    pthread_rwlock_wrlock(lock);
    if(p->key == key)
    {
        data = p->data;
        p->key = 0;
        
        if(p->next != NULL)
        {
            p_node  = p->next;
            p->key  = p_node->key;
            p->data = p_node->data;          
            free(p_node); 
        }

        pthread_rwlock_unlock(lock);
        return data;
    }

    p_node = p;
    p = p->next;
    while(p)
    {
        if(p->key == key)
        {
            data = p->data;
            p_node->next = p->next;
            pthread_rwlock_unlock(lock);
            
            free(p);
            return data;
        }
        else
        {
            p_node = p;
            p = p->next;           
        }
    }

    pthread_rwlock_unlock(lock);
    return data;
}


const void* find_node_by_key(u_int32 key)
{
    iint hash = get_hash_key(key);
    pthread_rwlock_t *lock = &(lock_head[hash]);

    hash_node *p = &(node_head[hash]), 
    void *p_data = NULL;

    pthread_rwlock_rdlock(lock);
    if(p->key == 0)
    {
        pthread_rwlock_unlock(lock);
        return NULL;
    }
    else
    {    
        while (p != NULL)
        {
            if(p->key == key)
            {
                p_data = p->data;
                pthread_rwlock_unlock(lock);
                return p_data;
            }

            p = p->next;
        }      
    }
    
    pthread_rwlock_unlock(lock);
    return NULL;
}


int free_hash_table()
{
    hash_node *p = NULL, *p_node_next = NULL;
    pthread_rwlock_t *lock = NULL;
    int i;

    for(i = 0; i < EP_HASH_MAX; i++)
    {
        p    = &(node_head[i]);
        lock = &(lock_head[i]);
        pthread_rwlock_wrlock(lock);
        if(p->key != 0)
        {
            free(p->data);
            p = p->next;
            while(p)
            {
                p_node_next = p->next;
                free(p->data);
                free(p);
                p = p_node_next;
            }
        }
        pthread_rwlock_unlock(lock);
        pthread_rwlock_destroy(lock);
    }

    free(node_head);
    free(lock_head);
    return 0;
}


