/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   family.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 18:44:10 by mtravez           #+#    #+#             */
/*   Updated: 2023/02/21 14:58:56 by mtravez          ###   ########.fr       */
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
	close (pipes[0]);
	if (execve(holder->cmds[index]->path, \
	holder->cmds[index]->argv, holder->envp) == -1)
	{
		exit(2);
		// return (0);
	}
	return (1);
}

int	parent(t_holder *holder, int index)
{
	int	her;
	int	fd[2];
	int	status;

	if (pipe(fd))
		return (0);
	her = fork();
	if (her == 0)
		if (child(holder, index, fd) == 0)
			return (0);
	close (holder->pipe->in_fd);
	holder->pipe->in_fd = fd[0];
	close (fd[1]);
	waitpid(her, &status, 0);
	return (1);
}
// child[0] -> dup2(in_fd, pipe[1])
// child[1] -> dup2(pipe[0], pipe1[1])
// child[2] -> dup2(pipe1[0], out_fd)