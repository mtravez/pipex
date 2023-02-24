/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   family.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 18:44:10 by mtravez           #+#    #+#             */
/*   Updated: 2023/02/24 18:42:31 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	child(t_holder *holder, int index, int *pipes)
{
	dup2(holder->pipe->in_fd, STDIN_FILENO);
	if (index != holder->argc - 4)
		dup2(pipes[1], STDOUT_FILENO);
	else
		dup2(holder->pipe->out_fd, STDOUT_FILENO);
	close (pipes[1]);
	close (holder->pipe->in_fd);
	close (holder->pipe->out_fd);
	close (pipes[0]);
	if (execve(holder->cmds[index]->path, \
	holder->cmds[index]->argv, holder->envp) == -1)
	{
		perror("command not found");
		exit(127);
	}
	return (1);
}

void	close_parent(t_holder *holder, int index, int *fd)
{
	close (holder->pipe->in_fd);
	holder->pipe->in_fd = fd[0];
	close (fd[1]);
	if (index == holder->argc - 4)
	{
		close (fd[0]);
		close (holder->pipe->out_fd);
	}
}

int	parent_ultimate(t_holder *holder)
{
	int	her;
	int	fd[2];
	int	status;
	int	index;

	index = 0;
	while (index < holder->argc - 3)
	{
		if (pipe(fd))
			return (0);
		her = fork();
		if (her == 0)
			child(holder, index, fd);
		else
			close_parent(holder, index++, fd);
	}
	waitpid(her, &status, 0);
	if (WIFEXITED(status))
	{
		if (status != 0)
			return (status);
	}
	return (1);
}

// child[0] -> dup2(in_fd, pipe[1])
// child[1] -> dup2(pipe[0], pipe1[1])
// child[2] -> dup2(pipe1[0], out_fd)