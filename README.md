c++进行跨平台开发的封装库   
windows: 在VS2010 VS2015 VS2017 VS2019都验证通过。     
linux:gcc7测试通过     
mac:      
android:16g测试通过     
    
为了使用方便，基本这些文件互相之间都尽量减少了依赖关系。可以随便复制到自己工程中使用     
     
     
文件介绍：    
Any.h        	C++ Any实现。用来解决低版本VS不支持any      
BaseFactory：	一个工厂类的模板       
CMutex.cpp		解决低版本VS不支持cmutex问题,并且实现了lock_guard 方便时使用      
CommFunction	一些常用的函数封装      
DateUtils		模仿java 的SimpleDateFormat。 JAVA的这个设计很方便     
DebugOut		调试信息的输出，可以通过宏控制。这样release版本就会删除该日志     
DuanThread		跨平台创建线程     
DuanThreadPool	基于DuanThread 简单的线程池     
DuanTime		一些常用的时间函数     
endian			处理机器大小端问题的函数      
FileUtils		常见的文件操作函数     
LoadLib			跨平台的动态库加载和使用     
NumberOper		常见的数字处理     
Reflection		C++实现反射（但是我没有找到合适的实现，就只是写了点日志给大家思路）     
SafeSTL			支持多线程的STL      
Singleton		单例模式的基类       
StringOper		常见的字符串操作      
types			一些跨平台常用的宏      
Uc2ToUtf8		 字符串转码      
      