/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpastor- <lpastor-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 07:51:38 by lpastor-          #+#    #+#             */
/*   Updated: 2023/09/12 07:51:38 by lpastor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef GNL_MAX_FD
#  define GNL_MAX_FD 2048
# endif

/**
 * @brief t_list
 *
 * Node of a linked list
 * @param content The information contained by the node
 * @param next    The address of the next node, or NULL if the
 *                  next node is the last
 */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/****************************
*                           *
*      MANDATORY PART       * 
*                           *
*****************************/

/**
 * @brief	It converts a string to integer
 * 
 * @param str	The string to be converted
 * 
 * @return	The int value produced by interpreting the input characters
 *			as a number
 */
int		ft_atoi(const char *str);

/**
 * @brief	Sets a buffer to the null character
 * 
 * @param s	Pointer to destination
 * @param n	Number of characters
 */
void	ft_bzero(void *s, size_t n);

/**
 * @brief	Allocates an array in memory with elements initialized to 0
 * 
 * @param nitems	Number of items/elements
 * @param size		Length (in bytes) of each element
 * 
 * @return	A pointer to the allocated space
 */
void	*ft_calloc(size_t nitems, size_t size);

/**
 * @brief	Determines whether an integer represents an alphanumeric character
 * 
 * @param c	Integer to test
 * 
 * @return	It returns a nonzero value if `c` is within the ranges
 *			A-Z, a-z or 0-9
 */
int		ft_isalnum(int c);

/**
 * @brief	Determinates whether an integer represents an alphabetic character
 * 
 * @param c	Integer to test
 * 
 * @return	It returns a nonzero value if `c` is within the ranges A-Z or a-z
 */
int		ft_isalpha(int c);

/**
 * @brief	Determines whether a particular character is an ASCII character
 * 
 * @param c	Integer to test
 * 
 * @return	It returns a nonzero value if `c` is an ASCII value
 */
int		ft_isascii(int c);

/**
 * @brief	Determines whether an integer represents a decimal-digit character
 * 
 * @param c	Integer to test
 * 
 * @return	It returns a nonzero value if `c` is a decimal digit (0-9)
 */
int		ft_isdigit(int c);

/**
 * @brief	Determines whether an integer represents a printable character
 * 
 * @param c	Integer to test
 * 
 * @return	It returns a nonzero value if `c` is a printable character
 */
int		ft_isprint(int c);

/**
 * @brief	Reserving memory, generate a string that represents the integer
 *			value received as an argument. Negative numbers have to be managed.
 * 
 * @param n	The integer to convert
 * 
 * @return	The string representing the number, or NULL if memory
 *			reservation fails.
 */
char	*ft_itoa(int n);

/**
 * @brief	Find characters in a string
 * 
 * @param str	Pointer to the string
 * @param c		Character to llok for
 * @param n		Number of characters to check
 * 
 * @return	If successful, returns a pointer to the first location
 *			of `c` in `buffer`; otherwise, it returns NULL
 */
void	*ft_memchr(const void *str, int c, size_t n);

/**
 * @brief	Compares characters in two strings
 * 
 * @param str1	First string
 * @param str2	Second string
 * @param n		Numbers of characters to compare
 * 
 * @return	If the strings are equal, return 0. Otherwise: if the return
 *			is greater than 0, the first string is greater; If it is smaller,
 *			the second is the larger.
 */
int		ft_memcmp(const void *str1, const void *str2, size_t n);

/**
 * @brief	Copies bytes between buffers (it isn't secure)
 * 
 * @param dest	New buffer
 * @param src	Buffer to copy from
 * @param n		Number of characters to copy
 * 
 * @return	The value of `dest`
 */
void	*ft_memcpy(void *dest, const void *src, size_t n);

/**
 * @brief	Moves one buffer to another
 * 
 * @param dest	Destination object
 * @param src	Source object
 * @param n		Number of bytes to copy
 * 
 * @return	The value of `dest`
 */
void	*ft_memmove(void *dest, const void *src, size_t n);

/**
 * @brief	Sets a buffer to a specified character
 * 
 * @param dest	Pointer to destination
 * @param c		Character to set
 * @param n		Number of characters
 * 
 * @return	The value of `dest`
 */
void	*ft_memset(void *str, int c, size_t n);

/**
 * @brief	Sends the character `c` to the specified file descriptor
 * 
 * @param c		The character to send
 * @param fd	The file descriptor to write about
 * 
 * @return	Number of printed characters
 */
int		ft_putchar_fd(char c, int fd);

/**
 * @brief	Sends the string `s` to the specified file descriptor,
 *			followed by a line break
 * 
 * @param s		The string to send
 * @param fd	The file descriptor to write about
 * 
 * @return	Number of printed characters
 */
int		ft_putendl_fd(char *s, int fd);

