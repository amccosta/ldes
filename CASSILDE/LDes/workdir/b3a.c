#include <stdlib.h>
#include <stdio.h>

main()
{
	float data[3];

	while (!feof(stdin) && !ferror(stdin))
	{
		if (fread(data, sizeof(float), 3, stdin)!=3) exit(1);
		printf("%g %g %g\n",
			data[0], data[1], data[2]);
	}
	exit(0);
}
