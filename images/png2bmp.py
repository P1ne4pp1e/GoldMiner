import os
from PIL import Image


def convert_to_bmp(image_path):
    # 打开原始 PNG 图片
    img = Image.open(image_path)

    # 获取图片文件名和扩展名
    file_name, _ = os.path.splitext(image_path)

    # 保存为 BMP 格式
    bmp_path = f"{file_name}.bmp"
    img.save(bmp_path, "BMP")


def main():
    # 获取当前目录下的所有 PNG 文件
    current_dir = os.getcwd()
    png_files = [f for f in os.listdir(current_dir) if f.endswith(".png")]

    for png_file in png_files:
        convert_to_bmp(png_file)
        print(f"已将 {png_file} 转换为 BMP 格式")


if __name__ == "__main__":
    main()
