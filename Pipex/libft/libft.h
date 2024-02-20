/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:45:14 by kcouchma          #+#    #+#             */
/*   Updated: 2024/02/20 10:28:07 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/******************************************************************************/
/* includes                                                                   */
/******************************************************************************/

# include <unistd.h>			/*size_t (unsigned long)*/
# include <stdlib.h>			/*malloc/free/calloc etc*/
# include <fcntl.h>				/*open*/
# include <stdio.h>				/*printf*/
# include <stdarg.h>			/*va_arg macros*/
# include "../../minishell.h"

/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/

# ifndef BUFFER_SIZE	/*get_next_line*/
#  define BUFFER_SIZE 5
# endif

# define FD_MAX 1024	/*get_next_line*/

/******************************************************************************/
/* Structures                                                                 */
/******************************************************************************/

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/******************************************************************************/
/* C-Type                                                                     */
/******************************************************************************/

/**
 * @brief Tells whether or not `c` is a letter.
 * @param c A character.
 * @return Whether or not `c` is a letter.
 */
int		ft_isalpha(int c);

/**
 * @brief Tells whether or not `c` is a digit.
 * @param c A character.
 * @return whether or not `c` is a digit.
 */
int		ft_isdigit(int c);

/**
 * @brief Tells whether or not `c` is a letter or a digit.
 * @param c A character.
 * @return Whether or not `c` is a letter or a digit.
 */
int		ft_isalnum(char c);

/**
 * @brief Tells whether or not `c` is an ascii character.
 * @param c A character.
 * @return Whether or not `c` is an ascii character.
 */
int		ft_isascii(int c);

/**
 * @brief Tells whether or not `c` is printable (c >= 32 && c <= 126).
 * @param c A character.
 * @return Whether or not `c` is printable.
 */
int		ft_isprint(int c);

/**
 * @brief If `c` is a letter, converts it to uppercase.
 * @param c a character.
 * @return The transformed character.
 */
int		ft_toupper(int c);

/**
 * @brief If `c` is a letter, converts it to lowercase.
 * @param c a character.
 * @return The transformed character.
 */
int		ft_tolower(int c);

/******************************************************************************/
/* String-Type                                                                */
/******************************************************************************/

/**
 * @brief Calculates th length of `str`.
 * @param str A string.
 * @return The length of `str`.
 */
size_t	ft_strlen(const char *c);

/**
 * @brief Returns a pointer to the first occurence of `c` in `str` if it exists,
 * `NULL` otherwise.
 * @param str A string.
 * @param c A character.
 * @return A pointer to the first occurence of `c` in `str` if it exists,
 * `NULL` otherwise.
 */
char	*ft_strchr(const char *s, int c);

/**
 * @brief Returns a pointer to the last occurence of `c` in `str` if it exists,
 * `NULL` otherwise.
 * @param str A string.
 * @param c A character.
 * @return A pointer to the last occurence of `c` in `str` if it exists,
 * `NULL` otherwise.
 */
char	*ft_strrchr(const char *s, int c);

/**
 * @brief Compares with the lexical order the `n` first characters of `str_1`
 * and `str_2`.
 * @param str_1 A string.
 * @param str_2 A string.
 * @param n The max ammount of characters to compare.
 * @return The lexical order of the two strings (ascii value difference of the 
 * first diverging character: 0 if identical).
 */
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/**
 * @brief Sets `n` bytes of `ptr` to `c`.
 * @param ptr A pointer to a memory area.
 * @param c A byte.
 * @param n The ammount of bytes to set to `c`.
 * @return The `ptr` pointer.
 */
void	*ft_memset(void *s, int c, size_t n);

/**
 * @brief Writes `n` zeros ('\0') to `ptr` (uses ft_memset).
 * @param ptr A pointer to a memory area.
 * @param n The amount of bytes to set to zero.
 */
void	ft_bzero(void *s, size_t n);

/**
 * @brief Returns a pointer to the first occurence of the byte `c` in `ptr` if
 * it exists, `NULL` otherwise.
 * @param ptr A memory area.
 * @param c A byte.
 * @return A pointer to the first occurence of the byte `c` in `ptr` if it
 * exists, `NULL` otherwise.
 */
