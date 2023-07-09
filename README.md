# Project1
2023暑期实践大作业

代码使用windows环境，通过easyx实现图形化界面
通过向archive文件夹写入txt文件实现对游戏记录的存储
图形界面使用字体方正经黑简体，在代码页fonts中可以找到


存档界面最多可显示6个存档，超过6个存档时，靠前的存档会被滚动替换掉（懒得做翻页）
清除存档可以删除所有存档（包括未显示的存档）并清除最高分（目前是这样设定的）


通过方向键控制图形左右移动、旋转和加速，按Esc键暂停游戏
失败结束的游戏不能存储游戏存档，会记录分数
暂停的游戏可以记录存档与分数


目前存在的特性：~~初始方块的形状和状态固定（因为随机种子是向暂存器写入，在后一次生成时，由暂存器向状态变量赋值）~~

已经修复该特性

![image](https://github.com/cadddddada/Tetris/assets/123754491/68e19a3d-c647-4e3b-aa52-75e1ffb1989b)
![image](https://github.com/cadddddada/Tetris/assets/123754491/f0404c3f-bb64-4fdc-8aba-1e53b898ae64)
![image](https://github.com/cadddddada/Tetris/assets/123754491/ee99acfe-11a8-4229-abaf-fa66750c37b1)
![image](https://github.com/cadddddada/Tetris/assets/123754491/77e4da9e-d3a0-4414-93c6-4aefa0b5dc73)
![image](https://github.com/cadddddada/Tetris/assets/123754491/71e3e536-d27d-4686-b893-967e51b58db8)
