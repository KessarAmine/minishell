/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmohamed <kmohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 13:50:59 by rdoukali          #+#    #+#             */
/*   Updated: 2023/05/12 16:55:20 by kmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/pipex.h"
#include "../Headers/memory.h"

char	*str_extr_norm(char *str, int n, int tmp, t_mnsh *minishell)
{
	int		i;
	int		j;
	int		start;
	char	*ptr;

	ptr = my_malloc(&minishell->memory_blocks, sizeof(char) * 500);
	ft_setenv_helper(&i, &j, &start);
	while (str[i])
	{
		if (str[i] == ':')
		{
			tmp++;
			start = i + 1;
		}
		while (tmp == n && str[start] != ':' && str[start])
		{
			ptr[j] = str[start];
			start++;
			j++;
		}
		ptr[j] = '\0';
		i++;
	}
	return (ptr);
}

char	*str_extr(char *str, int n, t_mnsh *minishell)
{
	int		tmp;
	char	*ptr;

	tmp = 1;
	if (n > 6 || n <= 0)
		return (NULL);
	ptr = str_extr_norm(str, n, tmp, minishell);
	return (ptr);
}

char	*ffss_norm(char **file, int i, int j, t_mnsh *minishell)
{
	int		k;
	char	*ptr;

	ptr = my_malloc(&minishell->memory_blocks,
			sizeof(char) * ft_strlen(&file[i][j]) + 1);
	k = 0;
	while (file[i][j])
	{
		ptr[k] = file[i][j];
		j++;
		k++;
	}
	ptr[k] = '\0';
	return (ptr);
}

char	*ft_file_search_str(char **file, char *str, t_mnsh *minishell)
{
	int		i;
	int		j;
	int		k;
	char	*ptr;

	i = 0;
	k = 0;
	j = 0;
	while (file[i])
	{
		j = 0;
		k = 0;
		while (file[i][j] == str[j])
		{
			j++;
			k++;
		}
		if (k == 5)
		{
			ptr = ffss_norm(file, i, j, minishell);
			return (ptr);
		}
		i++;
	}
	return (NULL);
}

char	*ft_path(char *path, char *cmd, t_mnsh *minishell)
{
	int		i;
	char	*str;
	char	*tmp;
	char	*tmp2;

	i = 1;
	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	if (!path)
		return (NULL);
	tmp = str_extr(path, i, minishell);
	while (str_extr(path, i, minishell))
	{
		str = ft_strjoin(tmp, "/", minishell);
		str = ft_strjoin(str, cmd, minishell);
		if (access(str, F_OK | X_OK) == 0)
			return (str);
		i++;
		my_free(&minishell->memory_blocks, tmp);
		tmp = str_extr(path, i, minishell);
	}
	return (NULL);
}
