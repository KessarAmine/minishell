/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmohamed <kmohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 21:12:26 by rdoukali          #+#    #+#             */
/*   Updated: 2023/05/12 11:24:36 by kmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/pipex.h"
#include "../Headers/memory.h"

//function realloc the enviroment
char	**ft_realloc_env(char *str, t_mnsh *minishell)
{
	char	**new_env;
	int		i;

	i = 0;
	while (minishell->env[i])
		i++;
	new_env = my_malloc(&minishell->memory_blocks, sizeof(char *) * (i + 2));
	if (!new_env)
		return (NULL);
	i = 0;
	while (minishell->env[i + 2])
	{
		new_env[i] = ft_strdup(minishell->env[i], minishell);
		i++;
	}
	new_env[i] = ft_strdup(str, minishell);
	new_env[i + 1] = ft_strdup(minishell->env[i], minishell);
	new_env[i + 2] = ft_strdup(minishell->env[i + 1], minishell);
	new_env[i + 3] = NULL;
	my_free(&minishell->memory_blocks, minishell->env);
	return (new_env);
}

char	*ft_strdup_variable(char *str, char *end, t_mnsh *env)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	while (str[i] != '=')
		i++;
	i++;
	while (str[i] != end[j])
	{
		i++;
		j++;
	}
	ret = my_malloc(&env->memory_blocks, sizeof(char) * (i - j));
	i = 0;
	j = 0;
	while (str[i - 1] != '=')
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	**ft_add_str_to_file(char *str, t_mnsh *minishell)
{
	int		i;
	char	*var;
	char	**new_env;

	var = ft_strdup_variable(str, "=", minishell);
	if (!var)
		return (NULL);
	i = 0;
	while (minishell->env[i])
	{
		if (ft_strncmp(minishell->env[i], var, ft_strlen(var)) == 0)
		{
			my_free(&minishell->memory_blocks, minishell->env[i]);
			minishell->env[i] = ft_strdup(str, minishell);
			my_free(&minishell->memory_blocks, var);
			return (minishell->env);
		}
		i++;
	}
	if (ft_strchr(str, '='))
		new_env = ft_realloc_env(str, minishell);
	return (new_env);
}

char	**ft_export(char *str, t_mnsh *minishell)
{
	int		i;
	char	**ptr;

	i = 0;
	if (str[i] >= '0' && str[i] <= '9')
	{
		ft_error(minishell, 4, str);
		return (ft_file_dup(minishell->env, minishell));
	}
	ptr = ft_split_whitespaces(str, minishell);
	minishell->env = ft_file_dup(minishell->env, minishell);
	if (ft_strchr(str, '='))
	{
		while (ptr[i])
		{
			minishell->env = ft_add_str_to_file(ptr[i], minishell);
			i++;
		}
	}
	return (minishell->env);
}
