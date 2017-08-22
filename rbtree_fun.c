#include <stdio.h>
#include <stdlib.h>
#include <rbtree.h>


/*Right Rotation*/
int right_rotation(rbtree **grandpar)
{
	rbtree *parent = (*grandpar)->l_child;

	/*Rotation*/
	(*grandpar)->l_child = parent->r_child;
	parent->r_child = *grandpar;
	*grandpar = parent;

	/*Recolour*/
	parent->colour = BLACK;
	parent->r_child->colour = RED;
}

/*Left Rotation*/
int left_rotation(rbtree **grandpar)
{
	rbtree *parent = (*grandpar)->r_child;

	/*Rotation*/
	(*grandpar)->r_child = parent->l_child;
	parent->l_child = *grandpar;
	*grandpar = parent;

	/*Recolour*/
	parent->colour = BLACK;
	parent->l_child->colour = RED;
}

/*Left triangle rotation*/
int left_triangle_rotation(rbtree **grandpar)
{
	rbtree *parent = (*grandpar)->l_child;
	rbtree *child = (*grandpar)->l_child->r_child;

	/*Rotation*/
	(*grandpar)->l_child = child;
	parent->r_child = child->l_child;
	child->l_child = parent;
}

/*Right triangle rotation*/
int right_triangle_rotation(rbtree **grandpar)
{
	rbtree *parent = (*grandpar)->r_child;
	rbtree *child = (*grandpar)->r_child->l_child;

	/*Rotation*/
	(*grandpar)->r_child = child;
	parent->l_child = child->r_child;
	child->r_child = parent;
}

/*Function for checking the Red black properties*/
void *rb_property(rbtree *root_node, rbtree **root, int flag)
{
	/*left parent*/
	if (flag == LEFT)
	{
		/*if the parent sibling is red*/
		if ((*root)->r_child != NULL && (*root)->r_child->colour == RED)
		{
			/*Recolour the parent sibling and parent*/
			(*root)->r_child->colour = BLACK;
			(*root)->l_child->colour = BLACK;

			/*if the grand par is not root node*/
			if (*root != root_node)
				/*Recolour*/
				(*root)->colour = RED;
		}
		/*if the parent sibling is not present or parent sibling is black*/
		else if ((*root)->r_child == NULL || (*root)->r_child->colour == BLACK)
		{
			/*if parent left child is present and child is RED node*/
			if ((*root)->l_child->l_child != NULL && (*root)->l_child->l_child->colour == RED)

				/*Rotate right*/
				right_rotation(root);

			/*if parent right child is present and child is RED node*/
			else if ((*root)->l_child->r_child != NULL && (*root)->l_child->r_child->colour == RED)
			{
				/*Rotate left triangle*/
				left_triangle_rotation(root);

				/*Rotate right*/
				right_rotation(root);
			}
		}
	}

	/*Right parent*/
	else if (flag == RIGHT)
	{
		/*if the parent sibling is red and sibling is present*/
		if ((*root)->l_child != NULL && (*root)->l_child->colour == RED)
		{
			/*Recolour*/
			(*root)->r_child->colour = BLACK;
			(*root)->l_child->colour = BLACK;

			/*if the grandparent is not root node*/
			if (*root != root_node)

				/*Recolour*/
				(*root)->colour = RED;
		}

		/*if the parent sibling is not present or parent sibling is black*/
		else if ((*root)->l_child == NULL || (*root)->l_child->colour == BLACK)
		{
			/*if parent right child is present and child is RED node*/
			if ((*root)->r_child->r_child != NULL && (*root)->r_child->r_child->colour == RED)

				/*Rotate right*/
				left_rotation(root);

			/*if parent left child is present and child is RED node*/
			else if ((*root)->r_child->l_child != NULL && (*root)->r_child->l_child->colour == RED)
			{
				/*Rotate left triangle*/
				right_triangle_rotation(root);

				/*Rotate right*/
				left_rotation(root);
			}
		}
	}
}


