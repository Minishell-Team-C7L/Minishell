int ft_skip_white_spaces(char *line)
{
	int i;
	int j;

	i  = 0;
	j = 0;
	if (!line)
		return 0;
	while (line[i])
	{
		if (line[i] > 32)
			j++;
		else if ((line[i] > 0 && line[i] <= 32) && line[i +1] > 32)
			j++;
		else if (line[i] > 32 && line[i +1] > 0 && line[i +1] <= 32)
			j++;
		i++;
	}
	return (j - 1);
}

#include <stdio.h>
int main()
{
	char line[70] = "     	e    w    hld							sodjkwj  		   kjjdsd  	   sdew      ";
	printf("%d", ft_skip_white_spaces(line));
}
