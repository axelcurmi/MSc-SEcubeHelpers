#include <stdio.h>
#include <stdlib.h>

#include "SEcubeSources/L0/L0.h"

int main()
{
    printf("SEcube L0 - Hello\n");

    L0 l0 = L0();
	if (l0.GetNumberDevices() == 0)
	{
		printf("No Devices connected!\n");
		return EXIT_FAILURE;
	}

    printf("%s\n", l0.GetDeviceHelloMsg());
    return EXIT_SUCCESS;
}