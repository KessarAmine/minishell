/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmohamed <kmohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 12:09:56 by rdoukali          #+#    #+#             */
/*   Updated: 2023/05/09 14:12:23 by kmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Headers/pipex.h"
# include "../Headers/memory.h"

void	ft_error(t_mnsh *mnsh, int n, char *str)
{
	if (n == 1)
	{
		ft_putstr_fd("No file or Directory", 2);
		exit(0);
	}
	else if (n == 2)
	{
		ft_putstr_fd("command not found", 2);
		exit(1);
	}
	else if (n == 3)
	{
		ft_putstr_fd("< file1 cmd1 | cmd2 > file2", 2);
		exit(0);
	}
	else if (n == 4)
	{
		ft_putstr("minishell: export: ");
		ft_putstr(str);
		ft_putstr(": not a valid identifier\n");
		mnsh->exit = 1;
		//exit(mnsh->exit);
	}
	else if (n == 5)
	{
		//ft_putstr("Failed to Find the Variable\n");
		//perror("Failed to Find the Variable\n");
		mnsh->exit = errno;
		//exit(mnsh->exit);
	}
}
