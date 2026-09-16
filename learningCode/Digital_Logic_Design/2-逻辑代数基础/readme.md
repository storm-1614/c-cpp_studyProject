# 逻辑代数基础

$$
Y = A + AB + A\overline{BC} + BC + \overline{B}C
$$

化简。  
## 逻辑函数及其化简
### 逻辑代数化简
#### 公式化简法
$$
\begin{array}{|c|c|c|}
\hline
\text{类别} & \text{公式} & \text{公式} \\
\hline
\text{0-1律} & (1)\ A\cdot 1=A,\quad (3)\ A\cdot 0=0 & (2)\ A+0=A,\quad (4)\ A+1=1 \\
\hline
\text{交换律} & (5)\ A\cdot B=B\cdot A & (6)\ A+B=B+A \\
\hline
\text{结合律} & (7)\ A\cdot(B\cdot C)=(A\cdot B)\cdot C & (8)\ A+(B+C)=(A+B)+C \\
\hline
\text{分配律} & (9)\ A\cdot(B+C)=A\cdot B+A\cdot C & (10)\ A+(B\cdot C)=(A+B)\cdot(A+C) \\
\hline
\text{互补律} & (11)\ A\cdot\overline{A}=0 & (12)\ A+\overline{A}=1 \\
\hline
\text{重叠律} & (13)\ A\cdot A=A & (14)\ A+A=A \\
\hline
\text{反演律} & (15)\ \overline{A\cdot B}=\overline{A}+\overline{B} & (16)\ \overline{A+B}=\overline{A}\cdot\overline{B} \\
\hline
\text{还原律} & (17)\ \overline{\overline{A}}=A & \\
\hline
\end{array}
$$
难点：10, 15, 16  
上面图表左右互为对偶式。  

#### 吸收律

$\text{(18)}\ A+AB=A$  
$\text{(19)}\ A\cdot(A+B)=A$  
$\text{(20)}\ A+\overline{A}B=A+B$  
$\text{(21)}\ AB+\overline{A}C+BC=AB+\overline{A}C$  
$\text{(22)}\ AB+\overline{A}C+BCD=AB+\overline{A}C$  

(1) 并项法  
利用公式 $A+\overline{A}=1$ 或公式 $AB+A\overline{B}=A$ 进行化简，通过合并公因子。消去变量。  


#### 规则
反演规则（摩根定理）——便于实现反函数。  
$\overline{A+B}=\overline{A}\overline{B}$
$\overline{A}\overline{B} = \overline{A}+\overline{B}$


对偶规则。  

#### 记忆
基础公式：  
$A + 0 = A$  
$A\cdot 1=A$  
$A + 1 = 1$  
$A\cdot 0 = 0$   
$A+A=A$  
$A\cdot A = A$  
$A\overline{A}=A$  
本质就是：  
- 或 0 不变，或 1 必为 1。  
- 与 1 不变，与 0 必为 0。  
- 自己和自己还是自己。   
- 原变量和反变量“或”为1，“与” 为 0  

交换律、结合律、分配律:  
$A+B=B+A$  
### 卡诺图化简
