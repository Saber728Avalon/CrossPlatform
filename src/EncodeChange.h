#pragma  once
 /**
 * @file		EncodeChange.h
 * @brief		���ַ�������GBK UTF8 UTF16���л���ת��
 * @author		duanqiang
 * @date		2020/09/08
 * @version 	1.0.0.1
 * @copyright	Copyright (C) 2009 duanqiang <email@2891018428@qq.com>
 */


#include <stdlib.h>
#include <exception>
#include <string>
#define SWAPBYTE(x)\
	((x & 0xff00)>>8) |\
	((x & 0x00ff)<<8)

typedef char U_GB;
typedef unsigned short U_NIC;
typedef unsigned char U_TF8;

//************************************
// @Method:    Uc2ToUtf8
// @Returns:   int ���� ת������ַ�������
// @Parameter: uc2Array unicode16Դ�ַ���
// @Parameter: uc2Len Դ�ַ�������
// @Parameter: utf8Buf utf8�ַ������buf
// @Parameter: utf8BufSize utf8�ַ���buf��С
// @Brief:
//************************************
  int Uc2ToUtf8(const U_NIC* uc2Array, size_t uc2Len, U_TF8* utf8Buf, size_t utf8BufSize);
//************************************
// @Method:    UtfToUc2
// @Returns:   int ����ת������ַ�������
// @Parameter: utf8Array Դutf8�ַ���
// @Parameter: utf8Len Դutf8�ַ�������
// @Parameter: uc2Buf uc2�ַ�����Ż���
// @Parameter: uc2BufSize ��Ż�������С
// @Brief:
//************************************
  int UtfToUc2(const U_TF8* utf8Array, size_t utf8Len, U_NIC* uc2Buf, size_t uc2BufSize);
//************************************
// @Method:    GbkToUtf8
// @Returns:   int ת������ַ�������
// @Parameter: gbkArray Դgbk�ַ���
// @Parameter: gbkArrayLen Դgbk�ַ�������
// @Parameter: utf8Buffer utf8��Ż���
// @Parameter: utf8BufferSize utf8��Ż����С
// @Brief:
//************************************
  int GbkToUtf8(const char* gbkArray, size_t gbkArrayLen, U_TF8* utf8Buffer, size_t utf8BufferSize);
//************************************
// @Method:    TraditionGbkToUtf8
// @Returns:   int ת�����ַ�������
// @Parameter: traGbkArray Դ���������ַ���
// @Parameter: arrayLen Դ�ִ�����
// @Parameter: utf8Buffer utf8�洢��
// @Parameter: utf8BufferSize utf8�洢�����С
// @Brief:
//************************************
  int TraditionGbkToUtf8(const U_NIC* traGbkArray, size_t arrayLen, U_TF8* utf8Buffer, size_t utf8BufferSize);
//************************************
// @Method:    Utf8ToGbk
// @Returns:   int ����ת�����ַ�������
// @Parameter: utf8SrcArray utf8Դ�ִ�
// @Parameter: utf8Len Դ�ִ�����
// @Parameter: gbkBuffer gbk����
// @Parameter: gbkBufferSize gbk�����С
// @Brief:
//************************************
  int Utf8ToGbk(const U_TF8* utf8SrcArray, size_t utf8Len, U_NIC* gbkBuffer, size_t gbkBufferSize);
//************************************
// @Method:    Utf8ToTraditionGbk
// @Returns:   int ת�����ִ�����
// @Parameter: utf8SrcArray utf8Դ�ִ�
// @Parameter: utf8Len Դ�ִ�����
// @Parameter: traGbkBuffer tragbk����
// @Parameter: traGbkBufferSz traGbk���峤��
// @Brief:
//************************************
  int Utf8ToTraditionGbk(const U_TF8* utf8SrcArray, size_t utf8Len, U_NIC* traGbkBuffer, size_t traGbkBufferSz);
//************************************
// @Method:    ToUpper
// @Returns:   void
// @Parameter: str ת�����ִ�
// @Brief:
//************************************
  void ToUpper(std::string& str);
//************************************
// @Method:    ToLower
// @Returns:   void
// @Parameter: str ת�����ִ�
// @Brief:
//************************************
  void ToLower(std::string& str);

//************************************
// @Method:    InitializeCodeFormatTransformer
// @Returns:   void
// @Brief:	��ʼ���ַ�ת����
//************************************
  void InitializeCodeFormatTransformer();

  class   CodeTransformUtility
  {
  public:
	  static std::string GetUtf8Code(char* gbkSource, int len);
	  static std::string GetGbkCode(char *utf8Source, int nLen);
  };
