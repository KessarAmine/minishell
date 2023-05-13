/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmohamed <kmohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:02:23 by kmohamed          #+#    #+#             */
/*   Updated: 2023/05/12 17:24:49 by kmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/pipex.h"
#include "../Headers/memory.h"

void	ft_stradd_helper(char *p, char const *s1, int *i)
{
	while (s1[(*i)])
	{
		p[(*i)] = (char)s1[(*i)];
		(*i)++;
	}
	if ((*i) != 0)
		p[(*i)++] = ' ';
}

void	ft_file_name_helper1(int *i, char *line)
{
	if (line[(*i) + 1] == '<')
	{
		ft_putstr("syntax error near unexpected token '");
		(*i)++;
		while (line[(*i)++] == '<')
			write(1, "<", 1);
		ft_putstr("'\n");	
	}
}

void	ft_stradd_helper2(char *line, int *i, int *j, int *r)
{
	while (line[(*i)] == ' ')
		(*i)++;
	if (line[(*i)])
		(*r) = (*i);
	(*j) = 0;
	while (line[(*i)] && line[(*i)] != ' ')
	{
		(*j)++;
		(*i)++;
	}
}

int	ft_stradd_helper3(char *line, int *i)
{
	if (line[(*i)] == '<')
	{
		ft_file_name_helper1(i, line);
		return (0);
	}
	return (1);
}

void	ft_stradd_helper4(char *name, char *line, int *j, int *r)
{
	name[(*j)] = line[(*r)];
	(*j)++;
	(*r)++;
}
