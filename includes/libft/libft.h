/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 12:56:44 by smarsi            #+#    #+#             */
/*   Updated: 2024/11/06 21:11:51 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdio.h>
# include <ctype.h>
# include <string.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>

int			ft_isdigit(int c);
size_t		ft_strlen(const char *s);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t len);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
long long	ft_atoi(char *str);
void		*ft_memset(void *b, int c, size_t len);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);
char		*ft_strdup(const char *s1);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int n);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
typedef struct s_list
{
	int				content;
	int				index;
	struct s_list	*next;
}	t_stack;
t_stack		*ft_lstnew(int content, int index);
void		ft_lstadd_front(t_stack **lst, t_stack *newd);
int			ft_lstsize(t_stack *lst);
t_stack		*ft_lstlast(t_stack *lst);
void		ft_lstadd_back(t_stack **lst, t_stack *newd);
void		ft_lstdelone(t_stack *lst, void (*del)(int));
void		ft_lstclear(t_stack **lst, void (*del)(int));
void		ft_lstiter(t_stack **lst);
t_stack		*ft_lstmap(t_stack *lst, int (*f)(int), void (*del)(int));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);

#endif
