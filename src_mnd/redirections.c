/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmohamed <kmohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 01:08:21 by rdoukali          #+#    #+#             */
/*   Updated: 2023/05/09 15:21:33 by kmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Headers/pipex.h"
# include "../Headers/memory.h"

void	ft_greather(char *file, int fdout)
{
	fdout = openfile(file, 1);
	dup2(fdout, STDOUT_FILENO);
	//close(fdout);
	return ;
}

void	ft_double_greater(char *file, int fdout)
{
	int	id;
	char	tmp[256];

	fdout = openfile(file, 2);
	// if (fdout == -1)
	// {
	// 	write(2, "minishell: no such file or directory: ", 35);
	// 	write(2, file, ft_strlen(file));
	// 	write(2, "\n", 1);
	// 	return ;
	// }
	if (!file)
		return ;
	dup2(fdout, STDOUT_FILENO);
	close(fdout);
	return ;
}


void	ft_grt_loop(char *line, t_mnsh *minishell)
{
	int	fd;
	int	i;
	int	nb;

	i = 1;
	nb = ft_count(line, '>');
	while(i <= nb)
	{
		ft_greather(ft2_word_after_sign(line, '>', 0, i, minishell), fd);
		i++;
	}
	return ;
}

void	ft_dblgrt_loop(char *line, t_mnsh *minishell)
{
	int	fd;
	int	i;
	int	nb;

	i = 1;
	nb = ft_2count(line, '>');
	while(i <= nb)
	{
		ft_double_greater(ft2_word_after_sign(line, '>', 2, i, minishell), fd);
		i++;
	}
	return ;
}

void	ft_under(char *file)
{
	char fdin;
	char	tmp[256];

	fdin = openfile(file, 0);
	if (fdin == -1)
	{
		write(2, "minishell: no such file or directory: ", 35);
		write(2, file, ft_strlen(file));
		write(2, "\n", 1);
		return ;
	}
	read(fdin, &tmp, sizeof(tmp));
	close(fdin);
	printf("%s", tmp);
}

char	**ft_exec_redir(char *line, char **env, t_mnsh *minishell)
{
	int	id;
	int	fd;
	int count = 0;

	if ((line[0] == '<' && line[1] != '<' ) || line[0] == '>')
		return(0);
	if(ft_str2strchr(line, "<<"))
	{
		ft_dbl_under(line, minishell);
		return (env);
	}
	id = fork();
	if (id == 0)
	{
		if(ft_str2chr(line, '<') && !ft_str2strchr(line, "<<"))
				ft_under(ft_word_after_sign(line, '<', 0, minishell));
		else if(ft_str2chr(line, '>'))
			{
				ft_grt_loop(line, minishell);
				env = ft_builtin(line, env, minishell);
			}
		else if(ft_str2strchr(line, ">>"))
			{
				ft_dblgrt_loop(line, minishell);
				env = ft_builtin(line, env, minishell);
			}
		exit(0);
	}
	else
		wait(NULL);
	return(env);
}