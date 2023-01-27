#ifndef GML_AVL_H
#define GML_AVL_H

#include"numeric.h"
#include<stddef.h>

#define avl_get_height(node) \
({\
    auto n=node;\
    n?n->height:-1;\
})

#define avl_max_height(node1,node2) \
({\
    nmax(avl_get_height(node1),avl_get_height(node2));\
})

#define avl_ll_rotate(_k2) \
({\
    typedef typeof(_k2) avl_node_t;\
    inline avl_node_t ll_rotate(avl_node_t k2)\
    {\
        auto k1=k2->left;\
        k2->left=k1->right;\
        k1->right=k2;\
        k2->height=avl_max_height(k2->left,k2->right)+1;\
        k1->height=avl_max_height(k1->left,k1->right)+1;\
        return k1;\
    }\
    ll_rotate(_k2);\
})

#define avl_rr_rotate(_k2) \
({\
    typedef typeof(_k2) avl_node_t;\
    inline avl_node_t rr_rotate(avl_node_t k2)\
    {\
        auto k1=k2->right;\
        k2->right=k1->left;\
        k1->left=k2;\
        k2->height=avl_max_height(k2->left,k2->right)+1;\
        k1->height=avl_max_height(k1->left,k1->right)+1;\
        return k1;\
    }\
    rr_rotate(_k2);\
})

#define avl_lr_rotate(_k3) \
({\
    auto k3=_k3;\
    k3->left=avl_rr_rotate(k3->left);\
    avl_ll_rotate(k3);\
})

#define avl_rl_rotate(_k3) \
({\
    auto k3=_k3;\
    k3->right=avl_ll_rotate(k3->right);\
    avl_rr_rotate(k3);\
})

#define avl_tree_default_compare(x,y) ((x)<(y))

#define avl_tree_find(root,_key,compare) \
({\
    typedef typeof(root) tree_node_t;\
    typedef typeof(_key) key_t;\
    tree_node_t avl_find(tree_node_t r,key_t k)\
    {\
        tree_node_t p=r;\
        while(p)\
        {\
            bool lr=compare(k,p->key);\
            bool rl=compare(p->key,k);\
            if(!lr&&!rl) break;\
            else if(lr) p=p->left;\
            else p=p->right;\
        }\
        return p;\
    }\
    avl_find(root,_key);\
})

#define avl_tree_add(root,node,compare) \
({\
    typedef typeof(root) tree_node_t;\
    static_assert_type_is_same(root,node);\
    tree_node_t avl_add(tree_node_t r,tree_node_t n)\
    {\
        if(r==NULL)\
        {\
            n->left=NULL;\
            n->right=NULL;\
            n->height=0;\
            return n;\
        }\
        if(compare(n->key,r->key))\
        {\
            r->left=avl_add(r->left,n);\
            int hl=avl_get_height(r->left);\
            int hr=avl_get_height(r->right);\
            if(hl-hr==2)\
            {\
                if(compare(n->key,r->left->key))\
                    r=avl_ll_rotate(r);\
                else if(compare(r->left->key,n->key))\
                    r=avl_lr_rotate(r);\
            }\
        }\
        else if(compare(r->key,n->key))\
        {\
            r->right=avl_add(r->right,n);\
            int hl=avl_get_height(r->left);\
            int hr=avl_get_height(r->right);\
            if(hr-hl==2)\
            {\
                if(compare(n->key,r->right->key))\
                    r=avl_rl_rotate(r);\
                else if(compare(r->right->key,n->key))\
                    r=avl_rr_rotate(r);\
            }\
        }\
        r->height=avl_max_height(r->left,r->right)+1;\
        return r;\
    }\
    avl_add(root,node);\
})

#endif