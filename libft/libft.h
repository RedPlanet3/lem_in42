/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 19:09:22 by eyohn             #+#    #+#             */
/*   Updated: 2022/12/11 20:19:22 by sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include "../includes/lem_in.h"

# define BUFFER_SIZE 64

typedef struct	s_split
{
	int			i;
	int			l;
	int			m;
	int			n;
}				t_split;

typedef struct 		s_step {
	int				room;			// room index
	char			old_ch;			//old char in matrix
	struct 	s_step *next;
	struct 	s_step *prew;        	
}					t_step;

int		get_next_line(int fd, char **line);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memccpy(void *dest, const void *src, int c, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_calloc(size_t n, size_t size);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlcpy(char *dst, const char *src, size_t n);
size_t	ft_strlcat(char *dst, const char *src, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *big, const char *little, size_t n);
char	*ft_itoa(int n);
char	**ft_split(const char *s, char c);
char	*ft_strdup(const char *src);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strmapi(const char *s, char (*f)(unsigned int, char));
char	*ft_strtrim(const char *s1, const char *set);
char	*ft_substr(const char *s, unsigned int start, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_strcmp(const char *x, const char *y);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *nptr);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
void	ft_lst_add_back_pn(t_step **lst, t_step *new);
void	ft_lst_del_back_pn(t_step **lst);
void	ft_lstadd_front_pn(t_step **lst, t_step *new);
void	ft_lstclear_pn(t_step **lst);
void	ft_lstdelone_pn(t_step *lst);
t_step	*ft_lstfirst_pn(t_step *lst);
void	ft_lstiter_pn(t_step *lst, void (*f)(void *));
t_step	*ft_lstlast_pn(t_step *lst);
t_step	*ft_lstmap_pn(t_step *lst, void *(*f)(void *), void (*del)(void *));
t_step	*ft_lstnew_pn(int index, char old);
int		ft_lstsize_pn(t_step *lst);
#endif