/*Function for inserting the element in the tree*/
int rb_insert_tree(rbtree *root_node, rbtree **root, int value)
{
	int r_value;

	/*If the root is empty*/
	if (*root == NULL)
	{
		/*allocating dynamic memory*/
		*root = malloc(sizeof (rbtree));

		/*storing the value*/
		(*root)->data = value;

		/*storing the null to the left and right child*/
		(*root)->l_child = NULL;
		(*root)->r_child = NULL;

		/*insert the node as red colour*/
		(*root)->colour = RED;

		/*return colour*/
		return (*root)->colour;
	}

	/*insert the value in the right tree*/
	else if (value > (*root)->data)
	{
		/*call the function recursively*/
		r_value = rb_insert_tree(root_node, &(*root)->r_child, value);

		if (r_value == CHECK)
		{
			/*check the property*/
			rb_property(root_node, root, RIGHT);

			/*return colour*/
			return (*root)->colour;
		}
	}

	/*insert the value in the left tree*/
	else if (value < (*root)->data)
	{
		/*call the function recursively*/
		r_value = rb_insert_tree(root_node, &(*root)->l_child, value);

		if (r_value == CHECK)
		{
			/*check the property*/
			rb_property(root_node, root, LEFT);

			/*return colour*/
			return (*root)->colour;
		}
	}
	else
	{
		printf("Error!!!! The duplicate numbers cant insert in the trees..\n");
		return -1;
	}

	/*if the colour is return value*/
	if ((*root)->colour == r_value)
		return CHECK;

	/*if the return value is -1*/
	if (r_value == -1)
		return r_value;

	/*return the root*/
	return (*root)->colour;
}


/*Function for insertion*/
rbtree *rb_insert(rbtree *root, int value)
{
	/*if the the root is empty*/
	if (root == NULL)
	{
		/*allocate the dynamic memory*/
		root = malloc(sizeof(rbtree));

		/*store the data*/
		root->data = value;

		/*store the left right child to the null*/
		root->l_child = NULL;
		root->r_child = NULL;

		/*insert the node with the black colour*/
		root->colour = BLACK;

		/*return root*/
		return root;
	}
	else
	{
		/*calling insert tree function*/
		rb_insert_tree(root, &root, value);

		/*return root*/
		return root;
	}
}


/*Function for to find the height of the tree*/
int rb_find_height(rbtree *root)
{
	int left_h, right_h;

	/*check if the tree is empty or not*/
	if (root == NULL)
	{
		return 0;
	}
	else
	{
		/*call the find height function recursively*/
		left_h = rb_find_height(root->l_child);

		/*call the find height function recursively*/
		right_h = rb_find_height(root->r_child);

		/*comparing the left_h and right_h*/
		if (left_h > right_h)
		{
			/*if it is true return left value*/
			return left_h + 1;
		}
		else
		{
			/*if it is else return right value*/
			return right_h + 1;
		}
	}
}


/*Function for bfs to traverse every node*/
void rb_bfs(rbtree *root, int level)
{
	/*check if the level is 0 or not*/
	if (level == 0)
	{
		if (root != NULL)
		{
			if (root->colour == RED)
			{
				/*print the data*/
				printf(COLOUR_RED "%d" COLOUR_BLACK, root->data);
				printf("\t");
			}
			else
			{
				/*print the data*/
				printf("%d\t", root->data);
			}
		}
	}
	else if(root != NULL)
	{
		/*call the left side of the root recursively*/
		rb_bfs(root->l_child, level - 1);

		/*call the right side of the root recursively*/
		rb_bfs(root->r_child, level -1);
	}
}

/*Function for the bfs to print level by level*/
void rb_print_level(rbtree *root)
{
	int i_index, Height;

	/*compute the height*/
	Height = rb_find_height(root);

	/*call the function upto the height*/
	for (i_index = 0; i_index <= Height; i_index++)
	{
		rb_bfs(root, i_index);

		printf("\n");
	}
}


/*Function for to find min value in the tree*/
int rb_find_min(rbtree *root)
{
	/*check if the tree is empty or not*/
	if(root == NULL)
	{
		/*if it is true, then print the message*/
		printf("Red-Black tree is empty...\n");
	}
	else
	{
		/*check if the root->left is not equal to null or not*/
		if (root->l_child != NULL)

			/*call the find_min function recursively...*/
			return rb_find_min(root->l_child);

		/*return the root->data*/
		return root->data;
	}
}



