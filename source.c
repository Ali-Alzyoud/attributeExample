#define EFL_BETA_API_SUPPORT 1
 
#include <Eina.h>
#include <Elementary.h>
#include <Efl_Ui.h>



/************ Application Logic ******************/

static void
_gui_quit_cb(void *data EINA_UNUSED, const Efl_Event *event EINA_UNUSED)
{
   efl_exit(0);
}
 
EAPI_MAIN void
efl_main(void *data EINA_UNUSED, const Efl_Event *ev EINA_UNUSED)
{
   Eo *win, *box, *canvas_text, *attribute_factory_default, *attribute_factory_cursor, *cursor_start, *cursor_end;
 
   win = efl_add(EFL_UI_WIN_CLASS, efl_main_loop_get(),
                 efl_ui_win_type_set(efl_added, EFL_UI_WIN_TYPE_BASIC),
                 efl_text_set(efl_added, "Hello World"),
                 efl_ui_win_autodel_set(efl_added, EINA_TRUE));
 
   efl_event_callback_add(win, EFL_UI_WIN_EVENT_DELETE_REQUEST, _gui_quit_cb, NULL);
 
   box = efl_add(EFL_UI_BOX_CLASS, win,
                efl_content_set(win, efl_added),
                efl_gfx_hint_size_min_set(efl_added, EINA_SIZE2D(360, 240)));

   canvas_text = efl_add(EFL2_CANVAS_TEXT_CLASS, box,
           efl2_text_set(efl_added, "Hello World"),
           efl_gfx_hint_weight_set(efl_added, 1.0, 1.0),
           efl_gfx_hint_align_set(efl_added, 0.5, 0.5),
           efl_pack(box, efl_added));


/* Insert Attribute as default */
   attribute_factory_default = efl_add(EFL2_TEXT_ATTRIBUTE_FACTORY_CLASS, canvas_text);
   efl2_text_font_family_set(attribute_factory_default, "Sans");
   efl2_text_font_size_set(attribute_factory_default, 10);
   efl2_canvas_text_style_set(canvas_text, "DEFAULT", efl2_text_attribute_factory_create(attribute_factory_default)),


/* Insert Attribute at cursor */
   attribute_factory_cursor = efl_add(EFL2_TEXT_ATTRIBUTE_FACTORY_CLASS, canvas_text);

   efl2_text_font_family_set(attribute_factory_cursor, "Georgia");
   efl2_text_font_size_set(attribute_factory_cursor, 30);
   efl2_text_style_background_color_set(attribute_factory_cursor, 255, 0, 0, 255);
	efl2_text_style_background_type_set(attribute_factory_cursor, EFL2_TEXT_STYLE_BACKGROUND_ON);
	efl2_text_style_underline_type_set(attribute_factory_cursor, EFL2_TEXT_STYLE_UNDERLINE_ON);
	efl2_text_style_underline_color_set(attribute_factory_cursor, 255, 255, 0, 255);

   cursor_start = efl_add(EFL2_TEXT_CURSOR_CLASS, canvas_text,
                        efl2_text_cursor_handle_set(efl_added, efl2_canvas_text_cursor_handle_new(canvas_text)));

   cursor_end = efl_add(EFL2_TEXT_CURSOR_CLASS, canvas_text,
                        efl2_text_cursor_handle_set(efl_added, efl2_canvas_text_cursor_handle_new(canvas_text)));

   efl2_text_cursor_position_set(cursor_start, 1);
   efl2_text_cursor_position_set(cursor_end, 4);
   
   efl2_text_attribute_factory_insert(attribute_factory_cursor, cursor_start, cursor_end);
}
EFL_MAIN()

/******************************************/
