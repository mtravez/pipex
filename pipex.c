/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:30:44 by mtravez           #+#    #+#             */
/*   Updated: 2023/02/21 18:08:20 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_holder	*holder;
	int			i;

	holder = init_holder(argv, argc, get_paths(envp));
	if (!holder)
	{
		write(STDERR_FILENO, "bad holder input", 9);
		return (EXIT_FAILURE);
	}
	holder->envp = envp;
	i = 0;
	while (i < argc - 3)
	{
		if (!parent(holder, i))
		{
			write(STDERR_FILENO, "bad command input", 9);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (0);
}
