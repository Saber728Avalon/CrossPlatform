#pragma once

/**
* @file		Reflection.h
* @brief		c++����ʵ�֡�ĿǰC++ʵ�ַ��������ַ�ʽ����1������һ���꣬Ȼ��ÿ��Ҫ�������ĺ��档������һ�κ꣬��Ҫ���ú�չ���Ȳ�������
*				caffe��ʵ��Ϊ����,ͨ��һ��������һ����̳еķ�ʽ,Ȼ���ڼ̳к����У�����һ��������. (2)����MFC������Ϣ��Ӧ������ӳ��һ��,����һ������Ϣ��,������Ҫһ������,ͨ��������������ú�ʵ��  . (3) ʹ��֮ǰȥĳ������ע�ᣬ��Ҫ�������ͺ���,��RTTRΪ����
*				���漸���У���ʵ����������ǿ����3��ʵ��,��������ʵ�ִ���Ҳ�ܻ�ɬ�Ѷ�. c++�﷨���ϸ�֧�ֵ�2,���ͨ�������. 1�û��ΰ루���羲̬��ʱ��1����ʵ���������,��̬����ʱ���û��չ����
*				��Ȼ��������ʵ�ֵķ�ʽ�����綨��һ��C�ĺ���ָ�룬Ȼ���������涨�徲̬�������ٰѾ�̬�����������������ȱ���ǲ�֧�ֶ�̬�Ĺ��캯��
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
