/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:36:11 by abmasnao          #+#    #+#             */
/*   Updated: 2025/03/11 23:28:47 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute(char *av, char **envp)
{
	char	*path;
	char	**cmd;

	if (av[0] == ' ' || av[ft_strlen(av) - 1] == ' ')
		(pts("command not found: ", 2), pts(av, 2), pts("\n", 2),
			exit(EXIT_FAILURE));
	cmd = ft_split(av, ' ');
	if (!cmd)
		exit(EXIT_FAILURE);
	if (-1 == access(cmd[0], F_OK | X_OK))
	{
		if (ft_strncmp(cmd[0], "./", 2) == 0)
			(pts("no such file or derectory: ", 2), pts(cmd[0], 2),
				pts("\n", 2), free_f(cmd, NULL), exit(EXIT_FAILURE));
		path = get_path(cmd[0], envp);
		if (!path)
			(free_f(cmd, NULL), exit(EXIT_FAILURE));
	}
	else
		path = cmd[0];
	if (execve(path, cmd, NULL) == -1)
		(free_f(cmd, NULL), error());
}

void	child_process_1(char **av, char **envp, int pipe_fd[])
{
	int	in_fd;

	close(pipe_fd[0]);
	in_fd = open(av[1], O_RDONLY);
	if (in_fd == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		error();
	}
	dup2(pipe_fd[1], STDOUT_FILENO);
	dup2(in_fd, STDIN_FILENO);
	close(in_fd);
	close(pipe_fd[1]);
	execute(av[2], envp);
}

void	child_process_2(char **av, char **envp, int pipe_fd[])
{
	int	out_fd;

	close(pipe_fd[1]);
	out_fd = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (out_fd == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		error();
	}
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	dup2(out_fd, STDOUT_FILENO);
	close(out_fd);
	execute(av[3], envp);
}

int	main(int ac, char **av, char **envp)
{
	int		pipe_fd[2];
	pid_t	cpid;
	pid_t	cpid2;

	if (ac == 5)
	{
		if (pipe(pipe_fd) == -1)
			error();
		cpid = fork();
		cpid2 = fork();
		if (cpid == -1 || cpid2 == -1)
			(close(pipe_fd[0]), close(pipe_fd[1]), error());
		if (cpid == 0)
			child_process_1(av, envp, pipe_fd);
		if (cpid2 == 0)
			child_process_2(av, envp, pipe_fd);
		(close(pipe_fd[0]), close(pipe_fd[1]));
		(wait(NULL), wait(NULL));
	}
	else
	{
		pts(RC"Error: bad arguments!\n"ED, 2);
		pts(YC"Ex: ./pipex <infile> <cmd1> <cmd2> <outfile>\n"ED, 2);
	}
}
