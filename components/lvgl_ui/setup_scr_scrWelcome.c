/*
 * Copyright 2022 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl/lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"


void setup_scr_scrWelcome(lv_ui *ui){

	//Write codes scrWelcome
	ui->scrWelcome = lv_obj_create(NULL);

	//Write style state: LV_STATE_DEFAULT for style_scrwelcome_main_main_default
	static lv_style_t style_scrwelcome_main_main_default;
	lv_style_reset(&style_scrwelcome_main_main_default);
	lv_style_set_bg_color(&style_scrwelcome_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_opa(&style_scrwelcome_main_main_default, 255);
	lv_obj_add_style(ui->scrWelcome, &style_scrwelcome_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrWelcome_imgLogo
	ui->scrWelcome_imgLogo = lv_img_create(ui->scrWelcome);
	lv_obj_set_pos(ui->scrWelcome_imgLogo, 0, 60);
	lv_obj_set_size(ui->scrWelcome_imgLogo, 240, 112);

	//Write style state: LV_STATE_DEFAULT for style_scrwelcome_imglogo_main_main_default
	static lv_style_t style_scrwelcome_imglogo_main_main_default;
	lv_style_reset(&style_scrwelcome_imglogo_main_main_default);
	lv_style_set_img_recolor(&style_scrwelcome_imglogo_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_scrwelcome_imglogo_main_main_default, 0);
	lv_style_set_img_opa(&style_scrwelcome_imglogo_main_main_default, 255);
	lv_obj_add_style(ui->scrWelcome_imgLogo, &style_scrwelcome_imglogo_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->scrWelcome_imgLogo, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->scrWelcome_imgLogo,&_nvt_240x112);
	lv_img_set_pivot(ui->scrWelcome_imgLogo, 0,0);
	lv_img_set_angle(ui->scrWelcome_imgLogo, 0);

	//Write codes scrWelcome_labelTitle
	ui->scrWelcome_labelTitle = lv_label_create(ui->scrWelcome);
	lv_obj_set_pos(ui->scrWelcome_labelTitle, 0, 200);
	lv_obj_set_size(ui->scrWelcome_labelTitle, 240, 14);
	lv_label_set_text(ui->scrWelcome_labelTitle, "Designd by Hang MENG");
	lv_label_set_long_mode(ui->scrWelcome_labelTitle, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->scrWelcome_labelTitle, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_scrwelcome_labeltitle_main_main_default
	static lv_style_t style_scrwelcome_labeltitle_main_main_default;
	lv_style_reset(&style_scrwelcome_labeltitle_main_main_default);
	lv_style_set_radius(&style_scrwelcome_labeltitle_main_main_default, 0);
	lv_style_set_bg_color(&style_scrwelcome_labeltitle_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_scrwelcome_labeltitle_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_scrwelcome_labeltitle_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_scrwelcome_labeltitle_main_main_default, 0);
	lv_style_set_text_color(&style_scrwelcome_labeltitle_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_scrwelcome_labeltitle_main_main_default, &lv_font_FiraCode_Retina_14);
	lv_style_set_text_letter_space(&style_scrwelcome_labeltitle_main_main_default, 0);
	lv_style_set_pad_left(&style_scrwelcome_labeltitle_main_main_default, 0);
	lv_style_set_pad_right(&style_scrwelcome_labeltitle_main_main_default, 0);
	lv_style_set_pad_top(&style_scrwelcome_labeltitle_main_main_default, 0);
	lv_style_set_pad_bottom(&style_scrwelcome_labeltitle_main_main_default, 0);
	lv_obj_add_style(ui->scrWelcome_labelTitle, &style_scrwelcome_labeltitle_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
}