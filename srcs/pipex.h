/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 17:23:10 by retcheba          #+#    #+#             */
/*   Updated: 2022/09/28 16:45:08 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_struct
{
	pid_t	pid1;
	pid_t	pid2;
	int		fds[2];
	int		fd_in;
	int		fd_out;
	int		child1;
	int		child2;
	char	**cmd1;
	char	*cmd_path1;
	char	**cmd2;
	char	*cmd_path2;
}	t_struct;

//globals fonctions
char	*get_cmd_path(char *cmd, char **envp);
int		ft_execute_cmds(t_struct *pipex, char **argv, char **envp);
//pipex error
int		check_cmd1(t_struct *pipex, char **argv, char **envp);
int		check_cmd2(t_struct *pipex, char **argv, char **envp);
//pipex utils
void	ft_free_paths(char **paths);
void	ft_free_var(char *cmd_path, char **cmd);
void	ft_close_free_wait(t_struct *pipex);
char	*detach_cmd_from_path(char *cmd_path);

#endif
