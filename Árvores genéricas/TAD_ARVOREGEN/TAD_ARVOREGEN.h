#ifndef __TAD_ARVOREGEN__
    #define __TAD_ARVOREGEN__

    #include "../../Lista Genérica/TAD_LISTAGEN/TAD_LISTAGEN.h"

    typedef struct node{
        void* info;
        struct node* lst;
        struct node* rst;
    } Node;

    int tree_empty(Node* root);
    Node* tree_create_empty();
    void tree_free(Node* root);
    Node* tree_copy_node(Node* original);
    ListaGen* tree_filter_as_list(Node* root, int (*condition)(void*), void* (*copy_info)(void*));

    Node* tree_create_node(void* info, Node* lst, Node* rst);
    void tree_map(Node* root, void (*operation)(void*));
    Node* tree_search(Node* root, int (*condition)(void*));

    Node* tree_load_from_file(char* file_name, void* (*read_line)(char*), int (*compare)(void*, void*));
    void tree_to_file(Node* root, char* file_name, char* (*create_line)(void*));
 
    Node* tree_filter(Node* root, int (*condition)(void*), void* (*copy_info)(void*), int (*compare)(void*, void*));
    Node* tree_delete_node(Node* root, int (*condition)(void*));
    Node* tree_insert_node(Node* root, Node* new_node, int (*compare)(void*, void*));
    
    int tree_get_height(Node* root);
    int tree_how_many_nodes(Node* root); 
    
    Node* rotate_right(Node* root);
    Node* rotate_left(Node* root);
    Node* tree_insert_balanced(Node* root, Node* new_node, int (*compare)(void*, void*));
    Node* tree_delete_balanced(Node* root, Node* new_node, int (*compare)(void*, void*));

    int tree_how_many_leaves(Node* root);
    int tree_how_many_nodes_at_level(Node* root, int level);
    Node* tree_find_min(Node* root);
    int tree_get_level(Node* root, void* info, int (*compare)(void*, void*));

    int tree_is_single_node(Node* root);
    int tree_one_child(Node* root);
    Node* tree_find_max(Node* root);
    int tree_sum_levels(Node* root, int level);
    int tree_same_structure(Node* a, Node* b);
    int tree_count_greater_than_parent(Node* root, void* parent_info, int (*cmp)(void*,void*));
    int tree_nodes_deepest_level(Node* root);
    int tree_is_bst(Node* root, void* min, void* max, int (*cmp)(void*,void*));
    
#endif