/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 15:44:50 by mtravez           #+#    #+#             */
/*   Updated: 2023/02/21 18:02:43 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_matrix(char **to_free)
{
	int	i;

	i = 0;
	while (to_free[i])
	{
		free(to_free[i]);
		i++;
	}
	free(to_free);
}

void	free_cmd(t_command *command)
{
	free(command->path);
	free_matrix(command->argv);
	free(command);
}

void	free_holder(t_holder *holder)
{
	int	i;

	i = 0;
	if (holder->cmds)
	{
		while (holder->cmds[i])
			free_cmd(holder->cmds[i++]);
	}
	close (holder->pipe->in_fd);
	close (holder->pipe->out_fd);
	free(holder->pipe);
	free(holder);
}