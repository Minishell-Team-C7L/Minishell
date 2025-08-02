/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 09:51:00 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/02 10:12:34 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execution.h"

int	msh_execute(t_node *ast_head, int status, t_env **env, t_gc **gc)
{
	if (!ast_head)
		return (status);
	if (msh_handle_heredocs(ast_head) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (ast_head->type == CMD_N)
		return (msh_execute_cmd(ast_head, status, env, gc));
	else if (ast_head->type == PIPE_N)
		return (msh_execute_pipeline(ast_head, status, env, gc));
	return (EXIT_SUCCESS);
}

// -----------------------------------------------------------------------------

static pid_t	static_fork_left_child(
		t_node *node, int *pipe_fd, int status, t_env **env, t_gc **gc);
static pid_t	static_fork_right_child(
		t_node *node, int *pipe_fd, int status, t_env **env, t_gc **gc);

int	msh_execute_pipeline(t_node *node, int status, t_env **env, t_gc **gc)
{
	int		pipe_fd[2];
	pid_t	left_pid;
	pid_t	right_pid;
	int		exit_status;

	if (pipe(pipe_fd) == -1)
		return (msh_perror("pipe"));
	left_pid = static_fork_left_child(node, pipe_fd, status, env, gc);
	right_pid = static_fork_right_child(node, pipe_fd, status, env, gc);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(left_pid, NULL, 0);
	waitpid(right_pid, &exit_status, 0);
	if (WIFEXITED(exit_status))
		return (WEXITSTATUS(exit_status));
	return (EXIT_FAILURE);
}

static pid_t	static_fork_left_child(
	t_node *node, int *pipe_fd, int status, t_env **env, t_gc **gc)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (msh_perror("fork"), -1);
	if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		exit(msh_execute(node->left, status, env, gc));
	}
	return (pid);
}

static pid_t	static_fork_right_child(
	t_node *node, int *pipe_fd, int status, t_env **env, t_gc **gc)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (msh_perror("fork"), -1);
	if (pid == 0)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		exit(msh_execute(node->right, status, env, gc));
	}
	return (pid);
}
