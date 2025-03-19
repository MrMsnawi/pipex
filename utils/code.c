/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:19:51 by abmasnao          #+#    #+#             */
/*   Updated: 2025/02/28 17:35:27 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*ft_encode(char *s)
{
	char	open_quote;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	open_quote = -1;
	while (s[i])
	{
		if (s[i] == ' ' && open_quote == 1)
			s[i] = 3;
		if (s[i] == '\'')
			open_quote *= -1;
		i++;
	}
	return (s);
}

char	*ft_decode(char *s)
{
	char	open_quote;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	open_quote = -1;
	while (s[i])
	{
		if (s[i] == 3 && open_quote == 1)
			s[i] = ' ';
		if (s[i] == '\'')
			open_quote *= -1;
		i++;
	}
	return (s);
}
