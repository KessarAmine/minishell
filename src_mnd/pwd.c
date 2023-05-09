/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmohamed <kmohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 18:52:14 by rdoukali          #+#    #+#             */
/*   Updated: 2023/05/09 15:14:38 by kmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Headers/pipex.h"
# include "../Headers/memory.h"

char	*ft_search_and_return(char **env, char *str, t_mnsh *minishell)
{
	int i;
	char *ret;
	
	i = 0;
	while(env[i])
	{
		if (ft_strncmp(env[i], str, ft_strlen(str)) == 0)
		{
			ret = ft_strdup_without_str(env[i], str, minishell);
			return (&ret[4]);
		}
		i++;
	}
	return (NULL);
}

void	ft_pwd(char **env, t_mnsh *minishell)
{
	char *pwd;

	pwd = ft_search_and_return(env, "PWD=", minishell);
	printf("%s\n", pwd);
}

void ft_env(char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}