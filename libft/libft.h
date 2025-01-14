/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 10:57:30 by ttero             #+#    #+#             */
/*   Updated: 2024/07/04 15:00:04 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int					ft_atoi(const char *str);
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t nitems, size_t size);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
char				*ft_itoa(int n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *str1, const void *str2, size_t n);
void				*ft_memset(void *str, int c, size_t n);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr_fd(char *s, int fd);
char				**ft_split(char const *s, char c);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strdup(char *s1);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlcpy(char *dest, char *src, size_t size);
size_t				ft_strlen(const char *str);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strncmp(const char *str1, const char *str2, size_t n);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(char *s, char *f);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_substr(char const *s, unsigned int start, size_t len);
int					ft_tolower(int c);
int					ft_toupper(int c);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
int					ft_memcmp(const void *str1, const void *str2, size_t n);
void				*ft_memchr(const void *str, int c, size_t n);
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstadd_back(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
int					ft_printf(const char *s, ...);
int					ft_putchar(int c);
int					ft_putnbr_mod(int nb);
int					ft_put_unsig(unsigned int nb);
int					ft_putstr(char *str);
int					ft_puthex(unsigned int nb);
int					ft_puthex_cap(unsigned int nb);
int					ft_puthex_long(unsigned long nb);
int					convert(void *pointer);
int					ft_printf_error(const char *s, ...);
int					ft_putchar_error(int c);
int					ft_putnbr_mod_error(int nb);
int					ft_put_unsig_error(unsigned int nb);
int					ft_putstr_error(char *str);
int					ft_puthex_error(unsigned int nb);
int					ft_puthex_error_cap(unsigned int nb);
int					ft_puthex_error_long(unsigned long nb);
int					convert_error(void *pointer);
double				ft_atod(char *str);
#endif
