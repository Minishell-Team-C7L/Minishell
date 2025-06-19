#include "include/minishell.h"


int main(int ac, char **av)
{
	t_data share_data;
	(void)ac;
	(void)av;
	int i = 0;
	while (1337)
	{
		share_data.line = readline("minishell-$ ");
		if (!share_data.line)
			continue;
		//if (!share_data.line);
			// if line == NULL cleanup
		// if line != NULL add to history
		add_history(share_data.line);
		share_data.token = to_tokens(share_data.line); // return pointer to token structs that have my tokens
		while (share_data.token)
		{
			printf("%s\n", share_data.token->val);
			printf("%u\n", share_data.token->type);
			share_data.token = share_data.token->next;
		}

	//	share_data.abs = to_parse(share_data.token);
	}
}
