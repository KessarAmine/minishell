/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmohamed <kmohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 13:49:14 by rdoukali          #+#    #+#             */
/*   Updated: 2023/05/12 12:43:19 by kmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/pipex.h"
#include "../Headers/memory.h"

int	ft_count(char *line, char find)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (line[i])
	{
		if (line[i] == find)
		{
			i++;
			k++;
		}
		i++;
	}
	return (k);
}

char *ft_word_after_sign(char *str, char sign, int dbl, t_mnsh *minishell)
{
	int		i;
	int		start;
	char	*ptr;

	i = 0;
	while (str[i] != sign && str[i] != '\0')
		i++;
	if (str[i] == '\0')
		return (NULL);
	if (str[i] == sign)
	{
		i++;
		if (dbl == 2 & str[i] == sign)
			i++;
	}
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	while (str[i] == '/' && str[i + 1] == 'd')
		i += 12;
	if (str[i] == '\0')
		return (NULL);
	start = i;
	while (str[i] != '\0' && str[i] != ' ' && str[i] != '\t')
		i++;
	ptr = my_malloc(&minishell->memory_blocks, sizeof(char) * (i - start + 1));
	i = 0;
	while (str[start] != '\0' && str[start] != ' ' && str[start] != '\t')
	{
		ptr[i] = str[start];
		start++;
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char *ft2_word_after_sign(char *str, char sign, int dbl, int index, t_mnsh *minishell)
{
	int		i;
	int		k;
	int		start;
	char	*ptr;

	i = 0;
	k = 1;
	while (str[i] != sign && str[i] != '\0')
		i++;
	if (str[i] == '\0')
		return (NULL);
	while (str[i] == sign && k != index)
	{
		i++;
		if (dbl == 2 & str[i] == sign)
			i++;
		while (str[i] != sign && str[i] != '\0')
			i++;
		if (str[i] == sign)
				k++;
	}
	if (str[i] == sign)
	{
		i++;
		if (dbl == 2 & str[i] == sign)
			i++;
	}
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (strncmp(&str[i], "/dev/null", 10) == 0)
		return (NULL);
	start = i;
	while (str[i] != '\0' && str[i] != ' ' && str[i] != '\t')
		i++;
	ptr = my_malloc(&minishell->memory_blocks, sizeof(char) * (i - start + 1));
	i = 0;
	while (str[start] != '\0' && str[start] != ' ' && str[start] != '\t')
	{
		ptr[i] = str[start];
		start++;
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

// void	ft_under(char *file)
// {
// 	//int	id;
// 	char fdin;
// 	char	tmp[256];

// 	// id = fork();
// 	// if (!id)
// 	// {
// 		fdin = openfile(file, 0);
// 		if (fdin == -1)
// 		{
// 			write(2, "minishell: no such file or directory: ", 35);
// 			write(2, file, ft_strlen(file));
// 			write(2, "\n", 1);
// 			return ;
// 		}
// 		read(fdin, &tmp, sizeof(tmp));
// 	// }
// 	// else
// 	// {
// 	// 	wait(NULL);
// 	// 	close(fdin);
// 	// }
// 	close(fdin);
// 	printf("%s", tmp);
// }
int	ft_2count(char *line, char find)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (line[i])
	{
		if (line[i] == find && line[i + 1] == find)
		{
			i++;
			k++;
		}
		i++;
	}
	return (k);
}

int	ft_str2strchr(char *str, char *find)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i + j] == find[j])
		{
			if (find[j + 1] == '\0')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
