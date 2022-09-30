/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 04:27:51 by retcheba          #+#    #+#             */
/*   Updated: 2022/09/28 18:29:58 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*detach_cmd_from_path(char *cmd_path)
{
	char	*cmd;
	int		start;
	int		len;

	start = 0;
	len = 0;
	while (cmd_path[start + 1])
		start++;
	while (cmd_path[start] != '/' && start != 0)
	{
		len++;
		start--;
	}
	cmd = ft_substr(cmd_path, start, len);
	return (cmd);
}

void	ft_free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		paths[i] = NULL;
		i++;
	}
	free(paths);
	paths = NULL;
}

void	ft_free_var(char *cmd_path, char **cmd)
{
	int	i;

	free(cmd_path);
	cmd_path = NULL;
	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		cmd[i] = NULL;
		i++;
	}
	free(cmd);
	cmd = NULL;
}

void	ft_close_free_wait(t_struct *pipex)
{
	close(pipex->fds[0]);
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
}
