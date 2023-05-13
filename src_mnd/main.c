/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmohamed <kmohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 20:42:38 by rdoukali          #+#    #+#             */
/*   Updated: 2023/05/12 11:37:11 by kmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/pipex.h"
#include "../Headers/memory.h"

//Too many functions in file

char	**ft_file_dup(char **file, t_mnsh *minishell)
{
	char	**new;
	int		i;

	i = 0;
	while (file[i])
		i++;
	new = my_malloc(&minishell->memory_blocks, sizeof(char *) * (i + 1));
	i = 0;
	while (file[i])
	{
		new[i] = ft_strdup(file[i], minishell);
		i++;
	}
	new[i] = NULL;
	return (new);
}

void	kill_fork(int id)
{
	write(2, "\033[32mExit", 10);
	kill(id, SIGINT);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0')
			return (0);
		i++;
	}
	return (s1[i] - s2[i]);
}

int	exit_cmp(char *str)
{
	if (ft_strcmp(str, "exit") == 0)
		return (1);
	return (0);
}

//function search string in string
int	ft_strchr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

//More than 25 lines
int	ft_strchr_pipe(char *str, char c)
{
	int	i;

	i = 0;
	// dprintf(2, "LINE IS : %s\n", str);
	while (str[i])
	{
		// while (ft_strchr(str, '\''))
		// 	str++;
		// while (str[i] != '\'' || str[i] != '\"')
		// 	i++;
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			// dprintf(2, "STR[%d] IS : %c\n", i, str[i]);
		}
		else if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
				i++;
			// dprintf(2, "STR[%d] IS : %c\n", i, str[i]);
		}
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

//More than 25 lines
t_token	*ft_lexing(char **file, char **env, t_mnsh *minishell)
{
	t_token	*token;
	t_token	*head;
	int		i;
	int		r;
	int		tmp;
	char	*path2;

	i = 0;
	r = 0;
	tmp = 0;
	token = my_malloc(&minishell->memory_blocks, sizeof(t_token));
	head = token;
	token->index = 0;

	while (file[i])
	{
		while (file[i])
		{
			path2 = ft_path(ft_file_search_str(env, "PATH=", minishell),
					file[i], minishell);
			if (path2 != NULL)
			{
				if (tmp == 1)
					r++;
				token->str = my_malloc(&minishell->memory_blocks,
						sizeof(char) * 100);
				token->str = file[i];
				token->type = 0;
				token->index = r;
				if (file[i + 1])
				{
					token->next = my_malloc(&minishell->memory_blocks,
							sizeof(t_token));
					token = token->next;
				}
				tmp = 1;
			}
			else if (strcmp(file[i], "|") != 0 && strcmp(file[i], " |") != 0
				&& strcmp(file[i], "| ") != 0)
			{
				token->str = my_malloc(&minishell->memory_blocks,
						sizeof(char) * 100);
				token->str = file[i];
				token->type = 1;
				token->index = r;
				if (file[i + 1])
				{
					token->next = my_malloc(&minishell->memory_blocks,
							sizeof(t_token));
					token = token->next;
				}
			}
			i++;
			path2 = NULL;
			my_free(&minishell->memory_blocks, path2);
		}
	}
	token->next = NULL;
	return (head);
}

void	sin_int_handler(int sig_num)
{
	exit(0);
}

void	sin_term_handler(int sig_num)
{
	exit(0);
}

void	ft_display(char **str)
{
	while (*str)
		dprintf(2, "[%s]\n", *str++);
	dprintf(2, "[%s]\n", *str);
	dprintf(2, "--------------\n");
}

//Too Many variables in function
//More than 25 lines
char	**ft_builtin(char *line, char **env, t_mnsh *minishell)
{
	int		id;
	char	*path;
	char	**cmds;
	char	**tab;
	t_token	*token;
	char	**new;
	int		status;

	tab = ft_split_whitespaces(line, minishell);
	//ft_display(tab);
	token = ft_lexing(tab, env, minishell);
	cmds = token_create_cmd(token, 0, minishell);
	path = ft_path(ft_file_search_str(env, "PATH=", minishell),
			ft_space_erase(cmds[0], minishell), minishell);
	//dprintf(2, "%s\n", path);
	// if(exit_cmp(line))
	// 	exit(0);
	if (ft_strncmp(line, "cd ", 3) == 0
		|| ft_strncmp(line, "/usr/bin/cd ", 12) == 0)
		ft_cd(line, minishell, &line[3]);
	else if (ft_strncmp(line, "cd\0", 3) == 0
		|| ft_strncmp(line, "/usr/bin/cd\0", 12) == 0)
		ft_cd(line, minishell, NULL);
	else if (ft_strncmp(line, "echo ", 5) == 0
		|| ft_strncmp(line, "/bin/echo ", 10) == 0)
		ft_echo(line, minishell);
	else if (ft_strncmp(line, "pwd", 3) == 0
		|| ft_strncmp(line, "/bin/pwd ", 9) == 0)
		ft_pwd(env, minishell);
	else if (ft_strncmp(line, "env", 3) == 0
		|| ft_strncmp(line, "/usr/bin/env ", 13) == 0)
		ft_env(env);
	else if (ft_strncmp(line, "export", 6) == 0)
		env = ft_export(&line[7], minishell);
	else if (ft_strncmp(line, "unset", 5) == 0)
		env = ft_unset(ft_file_dup(env, minishell), &line[6], minishell);
	else
	{
		new = ft_cmds_fix(tab, minishell);
		if (access(path, F_OK | X_OK))
		{
			ft_putstr("minishell: ");
			ft_putstr(new[0]);
			ft_putstr(": command not found\n");
			minishell->exit = 127;
		}
		else
		{
			//ft_display(new);
			// char *new2[] = {"ls", "-la", NULL};
			id = fork();
			if (id == 0)
			{
				if (execve(path, new, ft_file_dup(env, minishell)) == -1)
				{
					//dprintf(2, "errno is :: %d\n", errno);
					//perror("minishell : %s : command not found");
					ft_putstr("minishell: ");
					ft_putstr(new[0]);
					ft_putstr(": command not found\n");
					minishell->exit = 127;
				}
				else
					minishell->exit = 1;
			}
			else
			{
				if (waitpid(id, &status, 0) == -1)
				{
					perror("waitpid");
					exit(EXIT_FAILURE);
				}
			}
		}
	}
	//free(line);
	//free(cmd);
	return (env);
}

//More than 25 lines
char	*ft_space_erase(char *str, t_mnsh *minishell)
{
	int		i;
	int		j;
	char	*ptr;

	i = 0;
	j = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
	while (str[i] != ' ' && str[i] != '\t' && str[i])
	{
		i++;
		j++;
	}
	ptr = my_malloc(&minishell->memory_blocks, sizeof(char) * j + 1);
	j = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	while (str[i] && str[i] != ' ' && str[i] != '\t')
	{
		ptr[j] = str[i];
		i++;
		j++;
	}
	ptr[j] = '\0';
	return (ptr);
}

char	*ft_space_erase2(char *str, t_mnsh *minishell)
{
	int		i;
	int		j;
	int		k;
	char	*ptr;

	i = 0;
	j = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	while (str[j])
		j++;
	j--;
	while (str[j] == ' ')
		j--;
	ptr = my_malloc(&minishell->memory_blocks, sizeof(char) * (j - i) + 1);
	k = 0;
	while (i <= j)
	{
		ptr[k] = str[i];
		i++;
		k++;
	}
	ptr[k] = '\0';
	return (ptr);
}

char	**ft_exe(char *line, char **env, t_mnsh *minishell)
{
	line = ft_space_erase2(line, minishell);
	if (ft_strchr(line, '>') || ft_strchr(line, '<'))
		env = ft_exec_redir(line, env, minishell);
	else
		env = ft_builtin(line, env, minishell);
	return (env);
}

int	ft_count_str(char **str)
{
	int	i;

	i = 0;
	while (*str != NULL)
	{
		i++;
		str++;
	}
	return (i);
}

void	signal_handler(int signo)
{
	struct termios	t;

	tcgetattr(STDIN_FILENO, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signo == SIGQUIT)
		return ;
}

//More than 25 lines
//Too many variables
int	main(int ac, char **av, char **envp)
{
	char		*line;
	static int	a;
	char		*path;
	int			i;
	int			id;
	t_token		*token;
	char		**all;
	t_mnsh		minishell;

	a = 0;
	i = 0;
	minishell.exit = 0;
	minishell.memory_blocks = NULL;
	if (a == 0)
		minishell.env = ft_file_dup(envp, &minishell);
	a = 1;
	while (1)
	{
		//wrong scope
		struct sigaction	ctrl_c;
		sigemptyset(&ctrl_c.sa_mask);
		ctrl_c.sa_handler = signal_handler;
		ctrl_c.sa_flags = SA_RESTART;
		sigaction(SIGINT, &ctrl_c, NULL);
		signal(SIGINT, signal_handler);
		sigaction(SIGQUIT, &ctrl_c, NULL);
		signal(SIGQUIT, signal_handler);
		signal(SIGTERM, SIG_IGN);
		line = readline("ᴍɪɴɪꜱʜᴇʟʟ -> ");
				// TODO:
				
				// if (strcmp(line, "$?") == 0) 
				// 	write(1, "0\n", 2);		

				// heredoc : 
				// << :
				// 	handle the signal ctrl+c right make it stop like in bash 
				// ' and " :
				// 	ctl+D does sigsev add this candition if (!line2) break;	

				// check struct intilization
		if (!line)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			write(1, "exit\n", 5);
			break;
		}
		if (line[0] == 0)
			continue;
		if (ft_strcmp(line, "exit") == 0)
			break ;
		else if (ft_check_quote(line, '\''))
			ft_quote(line, minishell.env, '\'', &minishell);
		else if(ft_check_quote(line, '\"'))
			ft_quote(line, minishell.env, '\"', &minishell);
		else if(ft_strchr_pipe(line, '|'))
		{
			all = ft_split(line, '|', &minishell);
			minishell.env = ft_pipe(line, minishell.env, all, &minishell);
		}
		else
		{
			if(ft_strchr_pipe(line, '>') || ft_strchr_pipe(line, '<'))
				ft_exec_redir(line, minishell.env, &minishell);
			else
				minishell.env = ft_builtin(line, minishell.env, &minishell);
		}
		add_history(line);
		rl_on_new_line();
	}
	free_path(minishell.env, &minishell);
	free_all_mem(&minishell.memory_blocks);
	return (minishell.exit);
}

char *ft_last_word(char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '/')
			j = i + 1;
		i++;
	}
	return (&str[j]);
}
