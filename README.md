# char	*get_next_line(int fd)
A function that lets you read the text file pointed to by the file descriptor, one line at a time.

This function should work with any buffer size. You will need to set the buffer size at compile time like this:

```cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c tests.c```

The function uses a static array of cache strings to allow the function to work with up to 256 unique file descriptors without losing its place in any file.

# Return Values
This function should return the next line of the file, if successful.
If a read fails or there are memory allocation errors, it will return NULL.
