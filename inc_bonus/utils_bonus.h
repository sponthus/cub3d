/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:02:36 by sponthus          #+#    #+#             */
/*   Updated: 2024/11/08 12:14:22 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_BONUS_H
# define UTILS_BONUS_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdbool.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

// Map is on when map is found
// Empty is basically positive until proven otherwise
typedef struct s_list
{
	char			*content;
	struct s_list	*next;
	int				size;
	char			*id;
	bool			map;
	bool			empty;
}	t_list;

t_list			*ft_lstnew(void *content);
t_list			*ft_lstlast(t_list *lst);
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *), \
	void (*del)(void *));

void			ft_lstadd_front(t_list **lst, t_list *new);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstclear(t_list **lst, void (*del)(void*));
void			ft_lstiter(t_list *lst, void (*f)(void *));
void			*ft_memset(void *s, int c, size_t n);
void			*ft_calloc(size_t nmemb, size_t size);
void			free_split(char **str, size_t j);
void			free_full_split(char **split);
void			*ft_buffmove(char *dest, char *src, size_t size, int *n);

char			*ft_strlcpy_nl(char *str, char *s, int len, int *n);
char			*ft_strjoin_free(char *s1, char *s2, int *n, int size);
char			*get_next_line(int fd);
char			**ft_split(char const *s, char c);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_strnstr(const char *big, const char *little, size_t len);
char			*ft_strdup(char *s);
char			*ft_strtrim(char *s1, char *set);

int				ft_strlen(char *str);
int				write_err(char *error, char *target, char *obj, int errno);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				is_charset(char c, char	*charset);
int				ft_isdigit(int c);
int				ft_lstsize(t_list *lst);

unsigned int	color_atou(const char *nptr);

size_t			ft_strlcpy(char *dst, char *src, size_t size);

#endif
