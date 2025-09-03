# C-GuessNumber

把大一上期到大一寒假做的猜数游戏挖出来整理了一下...  
我第一次接触猜数游戏是在翁恺老师讲循环的时候, 因为觉得很有意思, 所以一直尝试写各种各样的猜数游戏————满足自己"玩"的心理以及初学者都有的对做项目的向往  
看着知识一点一点输出、项目一点一点变大、项目思维和能力一点一点变强, 着实高兴

## 项目版本
1. [v0.0.0](https://github.com/existed-name/C-GuessNumber/blob/main/GuessNumberV0.0.0.c)  
   1. 功能: 朴素的————猜限定范围内的数字 → 猜错提醒 → 猜对输出猜数次数 → 分隔线 → 循环
   2. 知识点:
      1. 生成[ 0, end )的随机数--`srand( time( NULL ) )` 以及 `rand() % end` ( 需添加 `time.h`、`stdlib.h` 头文件 )
      2. 循环读取数字--`while( scanf( "%d", &b ) != EOF )`--直到猜中 `break`
      3. 无限循环 `for ( int i = 0; ; ++i )`( 等同于 `for( ; ; )`、`while( 1 )`、`while( true )` )套在外面可以一直游戏
2. [v0.9.0](https://github.com/existed-name/C-GuessNumber/blob/main/GuessNumberV0.9.0.c)
   1. 功能: 游戏介绍 → 猜数并判定 → 根据猜错次数给出不同的回复 → 猜对则结束; 如果太多次猜错会被判定为捣乱, 进而终止程序
   2. 新增知识点:
      1. 使用 `switch-case` 分支, 根据不同的猜错次数将 `char *` 变量赋值为不同的字符串
      2. 函数原型声明、函数定义
3. [v1.0.0](https://github.com/existed-name/C-GuessNumber/blob/main/GuessNumberV1.0.0.c)  
   1. 新增功能:
      1. 完善游戏介绍————规则、玩法、提示
      2. 猜数结束后询问是否继续游戏
      3. 结束游戏后展示游戏战绩————游戏总场次、违规次数、每场游戏的目标数和猜数次数
   2. 新增知识点:
      1. 宏定义常量替代 `magic number`
      2. 创建结构体数组储存每局游戏数据
      3. 字符串拼接: `printf( ""  "" )` 可将括号内的字符串拼接在一起输出, 利用该点可在输出内容较长时合理换行, 增加可读性
      4. 简化主函数逻辑: 将复杂逻辑从 `main` 函数抽出, 只在 `main` 函数保留关键逻辑、函数
4. [v2.0.0](https://github.com/existed-name/C-GuessNumber/blob/main/GuessNumberV2.0.0.c)
   1. 新增功能:
      * 开发多模式: 经典模式、提示模式、挑战模式、轮回模式( 甚至写了半截小说 )
      * 看完源码各种模式的提示、输出, 大二的我感觉大一的自己很二, 但是很有趣
   2. 新增知识点:
      1. 使用枚举类代表各种模式的编号及其相关数据在数组中的下标
      2. 字符串数组 `char *[]` 储存文字段, 便于进行遍历展示或者通过指定下标获取指定语句

## 下载说明
1. 下载整个仓库: 仓库首页右上部分 → 绿色的 "<> Code" → Local → Download Zip
2. 只下载某一个文件
   进入该文件, 在代码框右上角
   * 选择 `Copy row file` 复制代码粘贴到编译器上
   * 或者 `Download row file` 下载文件
3. 下载特定文件夹:    
   1. 进入特定文件夹, 复制网址到 [DownGit](https://tool.mkblog.cn/downgit/#/home) 上进行下载    
   2. 在英文输入法下按 "," 或者 "." 键 → 进入 github.dev 线上 VScode → 在左边选择资源管理器 → 右键指定文件夹, 下载到电脑指定位置    
   3. 使用其他插件、网站    
4. 使用 Git 命令下载

## 其他仓库
* C 语言
  - [连珠棋游戏](https://github.com/existed-name/C-LianzhuChess)
  - [线性数据结构](https://github.com/existed-name/C-LinearDataStructre)
  - [二叉树节点序号的二进制表示法](https://github.com/existed-name/C-TreeNodeNumberInBinary)
* Java
  - [健康计算器](https://github.com/existed-name/Java-Health-Calculator)
 
---


