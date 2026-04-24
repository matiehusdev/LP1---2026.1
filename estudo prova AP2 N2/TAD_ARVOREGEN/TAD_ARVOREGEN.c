#include <stdio.h>
#include <stdlib.h>
#include "TAD_ARVOREGEN.h"

// Funções essências
int tree_empty(Node* root) {
    return root == NULL;
}
Node* tree_create_empty() {
    return NULL;
}
void tree_free(Node* root){
    if(tree_empty(root)) return;
    
    tree_free(root->lst);
    tree_free(root->rst);
    free(root);
}
Node* tree_copy_node(Node* original) {
    if(tree_empty(original)) return NULL;
    return tree_create_node(original->info, NULL, NULL);
}
ListaGen* tree_filter_as_list(Node* root, int (*condition)(void*), void* (*copy_info)(void*));

// Revisão de estudos
int tree_count_even(Node* root) {
    if(tree_empty(root)) return 0;
    int count = (*(int*)root->info % 2 == 0) ? 1 : 0;
    return count + tree_count_even(root->lst) + tree_count_even(root->rst);
}
int tree_sum_all(Node* root) {
    if(tree_empty(root)) return 0;
    int count = *(int*)root->info;
    return count + tree_sum_all(root->lst) + tree_sum_all(root->rst);
}
// Função auxiliar, só escreve e não mexe no arquivo
void tree_to_file_aux(Node* root, FILE* file, char* (*create_line)(void*)) {
    if(tree_empty(root)) return;
    char* line = create_line(root->info);
    fprintf(file, "%s\n", line);
    free(line);
    tree_to_file_aux(root->lst, file, create_line);
    tree_to_file_aux(root->rst, file, create_line);
}
void tree_to_file(Node* root, char* file_name, char* (*create_line)(void*)) {
    FILE* fp = fopen(file_name, "w");
    if(!fp) return;
    tree_to_file_aux(root, fp, create_line);
    fclose(fp);
}
Node* tree_load_from_file(char* file_name, void* (*read_line)(char*), int (*compare)(void*, void*)) {
    Node* root = NULL;
    
    FILE* fp = fopen(file_name, "r");
    if(!fp) return NULL;

    char line[256];
    while(fgets(line, 256, fp)) {
        line[strcspn(line, "\n")] = '\0';
        void* aux = read_line(line);
        Node* aux_node = tree_create_node(aux, NULL, NULL);
        root = tree_insert_node(root, aux_node, compare);
    }   

    fclose(fp);
    return root;
}
int tree_deepest_level(Node* root) {
    if(tree_empty(root)) return -1;
    int current = tree_deepest_level(root->lst);
    int current_r = tree_deepest_level(root->rst);
    if(current < current_r) return current_r + 1;
    return current + 1;
}
int tree_count_at_level(Node* root, int level, int (*condition)(void*)) {
    if(tree_empty(root)) return 0;
    if(level == 0)
        return (condition(root->info)) ? 1 : 0;
    return tree_count_at_level(root->lst, level-1, condition) + tree_count_at_level(root->rst, level-1, condition);
}

// funções importantes também
Node* tree_create_node(void* info, Node* lst, Node* rst) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if(!new_node) exit(1);

    new_node->info = info;
    new_node->lst = NULL;
    new_node->rst = NULL;

    return new_node;
}
void tree_map(Node* root, void (*operation)(void*)) {
    if(tree_empty(root)) return;

    operation(root->info);
    tree_map(root->lst, operation);
    tree_map(root->rst, operation);
}
Node* tree_search(Node* root, int (*condition)(void*)) {
    if(tree_empty(root)) return NULL;
    if(condition(root->info)) return root;
    ListaGen* found = tree_search(root->lst, condition);
    if(found) return found;
    return tree_search(root->rst, condition);
}

