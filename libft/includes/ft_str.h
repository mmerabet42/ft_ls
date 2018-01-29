/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 18:42:15 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/23 20:23:05 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STR_H
# define FT_STR_H

# include <stdlib.h>
# include <wctype.h>

size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s);
char				*ft_strndup(const char *s, size_t n);
char				*ft_strmdup(const char *s, size_t n);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t n);
char				*ft_strcat(char *a, const char *b);
char				*ft_strcatc(char *a, char b);
char				*ft_strncat(char *a, const char *b, size_t n);
size_t				ft_strlcat(char *a, const char *b, size_t n);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *a, const char *b);
char				*ft_strnstr(const char *a, const char *b, size_t n);
char				*ft_strpbrk(const char *s, const char *charset);
int					ft_strpbrk_pos(const char *s, const char *charset);
int					ft_strcmp(const char *a, const char *b);
int					ft_strncmp(const char *a, const char *b, size_t n);
char				*ft_strnchr(const char *s, int c, size_t n);
char				*ft_strnrchr(const char *s, int c, size_t n);
char				*ft_strrstr(const char *a, const char *b);
char				*ft_strnrstr(const char *a, const char *b, size_t n);
int					ft_strchr_pos(const char *a, int b);
int					ft_strstr_pos(const char *a, const char *b);
char				*ft_strrepeat(const char *s, int n);
char				*ft_strrepeat_clr(char *s, int n);
char				*ft_revstr(char *a);
char				*ft_revnstr(char *a, size_t n);
void				ft_swap(char *a, char *b);
int					ft_strforeach(const char *s, int (*f)(char c));

char				*ft_strnew(size_t size);
void				ft_strdel(char **ap);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char *s, char (*f)(char));
char				*ft_strmapi(char *s, char (*f)(unsigned int, char));
int					ft_strequ(const char *a, const char *b);
int					ft_strnequ(const char *a, const char *b, size_t n);
char				*ft_strsub(const char *s, unsigned int start, size_t len);
char				*ft_strjoin(const char *a, const char *b);
char				*ft_strjoinc(const char *a, char b);
char				*ft_strjoincs(char a, const char *b);
char				*ft_strjoin_clr(char *a, char *b, int d);
char				*ft_strjoinc_clr(char *a, char b);
char				*ft_strjoincs_clr(char a, char *b);
char				*ft_strtrim(const char *s);
char				*ft_strtrim_clr(char *s);
char				**ft_strsplit(const char *s, char sep);
char				**ft_strsplitstr(const char *s, const char *sep);
int					ft_strcount(const char *s, char a);
int					ft_strcountstr(const char *s, const char *a);
char				*ft_strrep(const char *s, char a, char b);
char				*ft_strrepc(char *s, char a, char b);
char				*ft_strrepstr(const char *s, const char *a, const char *b);
char				*ft_strrep_clr(char *s, char a, char b);
char				*ft_strrepstr_clr(char *s, const char *a, const char *b);
char				*ft_strafterstr(const char *s, const char *a);
char				*ft_strafter(const char *s, char a);
char				*ft_strbeforestr(const char *s, const char *a);
char				*ft_strbefore(const char *s, char a);

int					ft_strmatch(const char *str, const char *match);

int					ft_wcharlen(wchar_t wc);
char				*ft_getwchar(wchar_t wc);
int					ft_wstrlen(const wchar_t *wcs);
int					ft_wstrnlen(const wchar_t *wcs, int n);
char				*ft_getwstr(const wchar_t *wcs);
char				*ft_getnwstr(const wchar_t *wc, int n);

#endif
