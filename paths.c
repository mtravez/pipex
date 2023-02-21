/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 15:30:39 by mtravez           #+#    #+#             */
/*   Updated: 2023/02/21 15:42:15 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_paths(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (!envp[i])
		return (NULL);
	paths = ft_split(&(envp[i][5]), ':');
	return (paths);
}

char	*get_cpath(char **paths, char *cmd)
{
	int		i;
	char	*join_path;
	char	*path;

	i = 0;
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		join_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(join_path, cmd);
		free(join_path);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

t_pipe	*new_pipe(char	*path_in, char *path_out)
{
	t_pipe	*pipe;

	pipe = malloc(sizeof(t_pipe *));
	if (!pipe)
		return (NULL);
	pipe->in_fd = open (path_in, O_RDONLY);
	pipe->out_fd = open (path_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (pipe);
}
