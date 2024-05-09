import os
import subprocess

# 定义测试文件文件夹路径和输出文件夹路径
test_files_folder = '../Lab3Test'
output_folder = '../Lab3Test/OutPut'
output_name = './output.ir'

# 遍历测试文件文件夹中的文件
for filename in os.listdir(test_files_folder):
    # 检查文件是否是普通文件
    if os.path.isfile(os.path.join(test_files_folder, filename)):
        # 构建parser命令
        parser_command = ['./parser', os.path.join(test_files_folder, filename), output_name]

        # 构建输出文件路径
        output_file = os.path.join(output_folder, f'{filename}_output.txt')
        subprocess.run(parser_command)

        # 读取output.ir文件内容
        with open(output_name, 'r') as ir_file:
            ir_content = ir_file.read()

        # 将output.ir文件内容写入到输出文件中
        with open(output_file, 'w') as f:
            f.write(ir_content)

        # 清空output.ir文件内容
        with open('output.ir', 'w') as ir_file:
            ir_file.truncate(0)

