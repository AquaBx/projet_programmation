from PIL import Image

im = Image.open('map.png') # Can be many different formats.
pix = im.load()


color_to_offset = {
    (112, 72, 24, 255): "3 0",
    (255, 229, 0, 255): "0 0",
    (50, 80, 26, 255): "1 0",
    (105, 165, 57, 255): "2 0",
    (0, 253, 255, 255): "1 1",
    (52, 104, 105, 255): "0 1"
}

TILE_WIDTH, TILE_HEIGHT = 16, 16
width, height = im.size

out = f"MAPV1\n{width*TILE_WIDTH} {height*TILE_HEIGHT}\n"
for y in range(height):
    for x in range(width):
        out += f"0 {x*TILE_WIDTH} {y*TILE_HEIGHT} {color_to_offset[pix[x, y]]} 0\n"

out+=f"2 {width*TILE_WIDTH//2} {height*TILE_HEIGHT//2}"

with open("out.txt", 'w') as f:
    f.write(out)