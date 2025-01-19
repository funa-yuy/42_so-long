#include <stdlib.h>

void	str_malloc(char **str)
{
	if(!str || !*str)
		exit(1);
	*str = malloc(10);
	if (*str == NULL)
		exit(1);

}

int main()
{
	char *str;

	str_malloc(&str);
	// ...
}
