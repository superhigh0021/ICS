# 条款1 理解模板类型推导

```cpp
template<typename　T>
void f(ParamType param);

f(expr);   //调用
```

通常ParamType包含一些类型的装饰，比如const或引用特性。

---

- 第一种情况：ParamType是个非通用的引用或者是一个指针

1.如果expr的类型是引用，忽略引用的部分

2.利用expr的类型和ParamType对比去判断T的类型

```cpp
template<typename T>
void f(T& param); // param是一个引用类型

int x = 27; // x是一个int
const int cx = x; // cx是一个const int
const int& rx = x; // rx是const int的引用

f(x); 	// T是int，param的类型是int&
f(cx); 	// T是const int， 
		// param的类型是const int&
f(rx); 	// T是const int
		// param的类型时const int&
```

---

- 第二种情况：ParamType是个通用的引用(通用的引用参数声明类型是T&&右值引用)



如果expr是左值，T和ParamType都会被推到成坐直引用

如果expr是右值，执行普通法则(第一种情况)

```cpp
template<typename T>
void f(T&& param); // param现在是一个通用的引用

int x = 27; 
const int cx = x;
const int& rx = x;

f(x); 	// x是左值，所以T是int&
		// param的类型也是int&

f(cx); 	// cx是左值，所以T是const int&
		// param的类型也是const int&

f(rx); 	// rx是左值，所以T是const int&
		// param的类型也是const int&

f(27); 	// 27是右值，所以T是int 
		// 所以param的类型是int&&
```

---

- 第三种情况：ParamType既不是指针也不是引用(pass-by-value)

意味着param就是expr的一份拷贝——一个完全新的对象

1.如果expr的类型是引用，将会忽略引用的部分

2.如果在忽略expr的引用特性，exr是个const的，也要忽略const(volatile也要忽略)

```cpp
template<typename T>
void f(T param); // param现在是pass-by-value

int x = 27;
const int cx = x;
const int& rx = x;

f(x); // T和param的类型都是int
f(cx); // T和param的类型也都是int
f(rx); // T和param的类型还都是int
```

如果传递的是一个const char* const参数，那么经过拷贝后，指针本身的const特性将消失，只剩下对象的const特性，即**被推导为const char*，指针可以指向不同之物**

---

![image-20220303094627900](dependence/image-20220303094627900.png)



# 条款2 理解auto类型推导

**auto类型推导就是模板类型推导，auto相当于模板中的T**

---

**例外**：对待花括号初始化的行为

```cpp
auto x1 = 27; // 类型是int，值是27
auto x2(27); // 同上

auto x3 = { 27 }; // 类型是std::intializer_list<int> // 值是{ 27 }
auto x4{ 27 }; // 同上
```

当使用一对花括号来初始化一个auto类型变量时，推导的类型是std::intializer_list。**这一点导致花括号和auto容易被误用**

---

C++14允许auto作为函数返回值和lambda参数，但是其实是复用了模板的类型推导，然而**模板并不能将花括号初始化推导为std::intializer_list**，所以返回一个花括号初始化会无法编译。

![image-20220303095926062](dependence/image-20220303095926062.png)



# 条款3 理解decltype

- 给定一个变量名或表达式，decltype会告诉你它的类型

decltype的推导规则和auto、模板的规则不一样，是什么就返回什么

**auto作为返回值的时候会剥离对象的引用特性，所以返回decltype(auto)**

---

对于一个变量名，decltype返回左值，对于一个比变量名更复杂的左值表达式，**decltype返回左值引用**

```cpp
int x=0;
```

![image-20220303103300317](dependence/image-20220303103300317.png)



# 条款4 知道如何查看类型推导

- std::type_info::name的特化指定了类型会被当做他们传递给模板函数的时候**值传递**的参数

所以typeid有时候并不可靠



# 条款5 优先使用auto而非显式类型声明

- auto变量从它们的初始化推导出其类型，所以auto变量必须初始化；从而避免了普通声明忘记初始化。

---

- 使用std::function和使用auto不一样。

使用auto声明持有一个封装的变量和函数对象有同样的类型，也今消耗和函数对象同样大小的内存；

