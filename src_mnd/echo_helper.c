/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmohamed <kmohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 11:43:23 by kmohamed          #+#    #+#             */
/*   Updated: 2023/05/12 12:02:26 by kmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/pipex.h"
#include "../Headers/memory.h"

void	ft_putnbr(int num)
{
	if (num < 0)
	{
		ft_putchar('-');
		num = -num;
	}
	if (num > 9)
	{
		ft_putnbr(num / 10);
	}
	ft_putchar(num % 10 + '0');
}

void	init_ft_quote_count(int *i, int *a, int *b, int *c)
{
	*i = 0;
	*a = 0;
	*b = 0;
	*c = 0;
}

void	loop_cmd(int *i, char	**cmd, char	*fix, t_mnsh	*minishell)
{
	int		j;

	while (cmd[(*i)])
	{
		if (strcmp(cmd[(*i)], "$?") == 0)
			ft_putnbr(minishell->exit);
		else if (ft_strchr(cmd[(*i)], '$'))
		{
			j = 0;
			fix = ft_quote_chk(&cmd[(*i)][j], minishell);
			while (fix[j] != '$')
				write(1, &fix[j++], 1);
			if (fix[j] == '$' && ft_strchr(cmd[(*i)], '\'') == 0)
				ft_dollar(&fix[j], minishell);
			else
				ft_putstr(&fix[j]);
		}
		else
			ft_putstr_noquote(cmd[(*i)]);
		if (cmd[(*i) + 1] && ft_strchr(cmd[(*i) + 1], '|') == 0)
			write(1, " ", 1);
		(*i)++;
	}
}

void	ft_putstr_noquote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '\"')
			write(1, &str[i], 1);
		i++;
	}
}
