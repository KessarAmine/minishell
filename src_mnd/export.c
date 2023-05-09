/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmohamed <kmohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 21:12:26 by rdoukali          #+#    #+#             */
/*   Updated: 2023/05/09 16:36:18 by kmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Headers/pipex.h"
# include "../Headers/memory.h"

//function realloc the enviroment
char	**ft_realloc_env(char **env, char *str, t_mnsh *minishell)
{
	char **new_env;
	int i;
	
	i = 0;
	while (env[i])
		i++;
	if (!(new_env = my_malloc(&minishell->memory_blocks, sizeof(char *) * (i + 2))))
		return (NULL);
	i = 0;
	while (env[i + 2])
	{
		new_env[i] = ft_strdup(env[i], minishell);
		i++;
	}
	new_env[i] = ft_strdup(str, minishell);
	new_env[i + 1] = ft_strdup(env[i], minishell);
	new_env[i + 2] = ft_strdup(env[i + 1], minishell);
	new_env[i + 3] = NULL;
	my_free(&minishell->memory_blocks, env);
	return (new_env);
}

char *ft_strdup_variable(char *str, char *end, t_mnsh *env)
{
	int i;
	int j;
	char *ret;

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
	while (str[i-1] != '=')
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	**ft_add_str_to_file(char **env, char *str, t_mnsh *minishell)
{
	int i;
	char *var;
	char **new_env;

	var = ft_strdup_variable(str, "=", minishell);
	if (!var)
		return (NULL);
	i = 0;
	while(env[i])
	{
		if(ft_strncmp(env[i], var, ft_strlen(var)) == 0)
		{
			my_free(&minishell->memory_blocks, env[i]);
			env[i] = ft_strdup(str, minishell);
			my_free(&minishell->memory_blocks, var);
			return (env);
		}
		i++;
	}
	if (ft_strchr(str, '='))
		new_env = ft_realloc_env(env, str, minishell);
	return(new_env);
}

char	**ft_export(char **env, char *str, t_mnsh *minishell)
{
	int	i;
	char	**ptr;
	char	**new;

	i = 0;
	if (str[i] >= '0' && str[i] <= '9')
	{
		ft_error(minishell, 4, str);
		return (ft_file_dup(env, minishell));
	}
	ptr = ft_split_whitespaces(str, minishell);
	new = ft_file_dup(env, minishell);
	if (ft_strchr(str, '='))
	{
		while(ptr[i])
		{
			new = ft_add_str_to_file(new, ptr[i], minishell);
			i++;
		}
	}
	return (new);
}
