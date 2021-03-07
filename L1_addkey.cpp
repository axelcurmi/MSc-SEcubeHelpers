#include <stdio.h>
#include <stdlib.h>

#include "SEcubeSources/L1/L1.h"

static uint8_t pin_admin[32] = {
    't', 'e', 's', 't', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// TODO: I think this is an IV; Need to confirm this.
static uint8_t key_data[32] = {
    1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4,
    1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4};

int main()
{
    printf("SEcube L1 - AddKey\n");
    printf("Searching for SEcube(s)\n");
    L0 l0 = L0();

    if (l0.GetNumberDevices() == 0)
    {
        printf("No Devices connected!\n");
        return EXIT_FAILURE;
    }
    else
    {
        printf("Device Found!\n");
    }

    L1 l1 = L1();

    printf("Logging in...\n");
    try
    {
        l1.L1Login(pin_admin, SE3_ACCESS_ADMIN, true);
    }
    catch (...)
    {
        printf("Failed to Login!\n");
        l0.L0Close();
        return EXIT_FAILURE;
    }

    // Adding Key
    se3Key key;
    strcpy((char *)key.name, "Paramiko");
    key.id = 2000;
    key.nameSize = strlen((char *)key.name);
    key.dataSize = 32;
    key.data = key_data;
    key.validity = (uint32_t)time(0) + 365 * 24 * 3600;
    l1.L1KeyEdit(&key, 1); // SE3_KEY_OP_INSERT

    printf("Key with ID(%d) added successfully!\n", key.id);

    l1.L1Logout();
    l0.L0Close();

    return EXIT_SUCCESS;
}