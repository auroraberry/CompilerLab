import os
import subprocess

# 定义测试文件文件夹路径和输出文件夹路径
test_files_folder = '../Test'
output_folder = '../Test/Output'

# 遍历测试文件文件夹中的文件
for filename in os.listdir(test_files_folder):
    # 检查文件是否是普通文件
    if os.path.isfile(os.path.join(test_files_folder, filename)):
        # 构建parser命令
        parser_command = ['./parser', os.path.join(test_files_folder, filename)]

        # 构建输出文件路径
        output_file = os.path.join(output_folder, f'{filename}_output.txt')

        # 运行parser可执行文件，并将结果写入到输出文件中
        with open(output_file, 'w') as f:
            subprocess.run(parser_command, stdout=f)
