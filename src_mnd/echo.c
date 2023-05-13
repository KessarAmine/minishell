/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmohamed <kmohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 18:50:59 by rdoukali          #+#    #+#             */
/*   Updated: 2023/05/12 12:02:45 by kmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/pipex.h"
#include "../Headers/memory.h"

char	*ft_quote_erase(char *str, t_mnsh *env)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (str[i] == '\"' || str[i] == '\'')
		i++;
	tmp = my_malloc(&env->memory_blocks, sizeof(char) * (ft_strlen(str) - 1));
	while (str[i] && str[i] != '\"' && str[i] != '\'')
	{
		tmp[j] = str[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	dprintf(2, "++%s++\n", tmp);
	return (tmp);
}

int	ft_check_quote(char *line, char c)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	while (line[i])
	{
		if (line[i] == c)
			r++;
		i++;
	}
	if (r % 2 != 0)
		return (1);
	return (0);
}

int	ft_quote_count(char *str)
{
	int	i;
	int	a;
	int	b;
	int	c;

	init_ft_quote_count(&i, &a, &b, &c);
	while (str[i])
	{
		if (str[i] == '\"')
			a++;
		else if (str[i] == '\'')
			b++;
		i++;
	}
	if (a % 2 != 0 || b % 2 != 0)
		return (0);
	i--;
	while (str[i] == ' ')
	{
		i--;
		c++;
	}
	return (ft_strlen(str) - (a + b - c));
}

char	*ft_quote_chk(char *str, t_mnsh *env)
{
	int		i;
	int		j;
	int		mem;
	char	*ptr;

	i = 0;
	j = 0;
	ptr = my_malloc(&env->memory_blocks, sizeof(char)
			* ft_quote_count(str) + 1);
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '\"')
		{
			ptr[j] = str[i];
			j++;
		}
		i++;
	}
	ptr[j] = '\0';
	return (ptr);
}

// old version below :
// void	ft_echo(char *line, t_mnsh	*minishell)
// {
// 	int		i;
// 	int		j;
// 	int		tmp;
// 	char	**cmd;
// 	char	*fix;

// 	i = 1;
// 	tmp = 0;
// 	// cmd = ft_split(line, ' ');
// 	cmd = ft_split_whitespaces(line, minishell);
// 	// dprintf(2, "LINE IS ECHO : %d\n", line);
// 	cmd = ft_cmds_fix(cmd, minishell);
// 	//ft_display(cmd);
// 	if (strcmp(cmd[i], "-n") == 0)
// 	{
// 		i++;
// 		tmp = 1;
// 	}
// 	while (cmd[i])
// 	{
// 		// if (!cmd[i] || ft_strcmp(cmd[i], "|") == 0)
// 		// 	break;
// 		if (strcmp(cmd[i], "$?") == 0)
// 			ft_putnbr(minishell->exit);
// 		else if (ft_strchr(cmd[i], '$'))
// 		{
// 			j = 0;
// 			fix = ft_quote_chk(&cmd[i][j], minishell);
// 			while (fix[j] != '$')
// 			{
// 				write(1, &fix[j], 1);
// 				j++;
// 			}
// 			if (fix[j] == '$' && ft_strchr(cmd[i], '\'') == 0)
// 				ft_dollar(&fix[j], minishell);
// 			else
// 				ft_putstr(&fix[j]);
// 		}
// 		else
// 			ft_putstr_noquote(cmd[i]);
// 		if (cmd[i + 1] && ft_strchr(cmd[i + 1], '|') == 0)
// 			write(1, " ", 1);
// 		i++;
// 	}
// 	if (tmp != 1)
// 		write(1, "\n", 1);
// 	minishell->exit = 0;
// 	//if (ft_strchr(line, '>'))
// 	return ;
// }
void	ft_echo(char *line, t_mnsh	*minishell)
{
	int		i;
	int		j;
	int		tmp;
	char	**cmd;
	char	*fix;

	i = 1;
	tmp = 0;
	cmd = ft_split_whitespaces(line, minishell);
	cmd = ft_cmds_fix(cmd, minishell);
	if (strcmp(cmd[i], "-n") == 0)
	{
		i++;
		tmp = 1;
	}
	loop_cmd(&i, cmd, fix, minishell);
	if (tmp != 1)
		write(1, "\n", 1);
	minishell->exit = 0;
	return ;
}
