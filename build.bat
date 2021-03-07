g++ -O0 -g3 -fPIC -Wall -c -o obj\L0_base.o SEcubeSources\L0\L0Base\L0_base.cpp
g++ -O0 -g3 -fPIC -Wall -c -o obj\L0_commodities.o SEcubeSources\L0\L0_commodities.cpp
g++ -O0 -g3 -fPIC -Wall -c -o obj\L0_communication.o SEcubeSources\L0\L0_communication.cpp
g++ -O0 -g3 -fPIC -Wall -c -o obj\L0_provision.o SEcubeSources\L0\L0_provision.cpp
g++ -O0 -g3 -fPIC -Wall -c -o obj\L0.o SEcubeSources\L0\L0.cpp

g++ -O3 -g3 -fPIC -Wall -c -o obj\aes256.o SEcubeSources\L1\CryptoLibraries\aes256.cpp
gcc -O3 -g3 -fPIC -Wall -c -o obj\sha256.o SEcubeSources\L1\CryptoLibraries\sha256.c
gcc -O3 -g3 -fPIC -Wall -c -o obj\pbkdf2.o SEcubeSources\L1\CryptoLibraries\pbkdf2.c

g++ -O3 -g3 -fPIC -Wall -c -o obj\L1_base.o SEcubeSources\L1\L1Base\L1_base.cpp
g++ -O3 -g3 -fPIC -Wall -c -o obj\L1_login_logout.o SEcubeSources\L1\L1_login_logout.cpp
g++ -O3 -g3 -fPIC -Wall -c -o obj\L1_security.o SEcubeSources\L1\L1_security.cpp
g++ -O3 -g3 -fPIC -Wall -c -o obj\L1.o SEcubeSources\L1\L1.cpp

g++ -O0 -g3 -fPIC -Wall -c -o obj\L0_hello.o L0_hello.cpp
g++ -O0 -g3 -fPIC -Wall -c -o obj\L1_addkey.o L1_addkey.cpp
g++ -O0 -g3 -fPIC -Wall -c -o obj\L1_getkeys.o L1_getkeys.cpp
g++ -O0 -g3 -fPIC -Wall -c -o obj\digest_example.o digest_example.cpp
g++ -O0 -g3 -fPIC -Wall -c -o obj\encrypt_decrypt_example.o encrypt_decrypt_example.cpp

g++ -o bin/L0_hello.exe ^
    obj\L0.o ^
    obj\L0_commodities.o ^
    obj\L0_communication.o ^
    obj\L0_provision.o ^
    obj\L0_base.o ^
    obj\L0_hello.o

g++ -o bin/L1_addkey.exe ^
    obj\L0.o ^
    obj\L0_commodities.o ^
    obj\L0_communication.o ^
    obj\L0_provision.o ^
    obj\L0_base.o ^
    obj\aes256.o ^
    obj\sha256.o ^
    obj\pbkdf2.o ^
    obj\L1_base.o ^
    obj\L1_login_logout.o ^
    obj\L1_security.o ^
    obj\L1.o ^
    obj\L1_addkey.o

g++ -o bin/L1_getkeys.exe ^
    obj\L0.o ^
    obj\L0_commodities.o ^
    obj\L0_communication.o ^
    obj\L0_provision.o ^
    obj\L0_base.o ^
    obj\aes256.o ^
    obj\sha256.o ^
    obj\pbkdf2.o ^
    obj\L1_base.o ^
    obj\L1_login_logout.o ^
    obj\L1_security.o ^
    obj\L1.o ^
    obj\L1_getkeys.o

g++ -o bin/digest_example.exe ^
    obj\L0.o ^
    obj\L0_commodities.o ^
    obj\L0_communication.o ^
    obj\L0_provision.o ^
    obj\L0_base.o ^
    obj\aes256.o ^
    obj\sha256.o ^
    obj\pbkdf2.o ^
    obj\L1_base.o ^
    obj\L1_login_logout.o ^
    obj\L1_security.o ^
    obj\L1.o ^
    obj\digest_example.o

g++ -o bin/encrypt_decrypt_example.exe ^
    obj\L0.o ^
    obj\L0_commodities.o ^
    obj\L0_communication.o ^
    obj\L0_provision.o ^
    obj\L0_base.o ^
    obj\aes256.o ^
    obj\sha256.o ^
    obj\pbkdf2.o ^
    obj\L1_base.o ^
    obj\L1_login_logout.o ^
    obj\L1_security.o ^
    obj\L1.o ^
    obj\encrypt_decrypt_example.o
