/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:39:14 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/22 11:11:05 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execution.h"

#define PROSSES_IS_CHILD 0

static pid_t	static_fork_left_child(
					t_node *node, int *pipe_fd, t_data *data);
static pid_t	static_fork_right_child(
					t_node *node, int *pipe_fd, t_data *data);
static int		static_parent_wait(
					pid_t left_pid, pid_t right_pid, int *pipe_fd);
bool			msh_is_forkable(t_node *node);

int	msh_execute_pipe(t_node *node, t_data *data)
{
	int		pipe_fd[2];
	pid_t	left_pid;
	pid_t	right_pid;

	if (!msh_is_forkable(node))
		return (EXIT_FAILURE);
	if (pipe(pipe_fd) == -1)
		return (msh_perror("pipe"));
	msh_signal_off();
	left_pid = static_fork_left_child(node, pipe_fd, data);
	if (left_pid == -1)
	{
		(close(pipe_fd[0]), close(pipe_fd[1]));
		return (EXIT_FAILURE);
	}
	right_pid = static_fork_right_child(node, pipe_fd, data);
	return (static_parent_wait(left_pid, right_pid, pipe_fd));
}

bool	msh_is_forkable(t_node *node)
{
	pid_t	pid;
	int		status;

	if (!node)
		return (true);
	if (node->type == PIPE_N)
	{
		pid = fork();
		if (pid < 0)
			return (perror("fork"), 0);
		if (pid == 0)
			exit(!msh_is_forkable(node->left)
				|| !msh_is_forkable(node->right));
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) != EXIT_SUCCESS)
			return (false);
	}
	return (true);
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
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			exit(msh_perror("dup2"));
		close(pipe_fd[1]);
		exit(msh_execute(data, node->left));
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
		exit(msh_execute(data, node->right));
	}
	return (pid);
}

static int	static_parent_wait(
	pid_t left_pid, pid_t right_pid, int *pipe_fd)
{
	int	status_right;

	if (right_pid == -1)
	{
		waitpid(left_pid, NULL, 0);
		(close(pipe_fd[0]), close(pipe_fd[1]));
		return (EXIT_FAILURE);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(left_pid, NULL, 0);
	if (waitpid(right_pid, &status_right, 0) == -1)
		return (msh_perror("waitpid"));
	if (msh_signal() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (msh_signal_status(status_right));
}