void	*ft_memchr(const void *s, int c, size_t n);

/**
 * @brief Copies `n` bytes of `src` to `dst`. The memory areas must not overlap.
 * Use `ft_memmove` if the memory areas do overlap.
 * @param dst A pointer to a memory area.
 * @param src A pointer to a memory area.
 * @param n The ammount of bytes to copy.
 * @return The `dst` pointer.
 */
void	*ft_memcpy(void *dest, const void *src, size_t n);

/**
 * @brief Compares with the lexical order the `n` first bytes of `ptr_1`
 * and `ptr_2`.
 * @param ptr_1 A memory area.
 * @param ptr_2 A memory area.
 * @param n The max ammount of bytes to compare.
 * @return The lexical order of the two memory area.
 */
int		ft_memcmp(const void *s1, const void *s2, size_t n);

/**
 * @brief copies `n` bytes from memory area `src` to memory area `dst`.
 * The memory areas may overlap: copying takes place as though the bytes in
 * `src` are first copied into a temporary array that does not overlap `src`
 * or `dst`, and the bytes are then copied from the temporary array to `dst`.
 * @param dst A pointer to a memory area.
 * @param src A pointer to a memory area.
 * @param n The ammount of bytes to copy.
 * @return The `dst` pointer.
 */
void	*ft_memmove(void *dest, const void *src, size_t n);

/**
 * @brief Copies `src` to `dst`. Takes the full `size` of `dst` and guarantee
 * to NUL-terminate the result (as long as `size` is larger than 0). Note that a
 * byte for the NUL should be included in `size`. Can only operate on true "C"
 * strings. `src` must be NUL-terminated. Copies up to `size - 1` characters
 * from `src` to `dst`, NUL-terminating the result.
 * @param dst A pointer to a memory area.
 * @param src A string.
 * @param size The length of the string `ft_strlcopy` tries to create.
 * @return The length of `src`.
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

/**
 * @brief Concatenate `str` to `dst`. Takes the full `size` of `dst`
 * and guarantee to NUL-terminate the result (as long as there is at least one
 * byte free in `dst`). Note that a byte for the NUL should be included in
 * `size`. Can only operate on true “C” strings. This means that both `src`
 * and `dst` must be NUL-terminated. Appends the NUL-terminated string `src` to
 * the end of `dst`. It will append at most `size - ft_strlen(dst) - 1` bytes,
 * NUL-terminating the result.
 * @param dst A pointer to a memory area.
 * @param src A string.
 * @param size The length of the string `ft_strlcat` tries to create.
 * @return The initial length of `dst` plus the length of `src`.
 */
size_t	ft_strlcat(char *dst, const char *src, size_t size);

/**
 * @brief Locates the first occurrence of the null-terminated string `little`
 * in the string `big`, where not more than `len` characters are searched.
 * Characters that appear after a ‘\0’ character are not searched.
 * @param big The string to be searched.
 * @param little The string to search.
 * @param len The size of the search.
 * @return If `little` is an empty string, `big` is returned; if `little` occurs
 * nowhere in `big`, `NULL` is returned; otherwise a pointer to the first
 * character of the first occurrence of `little` is returned.
 */
char	*ft_strnstr(const char *big, const char *little, size_t len);

/**
 * @brief Allocates (with malloc(3)) and returns a copy of `str`.
 * @param str A string.
 * @return A copy of `str`.
 */
char	*ft_strdup(const char *s);

/**
 * @brief Allocates (with malloc(3)) and returns a substring from the
 * string `str`. The substring begins at index `start` and is of maximum
 * size `len`.
 * @param str The string from which to create the substring.
 * @param start The start index of the substring in the string `str`.
 * @param len The maximum length of the substring.
 * @return The substring or `NULL` if the allocation fails.
 */
char	*ft_substr(char const *s, unsigned int start, size_t len);

