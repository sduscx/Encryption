///*
//����ĳ���ʵ�ֵĹ��ܣ�
//���ַ���c1��AES�������ܷ���c2�У��ٽ��ܷ���c3�У���Կ��myKey
//*/
//
//#include "tomcrypt.h"  
////#pragma comment (lib,"tomcryptd.lib")  
//int main(int argc, char* argv[])
//{
//	unsigned char myKey[32] = "12345";// ������Կ    
//	symmetric_key skey;// ����״̬  
//
//	aes_setup(myKey, 32, 0, &skey);// ����ǰ��ʼ��״̬(��Կ����Կ���ȣ���������(0: ʹ���Ƽ�ֵ)������״̬)  
//
//
//	unsigned char c1[32] = "csdn";// ��Ҫ���ܵ��ַ�����������  
//	unsigned char c2[32];// �������>= ���볤�ȣ��ֶγ��ȵı���(�������16�ı���)      
//	printf("%s\n", c1);
//	c1[31] = '\0';			 // �ֶμ��ܣ�ÿ�γ���Ϊ16 (һ�㲻����ֻ��2�Σ��Լ�дѭ��)    
//	aes_ecb_encrypt(&c1[0], &c2[0], &skey);
//	aes_ecb_encrypt(&c1[16], &c2[16], &skey);
//	c2[31] = '\0';
//	printf("%s\n",c2);
//	unsigned char c3[32];
//	aes_setup(myKey, 32, 0, &skey);// ����ǰ��ʼ��״̬����ʵ�ͼ��ܵ�״̬����ȫһ�µ�  
//
//	c3[31] = '\0';							   // �ֶν���     
//	aes_ecb_decrypt(&c2[0], &c3[0], &skey);
//	aes_ecb_decrypt(&c2[16], &c3[16], &skey);
//	printf("%s\n", c3);
//	system("pause");
//	return 0;
//}