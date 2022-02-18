# PartⅡ 并发

**线程共享地址空间，从而能够访问相同的数据**

线程之间的上下文切换类似进程之间的上下文切换

对于进程，将状态保存到进程控制款PCB(Process Control Block)

对于线程，控制控制块TCB(Thread Conrtol Block)

**线程之间的上下文切换 地址空间保持不变(不需要切换当前使用的页表)  进程的切换需要**

多个线程可能共同执行的代码段称为**临界区** 一般不允许多个线程同时执行临界区代码

## 第27章 线程API

### 27.1线程创建

```c
//创建线程
int pthread_create(pthread_t *thread,
           const pthread_attr_t *attr,
           void (*start_routine)(void*),
           void *arg);
```

### 27.2线程完成

```c
//等待线程结束
int pthread_join(pthread_t thread,void **value_ptr)
//注意其第二个参数的类型是pointer to pointer
```

pthread_join()的第二个参数是一个指针，指向希望得到的返回值，如果不需要返回值，那么也可以传入NULL

### 27.3 锁

```c
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
```

如果意识到有一段代码是一个临界区，那么就需要通过锁来保护

**所有的锁必须正确初始化 以确保他们具有正确的值 并在锁和解锁被调用时按照需要工作**

**初始化锁：**

①使用PTHREAD_MUTEX_INITIALIZER

``` c
pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER
```

②动态方法 调用pthread_mutex_init()

```c
int rc=pthread_mutex_init(&lock,NULL);
assert(rc==0)  //alwasy check success!
```

第一个参数是锁本身的地址，第二个参数是可选属性

### 27.4 条件变量

当线程之间必须要发生某种信号时  如果一个线程在等待另一个线程继续执行某些操作，条件变量很有用

```c
int pthread_cond_wait(pthread_cond_t *cond,pthread_mutex_t *mutex);//使调用线程进入休眠状态
int pthread_cond_signal(pthread_cond_t *cond);
```

要使用条件变量 必须另外有一个与此条件相关的锁 **在调用函数时  要持有这个锁**

典型用法：

```c
pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond=PTHREAD_COND_INITIALIZER;
pthread_mutex_lock(&lock);
while(ready==0)	
    pthread_cond_wait(&cond,&lock);
pthread_mutex_unlock(&lock);
```

在初始化相关锁和条件后 一个线程检查变量ready是否已经被设置为0意外的值 如果没有 就调用等待函数休眠 直到其他线程唤醒它

唤醒线程的代码：

```c
pthread_mutex_lock(&lock,NULL);
ready=1;
pthread_cond_signal(&cond);
pthread_mutex_unlock(&lock);
```

**等待调用将锁作为第二个参数  而信号调用只需要一个参数：**因为等待调用除了使线程进入睡眠状态外，还会**让调用者在睡眠的时候释放锁(不然其他线程怎么获得锁  修改临界区内容从而唤醒该线程捏？)**

在被唤醒之后、返回之前。pthread_cond_wait()会重新获得该锁 确保整个过程都持有锁



**每个线程都有自己的栈**：线程的局部变量是线程私有的。线程之间共享数据，值要在堆区或者其他全局可访问的位置 e.g. ①刚刚的例子中ready就是全局变量  ②malloc出来的动态内存是位于堆区的

## 第28章 锁

并发编程最基本问题：我们希望原子式执行一系列指令  但是由于单处理器上的中断(或者多个线程在多处理器上并发执行)我们做不到

**所以我们运用锁**

### 28.1 锁的基本思想

lock()尝试获取锁  如果没有其他线程持有锁 那么该线程会获得锁  进入临界区  如果锁被另一线程持有 那么该调用就不会返回 **这样 当持有该锁的线程位于临界区  其他线程就无法进入临界区**

锁的持有者一旦unlock() 锁就变成可用的了：

①如果没有其他等待线程(即没有其他线程用过lock()并卡在那里) 锁就变成可用状态

②如果有线程卡在lock() **其中一个**就会注意到锁状态的变化  获得该锁  进入临界区

### 28.2 Pthread锁

任何临界区都是用同一个大锁(粗粒度方案)

用不同的锁保护不同的数据和结构  从而允许更多线程进入临界区(细粒度方案)

### 28.4 评价锁

①锁是否有效  能够阻止多个线程进入临界区

②公平性 当锁可用时  是否每一个竞争线程有公平的机会抢到锁  **是否有竞争锁的线程会饿死 一直无法获得锁**

③性能 使用锁之后增加的时间开销

### 28.5 控制中断

最早的互斥解决方案质疑  是**在临界区关闭中断**

优点：没有中断 线程可以确定它的代码会继续执行下去 不会被其他线程干扰

缺点： 要求我们允许所有调用线程执行特权操作(打开关闭中断)即信任这种机制不会被滥用

①一个贪婪的程序可能在开始的时候就调用lock()  从而独占处理器 如果一直死循环就必须重启系统了

