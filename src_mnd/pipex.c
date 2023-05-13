/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmohamed <kmohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 16:58:48 by rdoukali          #+#    #+#             */
/*   Updated: 2023/05/12 12:31:11 by kmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/pipex.h"
#include "../Headers/memory.h"

int	openfile(char *file, int perm)
{
	int	res;

	if (perm == 0)
	{
		res = open(file, O_RDONLY, 0777);
		if (access(file, F_OK | R_OK) != 0)
			ft_error(NULL, 1, NULL);
	}
	if (perm == 1)
		res = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (perm == 2)
		res = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (res == -1)
		exit(0);
	return (res);
}

// void	child_proc(int fd[2], char **argv, char **env)
// {
// 	char	*path;
// 	char	**cmds1;

// 	cmds1 = ft_split(argv[2], ' ');
// 	close(fd[0]);
// 	dup2(fd[1], 1);
// 	path = ft_path(ft_file_search_str(env, "PATH="), cmds1[0]);
// 	if (path == NULL)
// 		ft_error(2);
// 	if (execve(path, cmds1, env) == -1)
// 		ft_error(2);
// 	close(fd[1]);
// 	free_path(cmds1);
// 	free(path);
// }

// void	main_proc(int fd[2], int argc, char **argv, char **env)
// {
// 	int		fdout;
// 	char	*path2;
// 	char	**cmds2;

// 	fdout = openfile(argv[argc - 1], 1);
// 	cmds2 = ft_split(argv[3], ' ');
// 	dup2(fdout, STDOUT_FILENO);
// 	close(fd[1]);
// 	dup2(fd[0], 0);
// 	path2 = ft_path(ft_file_search_str(env, "PATH="), cmds2[0]);
// 	if (path2 == NULL)
// 		ft_error(2);
// 	if (execve(path2, cmds2, env) == -1)
// 		ft_error(2);
// 	close(fd[0]);
// 	wait(NULL);
// 	close(fdout);
// 	free_path(cmds2);
// 	free(path2);
// }
