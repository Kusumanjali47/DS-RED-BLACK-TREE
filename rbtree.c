#include <stdio.h>
#include <rbtree.h>

/*Main program*/
int main()
{
	
	int option, Element, value, i_index, limit, colour;

	char ch;

	rbtree *root = NULL;

	do
	{
		//Read the option
		printf("Enter the option :\n\t1. Insert\n\t2. Display\n\t3. Search\n\t4. Find Min\n\t5. Find Max\n\t6. Insert_tree_for_Delete\n\t7. Delete\n\t8. Exit\nChoose : ");

		scanf("%d", &option);

		switch (option)
		{
			case 1:

				printf("Enter the limit : ");
				scanf("%d", &limit);

				//Read the elements
				printf("Enter the elements : \n");

				for (i_index = 0; i_index < limit; i_index++)
				{
					scanf("%d", &value);

					root = rb_insert(root, value);
				}

				break;

			case 2:
	
				rb_print_level(root);

				break;

			case 3:

				//read the number to search
				printf("Enter the number to search : ");
				scanf("%d", &value);

				if (rb_search_node(root, value))
				{
					printf("The number %d is found\n", value);
				}
				else
				{
					printf("The number %d is not found\n", value);
				}

				break;

			case 4:

				printf("Minimum value : %d\n", rb_find_min(root));

				break;

			case 5:

				printf("Maximum value : %d\n", rb_find_max(root));

				break;

			case 6:
				
				printf("Enter the limit : ");
				scanf("%d", &limit);
				
				//Read the elements
				printf("Enter the elements : \n");

				for (i_index = 0; i_index < limit; i_index++)
				{
					reading_inputs(&root);
				}

				break;

			case 7:

				printf("Enter the value : ");
				scanf("%d", &value);

				rb_delete_node(root, root, value);

				break;

			case 8:

				//exit the loop
				return 0;

			default:
				printf("Check the option :\n");
		}

		printf("Do you want to continue : (y/n)");
		scanf("\n%c", &ch);

	} while (ch == 'y');

	return 0;

}
