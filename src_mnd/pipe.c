/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmohamed <kmohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 01:06:42 by rdoukali          #+#    #+#             */
/*   Updated: 2023/05/09 14:12:56 by kmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Headers/pipex.h"
# include "../Headers/memory.h"

char	**ft_pipe(char *line, char **env,char **cmd, t_mnsh *minishell)
{
	int c;
	int status;
	char	**cmds;
	char	**tab;
	pid_t pid;

	c = ft_count_str(cmd);
	int	pipefd[c-1][2];

	for (int i = 0; i < c-1; i++)
		pipe(pipefd[i]);
	for (int i = 0; i < c; i++)
	{
		pid = fork();
		if (pid == -1) 
			exit(EXIT_FAILURE);
		else if (pid == 0)
		{
			if (i != 0)
				dup2(pipefd[i-1][0], STDIN_FILENO);
			if (i != c-1)
				dup2(pipefd[i][1], STDOUT_FILENO);
			for (int j = 0; j < c-1; j++)
			{
				if (i != j && i != j+1)
				{
					close(pipefd[j][0]);
					close(pipefd[j][1]);
				}
			}
			env = ft_exe(cmd[i], env, minishell);
			exit(EXIT_FAILURE);
		}
		else
		{
			if (i != 0)
				close(pipefd[i-1][0]);
			if (i != c-1)
				close(pipefd[i][1]);
		}
	}

	for (int i = 0; i < c-1; i++)
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
	}
	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
		exit(EXIT_FAILURE);
	}
	return (env);
}