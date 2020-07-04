#ifndef AES_H_
#define AES_H_
#include "aes__internal.h"

enum class AESPadding : int{
    PKCS_7,
    AvailablePaddingSchemes,
};

template<int keySize>
void aes_encrypt_block(char *pInput128Bytes, char *pOutput128Bytes, char *pKey){
    static_assert(keySize == 128 || keySize == 192 || keySize == 256);
    
}

template<int keySize>
void aes_decrypt_block(char *pInput128Bytes, char *pOutput128Bytes, char *pKey){
    static_assert(keySize == 128 || keySize == 192 || keySize == 256);

}

#endif
