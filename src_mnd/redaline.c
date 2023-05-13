/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redaline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmohamed <kmohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 20:15:45 by rdoukali          #+#    #+#             */
/*   Updated: 2023/05/12 17:25:27 by kmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/pipex.h"
#include "../Headers/memory.h"

char	*ft_stradd(char const *s1, char const *s2, t_mnsh *minishell)
{
	int		i;
	int		j;
	char	*p;

	i = 0;
	j = 0;
	if ((!s1 && strncmp(s2, " \0", 2) == 0 || !s1 && strncmp(s2, "\n\0", 2) == 0))
	{
		printf("am out\n");
		return (NULL);
	}
	p = my_malloc(&minishell->memory_blocks,
			sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!p)
	{
		printf("am out2\n");
		return (NULL);
	}
	ft_stradd_helper(p, s1, &i);
	while (s2[j])
		p[i++] = (char)s2[j++];
	p[i] = '\0';
	return (p);
}

char	*ft_readline(char *str, char c, t_mnsh *minishell)
{
	char	*line;
	char	*file;

	file = ft_strdup_without_str(str, "echo echo ", minishell);
	file = ft_strjoin(file, "\n", minishell);
	while (1)
	{
		line = readline("> ");
		if (ft_strchr(line, c))
		{
			if (line[0] != c && line[1] != '\0')
				file = ft_strjoin(file, line, minishell);
			return (file);
			break ;
		}
		else
			file = ft_strjoin(file, ft_strjoin(line, "\n", minishell),
					minishell);
		add_history(line);
		rl_on_new_line();
	}
	return (file);
}

void	ft_quote(char *line, char **env, char c, t_mnsh *minishell)
{
	char	**cmd;

	cmd = ft_split(line, ' ', minishell);
	cmd[1] = ft_readline(line, c, minishell);
	cmd[2] = NULL;

	ft_builtin(cmd[1], env, minishell);
	return ;
}

char	*ft_file_name(char *line, t_mnsh *minishell)
{
	int		i;
	int		j;
	int		r;
	char	*name;

	i = 0;
	while (line[i])
	{
		if (line[i] == '<' && line[i + 1] == '<')
		{
			i += 2;
			if (ft_stradd_helper3(line, &i) == 0)
				return (0);
			ft_stradd_helper2(line, &i, &j, &r);
			name = my_malloc(&minishell->memory_blocks, j + 1);
			j = 0;
			while (r < i)
				ft_stradd_helper4(name, line, &j, &r);
			name[j] = '\0';
		}
		i++;
	}
	return (name);
}

void	ft_dbl_under(char *line, t_mnsh *minishell)
{
	char	*line2;
	char	*file;

	file = ft_file_name(line, minishell);
	if (!file)
		return ;
	while (1)
	{
		line2 = readline("> ");
		if (!line2)
			break ;
		if (ft_strcmp(line2, file) == 0)
			break ;
		rl_on_new_line();
	}
}
