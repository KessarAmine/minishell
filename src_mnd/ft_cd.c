/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmohamed <kmohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 20:44:36 by rdoukali          #+#    #+#             */
/*   Updated: 2023/05/09 15:10:18 by kmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Headers/pipex.h"
# include "../Headers/memory.h"

char *ft_getenv(char *str, char **env, t_mnsh *minishell)
{
	int i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], str, ft_strlen(str)) == 0)
			return (ft_strdup(&env[i][ft_strlen(str)], minishell));
		i++;
	}
	return (NULL);
}

void	ft_cd(char *line, t_mnsh *minishell, char *parm, char **env)
{
	char *path;
	char *tmp;

	while (*parm == ' ')
		parm++;
	if (parm == NULL || *parm == '\0') // add check fct to avoid spaces
		path = ft_strdup(ft_getenv("HOME=", env, minishell), minishell);
	else if (ft_strncmp(parm, "-", 1) == 0)
	{
		tmp = ft_getenv("OLDPWD=", env, minishell);
		if (tmp == NULL)
			ft_putstr("cd: OLDPWD not set\n");
		else
			path = ft_strdup(tmp, minishell);
	}
	else if (ft_strncmp(parm, "~", 1) == 0)
		path = ft_strdup(ft_getenv("HOME=", env, minishell), minishell);
	else if(ft_strncmp(parm, ".\0", 2) == 0)
		path = ft_strdup(ft_getenv("PWD=", env, minishell), minishell);
	else
		path = ft_strdup(parm, minishell);
	if (chdir(path) == -1)
	{
		minishell->exit = 1;
		ft_putstr("minishell: cd: ");
		ft_putstr(path);
		ft_putstr(": No such file or directory\n");
	}
	else
	{
		tmp = ft_getenv("PWD=", env, minishell);
		ft_search_and_add(env, "OLDPWD=", tmp, minishell);
		ft_search_and_add(env, "PWD=", getcwd(NULL, 0), minishell);
		tmp = ft_getenv("PWD=", env, minishell);
	}
	my_free(&minishell->memory_blocks, path);
}

