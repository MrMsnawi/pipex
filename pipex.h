/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:38:39 by abmasnao          #+#    #+#             */
/*   Updated: 2025/02/28 17:19:42 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include <stdio.h>

# define RC "\033[31m"
# define YC "\033[33m"
# define ED "\033[0m"

size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char *s, char c);
void	pts(char *s, int fd);
char	*ft_encode(char *s);
char	*ft_decode(char *s);
void	error(void);
void	free_f(char **bufs, char *buf);
char	*get_path(char *cmd, char **envp);

#endif