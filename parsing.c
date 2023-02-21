/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:44:50 by mtravez           #+#    #+#             */
/*   Updated: 2023/02/21 18:10:56 by mtravez          ###   ########.fr       */
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
	if (!command->path)
		return (NULL);
	return (command);
}

t_holder	*init_holder(char	**argv, int argc, char **paths)
{
	int			i;
	int			j;
	t_holder	*holder;

	if (argc < 5)
		return (NULL);
	holder = malloc(sizeof(t_holder *) + \
	(sizeof(t_command *) * (argc - 3)) + \
	sizeof(char *) * argc);
	if (!holder)
		return (NULL);
	holder->pipe = new_pipe(argv[1], argv[argc - 1]);
	holder->argc = argc;
	holder->argv = argv;
	holder->cmds = malloc(sizeof(t_holder *) * argc - 3);
	j = 0;
	i = 2;
	while (i <= argc - 2)
	{
		(holder->cmds)[j] = new_cmd(ft_split_cmds(argv[i]), paths);
		if (!holder->cmds[j])
			return (NULL);
		i++;
		j++;
	}
	return (holder);
}
