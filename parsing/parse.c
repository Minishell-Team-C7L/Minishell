#include "../include/minishell.h"
#include "../include/parse.h"


int msh_currtoken_pip(t_token **curr_token)
{
    t_token_types curr_type;

    if (!(*curr_token))
        return(0);
    curr_type = (*curr_token)->type;
    if (curr_type == PIPE_T)
        return (1);
    return (0);

}

void msh_next_token(t_token **curr_token)
{
    *curr_token = (*curr_token) -> next;
}

t_node *msh_tree(t_data *data)
{
    t_node *left = NULL;
    t_node *right= NULL;

    if (!data)
        return (NULL);

    left = before_pip(&data->token, &data);// must be change the start whit the curr_token wvry time i have thenew pip
	if (!left)
		return NULL;

	while (msh_currtoken_pip(&data->token))
	{
		msh_next_token(&data->token);
		if (!data)
			return (left);
		right = msh_tree(data);
		if (!right)
			return (left);
		left = msh_head_combine(data,left, right);
		if (!left)
			return (NULL); // must clear left and righ  t
	}
	return (left);
	// if (!data->token)
	// 	return (NULL); // that mean the no pip and the null is there return (simple_cmd(left));

    // msh_next_token(&data->token);
    // if (!data->token)
    //     return (NULL); // must be error here and go to left
    // right = ft_tree(data->token);
    // if (!right)
    //     return (left);
	// return msh_head_combine(left, right);
}


void to_parse(t_data *data)
{
	t_data *curr_data;

	curr_data = data;
	if (data->token)
		data->abs = msh_tree(curr_data);
	 // see if you have to append somthing her
}
t_node *before_pip(t_token **cur_token, t_data **cur_data)
{
	t_node *cmd_b_pip;
	int	args_state;
	// t_token *cur_start;
	cmd_b_pip = msh_new_node(CMD_N);
	if (!cmd_b_pip)
		return ((*cur_data)->err_prs.perr_type = MEMO_E, NULL);
	while ((*cur_token) && (*cur_token)->type == WORD_T)
	{

			args_state = msh_join_args(&(cmd_b_pip->args), *(cur_token), *(cur_data));
			if (!args_state)
				return ((*cur_data)->err_prs.perr_type = MEMO_E, NULL); // must clear command node
			// must handel the if its a rediraction
			msh_next_token(cur_token);

	}
	return (cmd_b_pip);
}
