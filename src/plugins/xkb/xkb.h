/*
//====================================================================
//  xfce4-xkb-plugin - XFCE4 Xkb Layout Indicator panel plugin
// -------------------------------------------------------------------
//  Alexander Iliev <sasoiliev@mamul.org>
//  20-Feb-04
// -------------------------------------------------------------------
//  Parts of this code belong to Michael Glickman <wmalms@yahooo.com>
//  and his program wmxkb.
//  WARNING: DO NOT BOTHER Michael Glickman WITH QUESTIONS ABOUT THIS
//           PROGRAM!!! SEND INSTEAD EMAILS TO <sasoiliev@mamul.org>
//====================================================================
*/

/* Modified by Hong Jen Yee (PCMan) <pcman.tw@gmail.com> on 2008-04-06 for lxpanel */

/* Modified by Giuseppe Penone <giuspen@gmail.com> starting from 2012-07 and lxpanel 0.5.10 */

#ifndef _XKB_PLUGIN_H_
#define _XKB_PLUGIN_H_

#include <X11/Xlib.h>
#include <X11/XKBlib.h>
#include <gtk/gtk.h>
#include <glib.h>

#include "plugin.h"
#include "misc.h"
#include "panel.h"
#include "ev.h"

#include "dbg.h"

typedef enum {
    DISP_TYPE_IMAGE=0,
    DISP_TYPE_TEXT=1,
    DISP_TYPE_IMAGE_CUST=2
} DisplayType;

typedef struct {

    /* Plugin interface. */
    Plugin       *p_plugin;                    /* Back pointer to Plugin */
    GtkWidget    *p_label;                     /* Label containing country name */
    GtkWidget    *p_image;                     /* Image containing country flag */
    DisplayType   display_type;                /* Display layout as image or text */
    gboolean      enable_perwin;               /* Enable per window layout */
    guint         source_id;                   /* Source ID for channel listening to XKB events */
    GtkWidget    *p_dialog_config;             /* Configuration dialog */
    GtkListStore *p_liststore_layout;
    GtkWidget    *p_treeview_layout;
    GtkTreeSelection  *p_treeselection_layout;
    GtkWidget    *p_button_kbd_model;
    GtkWidget    *p_button_change_layout;
    GtkWidget    *p_button_rm_layout;

    /* Mechanism. */
    int       base_event_code;                /* Result of initializing Xkb extension */
    int       base_error_code;
    int       current_group_xkb_no;           /* Current layout */
    int       group_count;                    /* Count of groups as returned by Xkb */
    char     *group_names[XkbNumKbdGroups];   /* Group names as returned by Xkb */
    char     *symbol_names[XkbNumKbdGroups];  /* Symbol names as returned by Xkb */
    GHashTable *p_hash_table_group;             /* Hash table to correlate window with layout */
    gchar    *kbd_model;
    gchar    *kbd_layouts;
    gchar    *kbd_variants;
    gchar    *kbd_change_option;
    guchar    flag_size;
    GString  *p_gstring_layouts_partial;
    GString  *p_gstring_variants_partial;
    int       num_layouts;
    gboolean  cust_dir_exists;

} XkbPlugin;

#define MAX_MARKUP_LEN  64
#define MAX_ROW_LEN  64

extern void xkb_redraw(XkbPlugin * xkb);
extern void  xkb_setxkbmap(XkbPlugin *p_xkb);

extern int xkb_get_current_group_xkb_no(XkbPlugin * xkb);
extern int xkb_get_group_count(XkbPlugin * xkb);
extern const char * xkb_get_symbol_name_by_res_no(XkbPlugin * xkb, int group_res_no);
extern const char * xkb_get_current_group_name(XkbPlugin * xkb);
extern const char * xkb_get_current_symbol_name(XkbPlugin * xkb);
extern const char * xkb_get_current_symbol_name_lowercase(XkbPlugin * xkb);
extern void xkb_mechanism_constructor(XkbPlugin * xkb);
extern void xkb_mechanism_destructor(XkbPlugin * xkb);
extern int xkb_change_group(XkbPlugin * xkb, int increment);

#endif

