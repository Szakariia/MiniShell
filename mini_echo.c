/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakaria <szakaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 01:45:03 by szakaria          #+#    #+#             */
/*   Updated: 2019/12/14 11:52:15 by szakaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*return_env_variable(t_my *my)
{
	if (&my->tmp4[0] == '\0')
		ft_memdel(&my->tmp4);
	return (NULL);
}

t_list	*return_vide(t_list *list, char **argv)
{
	ft_fresh(argv);
	return (list);
}

void	mini_echo(char **argv)
{
	int		i;

	i = 1;
	while (argv[i])
	{
		ft_putstr(argv[i]);
		ft_putchar(' ');
		i++;
	}
	ft_putchar('\n');
}

void	proc_signal_handler(int signo)
{
	if (signo == SIGINT)
		ft_putstr("\n");
}

void	signal_handler(int signo)
{
	char	*pwd;

	pwd = mypath();
	if (signo == SIGINT)
	{
		ft_putstr("\n");
		ft_putstr(pwd);
		ft_memdel(&pwd);
	}
}
