## 这是PPC E200Z0的移植文件。适用于MPC56、SPC56系列的单片机。

### 使用步骤：
#### 1.   请把该目录下的文件加入到工程中。
#### 2.  然后移植一个定时器，比如PIT定时器。 在定时器中断中，添加如下代码：
			rt_interrupt_enter();	
			rt_tick_increase();
			rt_interrupt_leave(); 
#### 3. 在任何中断中都需要加入		rt_interrupt_enter、rt_interrupt_leave 函数，具体请看RTT文档。
