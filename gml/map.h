#pragma once

#include"macro_kit.h"
#include"avl.h"
#include"new.h"

#define map(key_type,value_type) macro_cat(_g_map_,key_type,_,value_type)
#define _g_map_node(key_type,value_type) macro_cat(_g_map_node,key_type,_,value_type)
#define map_tuple(key_type,value_type) tuple(macro_cat(_g_map,key_type),macro_cat(_g_map,value_type))

#define map_def(key_type,value_type) \
typedef typeof(key_type) macro_cat(_g_map,key_type);\
typedef typeof(value_type) macro_cat(_g_map,value_type);\
tuple_def(macro_cat(_g_map,key_type),macro_cat(_g_map,value_type));\
typedef struct _g_map_node(key_type,value_type) \
{\
    struct _g_map_node(key_type,value_type) *left;\
    struct _g_map_node(key_type,value_type) *right;\
    ssize_t height;\
    map_tuple(key_type,value_type) key;\
}_g_map_node(key_type,value_type);\
typedef struct map(key_type,value_type) \
{\
    _g_map_node(key_type,value_type) *root;\
    ssize_t size;\
}map(key_type,value_type)

#define _g_map_default_compare(x,y) (tuple_get(x,0)<tuple_get(y,0))

#define map_init(map) \
({\
    auto m=map;\
    m->root=NULL;\
    m->size=0;\
})

#define map_find(...) macro_cat(_g_map_find_,count_macro_args(__VA_ARGS__))(__VA_ARGS__)
#define _g_map_find_2(map,_key) _g_map_find_3(map,_key,_g_map_default_compare)
#define _g_map_find_3(map,_key,compare)\
({\
    auto m=map;\
    typedef typeof(m->root->key) key_t;\
    avl_tree_find(m->root,(key_t){_key},compare);\
})

#define map_contains(...) macro_cat(_g_map_contains_,count_macro_args(__VA_ARGS__))(__VA_ARGS__)
#define _g_map_contains_2(map,_key) _g_map_contains_3(map,_key,_g_map_default_compare)
#define _g_map_contains_3(map,key,compare)\
({\
    (bool)(map_find(map,key,compare)!=NULL);\
})

#define map_insert(...) macro_cat(_g_map_insert_,count_macro_args(__VA_ARGS__))(__VA_ARGS__)
#define _g_map_insert_3(map,_key,_value) _g_map_insert_4(map,_key,_value,_g_map_default_compare)
#define _g_map_insert_4(map,_key,_value,compare) \
({\
    auto m=map;\
    typedef typeof(*(m->root)) node_t;\
    auto n=new(node_t,.key={_key,_value});\
    m->root=avl_tree_add(m->root,n,compare);\
    m->size++;\
})

#define map_ref(...) (*_g_map_ref(__VA_ARGS__)) 
#define _g_map_ref(...) macro_cat(_g_map_ref_,count_macro_args(__VA_ARGS__))(__VA_ARGS__)
#define _g_map_ref_2(map,_key) _g_map_ref_3(map,_key,_g_map_default_compare)
#define _g_map_ref_3(map,_key,compare) \
({\
    typedef typeof(map) map_t;\
    typedef typeof(tuple_get((map)->root->key,0)) key_t;\
    typedef typeof(tuple_get((map)->root->key,1)) value_t;\
    value_t* map_ref_helper(map_t m,key_t k)\
    {\
        auto target=map_find(m,k,compare);\
        if(target!=NULL) return &tuple_get(target->key,1);\
        map_insert(m,k,(value_t){0},compare);\
        target=map_find(m,k,compare);\
        return &tuple_get(target->key,1);\
    }\
    map_ref_helper(map,_key);\
})

#define map_erase(...) macro_cat(_g_map_erase_,count_macro_args(__VA_ARGS__))(__VA_ARGS__)
#define _g_map_erase_2(map,_key) _g_map_erase_3(map,_key,_g_map_default_compare)
#define _g_map_erase_3(map,key,compare) \
({\
    auto m=map;\
    auto k=key;\
    auto n=map_find(m,k);\
    auto ret=avl_tree_del(m->root,n,compare);\
    m->root=tuple_get(ret,0);\
    delete(tuple_get(ret,1));\
    m->size--;\
})

#define map_size(map) ((map)->size)

