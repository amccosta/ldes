#include <stdlib.h>
#include <stdio.h>

main()
{
	float data[6];

	while (!feof(stdin) && !ferror(stdin))
	{
		if (fread(data, sizeof(float), 6, stdin)!=6) exit(1);
		printf("%g %g %g %g %g %g\n",
			data[0], data[1], data[2], data[3], data[4], data[5]);
	}
	exit(0);
}
