/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmohamed <kmohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:08:08 by kmohamed          #+#    #+#             */
/*   Updated: 2023/05/12 12:13:57 by kmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/pipex.h"
#include "../Headers/memory.h"

int	env_helper(char *str, char *to_remove, char	*new)
{
	int	i;
	int	j;

	i = 0;
	j= 0;
	while (str[i])
	{
		if (ft_strcmp(&str[i], to_remove) != 0)
		{
			new[j] = str[i];
			i++;
			j++;
		}
		else
			i = i + ft_strlen(to_remove);
	}
	return (j);
}
