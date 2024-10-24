#include "../../includes/minishell.h"

/* Return the number of pipes in the string */
int	pipe_count(char *input)
{
	int	i;
	int	pcount;

	i = 0;
	pcount = 0;
	while (input[i])
	{
		if (input[i] == '|')
			if (!between_quotes(input, i))
				pcount++;
		i++;
	}
	return (pcount);
}

/* cmd_len condition for '>' (cf cmd_len) */
int	cmd_len2(char *input, int i, int j)
{
	if (!j)
	{
		if (input[i + j + 1] == '>')
			return (2);
		else
			return (1);
	}
	else
		return (j);
	return (j);
}

/* Return the length of the first command/option from index i */
int	cmd_len(char *input, int i)
{
	int j;

	j = 0;
	while (input[i + j])
	{
		if (input[i + j] == ' ' && !between_quotes(input, i + j))
			return (j);
		if (input[i + j] == '<' && !between_quotes(input, i + j))
		{
			if (!j)
			{
				if (input[i + j + 1] == '<')
					return (2);
				else
					return (1);
			}
			else
				return (j);
		}
		if (input[i + j] == '>' && !between_quotes(input, i + j))
			return (cmd_len2(input, i, j));
		j++;
	}
	return (j);
}
