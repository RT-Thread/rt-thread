# 假设我们有一个名为'example.txt'的文件，我们想要修改它
header_file_path = 'inc/ht32_usbd_core.h'
source_file_path = 'src/ht32_usbd_core.c'

def modification(file_path):  
    # 打开文件
    with open(file_path, 'r+') as file:  # 'r+'模式允许读写
        # 读取文件内容
        content = file.read()
        print("文件打开成功！")

        # 假设我们要将所有的'old_string'替换为'new_string'
        # updated_content = content.replace('old_string', 'new_string')
        content = content.replace('USB_STATE_UNCONNECTED', 'USER_USB_STATE_UNCONNECTED')
        content = content.replace('USB_STATE_ATTACHED', 'USER_USB_STATE_ATTACHED')
        content = content.replace('USB_STATE_POWERED', 'USER_USB_STATE_POWERED')
        content = content.replace('USB_STATE_SUSPENDED', 'USER_USB_STATE_SUSPENDED')
        content = content.replace('USB_STATE_DEFAULT', 'USER_USB_STATE_DEFAULT')
        content = content.replace('USB_STATE_ADDRESS', 'USER_USB_STATE_ADDRESS')
        content = content.replace('USB_STATE_CONFIGURED', 'USER_USB_STATE_CONFIGURED')

        # 移动文件指针到文件开头，准备写入
        file.seek(0)

        # 写入更新后的内容
        file.write(content)

        # 截断文件，删除旧内容（如果更新后的内容比原内容短）
        file.truncate()


# 文件现在已经被关闭，并且更改被保存
if __name__ == '__main__':
    modification(header_file_path)
    print('头文件已修改！\r\n')
    modification(source_file_path)
    print('源文件已修改！\r\n')
    print('请输入退出：')
    
