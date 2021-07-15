#pragma once
 /**
 * @file		AbstractFactory.h
 * @brief		�򵥹���ģʽģ�塣���ڳ��󹤳�ģʽ������ֱ��ʵ�ַ��䣬���Բ�ʵ�ֳ��󹤳�ģʽ.
 *				����ֻ��ģ�壬����Ҫ����¡����Բ�����Ϊʹ��ʱ����Ҫ��ȥ���壬�ڵ��þͲ����㡣
 * @author		duanqiang
 * @date		2020/12/08
 * @version 	1.0.0.1
 * @copyright	Copyright (C) 2009 duanqiang <email@2891018428@qq.com>
 */

#include <iostream>
#include <memory>

//productΪ�����Ʒ, concreateProductΪ�����Ʒ
template< typename product, typename concreateProduct>
class BaseFactory
{
public:
	virtual std::shared_ptr<concreateProduct> Factory(product) = 0;
};

//�����ǲ��Դ���
//enum XXX
//{
//	XXX_A,
//	XXX_B
//};
//
//class basexx
//{
//public:
//	virtual void Show() = 0;
//};
//
//class A :public basexx
//{
//public:
//	void Show() {printf("A \n"); }
//};
//
//class B : public basexx
//{
//public:
//	void Show() { printf("B \n"); }
//};
//
//class TestFactoryClass : public BaseFactory<XXX, basexx>
//{
//public:
//	std::shared_ptr<basexx> Factory(XXX nxx)
//	{
//		if (XXX_A == nxx)
//		{
//			return std::make_shared<A>();
//		}
//		else if (XXX_B == nxx)
//		{
//			return std::make_shared<B>();
//		}
//		else
//		{
//			return NULL;
//		}
//
//		return NULL;
//	}
//};
//
//static void TestFactory()
//{
//	TestFactoryClass fac;
//	auto ptr = fac.Factory(XXX_B);
//	ptr->Show();
//
//	return;
//}