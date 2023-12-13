import sys
from PIL import Image
import os
# Check if command line argument is provided
if len(sys.argv) < 2:
    print("Please provide a name as a command line argument.")
    sys.exit(1)

name = sys.argv[1]

with open("scene.ppm") as file:
    # Read header P3
    header = file.readline()
    # Read width and height
    width, height = map(int, file.readline().split())
    # Create new png
    img = Image.new("RGB", (width, height))
    # Read max color value
    max_color = int(file.readline())
    # Read all lines
    lines = " ".join([line.strip() for line in file.readlines()])
    lines = lines.split(" ")
    pixels = []
    for i in range(0, len(lines), 3):
        pixels.append((int(lines[i]), int(lines[i+1]), int(lines[i+2])))
    img.putdata(pixels)
    # Create renders folder if it doesn't exist
    os.makedirs("renders", exist_ok=True)
    img.save(f"renders/default{name}.png")