/*Function for to find max value in the tree*/
int rb_find_max(rbtree *root)
{
	/*check if the tree is empty or not*/
	if(root == NULL)
	{
		/*if it is true, then print the message*/
		printf("Red-Black tree is empty...\n");
	}
	else
	{
		/*check if the root->right is not equal to null or not*/
		if (root->r_child != NULL)

			/*call the find_max function recursively...*/
			return rb_find_max(root->r_child);

		/*return the root->data*/
		return root->data;
	}
}


/*Function for search the node*/
int rb_search_node(rbtree *root, int value)
{
	/*check if the tree is empty or not*/
	if (root == NULL)
	{
		/*if it is true, return 0*/
		return 0;
	}
	else
	{
		/*check if the root->dat is equal to value*/
		if (root->data == value)

			/*if it is true, return 1*/
			return 1;

		else
		{

			/*call the search node function recursively check if the value is non zero or not*/
			if (rb_search_node(root->l_child, value))

				/*if it is true, return 1*/
				return 1;

			/*call the search node function recursively check if the value is non zero or not*/
			else if (rb_search_node(root->r_child, value))

				/*if it is true, return 1*/
				return 1;

			else

				/*if the node is not found, return 0*/
				return 0;
		}

	}
}


int flag;

/*Function for case 1*/
int case1(rbtree *root_node, rbtree **root)
{
	printf("case 1\n");
	if (*root == root_node)
		return STOP;
}

/*Function for case 2*/
int case2(rbtree *root_node, rbtree **root)
{
	printf("case 2\n");
	left_rotation(root);

	find_delete_case(root_node, &(*root)->l_child);
}

int a_flag;

/*Function for case 3*/
int case3(rbtree *root_node, rbtree **root)
{
	printf("case 3\n");
	(*root)->r_child->colour = RED;

	if (*root == root_node)
		case1(root_node, root);
	else
		a_flag = 1;
}


/*Function for case 4*/
int case4(rbtree *root_node, rbtree **root)
{
	printf("case 4\n");
	(*root)->colour = BLACK;
	(*root)->r_child->colour = RED;

	return STOP;
}


/*Function for case 5*/
int case5(rbtree *root_node, rbtree **root)
{
	printf("case 5\n");
	right_triangle_rotation(root);

	(*root)->r_child->colour = BLACK;

	(*root)->r_child->r_child->colour = RED;

	find_delete_case(root_node, root);
}


/*Function for case 6*/
int case6(rbtree *root_node, rbtree **root)
{
	int i_flag = 1;

	if (*root == root_node)
	{
		i_flag = 0;
	}

	printf("case6\n");
	rbtree *parent = (*root)->r_child;

	/*Rotation*/
	(*root)->r_child = parent->l_child;

	parent->l_child = *root;

	*root = parent;

	/*Recolour*/
	parent->l_child->colour = BLACK;
	parent->r_child->colour = BLACK;

	printf("%d\n", i_flag);
	if (parent->l_child->l_child == NULL && i_flag)
	{
		parent->colour = RED;
	}

	return STOP;

}


/*Function for selecting the case*/
int find_delete_case(rbtree *root_node, rbtree **root)
{
	/*condition for selecting case 6 */
	if ((*root)->r_child->colour == BLACK  && (*root)->r_child->r_child != NULL && (*root)->r_child->r_child->colour == RED)
	{
		case6(root_node, root);
	}
	/*condition for selecting case 4 */
	else if ((*root)->colour == RED)
	{
		case4(root_node, root);
	}
	
	/*condition for selecting case 2 */
	else if ((*root)->r_child->colour == RED)
	{
		if ((*root)->r_child->l_child == NULL && (*root)->r_child->r_child == NULL || (*root)->r_child->l_child->colour == BLACK && (*root)->r_child->r_child->colour == BLACK)
		{
			case2(root_node, root);
		}
	}

	/*condition for selecting case 3 and case 5*/
	else if ((*root)->r_child->colour == BLACK)
	{
		if ((*root)->r_child->l_child == NULL && (*root)->r_child->r_child == NULL || (*root)->r_child->l_child->colour == BLACK && (*root)->r_child->r_child->colour == BLACK)
		{
			case3(root_node, root);
		}
		else if ((*root)->r_child->l_child->colour == RED && (*root)->r_child->r_child == NULL || (*root)->r_child->r_child->colour == BLACK)
		{
			case5(root_node, root);
		}
	}
}

