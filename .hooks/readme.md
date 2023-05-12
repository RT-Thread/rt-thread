# How to use git hook

## SDK install 

Please use cmd `git config --local core.hooksPath .hooks` for git hooks local.

## git hooks使用注意事项

- hooks里面的要安装cppcheck和astyle以及formatting命令行才能使用，如果想要去掉某个选项，在pre-commit中注释掉相应的命令即可。
- 取消hook选项请使用命令`git config --unset --local core.hooksPath .hooks` 可以取消hook格式化文件
- 这个githook不敲命令是不生效的
- githook会用astyle格式化一些文件（这个按照rt-thread coding-style里面的设置来的），这里要注意，如果之前文件没有经过astlye格式化的话，会出现很多修改，如果修改过多，建议不用astyle进行格式化。
- formatting命令只针对`c|cpp|h` 文件，并没有针对文件夹修改等。所以如果有SDK等不希望formatting的文件，请先将hooks功能去掉，commit之后，再考虑使用hooks命令。
- 如果对git的pre-commit不是很熟悉，建议可以先不用这个hooks。