// Importantes também
Node* tree_filter(Node* root, int (*condition)(void*), void* (*copy_info)(void*), int (*compare)(void*, void*)) {
    if(tree_empty(root)) return NULL;

    Node* filter_l = tree_filter(root->lst, condition, copy_info, compare);
    Node* filter_r = tree_filter(root->rst, condition, copy_info, compare);

    if(condition(root->info)){
        Node* new_node = tree_create_node(root->info, NULL, NULL);
        filter_l = tree_insert_node(filter_l, new_node, compare);
    }
    return filter_l;
}
Node* tree_delete_node(Node* root, int (*condition)(void*)) {
    if(tree_empty(root)) return NULL;

    if(condition(root->info)){
        if(root->lst == NULL && root->rst == NULL){
            free(root);
            return root;
        }
        if(root->lst == NULL){
            Node* aux = root->rst;
            free(aux);
            return aux;
        }
        if(root->rst == NULL){
            Node* aux = root->lst;
            free(root);
            return aux;
        }
    }
    else{
        root->lst = tree_delete_node(root->lst, condition);
        root->rst = tree_delete_node(root->rst, condition);
    }
    return root;
}
Node* tree_insert_node(Node* root, Node* new_node, int (*compare)(void*, void*)) {
    if(tree_empty(root)) return NULL;

    if(compare(root->info, new_node->info) <= 0)
        root->lst = tree_insert_node(root->lst, new_node, compare);
    else
        root->rst = tree_insert_node(root->rst, new_node, compare);
    return root;
}

// Funções legais
int tree_get_height(Node* root) {
    if(tree_empty(root)) return -1;
    int left = tree_get_height(root->lst);
    int right = tree_get_height(root->rst);

    if(left > right) return left+1;
    return right+1;
}
int tree_how_many_nodes(Node* root) {
    if(tree_empty(root)) return 0;
    return 1 + tree_how_many_nodes(root->lst) + tree_how_many_nodes(root->rst);
}

// Ignorar por enquanto
Node* rotate_right(Node* root);
Node* rotate_left(Node* root);
Node* tree_insert_balanced(Node* root, Node* new_node, int (*compare)(void*, void*));
Node* tree_delete_balanced(Node* root, Node* new_node, int (*compare)(void*, void*));

// Bom aprender
int tree_how_many_leaves(Node* root) {
    if(tree_empty(root)) return 0;
    if(root->lst == NULL && root->rst == NULL) return 1;
    return tree_how_many_leaves(root->lst) + tree_how_many_leaves(root->rst);
}
int tree_how_many_nodes_at_level(Node* root, int level) {
    if(tree_empty(root)) return 0;
    if(level == 0) return 1;
    return tree_how_many_nodes_at_level(root->lst, level-1) + tree_how_many_nodes_at_level(root->rst, level-1);
}
Node* tree_find_min(Node* root) {
    if(tree_empty(root)) return NULL;
    Node* min = tree_find_min(root->lst);
    if(min == NULL) return root;
    return min;
}
int tree_get_level(Node* root, void* info, int (*compare)(void*, void*)) {

}

// Bom aprender também
int tree_is_single_node(Node* root) {
    if(tree_empty(root)) return 0;
    return root->lst == NULL && root->rst == NULL;
}
int tree_one_child(Node* root) { 
    if(tree_empty(root)) return 0;
    int count = 0;
    if((root->lst == NULL && root->rst != NULL) || (root->lst != NULL && root->rst == NULL))
        count = 1;

    return count + tree_one_child(root->lst) + tree_one_child(root->rst);
}
Node* tree_find_max(Node* root) {
    if(tree_empty(root)) return 0;
    Node* max = tree_find_max(root->rst);
    if(max == NULL) return root;
    return max;
}
int tree_sum_levels(Node* root, int level) {
    if(tree_empty(root)) return 0;
    if(level == 0)
        return *(int*)root->info;
    return tree_sum_levels(root->lst, level-1) + tree_sum_levels(root->rst, level-1);
}
int tree_same_structure(Node* a, Node* b) {
    if(tree_empty(a) || tree_empty(b)) return 0;

}
int tree_count_greater_than_parent(Node* root, void* parent_info, int (*cmp)(void*,void*));
int tree_nodes_deepest_level(Node* root);
int tree_is_bst(Node* root, void* min, void* max, int (*cmp)(void*,void*));