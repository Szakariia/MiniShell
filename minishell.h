/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakaria <szakaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 23:31:18 by szakaria          #+#    #+#             */
/*   Updated: 2019/12/14 11:51:20 by szakaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include "GTN/get_next_line.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/types.h>
# include <unistd.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <readline/readline.h>
# include <readline/history.h>
# define BUFF_SIZE 1024

typedef struct		s_list
{
	char			*str;
	struct s_list	*first;
	struct s_list	*next;
}					t_list;

typedef struct		s_my
{
	char	c;
	int		i;
	int		x;
	int		j;
	int		start;
	int		per;
	int		per2;
	int		per3;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	char	*tmp4;
	char	*new;
}					t_my;

t_list				*return_vide(t_list *list, char **argv);
char				*mypath(void);
char				*return_env_variable(t_my *my);
int					tarit_my_setnv(char **argv, t_list *list);
char				*filter_return(t_my *my);
int					mylen2(char *str, char *argv);
int					mylen(char *str);
char				**my_magic(t_list *list);
int					ft_2eme(int len, char *cont, int index);
char				*ft_myjoin(char *newline, char c);
char				*env_variable(char *cont, char **env, int per2, int x);
void				mini_echo(char **argv);
char				**ft_filter_commande(char *commande, char **env);
char				*ft_filter_quote(int i, char *cont);
char				**ft_split_whitespaces(char *str);
int					ft_number_words(char *cont);
char				**ft_deux(char *cont, char **argv);
void				ft_fresh(char **tab);
int					search_commande(t_list *list, char *commande, char **argv);
void				free_mylist(t_list *list);
void				affichage_myenv(t_list *list);
int					serach_env(char *cont, char **env, int per);
char				*filter_string2(char *argv, char **env, char *new);
t_list				*ft_exit(t_list *list, char **argv, char *commande);
t_list				*ft_trait0(t_list *list, char *line);
t_list				*old_pwd(t_list *list);
t_list				*mini_cd2(t_list *list);
t_my				*initialisation_variablev2(t_my *my);
t_my				*env_variable_return(t_my *my);
t_list				*new_list(char *tmp);
t_list				*stock_list(char **env);
t_list				*my_setenv(char **argv, t_list *list);
t_list				*my_unsetenv(char **argv, t_list *list, int len);
t_list				*ft_myshell(char **argv, int com, t_list *list);
t_list				*mini_cd(char **argv, t_list *list);
t_my				*dollar_and_home(char *cont, t_my *my, char **env);
t_list				*ft_trait(char *commande, t_list *list, char **argv);
t_my				*home_user(char *cont, t_my *my, char	**env);
void				proc_signal_handler(int signo);
void				signal_handler(int signo);
#endif
