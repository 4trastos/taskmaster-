#include "taskmaster.h"

char	*ft_strchr(char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i] + 1);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_strjoin(char *board, char *buffer)
{
	size_t	i;
	size_t	z;
	char	*board_dir;

	if (ft_strlen(buffer) == 0)
		return (board);
	board_dir = malloc((ft_strlen(board) + ft_strlen(buffer) + 1));
	if (!board_dir)
	{
		free(board_dir);
		free(board);
		return (NULL);
	}
	i = -1;
	while (board[++i] != '\0')
		board_dir[i] = board[i];
	z = 0;
	while (buffer[z] != '\0')
		board_dir[i++] = buffer[z++];
	board_dir[i] = '\0';
	return (board_dir);
}

char	*ft_strdup(char *s1)
{
	int		i;
	int		len;
	char	*s2;

	if (!s1)
		return (NULL);
	i = 0;
	len = ft_strlen(s1);
	s2 = malloc(len + 1);
	if (!s2)
	{
		free(s2);
		return (NULL);
	}
	while (s1[i] != '\0')
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}