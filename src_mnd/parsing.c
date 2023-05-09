/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmohamed <kmohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 20:42:14 by rdoukali          #+#    #+#             */
/*   Updated: 2023/05/09 16:37:32 by kmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Headers/pipex.h"
# include "../Headers/memory.h"

int ft_count_word_len(char *str, int i)
{
	int		len;

	len = 0;

	if (str[i] == '\'' || str[i] == '\"')
	{
		i++;
		len++;
		while (str[i] != '\'' && str[i] != '\0' && str[i] != '\"')
		{
			i++;
			len++;
		}
		if (str[i] == '\'' || str[i] == '\"')
			len++;
	}
	else
	{
		while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
			i++;
		while(str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\0')
		{
			len++;
			i++;
		}
	}
	return (len);
}

int ft_count_words(char *str)
{
	int i;
	int j;
	int count;

	i = 0;
	j = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\'' || str[i] == '\"')
		{
			if (str[i] == '\'' || str[i] == '\"')
			{
				count++;
				i++;
				while (str[i] != '\'' && str[i] != '\0' && str[i] != '\"')
					i++;
			}
			else if (j > 0)
				count++;
			j = 0;
		}
		else
			j++;
		i++;
	}
	if (j > 0)
		count++;
	return (count);
}

//function that split input with space without quotes



char **ft_split_whitespaces(char *str, t_mnsh *minishell)
{
	char **tab;
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	//dprintf(2, "AARGS :: %d\n", ft_count_words(str));
	tab = my_malloc(&minishell->memory_blocks, sizeof(char *) * (ft_count_words(str) + 1));
	while (str[i] != '\0')
	{
		while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
			i++;
		if (str[i] == '\'' || str[i] == '\"')
		{
			//i++;
			//dprintf(2, "word count ' :: %d\n", ft_count_word_len(str, i));
			tab[j] = my_malloc(&minishell->memory_blocks, sizeof(char) * (ft_count_word_len(str, i) + 1));
			tab[j][k] = str[i];
			k++;
			i++;
			while (str[i] != '\0' && str[i] != '\'' && str[i] != '\"')
			{
				tab[j][k] = str[i];
				i++;
				k++;
			}
			if (str[i] == '\'')
				{
					tab[j][k] = '\'';
					k++;
				}
			if (str[i] == '\"')
				{
					tab[j][k] = '\"';
					k++;
				}
			tab[j][k] = '\0';
			k = 0;
			j++;
			i++;
		}
		else if (str[i] != '\0')
		{
			//dprintf(2, "word count :: %d\n", ft_count_word_len(str, i));
			tab[j] = my_malloc(&minishell->memory_blocks, sizeof(char) * (ft_count_word_len(str, i) + 1));
			while (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\0')
			{
				tab[j][k] = str[i];
				k++;
				i++;
			}
			tab[j][k] = '\0';
			j++;
			k = 0;
		}
	}
	tab[j] = 0;
	return (tab);
}



// int main()
// {
// 	char **tab;
// 	int i = 0;
// 	tab = ft_split_whitespaces("Hello Wor ld/ncat \"new line\" echo \"Hello World\"");
// 	while (tab[i] != 0)
// 	{
// 		printf("%s\n", tab[i]);
// 		i++;
// 	}
// 	return (0);
// }