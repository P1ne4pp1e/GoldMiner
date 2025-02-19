import os
from PIL import Image

def create_mask(image_path):
    # 打开原始图片
    img = Image.open(image_path).convert("RGBA")
    width, height = img.size

    # 创建掩码图（L模式表示灰度图）
    mask = Image.new("L", (width, height), 255)

    # 遍历原始图片的每个像素
    for x in range(width):
        for y in range(height):
            r, g, b, a = img.getpixel((x, y))
            if a > 0:
                mask.putpixel((x, y), 0)
            else:
                mask.putpixel((x, y), 255)
    #
    # # 设置最下面一行和最右边一列像素为纯黑
    # for x in range(width):
    #     mask.putpixel((x, height - 1), 255) # 最下面一行
    # for y in range(height):
    #     mask.putpixel((width - 1, y), 255)  # 最右边一列

    return mask

def main():
    # 获取当前目录下的所有 PNG 文件
    current_dir = os.getcwd()
    png_files = [f for f in os.listdir(current_dir) if f.endswith(".png")]

    for png_file in png_files:
        mask = create_mask(png_file)
        mask_filename = os.path.join(current_dir, f"mask_{os.path.splitext(png_file)[0]}.bmp")
        mask.save(mask_filename, "BMP")
        print(f"掩码图已生成并保存为 {mask_filename}")

if __name__ == "__main__":
    main()
