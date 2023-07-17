# 俄罗斯方块
2023暑期实践大作业

**项目环境：项目使用VS+EasyX实现**
**系统调用框架：NONE**

## 程序简述
代码使用windows环境，通过easyx实现图形化界面
通过向archive文件夹写入txt文件实现对游戏记录的存储
图形界面使用字体"mplus_hzk_12","UniDreamLED"，在文件夹fonts中可以找到，为了程序使用体验，建议在启动前安装相应字体

存档界面最多可显示6个存档，超过6个存档时，靠前的存档会被滚动替换（懒得做翻页），存档删除后，靠前的存档会滚回
清除存档可以删除所有存档（包括未显示的存档）并清除最高分（目前是这样设定的）

程序会生成archive文件夹，用于存储游戏记录

通过方向键控制图形左右移动、旋转和加速，按Esc键暂停游戏
失败结束的游戏不能存储游戏存档，会记录分数
暂停的游戏可以记录存档与分数

## 更新日志

#### 23.7.10 新增两种游戏玩法：
随机旋转模式，在经典模式的操作上，修改图形旋转为系统随机控制，不可自行控制

双人模式，通过ASDW控制左界面，方向键控制右界面，当任意一方结束游戏时，整局游戏结束，系统根据双方越界情况显示判定，该模式不能获得复活币

#### 23.7.10 新增复活币功能：

初始复活币数量为20，每次复活消耗5复活币，每局游戏结束时可以按分数获得复活币

#### 23.7.10 修改存档逻辑：

读取存档后，存档将被删除（用来防止刷复活币）

#### 23.7.11 新增游戏玩法介绍界面

#### 23.7.11 新增看广告复活：

当复活币不足时，用户可以选择看广告复活，广告存储形式如ad文件夹

#### 23.7.11 增加广告读取失败的界面，同时防止因读取失败导致程序崩溃

#### 23.7.17 重构键盘交互模块，放弃使用Sleep()提升界面刷新率至500+FPS……
放弃使用Sleep()控制按键及图形下落的方案，通过QueryPerformance获取系统高精度时间，从而精确控制程序运行，使方块下落速度更精准，按键操作更灵敏；

放弃使用Sleep()控制键盘防抖，转而使用tip标记，识别按键按下与松开，对tip进行操作，同时，定期更新tip使得用户可以通过长按按键进行操作（旋转键长按操作被关闭）；

长按的移动速度与按下加速键后的移动速度与难度关联，加速速度=当前下落速度x10，长按移动速度=当前下落速度x2；

新增长按按键延迟功能，当用户长按按键时，在第一次移动与第二次移动之间，存在额外的时间间隔（防止误触），额外时长=1/(难度*2) (秒)；


## 目前存在的特性：

~~初始方块的形状和状态固定（因为随机种子是向暂存器写入，在后一次生成时，由暂存器向状态变量赋值）~~

##### 23.7.9已经修复该特性

##### 23.7.11版本测试时发现，双人模式下初始方块随机性不强，推测与生成函数调用间隔过短有关，暂未修改

## 23.7.11版本界面

![image](https://github.com/cadddddada/Tetris/assets/123754491/4f55fdbd-10ff-4f98-bf92-1cfce915f1b4)

## 23.7.9版本界面

![image](https://github.com/cadddddada/Tetris/assets/123754491/68e19a3d-c647-4e3b-aa52-75e1ffb1989b)
![image](https://github.com/cadddddada/Tetris/assets/123754491/f0404c3f-bb64-4fdc-8aba-1e53b898ae64)
![image](https://github.com/cadddddada/Tetris/assets/123754491/ee99acfe-11a8-4229-abaf-fa66750c37b1)
![image](https://github.com/cadddddada/Tetris/assets/123754491/77e4da9e-d3a0-4414-93c6-4aefa0b5dc73)
![image](https://github.com/cadddddada/Tetris/assets/123754491/71e3e536-d27d-4686-b893-967e51b58db8)




