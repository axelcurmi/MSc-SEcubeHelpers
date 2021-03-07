#include <stdio.h>
#include <stdlib.h>

#include "SEcubeSources/L1/L1.h"

static uint8_t pin_admin[32] = {
    't', 'e', 's', 't', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int main()
{
    printf("SEcube Digest Example\n");
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

    uint8_t dataIn[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    size_t dataInLen = 10;

    uint8_t dataOut[256] = {0};
    uint16_t dataOutLen = 0;

    l1.L1CryptoSetTime(time(0));

    uint32_t sessionId = -1;
    l1.L1CryptoInit(L1Algorithms::Algorithms::SHA256,0, 2000, &sessionId);
    printf("Session ID: %d\n", sessionId);

    try {
        l1.L1CryptoUpdate(sessionId, L1Crypto::UpdateFlags::FINIT, 0, NULL,
            dataInLen, dataIn, &dataOutLen, dataOut);
    }
    catch(...)
    {
        printf("Exception...\n");
    }

    printf("Data Out Len: %d\n", dataOutLen);
    for (uint32_t i = 0; i < dataOutLen; i++)
    {
        printf("[%d] %x\n", i, dataOut[i]);
    }

    l1.L1Logout();
    l0.L0Close();

    return EXIT_SUCCESS;
}
