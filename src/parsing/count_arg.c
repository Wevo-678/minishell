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

/* cf count_cmd */
void	count_cmd2(char *input, int *i, int *new_cmd, int *count)
{
	if (*new_cmd && input[*i] != '<' && input[*i] != '>')
	{
		(*count)++;
		*new_cmd = 0;
	}
	if (input[*i] == '<' || input[*i] == '>')
	{
		if (input[*i + 1] == '<' || input[*i + 1] == '>')
			(*i)++;
		*new_cmd = 1;
		(*count)++;
	}
}

/* Count the number of commands/options/redir */
/* Return this number */
int	count_cmd(char *input)
{
	int	i;
	int	count;
	int new_cmd;

	i = 0;
	count = 0;
	new_cmd = 1;
	while (input[i])
	{
		if (input[i] == ' ')
		{
			while (input[i + 1] == ' ')
				i++;
			new_cmd = 1;
		}
		else
			count_cmd2(input, &i, &new_cmd, &count);
		i++;
	}
	return (count);
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
					return (-2);
				else
					return (-1);
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

/*
int	main(int argc, char **argv)
{
	printf("string : %s\n", argv[1]);
	printf("count : %d\n", count_cmd(argv[1]));
	return (0);
}*/