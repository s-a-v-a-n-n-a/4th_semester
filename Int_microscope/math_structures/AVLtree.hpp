#if 0
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Intercepted_int.hpp"
#include "Int_container.hpp"

// #define TREE_DUMP

typedef struct Avl_node Node;
struct Avl_node
{
	Intercepted_int parent;
	Intercepted_int left_son;
	Intercepted_int right_son;

	Intercepted_int next;

	Intercepted_int value;
	Intercepted_int depth;
	Intercepted_int balance;
};

class Tree
{
    Node *tree;

public:
    Intercepted_int root_index;
    Intercepted_int first_free;

    Tree()
    : tree(nullptr), root_index(0), first_free(0) {}

    Tree(const Intercepted_int amount)
    : tree(nullptr), root_index(0), first_free(0) 
    {
        tree = new Node[amount.get_num()];

        tree[0].parent    = -1;
        tree[0].right_son = -1;
        tree[0].left_son  = -1;

        tree[0].depth     = 0;
        tree[0].balance   = 0;

        root_index = 0;
        first_free = 0;

        for (Intercepted_int i = 0; i < amount; i++)
        {
            tree[i.get_num()].next = i + 1;
        }
    }

    ~Tree()
    {
        delete [] tree;
    }

    // Intercepted_int root_index const { return root_index; }
    // Intercepted_int first_free const { return first_free; }

    Node& operator[] (const Intercepted_int index)
    {
        return tree[index.get_num()];
    }
};

Intercepted_int maximum               (Intercepted_int first, Intercepted_int second);

Tree     *tree_init             (const Intercepted_int amount);

void      tree_destroy          (Tree *avl);

void      tree_update_point     (Tree *avl, Intercepted_int who);

void      tree_rotate_left      (Tree *avl, Intercepted_int parent, Intercepted_int son);

void      tree_rotate_right     (Tree *avl, Intercepted_int parent, Intercepted_int son);

void      tree_big_rotate_left  (Tree *avl, Intercepted_int parent,Intercepted_int son_right, Intercepted_int son_right_left);

void      tree_big_rotate_right (Tree *avl, Intercepted_int parent, Intercepted_int son_left, Intercepted_int son_left_right);

Intercepted_int tree_search_value     (Tree *avl, Intercepted_int key);

void      tree_check_bad_cases  (Tree *avl, Intercepted_int tree_tmp);

void      tree_insert           (Tree *avl, Intercepted_int value);

void      tree_delete           (Tree *avl, Intercepted_int value);

int       tree_existing         (Tree *avl, Intercepted_int value);

Intercepted_int tree_next             (Tree *avl, Intercepted_int value);

Intercepted_int tree_prev             (Tree *avl, Intercepted_int value);

void      generate_tests   ();

void      print_tree       (Node *tree, Intercepted_int root_index, FILE *picture, int go);

// int main()
// {
// 	const Intercepted_int MAX_ELEM = 1000;

// 	Intercepted_int key = 0;

// 	Tree *root = tree_init(MAX_ELEM);
// 	Intercepted_int root_index = 0;

//     generate_tests();

// 	tree_destroy(root);

// 	return 0;
// }

const int COMMANDS_AMOUNT     = 5;
const int REQUESTS_AMOUNT     = 50;
const int MAX_VALUE_GENERATED = 30;

void generate_tests(Tree *root, Int_container *container)
{
    for (int i = 0; i < REQUESTS_AMOUNT; i++)
    {
        int       index  = rand() % COMMANDS_AMOUNT;
        Intercepted_int number = rand() % container->get_length();
        
        switch (index)
        {
        case 0:
            tree_insert(root, (*container)[number]);
            break;
        case 1:
            tree_delete(root, (*container)[number]);
            break;
        case 2:
            tree_existing(root, (*container)[number]);
            break;
        case 3:
            tree_next(root, (*container)[number]);
            break;
        case 4:
            tree_prev(root, (*container)[number]);
            break;
        default:
            break;
        }
    }
}

Intercepted_int maximum(Intercepted_int first, Intercepted_int second)
{
	if (first > second)
	{
		return first;
    }
	else
	{
        return second;
    }
}


Tree *tree_init(const Intercepted_int amount)
{
    Tree *avl = new Tree(amount);

	return avl;
}

void tree_destroy(Tree *avl)
{
    delete avl;
}

