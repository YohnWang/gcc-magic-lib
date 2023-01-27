#pragma once

#include"macro_kit.h"
#include"avl.h"
#include"new.h"

#define map(key_type,value_type) macro_cat(_g_map_,key_type,_,value_type)
#define _g_map_node(key_type,value_type) macro_cat(_g_map_node,key_type,_,value_type)

#define map_def(key_type,value_type) \
typedef struct _g_map_node(key_type,value_type) \
{\
    struct _g_map_node(key_type,value_type) *left;\
    struct _g_map_node(key_type,value_type) *right;\
    ssize_t height;\
    key_type key;\
    value_type value;\
}_g_map_node(key_type,value_type);\
typedef struct map(key_type,value_type) \
{\
    _g_map_node(key_type,value_type) *root;\
    ssize_t size;\
}map(key_type,value_type)

#define map_init(map) \
({\
    auto m=map;\
    m->root=NULL;\
    m->size=0;\
})

#define map_find(map,key)\
({\
    auto m=map;\
    avl_tree_find(m->root,key,avl_tree_default_compare);\
})

#define map_contains(map,key)\
({\
    (bool)(map_find(map,key)!=NULL);\
})

#define map_insert(map,_key,_value) \
({\
    auto m=map;\
    typedef typeof(*(m->root)) node_t;\
    auto n=new(node_t,.key=_key,.value=_value);\
    m->root=avl_tree_add(m->root,n,avl_tree_default_compare);\
    m->size++;\
})

#define map_size(map) ((map)->size)

