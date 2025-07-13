#include "include/minishell.h"
#include "include/parse.h"




#include <stdlib.h>
#include <string.h>


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void msh_print_tree_with_branches(t_node *node, int depth)
{
    if (!node)
        return;
    // Print indentation
    for (int i = 0; i < depth; i++)
        printf("  ");
    // Print current node info
    if (node->type == PIPE_N)
        printf("PIPE_N\n");
    else if (node->type == CMD_N)
        printf("CMD_N [%s]\n", node->args ? node->args : "");
    // Print LEFT branch if exists
    if (node->left)
    {
        for (int i = 0; i < depth; i++)
            printf("  ");
        printf("├─ LEFT: ");
        if (node->left->type == PIPE_N)
            printf("PIPE_N\n");
        else
            printf("CMD_N [%s]\n", node->left->args ? node->left->args : "");

        msh_print_tree_with_branches(node->left, depth + 1);
    }
    // Print RIGHT branch if exists
    if (node->right)
    {
        for (int i = 0; i < depth; i++)
            printf("  ");
        printf("└─ RIGHT: ");
        if (node->right->type == PIPE_N)
            printf("PIPE_N\n");
        else
            printf("CMD_N [%s]\n", node->right->args ? node->right->args : "");

        msh_print_tree_with_branches(node->right, depth + 1);
    }
}
/* Clear LEFT/RIGHT structure display */
void msh_print_tree_left_right(t_node *node, int depth)
{
    if (!node)
        return;
    // Print indentation
    for (int i = 0; i < depth; i++)
        printf("    ");
    // Print current node
    printf("┌─ ");
    if (node->type == PIPE_N)
        printf("PIPE_N\n");
    else
        printf("CMD_N [%s]\n", node->args ? node->args : "");
    // Show LEFT branch
    if (node->left)
    {
        for (int i = 0; i < depth; i++)
            printf("    ");
        printf("├─ LEFT:\n");
        msh_print_tree_left_right(node->left, depth + 1);
    }
    else if (node->type == PIPE_N)
    {
        for (int i = 0; i < depth; i++)
            printf("    ");
        printf("├─ LEFT: NULL\n");
    }
    // Show RIGHT branch
    if (node->right)
    {
        for (int i = 0; i < depth; i++)
            printf("    ");
        printf("└─ RIGHT:\n");
        msh_print_tree_left_right(node->right, depth + 1);
    }
    else if (node->type == PIPE_N)
    {
        for (int i = 0; i < depth; i++)
            printf("    ");
        printf("└─ RIGHT: NULL\n");
    }
}
/* Easy function to show LEFT/RIGHT structure */
void msh_show_left_right(t_node *tree)
{
    if (!tree)
    {
        printf("Tree is empty (NULL)\n");
        return;
    }
    printf("\n=== Tree with LEFT/RIGHT branches ===\n");
    msh_print_tree_left_right(tree, 0);
    printf("\n");
}

int main(int ac, char **av)
{
	t_data share_data;
	(void)ac;
	(void)av;
	while (1337)
	{
	// share_data.line = ft_strdup("ls | l");
		share_data.line = readline("minishell-$ ");
		if (!share_data.line)
			continue;
		//if (!share_data.line);   //
			// if line == NULL cleanup
		// if line != NULL add to history
		add_history(share_data.line);
		share_data.token = to_tokens(&share_data); // return pointer to token structs that have my tokens

		// while (share_data.token)
		// {
		// 	printf("%s\n", share_data.token->val);
		// 	printf("%u\n", share_data.token->type);
		// 	share_data.token = share_data.token->next;
		// }

        share_data.abs = to_parse(&share_data);
		// if (share_data.token)
        // else
        //     continue;
		// free(share_data.line); // free this line give me sigabort

    // Print AST if you have a visualizer
    // visualize_ast_tree(share_data.abs);
	// t_
	msh_show_left_right(share_data.abs);

    // Free token list (later)
    return 0;
	}
}
