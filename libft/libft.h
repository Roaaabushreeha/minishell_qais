/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabu-shr <rabu-shr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 17:27:37 by jalqam            #+#    #+#             */
/*   Updated: 2025/03/06 15:51:59 by rabu-shr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <limits.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strchr(const char *s, int c);
void	ft_putstr_fd(char *s, int fd);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strdup(const char *s);
char	*ft_strrchr(const char *s, int c);
void	*ft_memcpy(void *dest, const void *src, size_t n);
size_t	lenst(long n);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int n, int fd);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_putendl_fd(char *s, int fd);
void	*ft_memchr(const void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
int		ft_isdigit(int c);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_atoi(const char *nptr);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
char	*g_ft_substr(char const *s, unsigned int start, size_t len);
char	*g_ft_strdup(const char *s);
char	*g_ft_strchr(const char *s, int c);
char	*g_ft_strjoin(char const *s1, char const *s2);
size_t	g_ft_strlen(const char *s);
char	*get_next_line(int fd);
int		ft_printf(const char *format, ...);
int		ft_putstr(const char *s);
int		ft_check(char c, va_list args);
int		ft_putnum(int n);
int		ft_putchar(int c);
int		ft_putun(unsigned int n);
int		ft_puthexx(unsigned int n);
int		ft_puthex(unsigned int n);
int		ft_pointer(unsigned long n, char *h);
int		ft_hex_pointer(size_t n);
char	*ft_strndup(const char *s, size_t n);

#endif
