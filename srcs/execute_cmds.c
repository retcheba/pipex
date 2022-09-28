/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 05:04:03 by retcheba          #+#    #+#             */
/*   Updated: 2022/09/28 04:23:48 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child_one(t_struct *pipex, char **envp)
{
	dup2(pipex->fd_in, 0);
	dup2(pipex->fds[1], 1);
	close(pipex->fds[0]);
	close(pipex->fds[1]);
	close(pipex->fd_in);
	execve(pipex->cmd_path1, pipex->cmd1, envp);
}

static void	child_two(t_struct *pipex, char **envp)
{
	dup2(pipex->fds[0], 0);
	dup2(pipex->fd_out, 1);
	ft_close_fd(pipex);
	execve(pipex->cmd_path2, pipex->cmd2, envp);
}

int	ft_execute_cmds(t_struct *pipex, char **argv, char **envp)
{
	pipex->fd_in = open(argv[1], O_RDONLY);
	if (pipex->fd_in == -1)
		perror("Error");
	else if (!(check_cmd1(pipex, argv, envp)))
	{
		pipex->pid1 = fork();
		if (pipex->pid1 == -1)
			return (1);
		if (pipex->pid1 == 0)
			child_one(pipex, envp);
	}
	pipex->fd_out = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (pipex->fd_out == -1)
		perror("Error");
	else if (!(check_cmd2(pipex, argv, envp)))
	{
		pipex->pid2 = fork();
		if (pipex->pid2 == -1)
			return (1);
		if (pipex->pid2 == 0)
			child_two(pipex, envp);
	}
	ft_close_fd(pipex);
	ft_wait_end_fork(pipex);
	return (0);
}
