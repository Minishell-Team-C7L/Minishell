/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_ft.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 09:51:26 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/14 15:36:06 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_FT_H
# define LIB_FT_H

# include <stdbool.h>
//	For: bool
# include <stddef.h>
//	For: size_t, NULL
# include <stdlib.h>
//	For: malloc(), free(), exit(), EXIT_FAILURE, EXIT_SUCCESS
# include <unistd.h>
//	For: write(), STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO
# include <limits.h>
//	For: LONG_MAX
# include <fcntl.h>
//	For: open(), O_RDONLY, O_WRONLY, O_CREAT, O_TRUNC, O_APPEND

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int		ft_atoi(const char *str);

void	*ft_calloc(size_t nmemb, size_t size);
void	ft_bzero(void *s, size_t nm);
void	ft_free(void **ptr);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
char	*ft_itoa(int n);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
int		ft_lstlen(const t_list *lst);
t_list	*ft_lstnew(void *content);
void	*ft_memcpy(void *dst, const void *src, size_t len);
void	*ft_memset(void *ptr, int c, size_t len);
void	ft_putchar(char c);
void	ft_putchar_err(char c);
void	ft_putchar_fd(char c, int fd);
void	ft_puterr(const char *str);
void	ft_putnbr_fd(int nbr, int fd);
void	ft_putstr_fd(char *str, int fd);
void	ft_putstr(const char *str);
void	ft_putstr_nl(const char *str);
bool	ft_str_is_mono(const char *str, char constant, size_t start);
bool	ft_str_is_num(const char *str);
char	*ft_strchr(const char *str, int c);
int		ft_strcmp(const char *str_1, const char *str_2);
char	*ft_strcpy(char *str_dst, const char *str_src);
char	*ft_strdup(const char *str);
char	*ft_strjoin(char const *str_1, char const *str_2);
size_t	ft_strlcpy(char *str_dst, const char *str_src, size_t size_dst);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *str_1, const char *str_2, size_t len);
char	*ft_substr(char const *str, size_t start, size_t len);
size_t	ft_wordcount(const char *str, char delimiter);

#endif
