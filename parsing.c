/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:44:50 by mtravez           #+#    #+#             */
/*   Updated: 2023/02/24 18:25:52 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	input_is_valid(char **args, int argc)
{
	int	fd;

	if (argc < 5)
		return (0);
	fd = access(args[1], O_RDONLY);
	if (fd != 0)
		return (0);
	return (1);
}

t_command	*new_cmd(char **cmd, char **paths)
{
	t_command	*command;

	command = malloc(sizeof(t_command *) + sizeof(char *) * 5);
	if (!command)
		return (NULL);
	command->argv = cmd;
	command->path = get_cpath(paths, cmd[0]);
	return (command);
}

t_command	**get_all_commands(t_holder *holder, char **paths)
{
	int			i;
	int			j;
	t_command	**cmds;

	cmds = malloc(sizeof(t_holder *) * holder->argc - 3);
	j = -1;
	i = 1;
	while (++i <= holder->argc - 2)
		cmds[++j] = new_cmd(ft_split_cmds(holder->argv[i]), paths);
	return (cmds);
}

t_holder	*init_holder(char **argv, int argc, char **paths)
{
	t_holder	*holder;

	if (!input_is_valid(argv, argc))
		return (NULL);
	holder = malloc(sizeof(t_holder *) + \
	(sizeof(t_command *) * (argc - 3)) + \
	sizeof(char *) * argc);
	if (!holder)
		return (NULL);
	holder->pipe = new_pipe(argv[1], argv[argc - 1]);
	if (holder->pipe->out_fd == -1)
		return (NULL);
	holder->argc = argc;
	holder->argv = argv;
	holder->cmds = get_all_commands(holder, paths);
	if (!holder->cmds)
		return (NULL);
	return (holder);
}
