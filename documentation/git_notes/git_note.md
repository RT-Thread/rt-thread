# Git 基本命令学习

## 用户名设置

项目级别仓库用户名设置：

* git config user.name Ericyinwork

* git config user.email ericyinwork@163.com

查看仓库用户名设置

* cat .git/config

系统级别仓库用户名设置：
* git config --global user.name Ericyinwork
* git config --global user.email ericyinwork@163.com

查看系统仓库用户名设置

* cat ~/.gitconfig

## 基本操作

* git status									查看工作区、暂存区状态

* git add ./git add [文件名]		提交到暂存区，并且转换换行符
* git rm -cached [文件名]		     从暂存区撤回
* git commit -m"commit message" [file name]	将暂存区的内容提交到本地库
* git restore [文件名]			  	撤销某个文件修改的操作
* git reset HEAD [file]			  可以吧暂存区的修改撤销掉（unstage），重新放回工作区
### 查看历史记录
* git log 					   查看版本历史记录
* git log --pretty=oneline		 每个历史只显示一行（hash值和日志）
* git log --oneline			   每个历史只显示一行且显示hash的部分值
* git reflog				  现实历史只显示一行，并且显示指针（要移动到版本多少步）
### 版本前进后退
* git reset --hard [局部索引值]	
* git reset --hard HEAD^^		注：一个^表示后退一步，n 个^表示后退 n 步
* git reset --hard HEAD~n		注：表示后退 n 步
### 比较文件差异
git diff [文件名]				  将工作区中的文件和暂存区进行比较
git diff [本地库中的文件和本地库历史记录比较]
## 分支管理

* git branch [分支名]			      创建分支
* git branch -v 		     	  	  查看分支
* git checkout [分支名]		       切换分支
* git merge [有新内容分支名]	 	合并分支
* git branch -d [分支名]			删除分支

![image-20210707193138830](F:\rt-thread\documentation\git_notes\git_note.assets\image-20210707193138830.png)

### 合并分支方法

**git checkout [****被合并分支名****master]** /*切换分支

第二步：执行 merge 命令 (合并分支指令)

**git merge [有新内容分支名***]**

冲突原因: 2个分支,修改同一文件,同一位置,修改内容不一样时.

**冲突的解决:**

第一步：编辑文件，删除特殊符号

第二步：把文件修改到满意的程度，保存退出

第三步：git add [文件名]

第四步：git commit -m "日志信息"

**注意：此时** **commit** **一定不能带具体文件名**

## 远程仓库

* git remote -v					查看当前所有远程地址别名
* git remote add [别名 origin] [远程地址]
* git push [别名] [分支名]    or  git push origin master
* $ git config --global http.sslVerify "false"			重新登录
* git clone [远程地址]							克隆仓库
克隆效果:
完整的把远程库下载到本地
创建 origin 远程地址别名 (git remote -v查看远程库别名)
初始化本地库(就是:git init)
* git pull = fetch+merge
git fetch [远程库地址别名origin] [远程分支名master]   /*抓去下来
 git checkout origin/master   /*切换到链接地址(别名)的master(可查看抓取下来内容
切换回  git checkout master
git merge [远程库地址别名origin/master远程分支名]   /*合并
git pull [远程库地址别名] [远程分支名]   /*等于上面步骤
## GitFlow工作流
* 主干分支 master 
主要负责管理正在运行的生产环境代码,永远保持与正在运行的生产环境完全一致
* 开发分支 develop 
主要负责管理正在开发过程中的代码。一般情况下应该是最新的代码。
* bug 修理分支 hotfix
主要负责管理生产环境下出现的紧急修复的代码。从主干分支分出，修理完毕并测试上线后，并回主干分支。并回后，视情况可以删除该分支。
* 准生产分支（预发布分支） release 
较大的版本上线前，会从开发分支中分出准生产分支，进行最后阶段的集成测试。该版本上线后，会合并到主干分支。生产环境运行一段阶段较稳定后可以视情况删除。
* 功能分支 feature 
为了不影响较短周期的开发工作，一般把中长期开发模块，会从开发分支中独立出来。开发完成后会合并到开发分支。
 ![image-20210707194107228](F:\rt-thread\documentation\git_notes\git_note.assets\image-20210707194107228.png)

## 团队协作
略

## Vim

创建文本		vim 文件名.txt  

 保存并退出	Esc  :wq  回车  



## 设置签名

用户名：Ericyinwork

Email地址：ericyinwork@163.com

作用:区分不同开发人员的身份

辨析：与登录远程库（代码托管中心）账号密码没有任何关系

命令：

项目级别仅在本地仓库有效

系统级别：登录当前操作系统用户范围

## 异常报错解决

![image-20210617142606742](F:\rt-thread\documentation\git_notes\git_note.assets\image-20210617142606742.png)

重新登录

$ git config --global http.sslVerify "false"