②不支持多处理器  如果多个线程运行在不同CPU上 每个线程都试图进入同一个临界区 **即使关闭中断也没有用  线程可以运行在其他处理器上**

③关闭中段导致中断丢失 假如磁盘完成IO读取 但CPU错失了这一事实 那么操作系统如何知道去唤醒等待读取的进程

④效率低

### 28.6 测试并设置指令(原子交换)

如果没有硬件支持 自旋锁   自旋等待在等待其他线程释放锁的时候会浪费时间

尤其是在单处理器上的上 一个等待线程 等待的目标甚至无法运行

### 28.7 实现可用的自旋锁

自旋锁 一直自旋 利用CPU周期 直到锁可用

在单处理器上，需要抢占式的调度器，即不断通过时钟中断一个线程，运行其他线程。否则，自旋锁在单CPU上无法使用 **因为一个自旋的程序永远不会放弃CPU**

### 28.8 评价自旋锁

①正确

②不公平  自旋的线程在竞争条件下可能会永远自旋   可能会导致饿死

③ 单CPU 性能开销相当大  (加上一个线程持有锁进入临界区时被抢占  调度器可能会运行其他每一个线程。而其他线程都在竞争锁 都会在放弃CPU之前 自旋一个时间片 浪费CPU周期)

​	多CPU **性能还不错**(如果线程数大致等于CPU数)

### 28.9 比较并交换

无等待同步   比较并交换强于测试并设置

自旋锁实现   两者无差别

### 28.10 链接的加载和条件式存储指令

```c
//加载
int LoadLinked(int *ptr){
    return *ptr;
}
//条件存储
int StoreConditional(int *ptr,int value){
    if(no one has updated *ptr since the LoadLinked to this address){
        *ptr=value;
        return 1;   //success!
    }else return 0; //failed to update
}
```

条件式存储：只有在上一次加载的地址在期间都没有更新时 才会成功

### 28.11 获取并增加

原子地返回特定地址的旧值，并且让该值自增1

此处查看原书代码

本方法能够保证所有线程都能抢到锁

### 28.12&28.13 解决自旋过多

①在要自旋的时候放弃CPU 让其他线程运行 **让出线程本质上取消调度了它自己**。

在单处理器上 yield方法十分有效。

然而如果多线程反复竞争一把锁。假如有100个线程，一个线程持有锁，在释放锁前被抢站，其他00个线程分别调用lock()，发现锁被抢占，然后让出CPU。那么这99个程序会一直处于运行yield这种模式 直到持有锁的线程再次运行   **上下文切换成本太大**  **而且可能会有饿死情况  一个线程不断谦让地yield  而其他线程反复进入临界区**

### 28.14 使用队列：休眠替代自旋

自旋和让出CPU(yield)真正问题是**存在太多偶然性** 调度程序决定如何调度 如果调度不合理就会出问题

因此  必须显式地事假某种控制    **决定锁释放时 谁能抢到锁**  需要一个队列来保存等待锁的线程

Solaris提供的支持：park()让调用线程休眠         unpark(threadID)唤醒threadID的线程

```c
typedef struct{
    int flag;
    int guard;
    queue_t *q;
}lock_t;

void lock_init{
    m->flag = 0;
    m->guard = 0;
    queue_init(m->q);
}

void lock(lock_t *m){
    while(TestAndSet(&m->guard,1) == 1)
        ;
    if(m->flag==0){
        m->flag=1; //有线程获得锁了
        m->guard=0;
    }else{
      	queue_add(m->q,gettid());  //挨个让未获得锁的线程入队并让他们休眠
        m->guard = 0;
        park();
    }
}

void unlock(lock_t *m){
    while(TestAndSet(&m->guard,1) == 1)
    	;
    if(queue_empty(m->q))
        m->flag = 0;
    else
        unpark(queue_remove(m->q)); //一次只让一个线程醒过来 hold lock for next thread!!
    m->guard = 0; 
}
```

通过队列来控制  避免饿死

PS.思索了一阵子终于想通 有种大仇得报的感觉......

唤醒线程是从该线程休眠的地方继续执行的，那么怎么让从park()处苏醒的线程获得锁呢？**就是直接将释放锁的线程的权限转交传递给获得锁的线程**



**可能出现的竞争条件** 在一个线程将要park()之前 切换到持有锁的线程 并且它释放了锁，那么之前的那个将要park()的线程将长眠不醒

**因为线程已经入队，但是还没睡就被持有锁的线程通过unlock()从队里pop出来并唤，那么等到我要睡的时候，就醒不过来了**

Solaris通过separk()调用解决这个问题。通过该函数，线程表明自己马上就要park。如果刚好另一个线程被调度了并且调用了unpark，那么后面我自己的park就直接返回，不睡觉了。

### 28.15 Linux提供futex

每个futex都关联一个特定的物理内存位置，也有一个事先建好的内核队列   调用者通过futex调用来睡眠或者唤醒

















