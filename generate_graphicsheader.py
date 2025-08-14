from pathlib import Path


paths_fontlarge = list(Path("graphics").glob("font_*_large.xbm"))
paths_fontsmall = list(Path("graphics").glob("font_*_small.xbm"))
paths_icons = list(Path("graphics").glob("[!font_]*.xbm"))
bitmap_name_overrides = {  # filename -> preferred name
    "percent": "%",
    "dot": ".",
    "colon": ":",
    "degree": "°",
    "dash": "-"
}

output = ""


# Add includes
for path in paths_fontlarge + paths_fontsmall + paths_icons:
    output += f"#include \"graphics/{path.name}\"\n"

output += """
#define FONT_LARGE_BASELINE 5
#define FONT_LARGE_PADDING 3
#define FONT_SMALL_PADDING 2
"""


# Add bitmap struct
output += """\n
struct Bitmap
{
    unsigned char* name;
    unsigned char* bits;
    int width;
    int height;
};\n\n"""


def getname(name):
    if name in bitmap_name_overrides:
        return bitmap_name_overrides[name]
    else:
        return name


# Fill large font array
output += f"const Bitmap font_large[{len(paths_fontlarge)}] = \n{{\n"
for path in paths_fontlarge:
    with open(path) as file:
        widthname = file.readline().split(" ")[1]
        heightname = file.readline().split(" ")[1]
        bitsname = file.readline().split(" ")[3][:-2]
        name = getname(widthname.split("_")[1])

    output += f"    {{ \"{name}\", {bitsname}, {widthname}, {heightname} }},\n"

output = output[:-2] + "\n};\n\n"


# Fill small font array
output += f"const Bitmap font_small[{len(paths_fontsmall)}] = \n{{\n"
for path in paths_fontsmall:
    with open(path) as file:
        widthname = file.readline().split(" ")[1]
        heightname = file.readline().split(" ")[1]
        bitsname = file.readline().split(" ")[3][:-2]
        name = getname(widthname.split("_")[1])

    output += f"    {{ \"{name}\", {bitsname}, {widthname}, {heightname} }},\n"

output = output[:-2] + "\n};\n\n"


# Fill icon array
output += f"const Bitmap icons[{len(paths_icons)}] = \n{{\n"
for path in paths_icons:
    with open(path) as file:
        widthname = file.readline().split(" ")[1]
        heightname = file.readline().split(" ")[1]
        bitsname = file.readline().split(" ")[3][:-2]
        name = getname(widthname.split("_")[1])

    output += f"    {{ \"{name}\", {bitsname}, {widthname}, {heightname} }},\n"

output = output[:-2] + "\n};\n\n"


# Add search functions
output += f"""
Bitmap getBitmapLarge(char* name)
{{
    for (int i = 0; i < {len(paths_fontlarge)}; i++)
        if (strcmp(name, font_large[i].name) == 0)
            return font_large[i];
}}
"""

output += f"""
Bitmap getBitmapSmall(char* name)
{{
    for (int i = 0; i < {len(paths_fontsmall)}; i++)
        if (strcmp(name, font_small[i].name) == 0)
            return font_small[i];
}}
"""

output += f"""
Bitmap getBitmapIcon(char* name)
{{
    for (int i = 0; i < {len(paths_icons)}; i++)
        if (strcmp(name, icons[i].name) == 0)
            return icons[i];
}}
"""


# Print for inspection
print(output)

# Optionally write to file
if input("\nWrite to graphics.h? (y/n) ") in "yY":
    with open("graphics.h", "w", encoding="utf-8") as file:
        file.write(output)



