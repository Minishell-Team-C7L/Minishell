/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:39:14 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/05 19:16:28 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execution.h"

#define PROSSES_IS_CHILD 0

static pid_t	static_fork_left_child(
					t_node *node, int *pipe_fd, t_data *data);
static pid_t	static_fork_right_child(
					t_node *node, int *pipe_fd, t_data *data);

int	msh_execute_pipe(t_node *node, t_data *data)
{
	int		pipe_fd[2];
	pid_t	left_pid;
	pid_t	right_pid;
	int		exit_status;

	if (pipe(pipe_fd) == -1)
		return (msh_perror("pipe"));
	left_pid = static_fork_left_child(node, pipe_fd, data);
	right_pid = static_fork_right_child(node, pipe_fd, data);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(left_pid, NULL, 0);
	waitpid(right_pid, &exit_status, 0);
	if (WIFEXITED(exit_status))
		return (WEXITSTATUS(exit_status));
	return (EXIT_FAILURE);
}

static pid_t	static_fork_left_child(
	t_node *node, int *pipe_fd, t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (msh_perror("fork"), -1);
	if (pid == PROSSES_IS_CHILD)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		exit(msh_execute(node->left, data));
	}
	return (pid);
}

static pid_t	static_fork_right_child(
	t_node *node, int *pipe_fd, t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (msh_perror("fork"), -1);
	if (pid == PROSSES_IS_CHILD)
	{
		close(pipe_fd[1]);
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
			exit(msh_perror("dup2"));
		close(pipe_fd[0]);
		exit(msh_execute(node->right, data));
	}
	return (pid);
}
