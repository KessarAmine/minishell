/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmohamed <kmohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 20:42:14 by rdoukali          #+#    #+#             */
/*   Updated: 2023/05/12 16:48:19 by kmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/pipex.h"
#include "../Headers/memory.h"

int	ft_count_word_len(char *str, int i)
{
	int		len;

	len = 0;
	if (str[i] == '\'' || str[i] == '\"')
	{
		i++;
		len++;
		while (str[i] != '\'' && str[i] != '\0' && str[i] != '\"')
		{
			i++;
			len++;
		}
		if (str[i] == '\'' || str[i] == '\"')
			len++;
	}
	else
	{
		while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
			i++;
		while (str[i] != ' ' && str[i] != '\t'
			&& str[i] != '\n' && str[i++] != '\0')
			len++;
	}
	return (len);
}

int	ft_count_words(char *str)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ' || str[i] == '\n'
			|| str[i] == '\t' || str[i] == '\'' || str[i] == '\"')
		{
			if (str[i] == '\'' || str[i] == '\"')
				ft_count_words_helper(&count, &i, str);
			else if (j > 0)
				count++;
			j = 0;
		}
		else
			j++;
		i++;
	}
	if (j > 0)
		count++;
	return (count);
}

//function that split input with space without quotes
char	**ft_split_whitespaces(char *str, t_mnsh *minishell)
{
	char		**tab;
	t_parsing	vars;

	ft_setenv_helper(&(vars.i), &(vars.j), &(vars.k));
	tab = my_malloc(&minishell->memory_blocks,
			sizeof(char *) * (ft_count_words(str) + 1));
	while (str[vars.i] != '\0')
	{
		while (str[vars.i] == ' ' || str[vars.i] == '\t' || str[vars.i] == '\n')
			(vars.i)++;
		if (str[vars.i] == '\'' || str[vars.i] == '\"')
		{
			tab[vars.j] = my_malloc(&minishell->memory_blocks,
					sizeof(char) * (ft_count_word_len(str, vars.i) + 1));
			ft_split_whitespaces_helper1(&vars, tab, str);
		}
		else if (str[vars.i] != '\0')
		{
			tab[vars.j] = my_malloc(&minishell->memory_blocks,
					sizeof(char) * (ft_count_word_len(str, vars.i) + 1));
			ft_split_whitespaces_helper2(&vars, tab, str);
		}
	}
	tab[vars.j] = 0;
	return (tab);
}
