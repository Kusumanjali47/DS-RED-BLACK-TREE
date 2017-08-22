#ifndef RBTREE_H
#define RBTREE_H

#define COLOUR_BLACK	"\x1b[0m"
#define COLOUR_RED		"\x1b[31m"
#define BLACK	0
#define RED		1
#define CHECK 	2
#define LEFT 	3
#define RIGHT 	4
#define STOP 	10

/*structure for red black tree*/
typedef struct _rbtree
{
	int data;

	int colour;

	struct _rbtree *l_child, *r_child;

}rbtree;

int right_rotation(rbtree **grandpar);

int left_rotation(rbtree **grandpar);

int left_triangle_rotation(rbtree **grandpar);

int right_triangle_rotation(rbtree **grandpar);

void *rb_property(rbtree *root_node, rbtree **root, int flag);

int rb_insert_tree(rbtree *root_node, rbtree **root, int value);

rbtree *rb_insert(rbtree *root, int value);

int rb_find_height(rbtree *root);

void rb_bfs(rbtree *root, int level);

void rb_print_level(rbtree *root);

int rb_find_min(rbtree *root);

int rb_find_max(rbtree *root);

int rb_search_node(rbtree *root, int value);

int case1(rbtree *root_node, rbtree **root);

int case2(rbtree *root_node, rbtree **root);

int case3(rbtree *root_node, rbtree **root);

int case4(rbtree *root_node, rbtree **root);

int case5(rbtree *root_node, rbtree **root);

int case6(rbtree *root_node, rbtree **root);

int find_delete_case(rbtree *root_node, rbtree **root);

rbtree *rb_delete_node(rbtree *root, rbtree *m_root, int value);

rbtree *delete_insert_tree(rbtree *root, int value, int colour);

void reading_inputs(rbtree **root);

#endif
