/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmohamed <kmohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 20:55:40 by rdoukali          #+#    #+#             */
/*   Updated: 2023/05/12 12:20:33 by kmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/pipex.h"
#include "../Headers/memory.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static int	dptr_len(char *str, char c)
{
	int		i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[j])
	{
		while (str[j] && str[j] == c)
			j++;
		if (str[j] && str[j] != c)
		{
			i++;
			while (str[j] && str[j] != c)
				j++;
		}
	}
	return (i);
}

static char	*splt(char *s, char c, t_mnsh *env)
{
	size_t	i;
	char	*ps;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	ps = my_malloc(&env->memory_blocks, sizeof(char) * (i + 1));
	if (!ps)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		ps[i] = s[i];
		i++;
	}
	ps[i] = '\0';
	return (ps);
}

char	**ft_split(char const*s, char c, t_mnsh *env)
{
	size_t		i;
	char		**dptr;
	char		*str;

	if (!s)
		return (NULL);
	i = 0;
	str = (char *)s;
	dptr = my_malloc(&env->memory_blocks, sizeof(char *)
			* (dptr_len(str, c) + 1));
	if (!dptr)
		return (NULL);
	while (*str)
	{
		while (*str && (*str == c))
			str++;
		if (*str && *str != c)
		{
			dptr[i++] = splt(str, c, env);
			while (*str && *str != c)
				str++;
		}
	}
	dptr[i] = NULL;
	return (dptr);
}