void tree_update_point(Tree *avl, Intercepted_int who)
{
	if ((*avl)[who].left_son >= 0 && (*avl)[who].right_son >= 0)
	{
		(*avl)[who].depth = maximum((*avl)[(*avl)[who].left_son].depth, (*avl)[(*avl)[who].right_son].depth) + 1;
		(*avl)[who].balance = (*avl)[(*avl)[who].left_son].depth - (*avl)[(*avl)[who].right_son].depth;
	}
	else if ((*avl)[who].left_son >= 0)
	{
		(*avl)[who].depth = (*avl)[(*avl)[who].left_son].depth + 1;
		(*avl)[who].balance = (*avl)[(*avl)[who].left_son].depth;
	}
	else if ((*avl)[who].right_son >= 0)
	{
		(*avl)[who].depth = (*avl)[(*avl)[who].right_son].depth + 1;
		(*avl)[who].balance = (*avl)[(*avl)[who].right_son].depth * (-1);
	}
	else
	{
		(*avl)[who].depth = 1;
		(*avl)[who].balance = 0;
	}
}

void tree_rotate_left(Tree *avl, Intercepted_int parent, Intercepted_int son)
{
	Intercepted_int tmp = (*avl)[parent].parent;

	(*avl)[parent].right_son = (*avl)[son].left_son;
	if ((*avl)[son].left_son >= 0)
	{
        (*avl)[(*avl)[son].left_son].parent = parent;
    }

	(*avl)[son].left_son  = parent;
	(*avl)[parent].parent = son;

	(*avl)[son].parent    = tmp;
	if (tmp >= 0)
	{
		if (parent == (*avl)[tmp].right_son)
		{
			(*avl)[tmp].right_son = son;
        }
		else
		{
			(*avl)[tmp].left_son = son;
        }
	}

	tree_update_point(avl, parent);
	tree_update_point(avl, son);
}

void tree_rotate_right(Tree *avl, Intercepted_int parent, Intercepted_int son)
{
	Intercepted_int tmp = (*avl)[parent].parent;

    (*avl)[parent].left_son = (*avl)[son].right_son;
	if ((*avl)[son].right_son >= 0)
	{
        (*avl)[(*avl)[son].right_son].parent = parent;
    }

    (*avl)[son].right_son   = parent;
	(*avl)[parent].parent   = son;

	(*avl)[son].parent      = tmp;
	if (tmp >= 0)
	{
		if (parent == (*avl)[tmp].left_son)
		{
			(*avl)[tmp].left_son = son;
        }
		else
		{
			(*avl)[tmp].right_son = son;
        }
	}

	tree_update_point(avl, parent);
	tree_update_point(avl, son);
}

void tree_big_rotate_left(Tree *avl, Intercepted_int parent,Intercepted_int son_right, Intercepted_int son_right_left)
{
	tree_rotate_right(avl, son_right, son_right_left);
	tree_rotate_left(avl, parent, son_right_left);
}

void tree_big_rotate_right(Tree *avl, Intercepted_int parent, Intercepted_int son_left, Intercepted_int son_left_right)
{
	tree_rotate_left(avl, son_left, son_left_right);
	tree_rotate_right(avl, parent, son_left_right);
}

Intercepted_int tree_search_value(Tree *avl, Intercepted_int key)
{
	Intercepted_int tree_tmp = avl->root_index;
	if ((*avl)[tree_tmp].depth == 0)
	{
        return avl->root_index;
    }
	while (tree_tmp >= 0)
	{
		if ((*avl)[tree_tmp].value == key)
		{
			break;
        }

        if ((*avl)[tree_tmp].value > key)
		{
			if ((*avl)[tree_tmp].left_son >= 0)
			{
                tree_tmp = (*avl)[tree_tmp].left_son;
            }
            else
            {
                break;
            }
        }
        else
		{
            if ((*avl)[tree_tmp].right_son >= 0)
            {
                tree_tmp = (*avl)[tree_tmp].right_son;
            }
            else
            {
                break;
            }
        }
	}

	return tree_tmp;
}

void tree_check_bad_cases(Tree *avl, Intercepted_int tree_tmp)
{
    while (tree_tmp >= 0)
        {
            tree_update_point(avl, tree_tmp);

            if ((*avl)[tree_tmp].balance == 2)
            {
                Intercepted_int son_balance = (*avl)[(*avl)[tree_tmp].left_son].balance;
                if (son_balance == 0 || son_balance == 1)
                {
                    tree_rotate_right(avl, tree_tmp, (*avl)[tree_tmp].left_son);
                }
                else if (son_balance == -1)
                {
                    tree_big_rotate_right(avl, tree_tmp, (*avl)[tree_tmp].left_son, (*avl)[(*avl)[tree_tmp].left_son].right_son);
                }
            }
            else if ((*avl)[tree_tmp].balance == -2)
            {
                Intercepted_int son_balance = (*avl)[(*avl)[tree_tmp].right_son].balance;
                if (son_balance == 0 || son_balance == -1)
                {
                    tree_rotate_left(avl, tree_tmp, (*avl)[tree_tmp].right_son);
                }
                else if (son_balance == 1)
                {
                    tree_big_rotate_left(avl, tree_tmp, (*avl)[tree_tmp].right_son, (*avl)[(*avl)[tree_tmp].right_son].left_son);
                }
            }

            if ((*avl)[tree_tmp].parent < 0)
            {
                avl->root_index = tree_tmp;
            }
            tree_tmp = (*avl)[tree_tmp].parent;
        }
}

