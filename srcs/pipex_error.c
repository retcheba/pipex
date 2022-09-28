/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 04:29:12 by retcheba          #+#    #+#             */
/*   Updated: 2022/09/28 04:34:14 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_cmd1(t_struct *pipex, char **argv, char **envp)
{
	pipex->cmd1 = ft_split(argv[2], ' ');
	if (access(pipex->cmd1[0], F_OK | X_OK) == 0)
	{
		pipex->cmd_path1 = pipex->cmd1[0];
		pipex->cmd1[0] = detach_cmd_from_path(pipex->cmd_path1);
	}
	else
		pipex->cmd_path1 = get_cmd_path(pipex->cmd1[0], envp);
	if (!pipex->cmd_path1)
	{
		write(2, "Error: command not found\n", 25);
		ft_free_var(pipex->cmd_path1, pipex->cmd1);
		return (1);
	}
	return (0);
}

int	check_cmd2(t_struct *pipex, char **argv, char **envp)
{
	pipex->cmd2 = ft_split(argv[3], ' ');
	if (access(pipex->cmd2[0], F_OK | X_OK) == 0)
	{
		pipex->cmd_path2 = pipex->cmd2[0];
		pipex->cmd2[0] = detach_cmd_from_path(pipex->cmd_path2);
	}
	else
		pipex->cmd_path2 = get_cmd_path(pipex->cmd2[0], envp);
	if (!pipex->cmd_path2)
	{
		write(2, "Error: command not found\n", 25);
		ft_free_var(pipex->cmd_path2, pipex->cmd2);
		return (1);
	}
	return (0);
}
