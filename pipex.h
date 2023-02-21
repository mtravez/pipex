/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:45:12 by mtravez           #+#    #+#             */
/*   Updated: 2023/02/21 12:52:41 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>
# include <string.h>

typedef struct s_pipe
{
	int	in_fd;
	int	out_fd;
}	t_pipe;

typedef struct s_command
{
	char	**argv;
	char	*path;
}	t_command;

typedef struct s_holder
{
	int			argc;
	t_pipe		*pipe;
	char		**argv;
	char		**envp;
	t_command	**cmds;
}	t_holder;

char		**get_paths(char **envp);
char		*get_cpath(char **paths, char *cmd);
t_holder	*init_holder(char	**argv, int argc, char **paths);
t_pipe		*new_pipe(char	*path_in, char *path_out);
int			parent(t_holder *holder, int index);
char		**ft_split_cmds(char *arg);

#endif