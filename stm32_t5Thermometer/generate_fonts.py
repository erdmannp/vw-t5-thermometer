# -*- coding: utf-8 -*-

from fontTools import ttLib
import os
import re
from PIL import Image, ImageFont, ImageDraw
from jinja2 import Environment, FileSystemLoader


def getTtf (font, ttf_searchfolder):
    ttf_files = []
    
    for dirpath, dirnames, filenames in os.walk(ttf_searchfolder):
        for filename in [f for f in filenames if f.endswith(".ttf")]:
            ttf_file = {'dir': dirpath, 'filename': filename}
            ttf_files.append(ttf_file)
            
    for ttf_file in ttf_files:
        ttf_absolute_filename = os.path.join(ttf_file['dir'], ttf_file['filename'])
        tt = ttLib.TTFont(ttf_absolute_filename)
        fm = tt['name'].names[4].string
        Font = fm.decode('ascii', errors ='replace')
                
        Font = re.sub('\x00','',Font)
        if(font == Font):
            return ttf_absolute_filename
        
    return None


def openFonts():
    fonts = []
    fonts.append({
        'font' : "FreeMono",
        'height' : 24 ,
        'width' : 16,
        'characters' : """ !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyzß|°"""
        })
    fonts.append({
        'font' : "OpenSymbol",
        'height' : 20,
        'width' : 14,
        'characters' : '❄'
        })
    
    return fonts


def getImageData(image):
    (width, height) = image.size
    print(width)
    image.load()
    b = image.tobytes()
    print(len(b))
    values = []

    for y in range(0, height):
        uint16_val = 0

        for x in range(0, width):
            if (image.getpixel((x,y)) != 255): 
                print (u'\u2B1B', end='')
                uint16_val += 1 << x
            else:
                print (u'\u2B1C', end='')
        values.append(uint16_val)
        print()
    print('--')
    return values
        
def createFontRaster(f):
    print(font['font'])
    pil_font = ImageFont.truetype(getTtf(font['font'], "/usr/share/fonts"), font['height'])
    results = []

    for ch in f['characters']:
        image = Image.new('1', (int(f['width']), f['height']), color=255)
        draw = ImageDraw.Draw(image)
        draw.text( (0,0), ch, font=pil_font)
        results.append( { 'char': ch, 'data' : getImageData(image) } )
    return results

def createCHeader():
    return

if (__name__ == '__main__'):
    fonts = openFonts()
    environment = Environment(loader=FileSystemLoader("."))
    template = environment.get_template("font_header.template")

    for font in fonts:
        res = createFontRaster(font)
        filename = f"font_{font['font'].lower()}.h"
    
        content = template.render(
            font=font,
            results=res,

        )
        with open(filename, mode="w", encoding="utf-8") as header:
            header.write(content)
        