/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 04:27:51 by retcheba          #+#    #+#             */
/*   Updated: 2022/09/29 18:32:19 by retcheba         ###   ########.fr       */
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
