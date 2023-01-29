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

#define avl_most_left(root) \
({\
    typedef typeof(root) tree_node_t;\
    tree_node_t avl_left_most(tree_node_t r)\
    {\
        auto p=r;\
        while(p!=NULL) p=p->left;\
        return p;\
    }\
    avl_left_most(root);\
})

#define avl_most_right(root) \
({\
    typedef typeof(root) tree_node_t;\
    tree_node_t avl_right_most(tree_node_t r)\
    {\
        auto p=r;\
        while(p!=NULL) p=p->right;\
        return p;\
    }\
    avl_right_most(root);\
})

#define avl_tree_find(root,_key,compare) \
({\
    typedef typeof(root) tree_node_t;\
    typedef typeof((root)->key) key_t;\
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
            return n;\
        }\
        if(compare(n->key,r->key))\
        {\
            r->left=avl_add(r->left,n);\
            auto hl=avl_get_height(r->left);\
            auto hr=avl_get_height(r->right);\
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
            auto hl=avl_get_height(r->left);\
            auto hr=avl_get_height(r->right);\
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

#define avl_tree_del(root,node,compare) \
({\
    typedef typeof(root) tree_node_t;\
    typedef typeof((root)->key) key_t;\
    tree_node_t move_out_node=NULL;\
    tree_node_t avl_del(tree_node_t r,tree_node_t n)\
    {\
        if(r==NULL) return NULL;\
        if(compare(n->key,r->key))\
        {\
            r->left=avl_del(r->left,n);\
            auto hl=avl_get_height(r->left);\
            auto hr=avl_get_height(r->right);\
            if(hr-hl==2)\
            {\
                auto right=r->right;\
                if(avl_get_height(right->left)>avl_get_height(right->right))\
                    r=avl_rl_rotate(r);\
                else\
                    r=avl_rr_rotate(r);\
            }\
        }\
        else if(compare(r->key,n->key))\
        {\
            r->right=avl_del(r->right,n);\
            auto hl=avl_get_height(r->left);\
            auto hr=avl_get_height(r->right);\
            if(hl-hr==2)\
            {\
                auto left=r->left;\
                if(avl_get_height(left->right)>avl_get_height(left->left))\
                    r=avl_lr_rotate(r);\
                else\
                    r=avl_ll_rotate(r);\
            }\
        }\
        else\
        {\
            if(r->left&&r->right)\
            {\
                if(avl_get_height(r->left)>avl_get_height(r->right))\
                {\
                    auto p=avl_most_right(r->left);\
                    swap(&r->key,&p->key);\
                    r->left=avl_del(r->left,p);\
                }\
                else\
                {\
                    auto p=avl_most_left(r->right);\
                    swap(&r->key,&p->key);\
                    r->right=avl_del(r->right,p);\
                }\
            }\
            else\
            {\
                auto p=r;\
                r=r->left?r->left:r->right;\
                move_out_node=p;\
            }\
        }\
        return r;\
    }\
    auto r=avl_del(root,node);\
    tuple_def(tree_node_t,tree_node_t);\
    (tuple(tree_node_t,tree_node_t)){r,move_out_node};\
})

#endif