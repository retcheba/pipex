/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 05:04:03 by retcheba          #+#    #+#             */
/*   Updated: 2022/09/27 06:53:19 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child_one(char **argv, char **envp, int fds[2])
{
	char	**cmd1;
	char	*cmd_path;
	int		fd_in;
	int		fd_out;

	fd_in = open(argv[1], O_RDONLY);
	fd_out = open(argv[4], O_WRONLY);
	dup2(fd_in, 0);
	dup2(fds[1], 1);
	close(fds[0]);
	close(fds[1]);
	close(fd_in);
	close(fd_out);
	cmd1 = ft_split(argv[2], ' ');
	cmd_path = get_cmd_path(cmd1[0], envp);
	if (!cmd_path)
		perror("Error!\n");
	execve(cmd_path, cmd1, envp);
}

static void	child_two(char **argv, char **envp, int fds[2])
{
	char	**cmd2;
	char	*cmd_path;
	int		fd_in;
	int		fd_out;

	fd_in = open(argv[1], O_RDONLY);
	fd_out = open(argv[4], O_WRONLY);
	dup2(fds[0], 0);
	dup2(fd_out, 1);
	close(fds[0]);
	close(fds[1]);
	close(fd_in);
	close(fd_out);
	cmd2 = ft_split(argv[3], ' ');
	cmd_path = get_cmd_path(cmd2[0], envp);
	if (!cmd_path)
		perror("Error!\n");
	execve(cmd_path, cmd2, envp);
}

int	ft_execute_cmds(char **argv, char **envp)
{
	pid_t	pid1;
	pid_t	pid2;
	int		fds[2];

	pipe(fds);
	pid1 = fork();
	if (pid1 == -1)
		return (1);
	if (pid1 == 0)
		child_one(argv, envp, fds);
	else if (pid1 > 0)
	{
		pid2 = fork();
		if (pid2 == -1)
			return (1);
		if (pid2 == 0)
			child_two(argv, envp, fds);
		else if (pid2 > 0)
		{
			close(fds[0]);
			close(fds[1]);
			waitpid(pid1, NULL, 0);
			waitpid(pid2, NULL, 0);
		}
	}
	return (0);
}