void tree_insert(Tree *avl, Intercepted_int value)
{
	if ((*avl)[avl->root_index].depth == 0)
	{
		(*avl)[avl->root_index].value = value;
		avl->first_free = (*avl)[avl->root_index].next;

		(*avl)[avl->root_index].parent    = -1;
        (*avl)[avl->root_index].right_son = -1;
        (*avl)[avl->root_index].left_son  = -1;

		tree_update_point(avl, avl->root_index);
	}
	else
	{
		Intercepted_int tree_tmp = tree_search_value(avl, value);

		if ((*avl)[tree_tmp].value != value)
		{
			(*avl)[avl->first_free].value     = value;
			(*avl)[avl->first_free].parent    = tree_tmp;
			(*avl)[avl->first_free].right_son = -1;
			(*avl)[avl->first_free].left_son  = -1;
			(*avl)[avl->first_free].depth     = 1;
			(*avl)[avl->first_free].balance   = 0;

			if ((*avl)[tree_tmp].value > value)
			{
				(*avl)[tree_tmp].left_son = avl->first_free;
			}
			else
			{
				(*avl)[tree_tmp].right_son = avl->first_free;
			}

			avl->first_free = (*avl)[avl->first_free].next;

			tree_check_bad_cases(avl, tree_tmp);
		}
	}
}

void tree_delete(Tree *avl, Intercepted_int value)
{
	Intercepted_int tree_tmp = tree_search_value(avl, value);

    if (tree_tmp == avl->root_index && (*avl)[tree_tmp].right_son < 0 && (*avl)[tree_tmp].left_son < 0 && (*avl)[tree_tmp].value == value)
	{
        (*avl)[tree_tmp].depth = 0;
        (*avl)[tree_tmp].next = avl->first_free;
        avl->first_free = tree_tmp;
	}
	else if ((*avl)[tree_tmp].value == value)
	{
		Intercepted_int tree_found = tree_tmp;

        if ((*avl)[tree_tmp].right_son >= 0)
		{
			tree_tmp = (*avl)[tree_tmp].right_son;

            Intercepted_int indicator_left = 0;
			while ((*avl)[tree_tmp].left_son >= 0)
			{
				tree_tmp = (*avl)[tree_tmp].left_son;
				indicator_left++;
			}

			(*avl)[tree_found].value = (*avl)[tree_tmp].value;
			(*avl)[tree_tmp].next = avl->first_free;
			avl->first_free = tree_tmp;

			if (indicator_left != 0)
			{
                (*avl)[(*avl)[tree_tmp].parent].left_son = (*avl)[tree_tmp].right_son;
                if ((*avl)[tree_tmp].right_son >= 0)
                    (*avl)[(*avl)[tree_tmp].right_son].parent = (*avl)[tree_tmp].parent;
            }
            else
            {
                (*avl)[(*avl)[tree_tmp].parent].right_son = (*avl)[tree_tmp].right_son;
                if ((*avl)[tree_tmp].right_son >= 0)
                    (*avl)[(*avl)[tree_tmp].right_son].parent = (*avl)[tree_tmp].parent;
            }
            tree_tmp = (*avl)[tree_tmp].parent;
		}

		else if ((*avl)[tree_tmp].left_son >= 0)
		{
			tree_tmp = (*avl)[tree_tmp].left_son;

            Intercepted_int indicator_right = 0;
			while ((*avl)[tree_tmp].right_son >= 0)
			{
				tree_tmp = (*avl)[tree_tmp].right_son;
				indicator_right++;
			}

			(*avl)[tree_found].value = (*avl)[tree_tmp].value;
			(*avl)[tree_tmp].next = avl->first_free;
			avl->first_free = tree_tmp;

			if (indicator_right != 0)
			{
                (*avl)[(*avl)[tree_tmp].parent].right_son = (*avl)[tree_tmp].left_son;
                if ((*avl)[tree_tmp].left_son >= 0)
                    (*avl)[(*avl)[tree_tmp].left_son].parent = (*avl)[tree_tmp].parent;
            }
            else
            {
                (*avl)[(*avl)[tree_tmp].parent].left_son = (*avl)[tree_tmp].left_son;
                if ((*avl)[tree_tmp].left_son >= 0)
                    (*avl)[(*avl)[tree_tmp].left_son].parent = (*avl)[tree_tmp].parent;
            }

            tree_tmp = (*avl)[tree_tmp].parent;
		}
		else
		{
			if (tree_tmp == (*avl)[(*avl)[tree_tmp].parent].right_son)
			{
				(*avl)[tree_tmp].next = avl->first_free;
                avl->first_free = tree_tmp;

				tree_tmp = (*avl)[tree_tmp].parent;
				(*avl)[tree_tmp].right_son = -1;
			}
			else
			{
				(*avl)[tree_tmp].next = avl->first_free;
                avl->first_free = tree_tmp;

				tree_tmp = (*avl)[tree_tmp].parent;
				(*avl)[tree_tmp].left_son = -1;
			}
		}

        tree_check_bad_cases(avl, tree_tmp);
	}
}