/**
 * @brief Allocates (with malloc(3)) and returns a new string, which is the
 * result of the concatenation of ’s1’ and ’s2’. *
 * @param s1 The prefix string.
 * @param s2 The suffix string.
 * @return char* The new string, or NULL if the allocation fails.
 */
char	*ft_strjoin(char const *s1, char const *s2);

/**
 * @brief Allocates (with malloc(3)) and returns a copy of ’s1’ with the
 * characters specified in ’set’ removed from the beginning and the end of
 * the string.
 * @param s1 The string to be trimmed.
 * @param set The reference set of characters to trim.
 * @return char* The trimmed string, or NULL if the allocation fails.
 */
char	*ft_strtrim(char const *s1, char const *set);

/**
 * @brief Allocates (with malloc(3)) and returns an array of strings obtained
 * by splitting ’s’ using the character ’c’ as a delimiter. The array must
 * end with a NULL pointer.
 * @param s The string to be split.
 * @param c The delimiter character.
 * @return char** The array of new strings resulting from the split, or NULL
 * if the allocation fails.
 */
char	**ft_split(char const *s, char c);

/**
 * @brief Allocates (with malloc(3)) and returns a string representing the
 * integer received as an argument. Negative numbers must be handled.
 * @param n The integer to convert
 * @return The string representing the integer, or NULL if the allocation fails.
 */
char	*ft_itoa(int n);

/**
 * @brief Applies the function ’f’ to each character of the string ’s’, and
 * passing its index as first argument to create a new string (with malloc(3))
 * resulting from successive applications of ’f’.
 * @param s The string on which to iterate.
 * @param f The function to apply to each character.
 * @return char* The string created from the successive applications of ’f’,
 * or NULL if the allocation fails.
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/**
 * @brief Applies the function ’f’ on each character of the string passed as
 * argument, passing its index as first argument. Each character is passed by
 * address to ’f’ to be modified if necessary.
 * @param s The string on which to iterate.
 * @param f The function to apply to each character.
 */
void	ft_striteri(char *s, void (*f)(unsigned int, char *));

/******************************************************************************/
/* Stdlib                                                                     */
/******************************************************************************/

/**
 * @brief Converts the initial portion of the string pointed to by `str` to an
 * integer.
 * @param str The string to be converted.
 * @return The converted value.
 */
int		ft_atoi(const char *str);

/**
 * @brief Atod episode II - atoi with extra sauce (thank you norminette)
 * Basically an atoi, with an extra step in the case of fract == 1.
 * In this case, the double created is divided by 10 ^ its length using the i
 * variable to track the number of digits. This creates the fraction part of 
 * the double (the part to the right of the decimal point).
 * @param argv input argument sent from ft_atod1 ('integer' or 'fraction' part)
 * @param fract if integer then 0, if fraction then 1 (to run division cycle)
 * @return double the integer or fraction part requested by ft_atod1
 */
double	ft_atod2(char **argv, int fract);

/**
 * @brief Atod episode I - the search for negs (thank you norminette)
 * In this function, each argument is checked to see if it's negative or 
 * positive, then stripped of the '-' or '+'. The string before the decimal (if
 * present) if transferred using a modified atoi (ft_atod2) into the double 
 * 'integer'. The decimal (if present) is then skipped and any remaining digits
 * sent through the atoi into the double 'fraction'. The two are then added 
 * together to create the output double.
 * @param argv input argument sent from ft_atod.
 * @return double constructed from the char * input.
 */
double	ft_atod1(char *argv);

/**
 * @brief Allocates memory for an array of `nmemb` elements of size bytes each
 * and returns a pointer to the allocated memory. The memory is set to zero.
 * If `nmemb` or `size` is 0, then calloc() returns either NULL, or a unique
 * pointer value that can later be successfully passed to free(). If the
 * multiplication of `nmemb` and `size` would result in integer overflow, then
 * calloc() returns `NULL`.
 * @param nmemb The number of elements if the array.
 * @param size The size in bytes of each element.
 * @return Return a pointer to the allocated memory or NULL if case of error.
 */
void	*ft_calloc(size_t nmemb, size_t size);

/******************************************************************************/
/* FD-Type                                                                    */
/******************************************************************************/

