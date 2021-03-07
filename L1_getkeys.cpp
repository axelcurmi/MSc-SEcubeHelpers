#include <stdio.h>
#include <stdlib.h>

#include "SEcubeSources/L1/L1.h"

static uint8_t pin_admin[32] = {
    't', 'e', 's', 't', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int main()
{
    printf("SEcube L1 - GetKeys\n");
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

    // Retrieve the list of the keys (their ID, not their values) currently
    // stored on the device
    uint16_t maxKeys = 128;
    uint16_t skip = 0;
    uint16_t count;

    se3Key keyArray[maxKeys];
    l1.L1KeyList(maxKeys, skip, keyArray, &count);
    printf("Keys List:\n");
    for (uint16_t i = 0; i < count; i++)
    {
        printf("  [%d] %s\n", keyArray[i].id, keyArray[i].name);
    }

    // Retrieve the list of crypto algorithms supported by the SEcube
    uint16_t maxAlgo = 128;
    se3Algo algorithmsArray[maxAlgo];
    l1.L1GetAlgorithms(maxAlgo, skip, algorithmsArray, &count);
    printf("Algorithms List:\n");
    for (uint16_t i = 0; i < count; i++)
    {
        char name[L1Crypto::AlgorithmInfoSize::NAME_SIZE] = {0};
        strcpy(name, (char *)algorithmsArray[i].name);
        char *type;
        switch (algorithmsArray[i].type)
        {
        case L1Crypto::CryptoTypes::SE3_CRYPTO_TYPE_BLOCKCIPHER:
            type = "block cipher";
            break;
        case L1Crypto::CryptoTypes::SE3_CRYPTO_TYPE_BLOCKCIPHER_AUTH:
            type = "block cipher with authentication and integrity";
            break;
        case L1Crypto::CryptoTypes::SE3_CRYPTO_TYPE_DIGEST:
            type = "digest algorithm";
            break;
        case L1Crypto::CryptoTypes::SE3_CRYPTO_TYPE_STREAMCIPHER:
            type = "stream cipher";
            break;
        case L1Crypto::CryptoTypes::SE3_CRYPTO_TYPE_OTHER:
            type = "other type";
            break;
        default:
            type = "invalid type";
            break;
        }
        printf("  %s (%s)\n", name, type);
    }

    return EXIT_SUCCESS;
}