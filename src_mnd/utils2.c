/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmohamed <kmohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 00:34:47 by rdoukali          #+#    #+#             */
/*   Updated: 2023/05/09 15:16:21 by kmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Headers/pipex.h"
# include "../Headers/memory.h"

int	ft_cmds_count(char **cmd)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while(cmd[i])
	{
		if (ft_strchr(cmd[i], '>') || ft_strchr(cmd[i], '<'))
		{
			if (ft_strncmp(cmd[i], ">\0", 2) == 0 || ft_strncmp(cmd[i], "<\0", 2) == 0)
				i++;
		}
		else
			k++;
		if (!cmd[i])
			break ;
		i++;
	}
	return (k);
}

char	**ft_cmds_fix(char **cmd, t_mnsh *minishell)
{
	int	i;
	int	j;
	char	**new;

	i = 0;
	j = 0;
	new = my_malloc(&minishell->memory_blocks, sizeof(char *) * (ft_cmds_count(cmd) + 1));
	while(cmd[i])
	{
		if (ft_strchr_pipe(cmd[i], '>') || ft_strchr_pipe(cmd[i], '<'))
		{
			if (ft_strncmp(cmd[i], ">\0", 2) == 0 || ft_strncmp(cmd[i], "<\0", 2) == 0 || ft_strncmp(cmd[i], ">>\0", 3) == 0 || ft_strncmp(cmd[i], "<<\0", 3) == 0)
				i++;
		}
		else
		{
			new[j] = cmd[i];
			j++;
		}
		if (!cmd[i])
			break ;
		i++;
	}
	new[j] = NULL;
	return(new);
}