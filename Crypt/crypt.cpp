//#include "tomcrypt.h"  
//#include <iostream>
//#include<string> 
//using namespace std;
///*
//	main function to crypt and decrypt the file
//*/
///*һ�μӽ����ڴ��ж�ȡ���ٶΣ�ÿ��16bit*/
//const int deal_block = 5;
//void Crypt(char *p, int method,int model, unsigned char *mykey);
//int main() {
//	cout<<"Welcome to use the program\n";
//	bool start = true;
//	while (start) {
//		start = false;
//		cout<<"please input the location of the file you want to crypt or decrypt:\n";
//		string buff = "";
//		cin >> buff;
//		const char * filePath = buff.c_str();
//		FILE *fp = NULL;
//		fopen_s(&fp, filePath,"r");
//		if (fp == NULL) {
//			cout << "�����ڸ��ļ�\n";
//		}
//		else {
//			//�����ļ�
//		    //�����ڴ�ռ�
//			fseek(fp, 0, SEEK_END);
//			int file_size = ftell(fp);
//			fseek(fp, 0, SEEK_SET);
//			int i = 0;
//			const int size = deal_block*16;
//			cout << "would you like to cyprt or decrypt?0 to crypt,1 to decrypt\n";
//			int type = -1;
//			cin >> type;
//			cout << "would you like to use des or aes or rs4?0 to des,1 to aes\n";
//			int method = -1;
//			cin >> method;
//			cout << "would you like to use which model?0 to cbc,1 to cfb,2 to ofb,3 to ctr\n";
//			int model = -1;
//			cin >> model;
//			cout << "please input the key:(the key length use )\n";
//			unsigned char mykey[64];
//			cin >> mykey;
//
//			do{
//				i++;
//				char p[size];
//				fread_s(p,size,4,size/4,fp);
//				p[size - 1] = '\0';
//				/*crypt p*/
//				cout << p;
//				if (type == 0) {
//					Crypt(&p[0],method,model,mykey);
//				}
//				else if (type == 1) {
//					//Decrypt(&p,model,mykey);
//				}
//				delete p;
//			} while (size*i<file_size);
//		}
//		fclose(fp);
//		cout<<"do you want to continue?input 0 to exit,1 to restart\n";
//		cin >> start;
//	}
//	cout<<"Thanks to use\n";
//	
//	system("pause");
//}
//
//void Crypt(char *p, int method,int model, unsigned char *myKey) {
//	symmetric_key skey;// ����״̬  
//	if (method == 0) {
//		//des
//		switch (model)
//		{
//		case 0:
//			//cbc
//			//symmetric_key skey;// ����״̬  
//			//des_setup(myKey, 32, 0, &skey);// ����ǰ��ʼ��״̬(��Կ����Կ���ȣ���������(0: ʹ���Ƽ�ֵ)������״̬) 
//			//cbc_start();
//			break;
//		case 1:
//			break;
//		case 2:
//			break;
//		case 3:
//			break;
//		default:
//			break;
//		}
//	}
//	else if (method == 1) {
//		//aes
//		switch (model)
//		{
//		case 0:
//			break;
//		case 1:
//			break;
//		case 2:
//			break;
//		case 3:
//			break;
//		default:
//			break;
//		}
//	}
//}
