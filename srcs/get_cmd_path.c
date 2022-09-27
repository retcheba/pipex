/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:07:55 by retcheba          #+#    #+#             */
/*   Updated: 2022/09/27 02:11:25 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_free_paths(char **paths)
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
}

static char	*ft_strstr_from_begin(char *str, char *to_find)
{
	int	i;

	i = 0;
	while (to_find[i])
	{
		if (to_find[i] != str[i])
			return (NULL);
		i++;
	}
	return (str);
}

char	*get_cmd_path(char *cmd, char **envp)
{
	char	*envp_PATH;
	char	**paths;
	char	*cmd_path;
	char	*tmp;
	int		i;

	i = 0;
	while (envp[i])
	{
		envp_PATH = ft_strstr_from_begin(envp[i], "PATH=");
		if (envp_PATH)
		{
			envp_PATH = ft_substr(envp_PATH, 5, (ft_strlen(envp[i]) - 5)); // On malloc
			break;
		}
		i++;
	}
	paths = ft_split(envp_PATH, ':');
	free(envp_PATH);
	envp_PATH = NULL;
	i = 0;
	while (paths[i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(tmp);
        tmp = NULL;
		i++;
	}
	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], cmd);
		if (access(cmd_path, F_OK | X_OK) == 0)
		{
			ft_free_paths(paths);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	ft_free_paths(paths);
	return (NULL);
}
