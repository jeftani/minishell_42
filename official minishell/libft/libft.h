/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloukas <gloukas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 08:37:59 by gloukas           #+#    #+#             */
/*   Updated: 2023/05/23 17:52:18 by gloukas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/*PART ONE*/
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_strlen(char *s);
void				*ft_memset(void *b, int c, int len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, void *src, int n);
void				*ft_memmove(void *dst, void *src, int n);
int					ft_strlcpy(char *dst, char *src, int dstsize);
int					ft_strlcat(char *dst, char *src, int size);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strchr(char *s, int find);
char				*ft_strrchr(char *s, int find);
int					ft_strncmp(char *s1, char *s2, int n);
void				*ft_memchr(void *s, int c, int n);
int					ft_memcmp(void *s1, void *s2, int n);
char				*ft_strnstr(char *str, char *to_find, int len);
int					ft_atoi(char *str);
void				*ft_calloc(size_t count, size_t size);
char				*ft_strdup(char *src);
/*PART TWO*/
char				*ft_substr(char *s, int start, int len);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_strtrim(char *s1, char *set);
char				**ft_split(char *s, char c);
void				ft_free(char **t, int n);
char				*ft_itoa(int n);
char				*ft_strmapi(char *s, char (*f)(int, char));
void				ft_striteri(char *s, void (*f)(int, char *));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
/*BONUS*/
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

#endif
