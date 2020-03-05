/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_filter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakaria <szakaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 02:50:04 by szakaria          #+#    #+#             */
/*   Updated: 2019/12/08 17:21:38 by szakaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_my		*initialisation_variablev2(t_my *my)
{
	my->new = ft_strnew(0);
	my->tmp = NULL;
	my->tmp2 = NULL;
	my->tmp4 = NULL;
	my->per2 = 1;
	my->x = 0;
	my->start = 0;
	my->per = 0;
	my->i = 0;
	return (my);
}

char		**filter_string(char **argv, char **env, int nb)
{
	int		i;
	int		start;
	char	*tmp;
	char	**new;

	new = (char **)malloc(sizeof(char *) * (nb + 1));
	new[nb] = NULL;
	tmp = NULL;
	start = 0;
	i = 0;
	while (argv[i])
	{
		new[i] = ft_strnew(0);
		tmp = new[i];
		if (ft_strchr(argv[i], '$') || ft_strchr(argv[i], 34)
				|| ft_strchr(argv[i], 39) || ft_strchr(argv[i], '~'))
			new[i] = filter_string2(argv[i], env, new[i]);
		else
			new[i] = ft_strdup(argv[i]);
		ft_memdel(&tmp);
		i++;
	}
	return (new);
}

char		**ft_filter_commande(char *cont, char **env)
{
	int		nb;
	char	**argv;
	char	**av;

	argv = NULL;
	av = NULL;
	cont = ft_filter_quote(0, cont);
	nb = ft_number_words(cont);
	argv = (char **)malloc(sizeof(char *) * (nb + 1));
	argv[nb] = NULL;
	argv = ft_deux(cont, argv);
	av = filter_string(argv, env, nb);
	ft_memdel(&cont);
	ft_fresh(argv);
	free(env);
	return (av);
}