/**
 * @brief Outputs the character ’c’ to the given file descriptor.
 * @param c The character to output.
 * @param fd The file descriptor on which to write.
 * @return Returns 1 (no. of characters written)
 */
int		ft_putchar_fd(char c, int fd);

/**
 * @brief Outputs the string ’s’ to the given file descriptor.
 * @param s The string to output.
 * @param fd The file descriptor on which to write.
 * @return Returns the number of characters written (ft_strlen(s)).
 */
int		ft_putstr_fd(char *s, int fd);

/**
 * @brief Outputs the string ’s’ to the given file descriptor followed by a 
 * newline.
 * @param s The string to output.
 * @param fd The file descriptor on which to write.
 */
void	ft_putendl_fd(char *s, int fd);

/**
 * @brief Outputs the integer ’n’ to the given file descriptor.
 * @param n Input int
 * @param fd The file descriptor on which to write.
 * @return int Returns the number of characters written.
 */
int		ft_putnbr_fd(long n, int fd);

/**
 * @brief ft_putnbr to hex (or other) base
 * @param n Input number to convert
 * @param base Base as a string
 * @param fd Output
 */
int		ft_putbase(size_t n, char *base, int fd);

/******************************************************************************/
/* Bonus                                                                      */
/******************************************************************************/

/**
 * @brief Allocates (with malloc(3)) and returns a new node. The member variable 
 * ’content’ is initialized with the value of the parameter ’content’. The 
 * variable ’next’ is initialized to NULL.
 */
t_list	*ft_lstnew(void *content);

/**
 * @brief Adds the node ’new’ at the beginning of the list. * 
 * @param lst The address of a pointer to the first link of a list.
 * @param new The address of a pointer to the node to be added to the list.
 */
void	ft_lstadd_front(t_list **lst, t_list *new);

/**
 * @brief Counts the number of nodes in a list.
 * @param lst The beginning of the list.
 * @return int The length of the list>
 */
int		ft_lstsize(t_list *lst);

/**
 * @brief Returns the last node of the list.
 * @param lst The beginning of the list.
 * @return t_list* Last node of the list>
 */
t_list	*ft_lstlast(t_list *lst);

/**
 * @brief Adds the node ’new’ at the end of the list.
 * @param lst The address of a pointer to the first link of a list.
 * @param new The address of a pointer to the node to be added to the list.
 */
void	ft_lstadd_back(t_list **lst, t_list *new);

/**
 * @brief Takes as a parameter a node and frees the memory of the node’s 
 * content using the function ’del’ given as a parameter and free the node. 
 * The memory of ’next’ must not be freed.
 * @param lst The node to free.
 * @param del The address of the function used to delete the content
 */
void	ft_lstdelone(t_list *lst, void (*del)(void*));

/**
 * @brief Deletes and frees the given node and every successor of that node, 
 * using the function ’del’ and free(3). Finally, the pointer to the list 
 * must be set to NULL.
 * @param lst The address of a pointer to a node.
 * @param del The address of the function used to delete the content of the 
 * node.
 */
void	ft_lstclear(t_list **lst, void (*del)(void *));

/**
 * @brief Iterates the list ’lst’ and applies the function ’f’ on the content 
 * of each node.
 * @param lst The address of a pointer to a node.
 * @param f The address of the function used to iterate on the list.
 */
void	ft_lstiter(t_list *lst, void (*f)(void *));

/**
 * @brief Iterates the list ’lst’ and applies the function ’f’ on the content 
 * of each node. Creates a new list resulting of the successive applications 
 * of the function ’f’. The ’del’ function is used to delete the content of a 
 * node if needed.
 * @param lst The address of a pointer to a node.
 * @param f The address of the function used to iterate on the list.
 * @param del The address of the function used to delete the content of a node 
 * if needed.
 * @return t_list* 
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/******************************************************************************/
/* Projects - printf                                                          */
/******************************************************************************/

/**
 * @brief If type is %s, uses ft_putstr_fd equivalent to print it to terminal.
 * @param str Input string to print.
 * @return int Number of characters printed to terminal.
 */
