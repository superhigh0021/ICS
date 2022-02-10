# 条款1 视C++为一个语言联邦

没啥好说的


# 条款2 尽量以const, enum, inline替换#define

## 宏定义的变量可能不会进入符号表(symbol table)

在define之后，可能在运用该常量的过程中获得一个编译错误，这个错误也许会提到定义的结果，而不会提到那个常量的名字，这样会导致困惑，因为需要追踪那个常量就显得十分困难。

const定义的**语言常量**肯定会被编译器看到，因此会进入符号表

## 宏定义无法创建class专属常量

**#define 不重视作用域** 

一旦宏被定义，就在其后的变异过程中有效  所以#define也没有封装性

## 一个属于枚举类型的数值可以充当int使用

```
#class GamePlayer{
private:
	enum{NumTurns=5};

	int scores[NumTurns];
};
```

## 对于形如函数的宏，最好用inline函数替换#define

**现代编译器会自动inline，而不是根据编写代码者是否添加inline来判断**
