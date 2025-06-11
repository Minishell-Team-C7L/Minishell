#include "include/minishell.h"

t_data share_data = {0};

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	int i = 0;
	while (1337)
	{
		share_data.line = readline("minishell-$ ");
		//if (!share_data.line);
			// if line == NULL cleanup
		// if line != NULL add to history
		share_data.token = to_tokens(share_data.line); // return pointer to token structs that have my tokens
		share_data.abs = to_parse();
	}
}