使用std::function持有一个可调用对象的变量类型是std::function模板的一个实例，并且对任何类型只有一个固定的大小。这个大小可能不满足需求，所以会开辟堆空间。结果就是**std::function可能比auto对象使用更多内存**。

此外，由于实现细节中，约束内嵌的使用和提供间接函数的调用，使用std::function对象会比auto要慢。

---

```cpp
std::unordered_map<std::string, int> m;
...
for(const std::pair<std::string, int>& p:m){
    ...
}
```

**std::unordered_map中key部分是const类型的**，所以pair的实际类型应该是 

**std::pair<const std::sting, int>**

而且此处不是循环体外的变量p声明，所以编译器会将std::pair<const std::sting, int>转换为std::pair<std::sting, int>。这个过程通过**复制m中的一个元素到一个临时对象，然后将这个临时对象和p绑定**。



# 条款6 当auto推导出非预期类型时应当使用显式的类型初始化

- 对std::vector<bool>的operator[]运算符不一定返回容器中的元素引用(它对所有类型都返回引用，就是除了bool)。

事实上，返回的是一个std::vector<bool>::reference对象(是一个在(std::vector<bool>内嵌的class)。

![image-20220304160610481](dependence/image-20220304160610481.png)

---

不可见的代理类不可以和auto一同使用。

使用显式的类型初始化即可：

```cpp
auto ep=static_cast<float>(calcEpsilon());
```

这样就可以迫使auto推导出你想要的类型。



# 条款7 在创建对象时注意区分()和{}

初始化的方式包括使用**小括号**、**等号**、**大括号**。

- 不可复制对i选哪个(如std::atomic类型的对象)可以采用大括号和小括号来初始化，而不能用"="。

大括号初始化**禁止内建类型之间进行隐式窄化类型转换**。

```cpp
double x,y,z;

int sum1{x+y+z}; //无法通过编译
```

---

- C++规定：任何能够解析为声明的都要解析为声明。

所以可能本来想要以默认初始化方式构造一个对象，结果不小心声明了一个函数。

:point_down:本意是想使用一个没有形参的构造函数声明一个对象。

```cpp
Widget w2();这个语句声明了一个函数
```

所以使用大括号就没有歧义了：

```cpp
Widget w2{};
```

---

在构造函数被调用时，只要形参中没有一个具备std::initializer_list类型，那么大括号和小括号没有区别；如果有的话，那么大括号会优先调用它们。

**空大括号表示的是没有参数，而不是空的std::initializer_list**，所以调用默认构造而不是形参为空的std::initializer_list的构造函数。如果要调用空的std::initializer_list的构造函数，就要用两个大括号，或者将大括号嵌套在小括号内。



# 条款8 优先使用nullptr而不是0或NULL

- 0和NULL都不属于指针类型



# 条款9 优先使用声明别名而不是typedef

- 使用using而不是typedef

![image-20220304164658267](dependence/image-20220304164658267.png)

---

在运用模板的地方，typedef就办不到了

![image-20220304165323003](dependence/image-20220304165323003.png)



# 条款10 优先使用作用域限制enums而不是无作用域的enum

- 无作用域的enul会将枚举元素隐式的转换为整数类型。

![image-20220304171359274](dependence/image-20220304171359274.png)

在enum后增加一个"class"，就可以将无作用域的enum转换为一个有作用域的enum。**有作用域的enum不存在从枚举元素到其他类型的隐式转换**。

---

编译器需要在枚举体之前知道它的大小。有作用域的潜在类型是已知的：int；对于没有作用域的枚举体，可以指定。

![image-20220304171936329](dependence/image-20220304171936329.png)

---

![image-20220304172621247](dependence/image-20220304172621247.png)



# 条款11 优先使用delete关键字删除函数而不是private却又不实现的函数

删除的函数和声明为私有函数的区别看上去只是时尚一些，但是有很多区别。

- 删除的函数不能通过任何方式被使用，即便是其他成员函数或者友元函数试图复制该对象时也会导致编译失败；而C++98中声明为private这种方式，直到链接的时候才会诊断出这个错误。

---

hint:如果给float一个转换为int或double的可能性，C++总倾向于转换为double。



# 条款12 使用override关键字声明覆盖的函数



# 条款13 优先使用const_iterator而不是iterator

- const_iterator在STL中等价于指向const的指针。

















































