## Attentions

1. This folder is "common" for armlibc newlibc and dlib.

2. If you want to add new `.c` files, please do not forget to fix SConscript file too. eg:

```python
if GetDepend('RT_USING_POSIX') == False:
        SrcRemove(src, ['unistd.c'])
```