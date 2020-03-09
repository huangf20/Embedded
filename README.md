# Embedded
My Embedded project
使用51单片机上的LED矩阵以及独立按键实现的贪吃蛇小游戏

main.c 主要是实现界面的显示，将数据转换成单片机上的LED亮灭；
使用一个8*8数组对应8*8LED灯，遍历数组，元素为1则灯亮，反之灯灭

snack.c 实现贪吃蛇的逻辑业务，小蛇的移动、长度变化、死亡判定方式、食物的随机出现
使用一个长度为20的结构体数组代表小蛇各个部位的位置，结构体包含横坐标与纵坐标