int b_flag, c_flag;

/*Function for the delete node in the tree*/
rbtree  *rb_delete_node(rbtree *root, rbtree *m_root, int value)
{
	//check if the tree is empty or not
	if (root == NULL)
	{
		//if it is true, then print the message
		printf("Empty tree \n");
	}
	else
	{
		//check if the data is greater than the value in the left node or not
		if (root->l_child != NULL && root->data > value)
		{
			//if it is true, call the function recursively
			root->l_child = rb_delete_node(root->l_child, m_root, value);

			if (flag)
			{
				flag = 0;
				find_delete_case(m_root, &root);

				if (a_flag)
				{
					a_flag = 0;
					b_flag = 1;
				}
			}
		}
		//check if the data is less than the value in the right node or not
		else if (root->r_child != NULL && root->data < value)
		{
			//if it is true, call the function recursively
			root->r_child = rb_delete_node(root->r_child, m_root, value);

			if (flag)
			{
				flag = 0;
				find_delete_case(m_root, &root);

				if (a_flag)
				{
					a_flag = 0;
					b_flag = 1;
				}
			}
		}
		//if the value is found
		else if (root->data == value)
		{	
			//check if the left node is null or not
			if (root->l_child == NULL)
			{
				//store the right node to temp
				rbtree *temp = root->r_child;

				if (root->colour == BLACK)
				{
					if (temp != NULL)
					{
						temp->colour = BLACK;
					}
					else
					{
						flag = 1;
					}
				}

				//deallocating the memory for that found node
				free(root);

				//return the right node stored in the temp
				return temp;
			}
			//check if the right node is null or not
			else if (root->r_child == NULL)
			{
				//store the left node to temp
				rbtree *temp = root->l_child;

				if (root->colour == BLACK)
				{
					if (temp != NULL)
					{
						temp->colour = BLACK;
					}
					else
					{
						flag = 1;
					}
				}


				//deallocating the memory for that found node
				free(root);

				//return the right node stored in the temp
				return temp;
			}
			else
			{
				//calling the find_min function to find the min at the right node
				int min = rb_find_min(root->r_child);

				//store the min value to the root->data
				root->data = min;

				//calling the function recursively to delete the duplicate node
				root->r_child = rb_delete_node(root->r_child, m_root, min);

				if (flag)
				{
					flag = 0;
					find_delete_case(m_root, &root);
				}
			}
		}
		else
			//if the element is not found, print the message
			printf("Element is not present\n");
	}

	if (c_flag)
	{
		c_flag = 0;
		find_delete_case(m_root, &root);
	}

	if (b_flag)
	{
		b_flag = 0;

		c_flag = 1;
	}

	//return the root value
	return root;
}


/*Function for inserting the element in the tree*/
rbtree *delete_insert_tree(rbtree *root, int value, int colour)
{
	/*check if the tree is empty or not*/
	if (root == NULL)
	{
		/*If the tree is empty then, assign the dynamic memory allocation for the root*/
		root = malloc(sizeof(rbtree));

		/*Assign root left to the null*/
		root->l_child = NULL;

		/*Assign root right to the null*/
		root->r_child = NULL;

		/*Assign the value to the root->data*/
		root->data = value;

		root->colour = colour;

		/*Return the root address*/
		return root;
	}

	/*check If the inserting data greater than the root->data or not*/
	if (value > root->data)

		/*if it is true, then call the insert_tree function recursively and insert the data at the right side*/
		root->r_child = delete_insert_tree(root->r_child, value, colour);

	/*check if the inserting data is less than the root->data or not*/
	else if (value < root->data)

		/*if it is true, then call the insert_tree function recursively and insert the data at the left side*/
		root->l_child = delete_insert_tree(root->l_child, value, colour);

	else
	{
		/*if the value is equal to root->data, print the error message, because we cant include the duplicate numbers in the tree*/
		printf("Error....The value is already existed in the tree\n");

		/*return null*/
		return root;
	}

	/*Return the root address*/
	return root;
}


/*Function for reading the inputs*/
void reading_inputs(rbtree **root)
{
	int value, colour;

	printf("Enter the value : ");
	scanf("%d", &value);

	printf("Enter the colour : ");
	scanf("%d", &colour);

	*root = delete_insert_tree(*root, value, colour);
}



