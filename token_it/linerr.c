#include "../include/minishell.h"
#include "../include/parse.h"

int check_after_op(char *line_err, int nm_op)
{
	while (nm_op > 0)
	{
		line_err++;
		nm_op--;
	}
	nm_op = 0;
	while (*line_err)
	{
		if (*line_err == ' ' || *line_err == '\t')
			line_err++;
		else
			nm_op++;
	}
	return (nm_op);
}

int op_calcule(char *line_err, char *operator)
{
	int nm_op;
	char *line_op;

	line_op = line_err;
	nm_op = 0;
	if (!line_op[-1] && (line_op[0] == '|' || (line_op[0] == '<' && line_op[1] == '<')))
		return 0;
	while(*line_err != ' ' && *line_err)
	{
		if (*line_err == *operator)
			nm_op++;
		++line_err;
	}
	if ((!line_err[nm_op - 1] && !check_after_op(line_op, nm_op)))
		return 0;
	if (*operator == '|' && nm_op > 1)
		return 0; // err
	else if ((*operator == '<' || *operator == '>') && nm_op > 2)
		return 0;
	else if (*operator == '\'' || *operator == '\"')
		return (nm_op);
	else
		return 1;
}
void ft_line_err()
{
	ft_putstr_fd("minishell: syntax error\n", 2);
}

int check_line_err(char **line_err)
{
	int nm_q;

	if (**line_err == '"')
		nm_q = op_calcule(*line_err, "\"");
	if (**line_err == '\'')
		nm_q = op_calcule(*line_err, "\'");
	if (**line_err == '|')
		return op_calcule(*line_err, "|");
	else if (**line_err == '<')
		return op_calcule(*line_err, "<");
	else if (**line_err == '>')
		return op_calcule(*line_err, ">");
	else if (**line_err == '&' || nm_q % 2 != 0)
		return 0;
	else
		return 1;
}

