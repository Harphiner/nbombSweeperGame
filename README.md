# nbombSweeperGame
## 该大作业为扫雷游戏
### 注意事项：
	1. 由于QtCreator在进行构建时不允许出现中文，所以文件夹命名中的姓名采用拼音；
	2. 根目录下共三个文件夹：
		a. nbombSweeperGame:其中有可执行文件以及依赖库，双击nbombSweeperGame.exe即可运行程序
		b. Qt_6_5_1_MinGW_64_bit-Release:（该文件较大）
			（1）. 由QtCreator以release模式构建的文件夹，其中的可执行文件双击 无法 运行！
			（2）. 需要将可执行文件单独移至一个新建文件夹，然后采用用 qt对应的kits：Qt 6.5.1 (MinGW 11.2.0 64-bit) 
			       在命令行中用指令 windeployqt nbombSweeperGame.exe（如果本地没有qt库，则无法成功）
		c. QtProject：
			（1）. 这个文件夹为原始项目文件夹，里面有最原始的c++源码和qt的图形化、资源文件以及配置文件（.pro）
			（2）. 要想重新构建，可打开.pro文件，在QtCreator软件中操作即可（需要本地已安装QtCreator）
### 操作说明：
	1. 开始页面：
		a. ”开始游戏“按钮，点击后进入选择页面
		b. 菜单栏中，可以在”开始“中选择难度，或在”自定义“中编辑难度
	2. 选择页面：与主页面的菜单栏功能一致
		a. 简单、正常、困难 分别对应 （10*10 10）（20*20 40）（30*30 99）
		b. 自定义 可设置行列数（范围1-30）和雷数（10-99），如果超出范围会报错重新填写
	3. 游戏页面：
		a. 上方为计时器和旗帜计数器
		b. 左键open，右键flag，没有 设计中间键的功能
		c. 成功与失败后均会弹出提示询问”重来“或者”退出“
		d. ”返回“按钮，回到选择页面
		e. 下方还有一个进度条，统计打开的安全区域百分比
