/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:02:36 by sponthus          #+#    #+#             */
/*   Updated: 2024/09/17 15:19:31 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdbool.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
	int				size;
	char			*id;
	bool			map; // Is on when map is found
	bool			empty; // Basically positive until proven otherwise
}	t_list;

int	ft_strlen(char *str);

int	write_error(char *error, char *target, int errno);

int		ft_lstsize(t_list *lst);
t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));

char	*get_next_line(int fd);

int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strnstr(const char *big, const char *little, size_t len);
int				is_charset(char c, char	*charset);
char			*ft_strtrim(char *s1, char *set);
size_t			ft_strlcpy(char *dst, char *src, size_t size);
char			*ft_strdup(char *s);
unsigned int	color_atoi(const char *nptr);
int				ft_isdigit(int c);

void	*ft_calloc(size_t nmemb, size_t size);

void	free_split(char **str, size_t j);
char	**ft_split(char const *s, char c);
void	free_full_split(char **split);

#endif
