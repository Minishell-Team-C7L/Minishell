
#include "include/minishell.h"
#include <stdio.h>

/*
 * print_args_array - Debug function to print the args array
 * @args: Array of string arguments to print
 * 
 * Prints each argument in the array with its index
 * Useful for debugging and verifying parsing results
 */
void print_args_array(char **args)
{
	int i;

	if (!args)
	{
		printf("Args: NULL\n");
		return;
	}
	i = 0;
	while (args[i])
	{
		printf("args[%d]: %s\n", i, args[i]);
		i++;
	}
}

/*
 * print_redirection_list - Debug function to print redirection list
 * @red_list: Linked list of redirections to print
 * 
 * Prints each redirection with its type and value
 * Shows the complete redirection chain for a command
 */
void print_redirection_list(t_red_node *red_list)
{
	t_red_node *current;
	char *type_str;

	current = red_list;
	while (current)
	{
		if (current->type == IN_RED)
			type_str = "INPUT";
		else if (current->type == OUT_RED)
			type_str = "OUTPUT";
		else if (current->type == APPEND_RED)
			type_str = "APPEND";
		else if (current->type == HEREDOC_RED)
			type_str = "HEREDOC";
		else
			type_str = "UNKNOWN";
		printf("Redirection: %s -> %s\n", type_str, current->val);
		current = current->next;
	}
}

/*
 * test_parsing_simple - Test function for simple command parsing
 * 
 * Tests basic parsing functionality with a simple command
 * Verifies that tokenization and parsing work correctly
 */
void test_parsing_simple(void)
{
	t_data data;
	char *test_line;

	printf("=== Testing Simple Command ===\n");
	test_line = ft_strdup("ls -la /home");
	
	data.line = test_line;
	data.token = to_tokens(test_line);
	data.abs = to_parse(&data);
	
	if (data.abs && data.abs->args)
	{
		printf("Command parsed successfully:\n");
		print_args_array(data.abs->args);
	}
	else
	{
		printf("Parsing failed or no arguments found\n");
	}
	
	free_token_list(&data.token);
	if (data.abs)
		msh_clear_cmd(data.abs);
	free(test_line);
}

int main(void)
{
	test_parsing_simple();
	return (0);
}
