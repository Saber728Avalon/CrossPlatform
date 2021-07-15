#pragma once

/**
* @file		Reflection.h
* @brief		c++反射实现。目前C++实现发射有三种方式。（1）定义一个宏，然后每个要反射的类的后面。都调用一次宏，主要利用宏展开等操作。以
*				caffe的实现为代表,通过一个宏生成一个类继承的方式,然后在继承函数中，设置一个公共类. (2)采用MFC定义消息相应函数宏映射一样,设置一连串消息宏,但是需要一个基类,通过这个基类与设置宏实现  . (3) 使用之前去某个函数注册，需要反射的类和函数,以RTTR为代表
*				上面几种中，其实最灵活，功能最强大是3的实现,但是最难实现代码也很晦涩难懂. c++语法最严格支持的2,因此通用性最好. 1好坏参半（比如静态库时候1，其实会有问题的,静态编译时候宏没有展开）
*				当然还有其他实现的方式，比如定义一个C的函数指针，然后在类里面定义静态函数，再把静态函数保存起来。这个缺点是不支持多态的构造函数
* @author		duanqiang
* @date		2020/12/09
* @version 	1.0.0.1
* @copyright	Copyright (C) 2009 duanqiang <email@2891018428@qq.com>
*/
#include <iostream>
#include "Any.h"
#include <memory>
#include <map>

namespace duan
{
	template<typename Ret, typename ClassValue, typename ...Args>
	class MethodReflect
	{
	public:
		typedef Ret(ClassValue::*pFunction)(Args...);

		//
		MethodReflect(duan::Any anyFunc) : m_func(duan::Any_Cast<pFunction>(anyFunc))
		{

		}

		//
		template<typename ...Args>
		duan::Any Invoker(Args...args)
		{
			return m_func(std::forward<Args>(args...));
		}
	private:
		pFunction m_func;
	};

	
	//class ClassReflectWapper
	//{
	//public:
	//	template<typename ClassValue, typename ...Args>
	//	ClassReflectWapper(Args...args)
	//	{
	//
	//	}
	//};

	template<typename ClassValue>
	class ClassReflectHolder
	{
	public:

		ClassReflectHolder() {}

		template<typename ...Args>
		static std::shared_ptr<ClassValue> Constructor(Args...args)
		{
			return std::make_shared<ClassValue>(std::forward<Args>(args)...);
		}

		ClassReflectHolder<ClassValue>& Cast()
		{
			return *this;
		}
	};

	class ClassReflect
	{
	public:
		ClassReflect()
		{

		}

		ClassReflect(const ClassReflect &param)
		{
			this->m_pMethod = param.m_pMethod;
			this->m_anyHolder = param.m_anyHolder;
		}

		ClassReflect& operator =(const ClassReflect &param)
		{
			this->m_pMethod = param.m_pMethod;
			this->m_anyHolder = param.m_anyHolder;
			return *this;
		}


		template<typename ClassValue>
		void BuildHolder()
		{
			ClassReflectHolder<ClassValue> holder;
			m_anyHolder = (duan::Any(holder));
		}


		//method
		template<typename Ret, typename ClassValue, typename ...Args>
		ClassReflect& Method(const std::string strName, duan::Any anyFunc)
		{
			bool bFind = m_pMethod.find(strName) != m_pMethod.end();
			if (false == bFind)
			{
				MethodReflect<Ret, ClassValue, Args...> tmpFunc(anyFunc);
				duan::Any func(tmpFunc);
				m_pMethod[strName] = func;
			}

			return *this;
		}
		
		template<typename ...Args>
		void Invoker(Args...)
		{
			bool bFind = m_pMethod.find(strName) != m_pMethod.end();
			if (true == bFind)
			{
				duan::Any andFuncHolder = m_pMethod[strName];

			}
		}
		//template<typename ...Args>
		//duan::Any Invoker(std::string strFuncName, Args...args)
		//{
		//	bool bFind = m_pMethod.find(strFuncName) != m_pMethod.end();
		//	if (false != bFind)
		//	{
		//		return duan::Any_Cast<BaseMethodReflect>(m_pMethod[strFuncName]).Invoker(std::forward<Args>(args...));
		//	}
		//}

		//variable

		//contructor
		template<typename ...Args>
		duan::Any Constructor(Args...args)
		{
			//return std::make_shared<ClassValue>(std::forward<Args>(args)...);

			return (m_anyHolder).Constructor(std::forward<Args>(args)...);
		}

	private:
		std::map<std::string, duan::Any> m_pMethod;
		duan::Any m_anyHolder;
	};

	class Reflect
	{
	public:



		static ClassReflect& Create(std::string strClassName)
		{
			bool bFind = m_mapRegister.find(strClassName) != m_mapRegister.end();
			if (false != bFind)
			{
				return  duan::Any_Cast<ClassReflect& >(m_mapRegister[strClassName]);
			}
			else
			{

			}
		}

		
		template<typename ClassValue>
		static ClassReflect Regiter(std::string strClasName)
		{
			bool bFind = m_mapRegister.find(strClasName) != m_mapRegister.end();
			if (false == bFind)
			{
				ClassReflect classReflect;
				classReflect.BuildHolder<ClassValue>();
				m_mapRegister[strClasName] = duan::Any(classReflect);


				auto& itemRet = m_mapRegister[strClasName];
				return  duan::Any_Cast<ClassReflect>(itemRet);
			}
		}

	private:
		static std::map<std::string, duan::Any> m_mapRegister;
	};

	std::map<std::string, duan::Any> Reflect::m_mapRegister;
}
