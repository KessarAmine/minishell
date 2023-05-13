/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmohamed <kmohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 18:12:38 by rdoukali          #+#    #+#             */
/*   Updated: 2023/05/11 14:52:27 by kmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/pipex.h"
#include "../Headers/memory.h"

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	*ft_strdup2(char *str, t_mnsh *minishell)
{
	char	*new;
	int		i;

	i = 0;
	while (str[i])
		i++;
	new = my_malloc(&minishell->memory_blocks, sizeof(char) * (i + 1));
	i = 0;
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	**token_create_cmd(t_token *token, int n, t_mnsh *minishell)
{
	int		i;
	char	**cmd;

	i = 0;
	cmd = my_malloc(&minishell->memory_blocks, sizeof(char *) * 10);
	while (token != NULL)
	{
		if (token->index == n)
		{
			cmd[i] = ft_strdup2(token->str, minishell);
			i++;
		}
		token = token->next;
	}
	cmd[i] = NULL;
	return (cmd);
}
