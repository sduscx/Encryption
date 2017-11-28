#include"tomcrypt.h"
#include<iostream>
#include<tchar.h>
#include <functional>
using namespace std;
/*
	注册方法，注册加密的方法，如des\aes等
*/
int regis(int Method) {
	if (Method == 1) {
		//aes
		if (register_cipher(&aes_desc) == -1) {
			printf("failed to register_cipher");
			return -1;
		}
	}
	else if (Method == 2) {
		//des
		if (register_cipher(&des_desc) == -1) {
			printf("failed to register_cipher");
			return -1;
		}
	}
	//成功
	return 1;
}

/*
	形成密文和解密文的文件名
*/
char* deal_fileName(char *deal_name,int type,char *pn) {
	int last = 0;
	for (; pn[last] != '\0'; last++);
	int dotlocation = last;
	for (; pn[dotlocation] != '.'; dotlocation--);
	if (type == 1) {
		int i = 0;
		for (; i < last; i++) {
			deal_name[i] = pn[i];
		}
		deal_name[i++] = '.';
		deal_name[i++] = 'c';
		deal_name[i++] = 'r';
		deal_name[i++] = 'y';
		deal_name[i++] = 'p';
		deal_name[i++] = 't';
		deal_name[i++] = '\0';
	}
	else if (type == 2) {
		int i = 0;
		for (; i < dotlocation; i++) {
			deal_name[i] = pn[i];
		}
	}
	return deal_name;
}
void generateRandomKey(unsigned char *mykey,unsigned char *key) {
	srand((unsigned)time(NULL));
	int b = -1;
	for (b = 0; key[b] != '\0';b++);
	int index = (rand() % b);
	for (int i = 0; i < b-index; i++) {
		mykey[i] = key[index+i];
	}
	for (int i = 0; i < index; i++) {
		mykey[i+ b - index] = key[i];
	}
	mykey[b] = '\0';
}
int main() {

	cout << "Welcome to use the program\n";
	int type = -1;//加密1 解密2
	int method = 0;//aes des
	int mode = 0;//cbc,ofb,cfb,ctr
	//加解密文件名
	char crypt_name[100] = "", plain_name[100] = "", decrypt_name[100] = "";
	char *Method[] = {"aes","des"};
	char *Mode[] = {"CBC","OFB","CFB","CTR"};
	int BlockSize[2] = {16,8};
	int keySize[2] = {16,7};
	int error = 0;//返回值
	int cipher = 0;//加解密索引
	
	unsigned char key[16] = "scx199702scx199";
	const unsigned char IV[16] = "oTvdDgf3mSab7Lv";//初始向量
	FILE *plaintText = 0, *cryptText = 0, *decryptText = 0;
	
	symmetric_CBC cbc = { 0 };
	symmetric_OFB ofb = { 0 };
	symmetric_CFB cfb = { 0 };
	symmetric_CTR ctr = { 0 };

	size_t len = 0;

	cout << "would you like to cyprt or decrypt?1 to crypt,2 to decrypt\n";
	cin >> type;

	int MethodLen = sizeof(Method) / sizeof(Method[0]);
	int ModeLen = sizeof(Mode) / sizeof(Mode[0]);

	for (int i = 0; i < MethodLen; i++) {
		cout << i + 1 << "\t" << Method[i] << "\n";
	}
	cout << "please choose one method:\n";
	cin >> method;
	
	unsigned char ct[16] = "";
	unsigned char pt[16] = "";

	for (int i = 0; i < ModeLen; i++) {
		cout << i + 1 << "\t" <<Mode[i] << "\n";
	}
	cout << "please choose one mode:\n";
	cin >> mode;

	cout << "please input the location of the file:\n";
	cin >> plain_name;
	if (type == 1) {
		 deal_fileName(&crypt_name[0],type,plain_name);
	}
	else if (type == 2) {
		 deal_fileName(&decrypt_name[0], type,plain_name);
	}
	
	//cout << "please input the key:(the key length use 8)\n";
	//cin >> key;//双方事先约定的口令，如scx199702
	/*cout << "please input the IV:\n";
	cin >> IV;*/
	//deal the key
	
	unsigned char mykey[16];
	


	//注册加密方法
	if (regis(method) == -1) {
		return -1;
	}
	cipher = find_cipher(Method[method-1]);

	if (cipher == -1) {
		printf("find_cipher error");
		goto Del;
	}
	switch (mode)
	{
	case 1:
		error = cbc_start(cipher,IV,mykey,keySize[method-1],0,&cbc);
		break;
	case 2:
		error = ofb_start(cipher, IV, mykey, keySize[method - 1], 0, &ofb);
		break;
	case 3:
		error = cfb_start(cipher, IV, mykey, keySize[method - 1], 0, &cfb);
		break;
	case 4:
		error = ctr_start(cipher, IV, mykey, keySize[method - 1], 0,0, &ctr);
		break;
	default:
		break;
	}
	if (error!=CRYPT_OK) {
		printf("failed to start", error_to_string(error));
		goto Del;
	}

	if (type == 1) {
		generateRandomKey(&mykey[0], key);
		//加密
		fopen_s(&plaintText, plain_name, "rb");
		fopen_s(&cryptText, crypt_name, "wb");
		////加密密钥
		switch (mode)
		{
		case 1:
			error = cbc_start(cipher, IV, key, keySize[method - 1], 0, &cbc);
			break;
		case 2:
			error = ofb_start(cipher, IV, key, keySize[method - 1], 0, &ofb);
			break;
		case 3:
			error = cfb_start(cipher, IV, key, keySize[method - 1], 0, &cfb);
			break;
		case 4:
			error = ctr_start(cipher, IV, key, keySize[method - 1], 0, 0, &ctr);
			break;
		default:
			break;
		}
		if (error != CRYPT_OK) {
			printf("failed to start", error_to_string(error));
			goto Del;
		}
		switch (mode)
		{
		case 1:
			error = cbc_encrypt(mykey, ct, 16, &cbc);
			break;
		case 2:
			error = ofb_encrypt(mykey, ct, 16, &ofb);
			break;
		case 3:
			error = cfb_encrypt(mykey, ct, 16, &cfb);
			break;
		case 4:
			error = ctr_encrypt(mykey, ct, 16, &ctr);
			break;
		default:
			break;
		}
		if (error != CRYPT_OK) {
			printf("failed to crypt key", error_to_string(error));
		}
		fwrite(ct, sizeof(ct[0]), 16, cryptText);
		//加密明文
		switch (mode)
		{
		case 1:
			cbc_done(&cbc);
			error = cbc_start(cipher, IV, mykey, keySize[method - 1], 0, &cbc);
			break;
		case 2:
			error = ofb_start(cipher, IV, mykey, keySize[method - 1], 0, &ofb);
			break;
		case 3:
			error = cfb_start(cipher, IV, mykey, keySize[method - 1], 0, &cfb);
			break;
		case 4:
			error = ctr_start(cipher, IV, mykey, keySize[method - 1], 0, 0, &ctr);
			break;
		default:
			break;
		}
		if (error != CRYPT_OK) {
			printf("failed to start", error_to_string(error));
			goto Del;
		}
		
		fseek(plaintText, 0L, SEEK_END);
		long end = ftell(plaintText);
		fseek(plaintText, 0L, SEEK_SET);
		long start = ftell(plaintText);

		while (start!=end) {
			memset(pt,0,BlockSize[method-1]);
			memset(ct, 0, BlockSize[method - 1]);
			
			len = fread(pt, sizeof(pt[0]), BlockSize[method-1], plaintText);
			start = ftell(plaintText);
			if (len < 1) {
				break;
			}
			switch (mode)
			{
			case 1:
				error = cbc_encrypt(pt,ct,16,&cbc);
				break;
			case 2:
				error = ofb_encrypt(pt, ct, 16, &ofb);
				break;
			case 3:
				error = cfb_encrypt(pt, ct, 16, &cfb);
				break;
			case 4:
				error = ctr_encrypt(pt, ct, 16, &ctr);
				break;
			default:
				break;
			}
			fwrite(ct,sizeof(ct[0]),16,cryptText);
		}
		printf("Success Crypt");
		fclose(plaintText);
		fclose(cryptText);
		goto Del;
	}
	else if (type == 2) {
		//解密
		fopen_s(&decryptText, decrypt_name, "wb");
		fopen_s(&cryptText, plain_name, "rb");
		////解密密钥
		switch (mode)
		{
		case 1:
			error = cbc_start(cipher, IV, key, keySize[method - 1], 0, &cbc);
			break;
		case 2:
			error = ofb_start(cipher, IV, key, keySize[method - 1], 0, &ofb);
			break;
		case 3:
			error = cfb_start(cipher, IV, key, keySize[method - 1], 0, &cfb);
			break;
		case 4:
			error = ctr_start(cipher, IV, key, keySize[method - 1], 0, 0, &ctr);
			break;
		default:
			break;
		}
		bool first = true;
		fseek(cryptText, 0L, SEEK_END);
		long end = ftell(cryptText);
		fseek(cryptText, 0L, SEEK_SET);
		long start = ftell(cryptText);
		while (!feof(cryptText)) {
			memset(pt, 0, sizeof(pt));
			memset(ct, 0, sizeof(ct));
			
			len = fread(ct, sizeof(ct[0]), BlockSize[method - 1], cryptText);
			
			//start = ftell(cryptText);
			if (len < 1) {
				break;
			}
			switch (mode)
			{
			case 1:
				error = cbc_decrypt(ct, pt, 16, &cbc);
				break;
			case 2:
				error = ofb_decrypt(ct, pt, 16, &ofb);
				break;
			case 3:
				error = cfb_decrypt(ct, pt, 16, &cfb);
				break;
			case 4:
				error = ctr_decrypt(ct, pt, 16, &ctr);
				break;
			default:
				break;
			}
			if (error != CRYPT_OK) {
				printf("failed to decrypt", error_to_string(error));
				break;
			}
			//cout << pt<<"\n";
			//fwrite(pt, sizeof(pt[0]), 16, decryptText);
			if (first) {
				first = false;
				switch (mode)
				{
				case 1:
					error = cbc_start(cipher, IV, pt, keySize[method - 1], 0, &cbc);
					break;
				case 2:
					error = ofb_start(cipher, IV, pt, keySize[method - 1], 0, &ofb);
					break;
				case 3:
					error = cfb_start(cipher, IV, pt, keySize[method - 1], 0, &cfb);
					break;
				case 4:
					error = ctr_start(cipher, IV, pt, keySize[method - 1], 0, 0, &ctr);
					break;
				default:
					break;
				}
			}
			else {
				fwrite(pt, sizeof(pt[0]), 16, decryptText);
			}
			
		}
		printf("Success decrypt");
		fclose(decryptText);
		fclose(cryptText);
		goto Del;
	}

Del:
	switch (mode)
	{
	case 1:
		cbc_done(&cbc);
		break;
	case 2:
		ofb_done(&ofb);
		break;
	case 3:
		cfb_done(&cfb);
		break;
	case 4:
		ctr_done(&ctr);
		break;
	default:
		break;
	}
	switch (method)
	{
	case 1:
		error = unregister_cipher(&aes_desc);
		break;
	case 2:
		error = unregister_cipher(&des_desc);
		break;
	default:
		break;
	}
	if (error != CRYPT_OK) {
		printf(("unregister error"));
		return -1;
	}
	return 0;
}
