///*
//下面的程序实现的功能：
//将字符串c1用AES方法加密放在c2中，再解密放在c3中，密钥是myKey
//*/
//
//#include "tomcrypt.h"  
////#pragma comment (lib,"tomcryptd.lib")  
//int main(int argc, char* argv[])
//{
//	unsigned char myKey[32] = "12345";// 加密密钥    
//	symmetric_key skey;// 加密状态  
//
//	aes_setup(myKey, 32, 0, &skey);// 加密前初始化状态(密钥，密钥长度，迭代次数(0: 使用推荐值)，加密状态)  
//
//
//	unsigned char c1[32] = "csdn";// 需要加密的字符串长度任意  
//	unsigned char c2[32];// 输出长度>= 输入长度，分段长度的倍数(这里就是16的倍数)      
//	printf("%s\n", c1);
//	c1[31] = '\0';			 // 分段加密，每段长度为16 (一般不可能只有2段，自己写循环)    
//	aes_ecb_encrypt(&c1[0], &c2[0], &skey);
//	aes_ecb_encrypt(&c1[16], &c2[16], &skey);
//	c2[31] = '\0';
//	printf("%s\n",c2);
//	unsigned char c3[32];
//	aes_setup(myKey, 32, 0, &skey);// 解密前初始化状态，其实和加密的状态是完全一致的  
//
//	c3[31] = '\0';							   // 分段解密     
//	aes_ecb_decrypt(&c2[0], &c3[0], &skey);
//	aes_ecb_decrypt(&c2[16], &c3[16], &skey);
//	printf("%s\n", c3);
//	system("pause");
//	return 0;
//}