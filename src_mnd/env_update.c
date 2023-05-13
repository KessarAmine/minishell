/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmohamed <kmohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 15:24:59 by rdoukali          #+#    #+#             */
/*   Updated: 2023/05/12 12:14:08 by kmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/pipex.h"
#include "../Headers/memory.h"

//More than 25 lines
// old version :
// char	*ft_strdup_without_str(char *str, char *to_remove, t_mnsh *env)
// {
// 	char	*new;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	while (str[i])
// 	{
// 		if (ft_strcmp(&str[i], to_remove) != 0)
// 			i++;
// 		else
// 		{
// 			i = i + ft_strlen(to_remove);
// 			j++;
// 		}
// 	}
// 	new = my_malloc(&env->memory_blocks, sizeof(char) * (i - j + 1));
// 	i = 0;
// 	j = 0;
// 	while (str[i])
// 	{
// 		if (ft_strcmp(&str[i], to_remove) != 0)
// 		{
// 			new[j] = str[i];
// 			i++;
// 			j++;
// 		}
// 		else
// 			i = i + ft_strlen(to_remove);
// 	}
// 	new[j] = '\0';
// 	return (new);
// }
char	*ft_strdup_without_str(char *str, char *to_remove, t_mnsh *env)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (ft_strcmp(&str[i], to_remove) != 0)
			i++;
		else
		{
			i = i + ft_strlen(to_remove);
			j++;
		}
	}
	new = my_malloc(&env->memory_blocks, sizeof(char) * (i - j + 1));
	j = env_helper(str, to_remove, new);
	new[j] = '\0';
	return (new);
}

//function that sreach and add in file
void	ft_search_and_add(char *find, char *cpy, t_mnsh *minishell)
{
	int	i;

	i = 0;
	while (minishell->env[i])
	{
		if (ft_strncmp(minishell->env[i], find, ft_strlen(find)) == 0)
		{
			minishell->env[i] = ft_strjoin(find, cpy, minishell);
			return ;
		}
		i++;
	}
}
