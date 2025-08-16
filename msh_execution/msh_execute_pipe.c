/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:39:14 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/14 16:02:38 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execution.h"

#define PROSSES_IS_CHILD 0

static pid_t	static_fork_left_child(
					t_node *node, int *pipe_fd, t_data *data);
static pid_t	static_fork_right_child(
					t_node *node, int *pipe_fd, t_data *data);
static int		static_wait_parent(pid_t left_pid, pid_t right_pid);

int	msh_execute_pipe(t_node *node, t_data *data)
{
	int		pipe_fd[2];
	pid_t	left_pid;
	pid_t	right_pid;

	if (pipe(pipe_fd) == -1)
		return (msh_perror("pipe"));
	if (msh_signal_off() == EXIT_FAILURE)
		return (msh_perror("sigaction"));
	left_pid = static_fork_left_child(node, pipe_fd, data);
	right_pid = static_fork_right_child(node, pipe_fd, data);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	return (static_wait_parent(left_pid, right_pid));
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

static int	static_wait_parent(pid_t left_pid, pid_t right_pid)
{
	int		exit_status;

	waitpid(left_pid, NULL, 0);
	waitpid(right_pid, &exit_status, 0);
	if (msh_signal() == EXIT_FAILURE)
		return (msh_perror("sigaction"));
	if (WIFSIGNALED(exit_status))
	{
		if (WTERMSIG(exit_status) == SIGINT)
			ft_putstr_nl("");
		else if (WTERMSIG(exit_status) == SIGQUIT)
			ft_putstr_nl("Quit: 3");
		return (WTERMSIG(exit_status) + 128);
	}
	if (WIFEXITED(exit_status))
		return (WEXITSTATUS(exit_status));
	return (EXIT_FAILURE);
}
