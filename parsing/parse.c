#include "../include/minishell.h"
#include "../include/parse.h"


int msh_currtoken_pip(t_token *curr_token)
{
    t_token_types curr_type;

    if (!curr_token)
        return(0);
    curr_type = (*curr_token).type;
    if (curr_type == PIPE_T)
        return (1);
    return (0);

}

void msh_next_token(t_data *cur_data)
{
    cur_data->cur_tokens = cur_data->cur_tokens->next;
}

t_node *msh_tree(t_data *data)
{
    t_node *left = NULL;
    t_node *right= NULL;

    if (!data->cur_tokens)
        return (NULL);
    left = before_pip(data);// must be change the start whit the curr_token wvry time i have thenew pip
	if (!left)
		return NULL;
	while (msh_currtoken_pip(data->cur_tokens))
	{
		msh_next_token(data);
		if (!data->cur_tokens)
			return (data->err_prs.perr_type = SYN_E,left);// set err
		right = msh_tree(data);
		if (!right)
			return (left);
		left = msh_head_combine(data,left, right);
		if (!left)
		{
			// msh_clear_tree(&left);
			// msh_clear_tree(&right);
			return (NULL);
		}
	}
	return (left);
}

t_node *to_parse(t_data *data)
{
	t_node *cur_abs;

	data -> cur_tokens = data->token;
	cur_abs = msh_tree(data);
	if (data->cur_tokens)
		return (cur_abs);
	return(cur_abs);
	 // see if you have to append somthing her
}

t_node *before_pip(t_data *cur_data)
{
	t_node		*cmd_b_pip;
	t_red_node	*red_list;
	// t_red_node 	*last_red;

	cmd_b_pip = msh_new_node(CMD_N);
	if (!cmd_b_pip)
		return (cur_data->err_prs.perr_type = MEMO_E, NULL);
	if (msh_red_list(cur_data, &red_list))
		cmd_b_pip->red_l = red_list;
	else
		return (free(cmd_b_pip), NULL);
	if (!msh_join_args(&cmd_b_pip->args, cur_data))
		return(msh_clear_cmd(cmd_b_pip), NULL);
	if (!msh_red_list(cur_data, &red_list))
		return(msh_clear_cmd(cmd_b_pip), NULL);
	if (red_list)
	{
		if (cmd_b_pip->red_l)
		{
			t_red_node *last_red = cmd_b_pip->red_l;
			while (last_red->next)
				last_red = last_red->next;
			last_red->next = red_list;
		}
		else
			cmd_b_pip->red_l = red_list;
	}
	return (cmd_b_pip);
}
