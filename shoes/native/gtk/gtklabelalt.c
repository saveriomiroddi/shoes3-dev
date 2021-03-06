/*
 * Thanks to Philip Chimento
 * http://ptomato.name/advanced-gtk-techniques/html/custom-container.html
*/

#include "shoes/app.h"
#include "shoes/ruby.h"
#include "shoes/config.h"
#include "shoes/world.h"
#include "shoes/native/native.h"
#include "shoes/internal.h"

#include "gtklabelalt.h"

/* Private class member */
#define GTKLABEL_ALT_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE((obj), \
	GTKLABEL_ALT_TYPE, GtKLabel_AltPrivate))

typedef struct _GtKLabel_AltPrivate GtKLabel_AltPrivate;

struct _GtKLabel_AltPrivate {
    GList *children;
};

/* Forward declarations */
static void gtklabel_alt_get_preferred_width(GtkWidget *widget,
        int *minimal, int *natural);
static void gtklabel_alt_get_preferred_height(GtkWidget *widget,
        int *minimal, int *natural);
//static void gtkfixed_alt_size_allocate(GtkWidget *widget,
//                                    GtkAllocation *allocation);
//static GType gtkfixed_alt_child_type(GtkContainer *container);

/* Define the GtKLabel_Alt type and inherit from GtkLabel */
G_DEFINE_TYPE(GtKLabel_Alt, gtklabel_alt, GTK_TYPE_LABEL);


/* Initialize the GtKLabel_Alt class */
static void
gtklabel_alt_class_init(GtKLabel_AltClass *klass) {
    /* Override GtkWidget methods */
    GtkWidgetClass *widget_class = GTK_WIDGET_CLASS(klass);
    widget_class->get_preferred_width = gtklabel_alt_get_preferred_width;
    widget_class->get_preferred_height = gtklabel_alt_get_preferred_height;
    //widget_class->size_allocate = gtkfixed_alt_size_allocate;

    /* Override GtkLabel methods */
    // TODO: determine whether fixed_class has any use.
    //GtkLabelClass *fixed_class = GTK_FIXED_CLASS(klass);
    // ...

    /* Add private indirection member */
    g_type_class_add_private(klass, sizeof(GtKLabel_AltPrivate));
}

/* Initialize a new GtKLabel_Alt instance */
static void
gtklabel_alt_init(GtKLabel_Alt *labelAlt) {
    /* This means that GtKLabel_Alt doesn't supply its own GdkWindow */
    gtk_widget_set_has_window(GTK_WIDGET(labelAlt), FALSE);

    /* Initialize private members */
    GtKLabel_AltPrivate *priv = GTKLABEL_ALT_PRIVATE(labelAlt);
    priv->children = NULL;
}

/* Return a new GtKLabel_Alt cast to a GtkWidget */
GtkWidget *
gtklabel_alt_new() {
    return GTK_WIDGET(g_object_new(gtklabel_alt_get_type(), NULL));
}


/* Get the width of the container(GtkLabel_Alt)
 * don't ask for children size so we can shrink as in gtk2
*/
static void
gtklabel_alt_get_preferred_width(GtkWidget *widget, int *minimal, int *natural) {
    g_return_if_fail(widget != NULL);
    g_return_if_fail(IS_GTKLABEL_ALT(widget));

    *minimal = 1;
    *natural = 1;
}

/* Get the height of the container(GtkLabel_Alt)
 * don't ask for children size so we can shrink as in gtk2
*/
static void
gtklabel_alt_get_preferred_height(GtkWidget *widget, int *minimal, int *natural) {
    g_return_if_fail(widget != NULL);
    g_return_if_fail(IS_GTKLABEL_ALT(widget));

    *minimal = 1;
    *natural = 1;
}
