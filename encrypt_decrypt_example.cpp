 #include <iostream>
 #include <stdlib.h>
 #include <stdio.h>

 #include "SEcubeSources/L1/L1.h"

 using namespace std;

 static uint8_t pin_user[32] = {
     't','e','s','t', 0,0,0,0, 0,0,0,0, 0,0,0,0,
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0
 };

 uint16_t encSize(uint16_t plain_size)
 {
     return (((plain_size/L1Parameters::Size::CRYPTO_BLOCK)+1)*L1Parameters::Size::CRYPTO_BLOCK);
 }

 int main()
 {
	 string strTest = "testtesttest";
	 uint16_t strLen = strTest.length();

	 L0 l0 = L0(); // low level SEcube object
     uint8_t numDevices = l0.GetNumberDevices(); // how many SEcube devices are currently connected to the host machine
     if(numDevices==0){
         cout << "No Devices connected!" << endl;
         return -1;
     }

     L1 l1 = L1(); // high level SEcube object
     try{
    	 l1.L1Login(pin_user, SE3_ACCESS_USER, true);// login to the SEcube as user with the pin of the user, force logout if currently the SEcube already has an active session
     } catch(...){
    	 cout << "Login failed!" << endl;
    	 return -1;
     }
     cout << "Login ok!" << endl;
     cout << endl;

     // Now we try to encrypt a payload
     uint32_t keyIdChoosen = 2000;
     uint32_t sessionId;
     uint8_t *buffer;
 	 unique_ptr<uint8_t[]> enc_buffer;
 	 unique_ptr<uint8_t[]> dec_buffer;
 	 uint16_t buffer_len = 0;
 	 uint16_t enc_buffer_len = 0;
 	 uint16_t dec_buffer_len = 0;

     l1.L1CryptoSetTime((uint32_t)time(0)); // this must be called at least one time before doing the first encryption/decryption operation after the login to the SEcube

 	 // now we setup the parameters we want to use for encryption: AES algorithm and ECB mode. We specify also the key that we want to use.
     l1.L1CryptoInit(L1Algorithms::Algorithms::AES, CryptoInitialisation::Mode::ENCRYPT | CryptoInitialisation::Feedback::ECB , keyIdChoosen, &sessionId);

     buffer_len = strLen;
     printf("buffer len plain -> %d\n", buffer_len);
     vector<uint8_t> myVector(strTest.begin(), strTest.end());
 	 buffer = &myVector[0];
 	 cout << "buffer plain -> " << strTest << endl;
 	 cout << "buffer plain (hex value) -> ";
 	 for(int n=0; n<strTest.length(); n++){
 		 printf("%02x ", strTest.at(n));
 	 }
 	 cout << endl;
 	 enc_buffer = make_unique<uint8_t[]>(encSize(buffer_len)*sizeof(uint8_t));
 	 memset(enc_buffer.get(), '\0', encSize(buffer_len)*sizeof(uint8_t));

 	 // with the L1CryptoUpdate we iterate over the plaintext until it is completely encrypted (FINIT flag is used to finalize the encryption)
 	 l1.L1CryptoUpdate(sessionId, CryptoInitialisation::Mode::ENCRYPT | CryptoInitialisation::Feedback::ECB | L1Crypto::UpdateFlags::FINIT, 0, NULL, encSize(buffer_len), buffer, &enc_buffer_len, enc_buffer.get());

 	 if(enc_buffer_len != (encSize(buffer_len)*sizeof(uint8_t))){
 		 cout << "Error, the length of the ciphertext does not correspond to the expected value." << endl;
 		 return -1;
 	 }

 	 cout<< "buffer len enc -> " << enc_buffer_len << endl;
 	 string encrypted((char*)enc_buffer.get(), enc_buffer_len);
 	 cout << "buffer enc -> " << encrypted << endl;
 	 cout << "buffer enc (hex value) -> ";
 	 for(int n=0; n<enc_buffer_len; n++){
 		 printf("%02x ", enc_buffer[n]);
 	 }
 	 cout << endl;

 	 //Decryption
 	 dec_buffer = make_unique<uint8_t[]>(encSize(buffer_len)*sizeof(uint8_t));
 	 memset(dec_buffer.get(), '\0', encSize(buffer_len)*sizeof(uint8_t));
 	 l1.L1CryptoInit(L1Algorithms::Algorithms::AES, CryptoInitialisation::Mode::DECRYPT | CryptoInitialisation::Feedback::ECB, keyIdChoosen, &sessionId);
 	 l1.L1CryptoUpdate(sessionId, CryptoInitialisation::Mode::DECRYPT | CryptoInitialisation::Feedback::ECB | L1Crypto::UpdateFlags::FINIT, 0, NULL, enc_buffer_len, enc_buffer.get(), &dec_buffer_len, dec_buffer.get());

 	 if(dec_buffer_len != (encSize(buffer_len)*sizeof(uint8_t))){
 		 cout << "Error, the length of the plaintext does not correspond to the expected value." << endl;
 		 return -1;
 	 }

 	 cout << "buffer len dec -> " << dec_buffer_len << endl;
 	 string decrypted((char*)dec_buffer.get(), dec_buffer_len);
 	 cout << "buffer dec -> " << decrypted << endl;
 	 cout << "buffer dec (hex value) -> ";
 	 for(int n=0; n<encSize(buffer_len); n++){ // we use here enc_buffer_len because we only want to compare the firt N bytes where N is the size of the original plaintext
 		 printf("%02x ", dec_buffer[n]);
 	 }
 	 cout << endl;

     if (memcmp(buffer, dec_buffer.get(), buffer_len) == 0) {
         cout << "Data match! Notice that trailing zeros are not considered since the decrypted value is checked against the original plaintext only for a number"
        		 " of bytes which is equal to the size of the original plaintext." << endl;
     }
     else {
         cout << "Error, data DO NOT match" << endl;
     }

     l1.L1Logout();
     cout << "Logout ok!" << endl;
     return 0;
 }