/**
 * @brief	Sends the number `n` to the specified file descriptor
 * 
 * @param n		The number to send
 * @param fd	The file descriptor to write about
 * 
 * @return	Number of printed characters
 */
int		ft_putnbr_fd(int n, int fd);

/**
 * @brief	Sends the string `s` to the specified file descriptor
 * 
 * @param s		The string to send
 * @param fd	The file descriptor to write about
 * 
 * @return	Number of printed characters
 */
int		ft_putstr_fd(char *s, int fd);

/**
 * @brief	Reserve an array of strings resulting from separating the string
 *			`s` into substrings using the character `c` as a delimiter. The
 *			array must be terminated with a NULL pointer.
 * 
 * @param s	The string to separate
 * @param c	The delimiter character
 * 
 * @return	The array of new strings resulting from the separation, or NULL
 *			if memory reservation fails.
 */
char	**ft_split(char const *s, char c);

/**
 * @brief	Find a character in a string
 * 
 * @param str	A null-terminated string
 * @param c		Character to be located
 * 
 * @return	A pointer to the first ocurrence of `c` in `str`,
 *			or NULL if `c` isn't found
 */
char	*ft_strchr(const char *str, int c);

/**
 * @brief	Duplicates a string
 * 
 * @param s	A null-terminated string
 * 
 * @return	A pointer to  the copied string, or NULL if stoerage can't
 *			be allocated
 */
char	*ft_strdup(const char *s);

/**
 * @brief	To each character of the string `s`, apply the function `f` giving
 *			as parameters the index of each character within `s` and the
 *			address of the character itself, which can be modified if necessary
 * 
 * @param s	The string to iterate
 * @param f	The function to apply on each character
 */
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

/**
 * @brief	Reserves memory and returns a string by concatenating `s1` and `s2`
 * 
 * @param s1	The first string
 * @param s2	The string to add to `s1`
 * 
 * @return	The new string, or NULL if there is no memory. Memory must be freed
 */
char	*ft_strjoin(char const *s1, char const *s2);

/**
 * @brief	Concatenates strings
 * 
 * @param dst		The destination array
 * @param src		The string to concatenate
 * @param dstsize	The number of characters
 * 
 * @return	The total length of the string tried to create
 */
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);

/**
 * @brief	Copy strings
 * 
 * @param dst	The destination string
 * @param src	The source string
 * @param size	The number of characters
 * 
 * @return	The total length of the string tried to create (length of `src`)
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

/**
 * @brief	Get the length of a string
 * 
 * @param str	A null-terminates string
 * 
 * @return	The length of the string
 */
size_t	ft_strlen(const char *str);

/**
 * @brief	To each character of the string `s`, apply the function `f` giving
 *			as parameters the index of each character within `s` and the
 *			character itself. Generates a new string with the result of
 *			successive use of `f`
 * 
 * @param s	The string to iterate
 * @param f	The function to apply on each character
 * 
 * @return	The string created after the correct use of `f` over each
 *			character, or NULL if memory reservation fails
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/**
 * @brief	Compares up to the specified count of characters of two strings
 * 
 * @param str1	First string to compare
 * @param str2	Second string to compare
 * @param n		Number of characters to compare
 * 
 * @return	If the strings are equal, return 0. Otherwise: if the return
 *			is greater than 0, the first string is greater; If it is smaller,
 *			the second is the larger.
 */
int		ft_strncmp(const char *str1, const char *str2, size_t n);

/**
 * @brief	Locates the first ocurrence of `little` in the string `big`,
 *			where not more than `len` characters are searched
 * 
 * @param big		The destination string, null-terminated
 * @param little	The soruce string, null-terminated
 * @param len		Max count of characters searched
 * 
 * @return	If `little` is empty, `big` is returned; if `little` occurs nowhere
 *			in `big`, NULL is returned; otherwise, a pointer to the first
 *			character of the first occurrence of `little` in `big` is returned
 */
char	*ft_strnstr(const char *big, const char *little, size_t len);

/**
 * @brief	Scans a string for the last ocurrence of a character
 * 
 * @param str	A null-terminated string to search
 * @param c		Character to be located
 * 
 * @return	A pointer to the last ocurrence of `c` in `str`,
 *			or NULL if `c` isn't found
 */
char	*ft_strrchr(const char *str, int c);

/**
 * @brief	Remove all characters from the string `set` from the beginning and
 *			rom the end of `s1`, until find a character not belonging to `set`.
 *			The string is returned with memory reservation.
 * 
 * @param s1	The string that should be trimmed
 * @param set	The characters to remove from the string `s1`
 * 
 * @return	The trimmed string; NULL if memory reservation fails
 */
char	*ft_strtrim(char const *s1, char const *set);

