# 编程技巧

## 1.  INF 0x3f3f3f3f

`0x3f3f3f3f` 是满足以下两个条件的最大整数：

1. 整数的两倍不超过 `0x7f7f7f7f`，即 `int` 能表示的最大正整数。
2. 整数的每 $8$ 位（每个字节）都是相同的。

:star: `memset(a, val, sizeof a)` 初始化数组的含义？

`memset` 是按字节赋初始值，它将数值 `val(0x3f, -1)` 填充到数组 `a` 的每个字节上。

当需要将数组值初始化成 $\infty$ 时，为避免加法算术上溢出，常用 `memset(a, 0x3f, sizeof(a))` 给数组赋值。


## 2. 输入输出相关

`cin, cout` 代码简单速度慢

`scanf, printf` 速度快

```cpp
#include <iostream>
#include <string.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); // 加速cin/cout，限制：不能再使用scanf/printf了
    
    // 当输入输出的规模 >= 1000000，建议用scanf/printf，否则建议用cin/cout
    
    cin / cout  // 好处：代码简单，坏处：速度慢
        
    scanf/printf  //  好处：速度快， 坏处：难写
}
```

`scanf` 函数返回值：表示正确输入参数的个数
`0`，表示用户的输入不匹配，无法正确输入任何值。

`EOF`，这是在 `stdio.h` 里面定义的常量（通常值为 $-1$），表示输入流已经结束。在 Windows 下，用户按下`CTRL+Z`（会看到一个 ^Z 字符）再按下回车（可能需要重复 $2$ 次），就表示输入结束；Linux/Unix下使用`CTRL+D` 表示输入结束。

```cpp
while (scanf("%s %c %c", str, &oldchar, &newchar) == 3) 
/* 或!= EOF , 但前者更好 */
{
    ; //处理
}
```


## 3. map 和 unordered_map 区别

`map` 内部是红黑树，有序，很多操作是 `logn` 复杂度，但占用空间多

`unordered_map`  内部是哈希表，查找速度快

```cpp
map<int,int>::iterator it=m.lower_bound(x);
//返回比第一个大于或等于x的值的位置 ，当m为空时，返回m.end()

map<int,int>::iterator it=m.upper_bound(x);
//返回比最后一个大于或等于x的值的
```

## 4. 字符串相关

int to string

```cpp
int a=12345;
string b=to_string(a);
```

char to int


```cpp
string a = '1'; 
int b = a - '0';
```


大小写字母可匹配 
```cpp
s[i] != (s[j]^32) 
```


## 5. 数组相关

初始化
```cpp
f = vector<int>(n+1, 0);
vector<vector<int>> A(m, vector<int>(n, 0))
path = vector<string>(n, string(n,'.'));

```

用 `memset` 
```cpp
int dp[101];
memset(dp, 0, sizeof(dp));
```


## 6. 常用 STD 函数

排序 
```cpp
static bool cmp(vector<int>&a,vector<int>&b)
{
    return a[1]<b[1];
}

sort(x.beging(),x.end(),cmp);

// 用匿名函数速度慢：
sort(intervals.begin(),intervals.end(),[](vector<int> a, vector<int> b){
    return a[1]<b[1];
});
```

累加
```cpp
accumulate(x.begin(),x.end(),0);	// init=0
```
