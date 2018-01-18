# ReadMe.txt #

##**configuration instructions**##

该程序可由任意C++编译器编译，测试时在visual studio下经C++11标准及以上编译器编译成功。在文件夹内双击解决方案 **2018_SPRING_DEV.sln** 可打开所有文件并实现编译。打开后可能因版本过高需修改*.sln内visual studio的版本号，可删除 **visualstudioversion** 和 **minimumvisualstudioversion** 两行点击保存关闭后重新打开即可。具体详情参见[***百度经验***](https://jingyan.baidu.com/article/066074d628681bc3c21cb037.html)


##**operating instructions**##
无人机活动信号的文本文件名称及路径可由控制台参数输入，也可在文中**2018_SPRING_DEV.cpp**文件下的全局变量 **g_filename、g_filepath**修改。其传入两个参数，其一为文件名，其二为文件路径。路径由于转义字符的存在，路径间请使用“\\\”。控制台参数详情请输入 **-h**    
如果直接双击.exe后无法正常运行并提示输入数据有误，请将data.txt文件放至与exe同路径。亦或选择将exe文件放入cmd后添加额外的命令，例如 2018_SPRING_DEV.exe --filename="data.txt"   
某些情况下可能因sscanf的不安全性导致编译失败。请在**属性-C/C++-预处理器-预处理器定义** 添加宏命令 **_CRT_SECURE_NO_WARNINGS**

## **file manifest** ##
stdafx.h	预编译头文件  
help_hbx.h	用户自定义帮助函数头文件
UserDefEnum.h	用户自定义枚举头文件  
UserDefFunc.h UserDefFunc.h	用户自定义函数头文件及cpp文件
2018_SPRING_DEV.cpp 主函数cpp文件   

**《高端大气上档次文艺复古小清新》筛选器**   
	BaseComponent.h	基础组件基类   
	CConsoleOutput.h	输出类，派生自基础组件基类    
	CrudeTimer.h	延时用定时器类    
	CTXTReader.h	数据文件文档读取类    
	Dispatch.h		消息队列管理类    
	EntityManager.h	组件管理类    
	Package.h		消息包类

## **contact information for the programmer** ##

 [鄙人的github，无CSDN博客。保密单位很少发帖很少传代码，但自己会总结 ~](https://github.com/hubin8851)    
<font color=green>工厂模式、C组件、状态机、继承-派生均在项目FEM_CUDA _ _BOOST_ _V2项目中有所体现。   
<font color=red>联系电话：<font color=#0099ff>**18109239467**    


## <font color=black>**troubleshooting** ##
*弃用联合体*：联合体内存放状态枚举与偏移量可能导致数据与枚举状态间的冲突进而导致判断失误   
*未用map做索引*：暂不考虑文本内容的序列出现遗漏的情况，故用vector。若有遗漏可改用map，经输入后使用find函数即可。   
*假定文本格式正确*：未用正则表达式判定飞行器名称是否为字符串与数字的组合，假定需要可以添加。   

## log ##
1/18/2018 8:06:43 PM    
将txt读取函数封装为类，控制台输入输出相关操作封装为类。采用消息模式，当程序拓展时更为方便。因此分为两个版本，其一为RunTest函数，其二为ClassRunTest下的所有操作。如有不当恳请指教。

1/16/2018 10:56:06 PM 
无
