#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*get_next_line(int fd);
size_t	str_len(const char *s);
char	*str_join(char *remainder, char *buffer);
char	check_newline_char(char *remainder);
char	*free_buffer(char **buffer);

#endif
