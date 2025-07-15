#include "include/minishell.h"
#include "include/parse.h"
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
        printf("CMD_N [%s]\n", (node->args[0]) ? node->args[0] : "");
    // Print LEFT branch if exists
    if (node->left)
    {
        for (int i = 0; i < depth; i++)
            printf("  ");
        printf("├─ LEFT: ");
        if (node->left->type == PIPE_N)
            printf("PIPE_N\n");
        else
        {
            int i = 0;
            // Print all command arguments in LEFT branch
            while (node->left->args[i])
            {
                printf("CMD_N [%s]\n", node->left->args[i]);
                i++;
            }
        }
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
            printf("CMD_N [%s]\n", (node->right->args[0]) ? node->right->args[0] : "");

        msh_print_tree_with_branches(node->right, depth + 1);
    }
}

/* Function to show LEFT/RIGHT structure display */
void msh_print_tree_left_right(t_node *node, int depth)
{
    if (!node)
        return;
    
    // Print indentation
    for (int i = 0; i < depth; i++)
        printf("    ");
    
    // Print current node
    printf(" ─ ");
    if (node->type == PIPE_N)
        printf("PIPE_N\n");
    else if (node->type == CMD_N)
    {
        printf("CMD_N [");
        // Print all arguments in the command
        int i = 0;
        while (node->args[i])
        {
            printf("%s", node->args[i]);
            if (node->args[i + 1])
                printf(" ");
            i++;
        }
        printf("]\n");
    }
    
    // Show LEFT branch (command before pipe)
    if (node->left)
    {
        for (int i = 0; i < depth; i++)
            printf("    ");
        printf("├─ LEFT: ");
        if (node->left->type == PIPE_N)
            printf("PIPE_N\n");
        else
        {
            printf("CMD_N [");
            int i = 0;
            while (node->left->args[i])
            {
                printf("%s", node->left->args[i]);
                if (node->left->args[i + 1])
                    printf(" ");
                i++;
            }
            printf("]\n");
        }
        msh_print_tree_left_right(node->left, depth + 1);
    }
    
    // Show RIGHT branch (command after pipe)
    if (node->right)
    {
        for (int i = 0; i < depth; i++)
            printf("    ");
        printf("└─ RIGHT: ");
        if (node->right->type == PIPE_N)
            printf("PIPE_N\n");
        else
        {
            printf("CMD_N [");
            int i = 0;
            while (node->right->args[i])
            {
                printf("%s", node->right->args[i]);
                if (node->right->args[i + 1])
                    printf(" ");
                i++;
            }
            printf("]\n");
        }
        msh_print_tree_left_right(node->right, depth + 1);
    }
}

/* Main function to show LEFT/RIGHT structure */
void msh_show_left_right(t_node *tree, int depth)
{
    if (!tree)
    {
        printf("Tree is empty (NULL)\n");
        return;
    }
    printf("\n=== Tree with LEFT/RIGHT branches ===\n");
    msh_print_tree_left_right(tree, depth);
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
                share_data.line =
                readline("minishell-$ ");
                if (!share_data.line)
                        continue;
                //if (!share_data.line);   //
                        // if line == NULL cleanup
                // if line != NULL add to history
                add_history(share_data.line);
                share_data.token = to_tokens(share_data.line); // return pointer to token structs that have my tokens

                // while (share_data.token)
                // {
                //      printf("%s\n", share_data.token->val);
                //      printf("%u\n", share_data.token->type);
                //      share_data.token = share_data.token->next;
                // }

                share_data.abs = to_parse(&share_data);
                msh_show_left_right(share_data.abs, 0);
                msh_print_tree_with_branches(share_data.abs, 0);
                printf("\n");
                //free(share_data.line);
                //free(share_data.token);
                //free_the_tree(share_data.abs);
        }
        return (0);
}