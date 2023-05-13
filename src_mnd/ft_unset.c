/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmohamed <kmohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 21:47:59 by rdoukali          #+#    #+#             */
/*   Updated: 2023/05/12 11:40:05 by kmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/pipex.h"
#include "../Headers/memory.h"

//note: when i tried to remove the char **env when i have the t_mnsh *minishell 
//in both unset and unset_env i got a segsev so i left it like that
// below code is comment from ft_unset_env
// if (ft_strncmp(env[i], str, ft_strlen(str)) == 0)
// {
// 	i++;
// 	// while (env[i])
// 	// {
// 	// 	env[i] = env[i + 1];
// 	// 	i++;
// 	// }
// 	// env[i] = NULL;
// 	// return (env);
// }

int	ft_check_env(char **env, char *str)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], str, ft_strlen(str)) == 0)
			return (1);
		i++;
	}
	return (0);
}

//More than 25 lines
char	**ft_unset_env(char **env, char *str, t_mnsh *minishell)
{
	int		i;
	int		j;
	char	**new;

	i = 0;
	j = 0;
	str = ft_strjoin(str, "=", minishell);
	new = my_malloc(&minishell->memory_blocks, sizeof(char *)
			* (ft_count_str(env)));
	while (env[i])
	{
		if (ft_strncmp(env[i], str, ft_strlen(str)) == 0)
			i++;
		new[j] = ft_strdup(env[i], minishell);
		j++;
		i++;
	}
	my_free(&minishell->memory_blocks, env);
	return (new);
}

char	**ft_unset(char **env, char *str, t_mnsh *minishell)
{
	int		i;
	char	**ptr;
	char	**new;

	i = 0;
	ptr = ft_split_whitespaces(str, minishell);
	new = ft_file_dup(env, minishell);
	while (ptr[i])
	{
		new = ft_unset_env(new, ptr[i], minishell);
		i++;
	}
	return (new);
}
