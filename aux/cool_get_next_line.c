#include "../incl/taskmaster.h"

char	*ft_new_line(char *board)
{
	char	*new_line;

	if (!board)
		return (NULL);
	if (!ft_strchr(board, '\n'))
	{
		free(board);
		return (NULL);
	}
	new_line = ft_strchr(board, '\n');
	new_line = ft_strdup(new_line);
	free(board);
	return (new_line);
}

char	*ft_line(char *board)
{
	char	*ln;
	int		i;

	i = 0;
	if (!board[i])
		return (NULL);
	if (!ft_strchr(board, '\n'))
		ln = ft_strdup(board);
	else
	{
		ln = malloc(ft_strchr(board, '\n') - board + 1);
		if (!ln)
			return (NULL);
		while (board[i] != '\n')
		{
			ln[i] = board[i];
			i++;
		}
		ln[i] = board[i];
		ln[i + 1] = '\0';
	}
	return (ln);
}

char	*ft_read(int fd, char *board, int	*bytes_read)
{
	char	*buffer;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (0);
	while (board && !ft_strchr(board, '\n') && *bytes_read > 0)
	{
		*bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (*bytes_read == -1)
		{
			free(buffer);
			free(board);
			return (0);
		}
		buffer[*bytes_read] = '\0';
		board = ft_strjoin(board, buffer);
	}
	free(buffer);
	return (board);
}

int	get_next_line(int fd, char **line)
{
	static char	*board;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (0);
	if (!board)
	{
		board = malloc(1);
		if (!board)
		{
			free(board);
			return (0);
		}
		board[0] = '\0';
	}
	bytes_read = 1;
	board = ft_read(fd, board, &bytes_read);
	if (!board)
		return (0);
	*line = ft_line(board);
	board = ft_new_line(board);
	if (bytes_read == 0 && !board)
		return (0);
	return (1);
}