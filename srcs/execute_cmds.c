/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 05:04:03 by retcheba          #+#    #+#             */
/*   Updated: 2022/09/29 19:46:28 by retcheba         ###   ########.fr       */
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
	close(pipex->fds[0]);
	close(pipex->fds[1]);
	if (pipex->fd_in != -1)
		close(pipex->fd_in);
	close(pipex->fd_out);
	execve(pipex->cmd_path2, pipex->cmd2, envp);
}

void	ft_execute_cmd1(t_struct *pipex, char **argv, char **envp)
{
	pipex->fd_in = open(argv[1], O_RDONLY);
	if (pipex->fd_in == -1)
		perror("Error");
	else if (!(check_cmd1(pipex, argv, envp)))
	{
		pipex->child1 = 1;
		pipex->pid1 = fork();
		if (pipex->pid1 == -1)
			perror("Error");
		if (pipex->pid1 == 0)
			child_one(pipex, envp);
	}
}

void	ft_execute_cmd2(t_struct *pipex, char **argv, char **envp)
{
	pipex->fd_out = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (pipex->fd_out == -1)
		perror("Error");
	else if (!(check_cmd2(pipex, argv, envp)))
	{
		pipex->child2 = 1;
		pipex->pid2 = fork();
		if (pipex->pid2 == -1)
			perror("Error");
		if (pipex->pid2 == 0)
			child_two(pipex, envp);
	}
}

int	ft_execute_cmds(t_struct *pipex, char **argv, char **envp)
{
	ft_execute_cmd1(pipex, argv, envp);
	ft_execute_cmd2(pipex, argv, envp);
	if (pipex->fds[0] != -1)
		close(pipex->fds[0]);
	if (pipex->fds[1] != -1)
		close(pipex->fds[1]);
	if (pipex->fd_in != -1)
		close(pipex->fd_in);
	if (pipex->fd_out != -1)
		close(pipex->fd_out);
	if (pipex->child1 == 1)
		ft_free_var(pipex->cmd_path1, pipex->cmd1);
	if (pipex->child2 == 1)
		ft_free_var(pipex->cmd_path2, pipex->cmd2);
	if (pipex->child1 == 1)
		waitpid(pipex->pid1, NULL, 0);
	if (pipex->child2 == 1)
		waitpid(pipex->pid2, NULL, 0);
	return (0);
}
