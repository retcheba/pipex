/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 17:21:34 by retcheba          #+#    #+#             */
/*   Updated: 2022/09/29 18:31:26 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_struct	pipex;

	if (argc == 5)
	{
		if (pipe(pipex.fds) == -1)
			perror("Error");
		else
		{
			pipex.child1 = 0;
			pipex.child2 = 0;
			ft_execute_cmds(&pipex, argv, envp);
		}
	}
	else
		write (2, "Error: 4 arguments required\n", 28);
	return (0);
}