int		ft_print_string(char *str);

/**
 * @brief If type is %p, uses ft_putbase_fd equivalentto print it to terinmal.
 * Prints first 0x prefix, then uses a putbase with hexadecimal output to print
 * the pointer read initally as a size_t (unsigned long).
 * @param str Input pointer to print.
 * @return int Number of characters printed to terminal (including 0x).
 */
int		ft_print_ptr(void *str);

/**
 * @brief Function to dispatch printf flag inputs to their respective print 
 * functions.
 * @param type Printf flags : %c(char), %s(string), %p(pointer), %d(decimal),
 *  %i(integer), %u(unsigned decimal), %x(hex lowercase), %X(hex uppercase), 
 * %%(% sign).
 * @param args Argument from va_list.
 * @return int Number of characters printed to the terminal.
 */
int		ft_put_type(char type, va_list args);

/**
 * @brief Recode the printf() function from libc (man 3 printf).
 * Implements the following conversions:
• %c %s %p %d %i %u %x %X %%
 * @param ... variadic input
 * @return int 
 */
int		ft_printf(const char *input, ...);

/******************************************************************************/
/* Projects - get_next_line                                                   */
/******************************************************************************/

/**
 * @brief Copies the contents of buffer (up to and including the first \n) into 
 * line (ft_strjoin). Resets the buffer to remove copied contents (ft_strcpy).
 * @param line A pointer to a memory area.
 * @param buffer Buffer to read into line.
 * @return char* Line with buffer contents.
 */
char	*ft_buff2line(char *line, char *buffer);

/**
 * @brief While line does not contain a newline, reads from the file (fd) for 
 * length BUFFER_SIZE, and concatenates the result into line. Once a \n is 
 * present, sends to ft_buff2line to fill buffer into line and reset the buffer
 * correctly.
 * @param line A pointer to a memory area.
 * @param buffer Buffer to read into line.
 * @param fd File to be read.
 * @return char* The next line to be returned to get_next_line.
 */
char	*ft_read2buff(char *line, char *buffer, int fd);

/**
 * @brief Returns a line read from a file descriptor.
 * @param fd The file descriptor to read from.
 * @return char * The line that was read or NULL if there is nothing else 
 * to read, or an error occurred.
 */
char	*get_next_line(int fd);

/******************************************************************************/
/* Projects - get_next_line_utils                                             */
/******************************************************************************/

/**
 * @brief Searches string buffer for a newline character '\n'.
 * @param buffer Input string.
 * @return int Returns index of \n if present or -1 if not found.
 */
int		ft_findnl(char *buffer);

/**
 * @brief Copies `str2` to `str1`. Takes the full size of `str2` and guarantee
 * to NUL-terminate the result.
 * @param str1 A pointer to a memory area.
 * @param str2 A string.
 * @return pointer to str1.
 */
char	*ft_strcpy(char *str1, char *str2);

/**
 * @brief Calculates th length of `str`.
 * @param str A string.
 * @return The length of `str`.
 */
size_t	ft_gnl_strlen(const char *c);

/**
 * @brief Allocates memory for an array of `nmemb` elements of size bytes each
 * and returns a pointer to the allocated memory. The memory is set to zero.
 * If `nmemb` or `size` is 0, then calloc() returns either NULL, or a unique
 * pointer value that can later be successfully passed to free(). If the
 * multiplication of `nmemb` and `size` would result in integer overflow, then
 * calloc() returns `NULL`.
 * @param nmemb The number of elements if the array.
 * @param size The size in bytes of each element.
 * @return Return a pointer to the allocated memory or NULL if case of error.
 */
void	*ft_gnl_calloc(size_t nmemb, size_t size);

/**
 * @brief Allocates (with malloc(3)) and returns a new string, which is the
 * result of the concatenation of ’s1’ and ’s2’. FREES original s1.
 * @param s1 The prefix string.
 * @param s2 The suffix string.
 * @return char* The new string, or NULL if the allocation fails.
 */
char	*ft_gnl_strjoin(char *s1, char *s2);
#endif