int tree_existing(Tree *avl, Intercepted_int value)
{
	Intercepted_int tree_tmp = tree_search_value(avl, value);

    if ((*avl)[tree_tmp].value == value && (*avl)[tree_tmp].depth > 0)
	{
		return 1;
    }
	else
	{
		return 0;
    }
}

Intercepted_int tree_next(Tree *avl, Intercepted_int value)
{
	if ((*avl)[avl->root_index].depth == 0)
	{
        return -1;
    }

	Intercepted_int this_branch = avl->root_index;
	Intercepted_int tmp = this_branch;

	while (this_branch >= 0)
    {
        if ((*avl)[this_branch].value <= value)
        {
            if ((*avl)[this_branch].right_son >= 0)
            {
                this_branch = (*avl)[this_branch].right_son;
            }
            else
            {
                break;
            }
        }
        else if ((*avl)[this_branch].value > value)
        {
            tmp = this_branch;
            if ((*avl)[this_branch].left_son >= 0)
            {
                this_branch = (*avl)[this_branch].left_son;
            }
            else
            {
                break;
            }
        }
    }

	if ((*avl)[tmp].value > value)
	{
        return tmp;
    }
    else
    {
        return -1;
    }
}

Intercepted_int tree_prev(Tree *avl, Intercepted_int value)
{
	if ((*avl)[avl->root_index].depth == 0)
	{
        return -1;
    }

	Intercepted_int this_branch = avl->root_index;
	Intercepted_int tmp = this_branch;

	while (this_branch >= 0)
    {
        if ((*avl)[this_branch].value < value)
        {
            tmp = this_branch;
            if ((*avl)[this_branch].right_son >= 0)
            {
                this_branch = (*avl)[this_branch].right_son;
            }
            else
            {
                break;
            }
        }
        else if ((*avl)[this_branch].value >= value)
        {
            if ((*avl)[this_branch].left_son >= 0)
            {
                this_branch = (*avl)[this_branch].left_son;
            }
            else
            {
                break;
            }
        }
    }

	if ((*avl)[tmp].value < value)
	{
        return tmp;
    }
    else
    {
        return -1;
    }
}

#if 0
#endif


#ifdef TREE_DUMP
void print_tree (Node *tree, Intercepted_int root_index, FILE *picture, int go)
{
    if (tree[root_index].left_son < 0 && tree[root_index].right_son < 0)
    {
        if (!go)
        {
            fprintf(picture, "  nod%lld[shape=\"record\" , fillcolor = \"#FEC9E3\", style = filled, ", tree[root_index].value);
            fprintf(picture, "label = \" index %lld | %lld | %lld |  ls %lld | rs %lld | parent %lld\"];\n",
                    root_index, tree[root_index].value, tree[root_index].balance, tree[root_index].left_son, tree[root_index].right_son, tree[root_index].parent);
        }
        else
            fprintf(picture, "nod%lld->", tree[root_index].value);
        return ;
    }

    if (tree[root_index].left_son >= 0)
    {
        print_tree(tree, tree[root_index].left_son, picture, go);
        if (go)
            fprintf(picture, "nod%lld\n", tree[root_index].value);
    }
    if (tree[root_index].right_son >= 0)
    {
        print_tree(tree, tree[root_index].right_son, picture, go);
        if (go)
            fprintf(picture, "nod%lld\n", tree[root_index].value);
    }

    if (!go)
    {
        fprintf(picture, "  nod%lld[shape=\"record\" , fillcolor = \"#FEC9E3\", style = filled, ", tree[root_index].value);
        fprintf(picture, "label = \" index %lld | %lld | %lld |  ls %lld | rs %lld | parent %lld\"];\n",
                          root_index, tree[root_index].value, tree[root_index].balance, tree[root_index].left_son, tree[root_index].right_son, tree[root_index].parent);
    }
    else
        fprintf(picture, "nod%lld->", tree[root_index].value);
    return;
}
#endif