/**
 * @brief	Allocate memory and return a substring of the string `s`.
 *			The substring starts from index `start` and. has a maximum
 *			length `len`.
 * 
 * @param s		The source string, null-terminated
 * @param start	The position in which the substrig starts
 * @param len	The final length of the substring
 * 
 * @return	A pointer to the substring, or NULL if there is no memory.
 *			Memory must be freed
 */
char	*ft_substr(char const *s, unsigned int start, size_t len);

/**
 * @brief	Convert character to lowercase
 * 
 * @param c	Character to convert
 * 
 * @return	If the character is a uppercase letter, it returns it in lowercase
 */
int		ft_tolower(int c);

/**
 * @brief	Convert character to uppercase
 * 
 * @param c	Character to convert
 * 
 * @return	If the character is a lowercase letter, it returns it in uppercase
 */
int		ft_toupper(int c);

/******************
*                 * 
*      BONUS      *
*                 *
*******************/

/**
 * @brief	Add the `new` node to the end of the `lst` list.
 * 
 * @param lst	The pointer to the first node in a list
 * @param new	The pointer to a node to add to the list
 */
void	ft_lstadd_back(t_list **lst, t_list *new);

/**
 * @brief	Add the `new` node to the beginning of the `lst` list.
 * 
 * @param lst	The address of a pointer to the first node in a list.
 * @param new	A pointer to the node to add to the beginning of the list.
 */
void	ft_lstadd_front(t_list **lst, t_list *new);

/**
 * @brief	Removes and frees the given `lst` node and all consecutive
 *			nodes of that node, using the `del` function.
 *			At the end, the pointer to the list must be NULL.
 * 
 * @param lst	The address of a pointer to a node
 * @param del	A function pointer used to remove the contents of a node
 */
void	ft_lstclear(t_list **lst, void (*del)(void*));

/**
 * @brief	It takes as a parameter a node `lst` and frees the memory
 *			of the content using the `del` function given as a parameter,
 *			in addition to freeing the node. The `next` memory must not be
 *			freed.
 * 
 * @param lst	The node to release
 * @param del	A pointer to the function used to free
 *				the contents of the node
 */
void	ft_lstdelone(t_list *lst, void (*del)(void*));

/**
 * @brief	Iterate the `lst` list and apply the `f` function on the
 *			content of each node
 * 
 * @param lst	A pointer to the first node
 * @param f		A pointer to the function used by each node
 */
void	ft_lstiter(t_list *lst, void (*f)(void *));

/**
 * @brief	Returns the last node in the list.
 * 
 * @param lst	The beginning of the list
 * 
 * @return	The last node in the list.
 */
t_list	*ft_lstlast(t_list *lst);

/**
 * @brief	Iterates through the `lst` list and applies the `f` function to the
 *			contents of each node. Create a list resulting from the correct and
 *			successive application of the function `f` on each node. The `del`
 *			function is used to remove the contents of a node, if necessary.
 * 
 * @param lst	A pointer to a node
 * @param f		The address of a pointer to a function used to iterate through
 *				each element of the list
 * @param del	A function pointer used to remove the contents of
 *				a node, if necessary
 * 
 * @return
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/**
 * @brief	Create a new node reserving memory. The member variable `content`
 *			is initialized with the content of the parameter `content`. The
 *			`next` variable, with NULL.
 * 
 * @param content	The content with which to create the node
 * 
 * @return	The new node
 */
t_list	*ft_lstnew(void *content);

/**
 * @brief	Counts the number of nodes in a list.
 * 
 * @param lst	The beginning of the list
 * 
 * @return	The length of the list
 */
int		ft_lstsize(t_list *lst);

/************************************
*                                   *
*      GET_NEXT_LINE FUNCTIONS      *
*                                   *
*************************************/

size_t	gnl_strlen(char *str);
char	*gnl_cpy(char *data);
int		gnl_find_ch(char *data, char ch);
void	*gnl_free(void **memory);
char	*add_line(char *data, char *add);

/**
 * @brief	It reads a line from a file, represented by a file descriptor
 * 
 * @param fd	The file descriptor of the file
 * 
 * @return	The line readed (allocated with a malloc),
 *			or NULL if the file dont have more lines or in case of error
 */
char	*get_next_line(int fd);

/******************************
*                             *
*      PERSONAL FUNCIONS      *
*                             *
*******************************/

/**
 * @brief	It converts a string to integer. If there is a strange character,
 * 			the conversion stops and the `flag` get a negative value
 * 
 * @param str	The string to be converted
 * @param flag	A pinter to the flag
 * 
 * @return	The int value produced by interpreting the input characters
 *			as a number
 */
int		ft_strict_atoi(const char *str, int *flag);

/**
 * @brief	It compares 2 strings.
 * 
 * @param s1	The first string
 * @param s2	The second string
 * 
 * @return	0 if two strings are equal, a positive number if the first is
 * 			greater, or negative number if the second is greater
 */
int		ft_strcmp(const char *s1, const char *s2);

void	*free_split(char **spl);

#endif