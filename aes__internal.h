#ifndef AES_INTERNAL_H_
#define AES_INTERNAL_H_

void aes_internal_in_place_subBytes(char *pState128Bytes);
void aes_internal_in_place_shiftRows(char *pState128Bytes);
void aes_internal_in_place_mixColumns(char *pState128Bytes);

template<int keySize>
void aes_internal_in_place_addRoundKey(char *pState128Bytes, char *pRoundKey);

template<int keySize>
void aes_internal_in_place_performRound(char *pState128Bytes, char *pRoundKey, int roundNumber);

#endif