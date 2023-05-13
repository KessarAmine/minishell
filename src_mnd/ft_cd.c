/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmohamed <kmohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 20:44:36 by rdoukali          #+#    #+#             */
/*   Updated: 2023/05/12 11:30:21 by kmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/pipex.h"
#include "../Headers/memory.h"

char	*ft_getenv(char *str, t_mnsh *minishell)
{
	int	i;

	i = 0;
	while (minishell->env[i])
	{
		if (ft_strncmp(minishell->env[i], str, ft_strlen(str)) == 0)
			return (ft_strdup(&minishell->env[i][ft_strlen(str)], minishell));
		i++;
	}
	return (NULL);
}

//More than 25 lines
void	ft_cd(char *line, t_mnsh *minishell, char *parm)
{
	char	*path;
	char	*tmp;

	while (*parm == ' ')
		parm++;
	// add check fct to avoid spaces
	if (parm == NULL || *parm == '\0')
		path = ft_strdup(ft_getenv("HOME=", minishell), minishell);
	else if (ft_strncmp(parm, "-", 1) == 0)
	{
		tmp = ft_getenv("OLDPWD=", minishell);
		if (tmp == NULL)
			ft_putstr("cd: OLDPWD not set\n");
		else
			path = ft_strdup(tmp, minishell);
	}
	else if (ft_strncmp(parm, "~", 1) == 0)
		path = ft_strdup(ft_getenv("HOME=", minishell), minishell);
	else if (ft_strncmp(parm, ".\0", 2) == 0)
		path = ft_strdup(ft_getenv("PWD=", minishell), minishell);
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
		tmp = ft_getenv("PWD=", minishell);
		ft_search_and_add("OLDPWD=", tmp, minishell);
		ft_search_and_add("PWD=", getcwd(NULL, 0), minishell);
		tmp = ft_getenv("PWD=", minishell);
	}
	my_free(&minishell->memory_blocks, path);
}
