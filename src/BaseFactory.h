#pragma once
 /**
 * @file		AbstractFactory.h
 * @brief		简单工厂模式模板。由于抽象工厂模式，不如直接实现反射，所以不实现抽象工厂模式.
 *				该类只是模板，在需要情况下。可以不用因为使用时候，需要先去定义，在调用就不方便。
 * @author		duanqiang
 * @date		2020/12/08
 * @version 	1.0.0.1
 * @copyright	Copyright (C) 2009 duanqiang <email@2891018428@qq.com>
 */

#include <iostream>
#include <memory>

//product为抽象产品, concreateProduct为具体产品
template< typename product, typename concreateProduct>
class BaseFactory
{
public:
	virtual std::shared_ptr<concreateProduct> Factory(product) = 0;
};

//以下是测试代码
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