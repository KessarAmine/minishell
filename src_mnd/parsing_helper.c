/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmohamed <kmohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:29:24 by kmohamed          #+#    #+#             */
/*   Updated: 2023/05/12 16:48:04 by kmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/pipex.h"
#include "../Headers/memory.h"

void	ft_count_words_helper(int *count, int *i, char *str)
{
	(*count)++;
	(*i)++;
	while (str[(*i)] != '\'' && str[(*i)] != '\0' && str[(*i)] != '\"')
		(*i)++;
}

void	ft_split_whitespaces_helper1(t_parsing *vars, char	**tab, char *str)
{
	tab[(*vars).j][(*vars).k] = str[(*vars).i];
	(*vars).k++;
	(*vars).i++;
	while (str[(*vars).i] != '\0'
		&& str[(*vars).i] != '\'' && str[(*vars).i] != '\"')
	{
		tab[(*vars).j][(*vars).k] = str[(*vars).i];
		(*vars).i++;
		(*vars).k++;
	}
	if (str[(*vars).i] == '\'')
	{
		tab[(*vars).j][(*vars).k] = '\'';
		(*vars).k++;
	}
	if (str[(*vars).i] == '\"')
	{
		tab[(*vars).j][(*vars).k] = '\"';
		(*vars).k++;
	}
	tab[(*vars).j][(*vars).k] = '\0';
	(*vars).k = 0;
	(*vars).j++;
	(*vars).i++;
}

void	ft_split_whitespaces_helper2(t_parsing *vars, char	**tab, char *str)
{
	while (str[(*vars).i] != ' ' && str[(*vars).i] != '\t'
		&& str[(*vars).i] != '\n' && str[(*vars).i] != '\0')
	{
		tab[(*vars).j][(*vars).k] = str[(*vars).i];
		(*vars).k++;
		(*vars).i++;
	}
	tab[(*vars).j][(*vars).k] = '\0';
	(*vars).j++;
	(*vars).k = 0;
}
