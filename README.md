# IM_INSAN

## 9/5 搭建好了认为自身需要的类
	component组件还缺些东西,另外scene类似乎多余
## 9/6 建立了一堆类
	大的更新:
    Object等类(注意GameObject是Object的类名)
    BreedFactury的工厂模式(注意Factury只将其血量设置为0)
    SceneManagr被删除,其功能由mainwindow替代
    ComponentPaint写了一种绘图方式
    Constant制定了scene的编号并将SCENE_NUM定义为了int的代名词,同时规定所有无逻辑的可显示物血量为1.
    ObjectManager 添加了数个list,其中给你allist和factury一起负责其生与死,其他list负责逻辑部分,若有object需清除只许将其hp设置为0即可

    架构模式:
    Object 类型对象
    Factury 半个工厂,死的时候用脏标记代替析构
    Scene 切换:解释器(TODO jason?)+DFA
    Skills 由Effect组成(沙盒),可考虑加上解释器

    ...另外
    QGraphicsItem可以用来碰撞检测的样子,太爽了...(甚至可以将GameObject和其合并)
## 9/8 学会了多线程建立loadingscreen + splashscreen
    方法见:https://blog.csdn.net/liang19890820/article/details/52186626
	多线程太难用额
	评价:有自知之明,你坑我坑的好惨
## 9/9 配置文件选择ini 和 json
	已在SceneStart等处写了样本
## 9/9 用上了QGraphicsView的架构
	1 删去了ObjectManager 的华而不实的类
	2 将Scene 变为了 QGraphicsScene 的子类
	3 将GameObject 变为了 QGraphicsPixmapItem 和 QObject的子类
## 9/9 今天又弄好了多线程+scene转换 
	DONE:
    多线程用来loading screen弄好了
    Scene的FSM转化器弄好了
    原来的GraphicsItem中重载函数的bug调好了
    给每个场景都增加了一个getSceneId(),并用此判断是否相等
    TODO:
    之后将每个Scene做完
    弄好SceneManager的内存分配
    弄好加载LoadingScreen的判断条件
    Caution!:
    多线程在使用的时候真的是有很多不便,最好注意着使用
## 9/10 单例模式的GVariant解决machine中内存难题
	看似没有bug....
	评价:ntm在逗我
## 9/10 弄好了字幕(Script类)的显示和加载
	并且画了女主/boss
	评价:已经能成为一部gal了
## 9/10 写好了剧本
	和整个流程
## 9/10 debug了一堆
	一个变量被反复用到->这个变量适合作为指针->这个变量不应该放在占空间->把析构函数写成private的 !
	重载的Shape 默认返回boundingrect 但是他们的坐标系并不是一个概念..我能骂人吗
	TODO:制作battleScene!
	