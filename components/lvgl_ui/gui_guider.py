# Copyright 2021 NXP
# SPDX-License-Identifier: MIT

import SDL
import utime as time
import usys as sys
import lvgl as lv
import lodepng as png
import ustruct

lv.init()
SDL.init(w=240,h=320)

# Register SDL display driver.
disp_buf1 = lv.disp_draw_buf_t()
buf1_1 = bytearray(240*10)
disp_buf1.init(buf1_1, None, len(buf1_1)//4)
disp_drv = lv.disp_drv_t()
disp_drv.init()
disp_drv.draw_buf = disp_buf1
disp_drv.flush_cb = SDL.monitor_flush
disp_drv.hor_res = 240
disp_drv.ver_res = 320
disp_drv.register()

# Regsiter SDL mouse driver
indev_drv = lv.indev_drv_t()
indev_drv.init() 
indev_drv.type = lv.INDEV_TYPE.POINTER
indev_drv.read_cb = SDL.mouse_read
indev_drv.register()

# Below: Taken from https://github.com/lvgl/lv_binding_micropython/blob/master/driver/js/imagetools.py#L22-L94

COLOR_SIZE = lv.color_t.__SIZE__
COLOR_IS_SWAPPED = hasattr(lv.color_t().ch,'green_h')

class lodepng_error(RuntimeError):
    def __init__(self, err):
        if type(err) is int:
            super().__init__(png.error_text(err))
        else:
            super().__init__(err)

# Parse PNG file header
# Taken from https://github.com/shibukawa/imagesize_py/blob/ffef30c1a4715c5acf90e8945ceb77f4a2ed2d45/imagesize.py#L63-L85

def get_png_info(decoder, src, header):
    # Only handle variable image types

    if lv.img.src_get_type(src) != lv.img.SRC.VARIABLE:
        return lv.RES.INV

    data = lv.img_dsc_t.__cast__(src).data
    if data == None:
        return lv.RES.INV

    png_header = bytes(data.__dereference__(24))

    if png_header.startswith(b'\211PNG\r\n\032\n'):
        if png_header[12:16] == b'IHDR':
            start = 16
        # Maybe this is for an older PNG version.
        else:
            start = 8
        try:
            width, height = ustruct.unpack(">LL", png_header[start:start+8])
        except ustruct.error:
            return lv.RES.INV
    else:
        return lv.RES.INV

    header.always_zero = 0
    header.w = width
    header.h = height
    header.cf = lv.img.CF.TRUE_COLOR_ALPHA

    return lv.RES.OK

def convert_rgba8888_to_bgra8888(img_view):
    for i in range(0, len(img_view), lv.color_t.__SIZE__):
        ch = lv.color_t.__cast__(img_view[i:i]).ch
        ch.red, ch.blue = ch.blue, ch.red

# Read and parse PNG file

def open_png(decoder, dsc):
    img_dsc = lv.img_dsc_t.__cast__(dsc.src)
    png_data = img_dsc.data
    png_size = img_dsc.data_size
    png_decoded = png.C_Pointer()
    png_width = png.C_Pointer()
    png_height = png.C_Pointer()
    error = png.decode32(png_decoded, png_width, png_height, png_data, png_size)
    if error:
        raise lodepng_error(error)
    img_size = png_width.int_val * png_height.int_val * 4
    img_data = png_decoded.ptr_val
    img_view = img_data.__dereference__(img_size)

    if COLOR_SIZE == 4:
        convert_rgba8888_to_bgra8888(img_view)
    else:
        raise lodepng_error("Error: Color mode not supported yet!")

    dsc.img_data = img_data
    return lv.RES.OK

# Above: Taken from https://github.com/lvgl/lv_binding_micropython/blob/master/driver/js/imagetools.py#L22-L94

decoder = lv.img.decoder_create()
decoder.info_cb = get_png_info
decoder.open_cb = open_png

def anim_x_cb(obj, v):
    obj.set_x(v)

def anim_y_cb(obj, v):
    obj.set_y(v)

def ta_event_cb(e,kb):
    code = e.get_code()
    ta = e.get_target()
    if code == lv.EVENT.FOCUSED:
        kb.set_textarea(ta)
        kb.clear_flag(lv.obj.FLAG.HIDDEN)

    if code == lv.EVENT.DEFOCUSED:
        kb.set_textarea(None)
        kb.add_flag(lv.obj.FLAG.HIDDEN)


scrPowerMeter = lv.obj()
# create style style_scrpowermeter_main_main_default
style_scrpowermeter_main_main_default = lv.style_t()
style_scrpowermeter_main_main_default.init()
style_scrpowermeter_main_main_default.set_bg_color(lv.color_make(0x00,0x00,0x00))
style_scrpowermeter_main_main_default.set_bg_opa(255)

# add style for scrPowerMeter
scrPowerMeter.add_style(style_scrpowermeter_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

scrPowerMeter_labelVolVal = lv.label(scrPowerMeter)
scrPowerMeter_labelVolVal.set_pos(75,150)
scrPowerMeter_labelVolVal.set_size(120,40)
scrPowerMeter_labelVolVal.set_text("0.000")
scrPowerMeter_labelVolVal.set_long_mode(lv.label.LONG.CLIP)
scrPowerMeter_labelVolVal.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_scrpowermeter_labelvolval_main_main_default
style_scrpowermeter_labelvolval_main_main_default = lv.style_t()
style_scrpowermeter_labelvolval_main_main_default.init()
style_scrpowermeter_labelvolval_main_main_default.set_radius(0)
style_scrpowermeter_labelvolval_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_scrpowermeter_labelvolval_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_scrpowermeter_labelvolval_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_scrpowermeter_labelvolval_main_main_default.set_bg_opa(0)
style_scrpowermeter_labelvolval_main_main_default.set_text_color(lv.color_make(0x00,0x7f,0xff))
try:
    style_scrpowermeter_labelvolval_main_main_default.set_text_font(lv.font_MONACO_40)
except AttributeError:
    try:
        style_scrpowermeter_labelvolval_main_main_default.set_text_font(lv.font_montserrat_40)
    except AttributeError:
        style_scrpowermeter_labelvolval_main_main_default.set_text_font(lv.font_montserrat_16)
style_scrpowermeter_labelvolval_main_main_default.set_text_letter_space(0)
style_scrpowermeter_labelvolval_main_main_default.set_pad_left(0)
style_scrpowermeter_labelvolval_main_main_default.set_pad_right(0)
style_scrpowermeter_labelvolval_main_main_default.set_pad_top(0)
style_scrpowermeter_labelvolval_main_main_default.set_pad_bottom(0)

# add style for scrPowerMeter_labelVolVal
scrPowerMeter_labelVolVal.add_style(style_scrpowermeter_labelvolval_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

scrPowerMeter_labelCurVal = lv.label(scrPowerMeter)
scrPowerMeter_labelCurVal.set_pos(75,200)
scrPowerMeter_labelCurVal.set_size(120,40)
scrPowerMeter_labelCurVal.set_text("0.000")
scrPowerMeter_labelCurVal.set_long_mode(lv.label.LONG.CLIP)
scrPowerMeter_labelCurVal.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_scrpowermeter_labelcurval_main_main_default
style_scrpowermeter_labelcurval_main_main_default = lv.style_t()
style_scrpowermeter_labelcurval_main_main_default.init()
style_scrpowermeter_labelcurval_main_main_default.set_radius(0)
style_scrpowermeter_labelcurval_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_scrpowermeter_labelcurval_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_scrpowermeter_labelcurval_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_scrpowermeter_labelcurval_main_main_default.set_bg_opa(0)
style_scrpowermeter_labelcurval_main_main_default.set_text_color(lv.color_make(0xff,0x00,0x00))
try:
    style_scrpowermeter_labelcurval_main_main_default.set_text_font(lv.font_MONACO_40)
except AttributeError:
    try:
        style_scrpowermeter_labelcurval_main_main_default.set_text_font(lv.font_montserrat_40)
    except AttributeError:
        style_scrpowermeter_labelcurval_main_main_default.set_text_font(lv.font_montserrat_16)
style_scrpowermeter_labelcurval_main_main_default.set_text_letter_space(0)
style_scrpowermeter_labelcurval_main_main_default.set_pad_left(0)
style_scrpowermeter_labelcurval_main_main_default.set_pad_right(0)
style_scrpowermeter_labelcurval_main_main_default.set_pad_top(0)
style_scrpowermeter_labelcurval_main_main_default.set_pad_bottom(0)

# add style for scrPowerMeter_labelCurVal
scrPowerMeter_labelCurVal.add_style(style_scrpowermeter_labelcurval_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

scrPowerMeter_labelPwrVal = lv.label(scrPowerMeter)
scrPowerMeter_labelPwrVal.set_pos(75,250)
scrPowerMeter_labelPwrVal.set_size(120,40)
scrPowerMeter_labelPwrVal.set_text("0.000")
scrPowerMeter_labelPwrVal.set_long_mode(lv.label.LONG.CLIP)
scrPowerMeter_labelPwrVal.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_scrpowermeter_labelpwrval_main_main_default
style_scrpowermeter_labelpwrval_main_main_default = lv.style_t()
style_scrpowermeter_labelpwrval_main_main_default.init()
style_scrpowermeter_labelpwrval_main_main_default.set_radius(0)
style_scrpowermeter_labelpwrval_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_scrpowermeter_labelpwrval_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_scrpowermeter_labelpwrval_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_scrpowermeter_labelpwrval_main_main_default.set_bg_opa(0)
style_scrpowermeter_labelpwrval_main_main_default.set_text_color(lv.color_make(0xff,0x7f,0x00))
try:
    style_scrpowermeter_labelpwrval_main_main_default.set_text_font(lv.font_MONACO_40)
except AttributeError:
    try:
        style_scrpowermeter_labelpwrval_main_main_default.set_text_font(lv.font_montserrat_40)
    except AttributeError:
        style_scrpowermeter_labelpwrval_main_main_default.set_text_font(lv.font_montserrat_16)
style_scrpowermeter_labelpwrval_main_main_default.set_text_letter_space(0)
style_scrpowermeter_labelpwrval_main_main_default.set_pad_left(0)
style_scrpowermeter_labelpwrval_main_main_default.set_pad_right(0)
style_scrpowermeter_labelpwrval_main_main_default.set_pad_top(0)
style_scrpowermeter_labelpwrval_main_main_default.set_pad_bottom(0)

# add style for scrPowerMeter_labelPwrVal
scrPowerMeter_labelPwrVal.add_style(style_scrpowermeter_labelpwrval_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

scrPowerMeter_labelVolLab = lv.label(scrPowerMeter)
scrPowerMeter_labelVolLab.set_pos(15,150)
scrPowerMeter_labelVolLab.set_size(60,40)
scrPowerMeter_labelVolLab.set_text("U:")
scrPowerMeter_labelVolLab.set_long_mode(lv.label.LONG.CLIP)
scrPowerMeter_labelVolLab.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_scrpowermeter_labelvollab_main_main_default
style_scrpowermeter_labelvollab_main_main_default = lv.style_t()
style_scrpowermeter_labelvollab_main_main_default.init()
style_scrpowermeter_labelvollab_main_main_default.set_radius(0)
style_scrpowermeter_labelvollab_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_scrpowermeter_labelvollab_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_scrpowermeter_labelvollab_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_scrpowermeter_labelvollab_main_main_default.set_bg_opa(0)
style_scrpowermeter_labelvollab_main_main_default.set_text_color(lv.color_make(0x00,0x7f,0xff))
try:
    style_scrpowermeter_labelvollab_main_main_default.set_text_font(lv.font_MONACO_40)
except AttributeError:
    try:
        style_scrpowermeter_labelvollab_main_main_default.set_text_font(lv.font_montserrat_40)
    except AttributeError:
        style_scrpowermeter_labelvollab_main_main_default.set_text_font(lv.font_montserrat_16)
style_scrpowermeter_labelvollab_main_main_default.set_text_letter_space(0)
style_scrpowermeter_labelvollab_main_main_default.set_pad_left(0)
style_scrpowermeter_labelvollab_main_main_default.set_pad_right(0)
style_scrpowermeter_labelvollab_main_main_default.set_pad_top(0)
style_scrpowermeter_labelvollab_main_main_default.set_pad_bottom(0)

# add style for scrPowerMeter_labelVolLab
scrPowerMeter_labelVolLab.add_style(style_scrpowermeter_labelvollab_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

scrPowerMeter_labelCurLab = lv.label(scrPowerMeter)
scrPowerMeter_labelCurLab.set_pos(15,200)
scrPowerMeter_labelCurLab.set_size(60,40)
scrPowerMeter_labelCurLab.set_text("I:")
scrPowerMeter_labelCurLab.set_long_mode(lv.label.LONG.CLIP)
scrPowerMeter_labelCurLab.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_scrpowermeter_labelcurlab_main_main_default
style_scrpowermeter_labelcurlab_main_main_default = lv.style_t()
style_scrpowermeter_labelcurlab_main_main_default.init()
style_scrpowermeter_labelcurlab_main_main_default.set_radius(0)
style_scrpowermeter_labelcurlab_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_scrpowermeter_labelcurlab_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_scrpowermeter_labelcurlab_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_scrpowermeter_labelcurlab_main_main_default.set_bg_opa(0)
style_scrpowermeter_labelcurlab_main_main_default.set_text_color(lv.color_make(0xff,0x00,0x00))
try:
    style_scrpowermeter_labelcurlab_main_main_default.set_text_font(lv.font_MONACO_40)
except AttributeError:
    try:
        style_scrpowermeter_labelcurlab_main_main_default.set_text_font(lv.font_montserrat_40)
    except AttributeError:
        style_scrpowermeter_labelcurlab_main_main_default.set_text_font(lv.font_montserrat_16)
style_scrpowermeter_labelcurlab_main_main_default.set_text_letter_space(0)
style_scrpowermeter_labelcurlab_main_main_default.set_pad_left(0)
style_scrpowermeter_labelcurlab_main_main_default.set_pad_right(0)
style_scrpowermeter_labelcurlab_main_main_default.set_pad_top(0)
style_scrpowermeter_labelcurlab_main_main_default.set_pad_bottom(0)

# add style for scrPowerMeter_labelCurLab
scrPowerMeter_labelCurLab.add_style(style_scrpowermeter_labelcurlab_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

scrPowerMeter_labelPwrLab = lv.label(scrPowerMeter)
scrPowerMeter_labelPwrLab.set_pos(15,250)
scrPowerMeter_labelPwrLab.set_size(60,40)
scrPowerMeter_labelPwrLab.set_text("P:")
scrPowerMeter_labelPwrLab.set_long_mode(lv.label.LONG.WRAP)
scrPowerMeter_labelPwrLab.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_scrpowermeter_labelpwrlab_main_main_default
style_scrpowermeter_labelpwrlab_main_main_default = lv.style_t()
style_scrpowermeter_labelpwrlab_main_main_default.init()
style_scrpowermeter_labelpwrlab_main_main_default.set_radius(0)
style_scrpowermeter_labelpwrlab_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_scrpowermeter_labelpwrlab_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_scrpowermeter_labelpwrlab_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_scrpowermeter_labelpwrlab_main_main_default.set_bg_opa(0)
style_scrpowermeter_labelpwrlab_main_main_default.set_text_color(lv.color_make(0xff,0x7f,0x00))
try:
    style_scrpowermeter_labelpwrlab_main_main_default.set_text_font(lv.font_MONACO_40)
except AttributeError:
    try:
        style_scrpowermeter_labelpwrlab_main_main_default.set_text_font(lv.font_montserrat_40)
    except AttributeError:
        style_scrpowermeter_labelpwrlab_main_main_default.set_text_font(lv.font_montserrat_16)
style_scrpowermeter_labelpwrlab_main_main_default.set_text_letter_space(0)
style_scrpowermeter_labelpwrlab_main_main_default.set_pad_left(0)
style_scrpowermeter_labelpwrlab_main_main_default.set_pad_right(0)
style_scrpowermeter_labelpwrlab_main_main_default.set_pad_top(0)
style_scrpowermeter_labelpwrlab_main_main_default.set_pad_bottom(0)

# add style for scrPowerMeter_labelPwrLab
scrPowerMeter_labelPwrLab.add_style(style_scrpowermeter_labelpwrlab_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

scrPowerMeter_labelVolUnit = lv.label(scrPowerMeter)
scrPowerMeter_labelVolUnit.set_pos(195,150)
scrPowerMeter_labelVolUnit.set_size(30,40)
scrPowerMeter_labelVolUnit.set_text("V")
scrPowerMeter_labelVolUnit.set_long_mode(lv.label.LONG.CLIP)
scrPowerMeter_labelVolUnit.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_scrpowermeter_labelvolunit_main_main_default
style_scrpowermeter_labelvolunit_main_main_default = lv.style_t()
style_scrpowermeter_labelvolunit_main_main_default.init()
style_scrpowermeter_labelvolunit_main_main_default.set_radius(0)
style_scrpowermeter_labelvolunit_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_scrpowermeter_labelvolunit_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_scrpowermeter_labelvolunit_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_scrpowermeter_labelvolunit_main_main_default.set_bg_opa(0)
style_scrpowermeter_labelvolunit_main_main_default.set_text_color(lv.color_make(0x00,0x7f,0xff))
try:
    style_scrpowermeter_labelvolunit_main_main_default.set_text_font(lv.font_MONACO_40)
except AttributeError:
    try:
        style_scrpowermeter_labelvolunit_main_main_default.set_text_font(lv.font_montserrat_40)
    except AttributeError:
        style_scrpowermeter_labelvolunit_main_main_default.set_text_font(lv.font_montserrat_16)
style_scrpowermeter_labelvolunit_main_main_default.set_text_letter_space(0)
style_scrpowermeter_labelvolunit_main_main_default.set_pad_left(0)
style_scrpowermeter_labelvolunit_main_main_default.set_pad_right(0)
style_scrpowermeter_labelvolunit_main_main_default.set_pad_top(0)
style_scrpowermeter_labelvolunit_main_main_default.set_pad_bottom(0)

# add style for scrPowerMeter_labelVolUnit
scrPowerMeter_labelVolUnit.add_style(style_scrpowermeter_labelvolunit_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

scrPowerMeter_labelCurUnit = lv.label(scrPowerMeter)
scrPowerMeter_labelCurUnit.set_pos(195,200)
scrPowerMeter_labelCurUnit.set_size(30,40)
scrPowerMeter_labelCurUnit.set_text("A")
scrPowerMeter_labelCurUnit.set_long_mode(lv.label.LONG.CLIP)
scrPowerMeter_labelCurUnit.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_scrpowermeter_labelcurunit_main_main_default
style_scrpowermeter_labelcurunit_main_main_default = lv.style_t()
style_scrpowermeter_labelcurunit_main_main_default.init()
style_scrpowermeter_labelcurunit_main_main_default.set_radius(0)
style_scrpowermeter_labelcurunit_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_scrpowermeter_labelcurunit_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_scrpowermeter_labelcurunit_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_scrpowermeter_labelcurunit_main_main_default.set_bg_opa(0)
style_scrpowermeter_labelcurunit_main_main_default.set_text_color(lv.color_make(0xff,0x00,0x00))
try:
    style_scrpowermeter_labelcurunit_main_main_default.set_text_font(lv.font_MONACO_40)
except AttributeError:
    try:
        style_scrpowermeter_labelcurunit_main_main_default.set_text_font(lv.font_montserrat_40)
    except AttributeError:
        style_scrpowermeter_labelcurunit_main_main_default.set_text_font(lv.font_montserrat_16)
style_scrpowermeter_labelcurunit_main_main_default.set_text_letter_space(1)
style_scrpowermeter_labelcurunit_main_main_default.set_pad_left(0)
style_scrpowermeter_labelcurunit_main_main_default.set_pad_right(0)
style_scrpowermeter_labelcurunit_main_main_default.set_pad_top(0)
style_scrpowermeter_labelcurunit_main_main_default.set_pad_bottom(0)

# add style for scrPowerMeter_labelCurUnit
scrPowerMeter_labelCurUnit.add_style(style_scrpowermeter_labelcurunit_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

scrPowerMeter_labelPwrUnit = lv.label(scrPowerMeter)
scrPowerMeter_labelPwrUnit.set_pos(195,250)
scrPowerMeter_labelPwrUnit.set_size(30,40)
scrPowerMeter_labelPwrUnit.set_text("W")
scrPowerMeter_labelPwrUnit.set_long_mode(lv.label.LONG.CLIP)
scrPowerMeter_labelPwrUnit.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_scrpowermeter_labelpwrunit_main_main_default
style_scrpowermeter_labelpwrunit_main_main_default = lv.style_t()
style_scrpowermeter_labelpwrunit_main_main_default.init()
style_scrpowermeter_labelpwrunit_main_main_default.set_radius(0)
style_scrpowermeter_labelpwrunit_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_scrpowermeter_labelpwrunit_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_scrpowermeter_labelpwrunit_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_scrpowermeter_labelpwrunit_main_main_default.set_bg_opa(0)
style_scrpowermeter_labelpwrunit_main_main_default.set_text_color(lv.color_make(0xff,0x7f,0x00))
try:
    style_scrpowermeter_labelpwrunit_main_main_default.set_text_font(lv.font_MONACO_40)
except AttributeError:
    try:
        style_scrpowermeter_labelpwrunit_main_main_default.set_text_font(lv.font_montserrat_40)
    except AttributeError:
        style_scrpowermeter_labelpwrunit_main_main_default.set_text_font(lv.font_montserrat_16)
style_scrpowermeter_labelpwrunit_main_main_default.set_text_letter_space(2)
style_scrpowermeter_labelpwrunit_main_main_default.set_pad_left(0)
style_scrpowermeter_labelpwrunit_main_main_default.set_pad_right(0)
style_scrpowermeter_labelpwrunit_main_main_default.set_pad_top(0)
style_scrpowermeter_labelpwrunit_main_main_default.set_pad_bottom(0)

# add style for scrPowerMeter_labelPwrUnit
scrPowerMeter_labelPwrUnit.add_style(style_scrpowermeter_labelpwrunit_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

scrPowerMeter_img_1 = lv.img(scrPowerMeter)
scrPowerMeter_img_1.set_pos(0,20)
scrPowerMeter_img_1.set_size(240,112)
scrPowerMeter_img_1.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('/home/nvt10127/GUI-Guider-Projects/esp32/lvgl_ui/generated/mp-408061278.png','rb') as f:
        scrPowerMeter_img_1_img_data = f.read()
except:
    print('Could not open /home/nvt10127/GUI-Guider-Projects/esp32/lvgl_ui/generated/mp-408061278.png')
    sys.exit()

scrPowerMeter_img_1_img = lv.img_dsc_t({
  'data_size': len(scrPowerMeter_img_1_img_data),
  'header': {'always_zero': 0, 'w': 240, 'h': 112, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': scrPowerMeter_img_1_img_data
})

scrPowerMeter_img_1.set_src(scrPowerMeter_img_1_img)
scrPowerMeter_img_1.set_pivot(0,0)
scrPowerMeter_img_1.set_angle(0)
# create style style_scrpowermeter_img_1_main_main_default
style_scrpowermeter_img_1_main_main_default = lv.style_t()
style_scrpowermeter_img_1_main_main_default.init()
style_scrpowermeter_img_1_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_scrpowermeter_img_1_main_main_default.set_img_recolor_opa(0)
style_scrpowermeter_img_1_main_main_default.set_img_opa(255)

# add style for scrPowerMeter_img_1
scrPowerMeter_img_1.add_style(style_scrpowermeter_img_1_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)




# content from custom.py

# Load the default screen
lv.scr_load(scrPowerMeter)

while SDL.check():
    time.sleep_ms(5)
