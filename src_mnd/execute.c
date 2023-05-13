/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmohamed <kmohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 20:40:13 by rdoukali          #+#    #+#             */
/*   Updated: 2023/05/12 12:19:00 by kmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/pipex.h"
#include "../Headers/memory.h"

int	ft_setenv(char *name, char *value, t_mnsh *minishell)
{
	int	i;
	int	j;
	int	k;

	ft_setenv_helper(&i, &j, &k);
	while (minishell->env[i])
	{
		if (ft_strcmp(minishell->env[i], name) == 0)
		{
			j = i;
			k = 1;
		}
		i++;
	}
	if (k == 1)
	{
		my_free(&minishell->memory_blocks, minishell->env[j]);
		minishell->env[j] = ft_strjoin(name, value, minishell);
	}
	else
	{
		minishell->env[i] = ft_strjoin(name, value, minishell);
		minishell->env[i + 1] = NULL;
	}
	return (0);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i] && i < n)
		i++;
	if (i == n)
		return (0);
	return (s1[i] - s2[i]);
}

int	ft_search_and_edit(char **tab, char *str)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (ft_strcmp(tab[i], str) == 0)
		{
			tab[i] = NULL;
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

char	*ft_strdup(char *str, t_mnsh *env)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = my_malloc(&env->memory_blocks, sizeof(char) * ft_strlen(str));
	while (str[i])
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}
