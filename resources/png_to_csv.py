from PIL import Image

im = Image.open('map.png') # Can be many different formats.
pix = im.load()

out = ""

TILE = 0

col_to_texture = {
    (112, 72, 24, 255): "dirt",
    (255, 229, 0, 255): "sand",
    (50, 80, 26, 255): "forest",
    (105, 165, 57, 255): "grass",
    (0, 253, 255, 255): "water",
    (52, 104, 105, 255): "deep_water",
}


TILE_WIDTH, TILE_HEIGHT = 16, 16
width, height = im.size

out += str(width * TILE_WIDTH) + " " + str(height * TILE_HEIGHT) + "\n"
for y in range(height):
    for x in range(width):
        out += f"0 {x * TILE_WIDTH} {y * TILE_HEIGHT} {col_to_texture[pix[x, y]]}\n"

with open("out.txt", 'w') as f:
    f.write(out)