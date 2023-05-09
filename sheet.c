#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

// void handle_pipes(char** commands, char** env) 
// {
//     int num_commands = 0;
//     while (commands[num_commands] != NULL) {
//         num_commands++;
//     }

//     int pipefd[num_commands-1][2];
//     pid_t pid;

//     // Create pipes
//     for (int i = 0; i < num_commands-1; i++) {
//         if (pipe(pipefd[i]) == -1) {
//             perror("pipe");
//             exit(EXIT_FAILURE);
//         }
//     }

//     for (int i = 0; i < num_commands; i++) {
//         pid = fork();

//         if (pid == -1) {
//             perror("fork");
//             exit(EXIT_FAILURE);
//         } else if (pid == 0) {
//             // Child process
//             if (i != 0) {
//                 // Redirect stdin to pipe
//                 dup2(pipefd[i-1][0], STDIN_FILENO);
//             }
//             if (i != num_commands-1) {
//                 // Redirect stdout to pipe
//                 dup2(pipefd[i][1], STDOUT_FILENO);
//             }

//             // Close all pipes in child process
//             for (int j = 0; j < num_commands-1; j++) {
//                 if (i != j && i != j+1) {
//                     close(pipefd[j][0]);
//                     close(pipefd[j][1]);
//                 }
//             }

//             char* command = commands[i];
//             char* argv[] = {"sh", "-c", command, NULL};
//             execve("/bin/sh", argv, env);
//             perror("execve");
//             exit(EXIT_FAILURE);
//         } else {
//             // Parent process
//             if (i != 0) {
//                 close(pipefd[i-1][0]);
//             }
//             if (i != num_commands-1) {
//                 close(pipefd[i][1]);
//             }
//         }
//     }

//     // Close all pipes in parent process
//     for (int i = 0; i < num_commands-1; i++) {
//         close(pipefd[i][0]);
//         close(pipefd[i][1]);
//     }

//     // Wait for last child process to finish
//     int status;
//     if (waitpid(pid, &status, 0) == -1) {
//         perror("waitpid");
//         exit(EXIT_FAILURE);
//     }

//     // Print error message if child process exits with non-zero status
//     if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
//         fprintf(stderr, "Child process exited with status %d\n", WEXITSTATUS(status));
//     }
// }

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static int	dptr_len(char *str, char c)
{
	int		i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[j])
	{
		while (str[j] && str[j] == c)
			j++;
		if (str[j] && str[j] != c)
		{
			i++;
			while (str[j] && str[j] != c)
				j++;
		}
	}
	return (i);
}

static char	*splt(char *s, char c)
{
	size_t	i;
	char	*ps;

	i = 0;
	while (s[i] != c && s[i] && s[i] != ' ')
		i++;
	ps = (char *)malloc(sizeof(char) * (i + 1));
	if (!ps)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c && s[i] != ' ')
	{
		ps[i] = s[i];
		i++;
	}
	ps[i] = '\0';
	return (ps);
}

char	**ft_split(char const*s, char c)
{
	size_t		i;
	char		**dptr;
	char		*str;

	if (!s)
		return (NULL);
	i = 0;
	str = (char *)s;
	dptr = malloc(sizeof(char *) * (dptr_len(str, c) + 1));
	if (!dptr)
		return (NULL);
	while (*str)
	{
		while (*str && (*str == c || *str == ' '))
			str++;
		if (*str && *str != c && *str != ' ')
		{
			dptr[i] = splt(str, c);
			i++;
			while (*str && *str != c && *str != ' ')
				str++;
		}
	}
	dptr[i] = NULL;
	return (dptr);
}

int	ft_count_str(char **str)
{
	int i= 0;

	while (*str != NULL) {
		i++;
		str++;
	}
	return i;
}





char	**ft_pipe(char *line, char **env,char **cmd, int fd2)
{
	char **prc;
	int c;
	int status;
	pid_t pid;

	prc = ft_split(line, '|');
	c = ft_count_str(prc);
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
			//ft_exe(prc[i], cmd, fd2, env);
			char* command = cmd[i];
			char* argv[] = {"sh", "-c", command, NULL};
			execve("/bin/sh", argv, env);
			// perror("execve");
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

// int main(int ac, char **av, char **env)
// {
//     char* commands[] = {"ls -l", "grep .c", "ls","grep a.     ", NULL};
//     char *line = "ls -l | grep .c | ls | grep a.";
//     int fd;
//     ft_pipe(line, env, commands, fd);
//     //handle_pipes(commands, NULL);
//     return 0;
// }

int	ft_strchr(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i] && i < n)
		i++;
	if (i == n)
		return (0);
	return (s1[i] - s2[i]);
}

int	ft_cmds_count(char **cmd)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while(cmd[i])
	{
		if (ft_strchr(cmd[i], '>') || ft_strchr(cmd[i], '<'))
		{
			if (ft_strncmp(cmd[i], ">\0", 2) == 0 || ft_strncmp(cmd[i], "<\0", 2) == 0)
				i++;
		}
		else
			k++;
		if (!cmd[i])
			break ;
		i++;
	}
	return (k);
}

char	**ft_cmds_fix(char **cmd)
{
	int	i;
	int	j;
	char	**new;

	i = 0;
	j = 0;
	new = malloc(sizeof(char *) * (ft_cmds_count(cmd) + 1));
	while(cmd[i])
	{
		if (ft_strchr(cmd[i], '>') || ft_strchr(cmd[i], '<'))
		{
			if (ft_strncmp(cmd[i], ">\0", 2) == 0 || ft_strncmp(cmd[i], "<\0", 2) == 0)
				i++;
		}
		else
			{
				new[j] = cmd[i];
				j++;
			}
		if (!cmd[i])
			break ;
		i++;
	}
	new[j] = NULL;
	return(new);
}

char	*ft_file_name(char *line)
{
	int	i;
	int	j;
	int	r;
	char	*name;

	i = 0;
	while(line[i])
	{
		if (line[i] == '<' && line[i + 1] == '<')
		{
			i += 2;
			if (line[i] == '<')
				{
					printf("syntax error near unexpected token ");
					exit(0);
				}
			while(line[i] == ' ')
				i++;
			if (line[i])
				r = i;
			j = 0;
			while(line[i] && line[i] != ' ')
				{
					j++;
					i++;
				}
			name = malloc(j + 1);
			j = 0;
			while(r < i)
			{
				name[j] = line[r];
				j++;
				r++;
			}
			name[j] = '\0';
		}
		i++;
	}
	return (name);
}

int main()
{
	// int i = 0;
	// char *cmd[] = {"echo 45", "ls", ">", "ff", "grep a","<", "gh", "7", NULL};
	// char **new = ft_cmds_fix(cmd);

	// char **tst;

	// tst = ft_split("reda    |dayr    |       Kagol", '|');

	// printf("LINE 1 : |%s|\n", tst[0]);
	// printf("LINE 2 : |%s|\n", tst[1]);
	// printf("LINE 3 : |%s|\n", tst[2]);
	// printf("LINE 4 : |%s|\n", tst[3]);
	// while(new[i])
	// 	{
	// 		printf("|%s|\n", new[i]);
	// 		i++;
	// 	}
	//printf("NUM OF CMD IS :: %d", ft_cmds_count(cmd));
	char *str = ft_file_name("<<rf s4dfds65g4ds5");
	printf("|%s|\n", str);
	return 0;
}