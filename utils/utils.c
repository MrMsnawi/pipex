/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 17:18:11 by abmasnao          #+#    #+#             */
/*   Updated: 2025/03/01 13:47:43 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	error(void)
{
	perror(RC"Error");
	exit(EXIT_FAILURE);
}

void	free_f(char **bufs, char *buf)
{
	int	i;

	i = -1;
	if (bufs)
	{
		while (bufs[++i])
			free(bufs[i]);
		free(bufs);
	}
	if (buf)
		free(buf);
}

char	*get_path(char *cmd, char **envp)
{
	int		i;
	char	*path;
	char	*scmd;
	char	**all_paths;

	i = 0;
	while (envp[i] && ft_strncmp("PATH=", envp[i], 5) != 0)
		i++;
	if (envp[i])
		path = envp[i] + 5;
	all_paths = ft_split(path, ':');
	if (!all_paths)
		return (NULL);
	i = -1;
	scmd = ft_strjoin("/", cmd);
	while (all_paths[++i])
	{
		path = ft_strjoin(all_paths[i], scmd);
		if (0 == access(path, F_OK | X_OK))
			break ;
		(free_f(NULL, path), path = NULL);
	}
	if (!path)
		(pts("command not found: ", 2), pts(cmd, 2), pts("\n", 2));
	return (free_f(all_paths, scmd), path);
}
