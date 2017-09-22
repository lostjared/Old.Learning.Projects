#include<gdk/gdk.h>
#include<gtk/gtk.h>
#include<stdlib.h>
#include<memory.h>
#include<libgnome/libgnome.h>
#include<libgnomeui/gnome-app.h>
#include<libgnomeui/gnome-about.h>
#include<libgnomeui/gnome-messagebox.h>
#include<libgnomeui/gnome-dialog-util.h>
#include"score.h"
#include"mp.h"
#define SIZE_X 640
#define SIZE_Y 480
int GAME_TIME = 150;
static GtkWidget *render_space,*window,*options,*label,*highscore,*hlabel;
static GdkPixbuf *background,*about_img, *front,*img[10];
static gchar *menu_strings[] = {"New Game","High Scores", "About", "Exit", 0 };
static gchar *block_img[] = { "./images/block_black.png", "./images/block_clear.png", "./images/block_dblue.png",
"./images/block_gray.png", "./images/block_green.png", "./images/block_ltblue.png", "./images/block_orange.png",
"./images/block_pink.png","./images/block_purple.png", "./images/block_red.png", "./images/block_yellow.png", 

 0 };


typedef enum menu_type { ID_NEW, ID_HIGHSCORES, ID_ABOUT, ID_EXIT } menu_id;

struct gmp_rgb {
	guchar r,g,b;
};



struct gmp_rgb pixels[640*480];

struct gmp_rgb colors[] = { {0,0,0}, {100,25,75}, {100,25,10}, {0,0,255}, {0,255,0}, {100,100,100}, {255,255,255}, {159,0,75} };


static gint timeout_id = 0, idle_id = 0;
int screen = 0;

void fill_rect(int x, int y, int w, int h, unsigned long color) {
	if(img[color] != 0) 
	gdk_pixbuf_copy_area(img[color], 0, 0, w, h, front, x, y);
	else printf("error image %s not found !\n", block_img[color]);
}


static menu_id menu_lookup(gchar *string) {
	guint i;
	for(i = 0; menu_strings[i] != 0; i++) {

		if(strcmp(string, menu_strings[i]) == 0)
			return (menu_id)i;
	
	}
	return 0;
}

static void quit() {
	g_source_remove(timeout_id);
	gtk_main_quit();
}

void create_entry();

void gameover() {

	gchar buf_gscore[255];
	screen = 0;
	sprintf(buf_gscore,"Game Over\n Score %d Cleared %d\nEnter Your Name:", score, lines);
	create_entry();
	gtk_label_set_text(GTK_LABEL(label), buf_gscore);
	gtk_widget_show_all(options);

}

static gboolean load_gfx() {

	guint i;
	background = gdk_pixbuf_new_from_file ("./images/background.png", NULL);

	if(!background)
		return FALSE;

	about_img = gdk_pixbuf_new_from_file("./images/about.png", NULL);

	for(i = 0; i < 10; i++) {

		img[i] = gdk_pixbuf_new_from_file(block_img[i], NULL);
		if(!img[i])
		return FALSE;
	}
	

	return TRUE;
}

static gint keydown(GtkWidget *widget, GdkEventKey *event, gpointer data) {


	switch(event->keyval) {
		case 'a':
		move_left();
		break;
		case 's':
		move_right();
		break;
		case 'z':
		proc_move();
		break;
		case 'd':
		shiftcolor(&gblock, 0);
		break;
		
	}	

	return TRUE;

}

static void about_cmd() {

	static GtkWidget *about = 0;
	const gchar *authors[] = {"Jared Bruni <jaredbruni@gmail.com>", NULL };
	about = gnome_about_new("GMasterPiece", "1.0", "GPL","a 2D Puzzle Game for Gnome", authors, authors, "Nobody yet", about_img);
	gtk_window_set_modal(GTK_WINDOW(about), FALSE);
	gtk_widget_show(about);


}

void create_highscore();

static void menuitem_response( gchar *string ) {

    switch(menu_lookup(string)) {
	case ID_NEW:
	{
		gtk_window_set_title(GTK_WINDOW(window),"GMasterPiece");
		init_matrix();
		screen = 1;
	}
	break;
	break;
	case ID_HIGHSCORES:
	{
		static gchar gbuf[5000];
		memset(gbuf, 0, sizeof(gbuf));
		create_highscore();
		sort_scores();
		guint i;
		for(i = 0; i < 10; i++) {
			sprintf(gbuf,"%s%s Score: %d , Cleared %d\n", gbuf,scores[i].name, scores[i].score, scores[i].clr);
		}

		gtk_window_set_title(GTK_WINDOW(highscore), "High scores - GMasterPiece");
		gtk_label_set_text(GTK_LABEL(hlabel), gbuf);
		gtk_widget_show_all(highscore);
		
	}
	break;

	break;
	case ID_ABOUT:
	about_cmd();
	break;
	case ID_EXIT:
	{
		quit();
	}
	break;
   }

}

static void init_pixels() {
	memset(pixels, 0, sizeof(pixels));
}

static void destroy(GtkObject *obj, gpointer data) {
	g_source_remove(timeout_id);
	gtk_main_quit();
}

static gint render(GtkWidget *widget, GdkEventExpose *event, gpointer data) {
	
	guint rowstride = gdk_pixbuf_get_rowstride(front);
	guchar *pixel_data;
	pixel_data = gdk_pixbuf_get_pixels(front);
	gdk_draw_rgb_image_dithalign (widget->window,
				      widget->style->black_gc,
				      event->area.x, event->area.y,
				      event->area.width, event->area.height,
				      GDK_RGB_DITHER_NORMAL,
				     (guchar*) pixel_data, SIZE_X*3,
				      event->area.x, event->area.y);


	return TRUE;
}


static gint logic(gpointer data) {



	if(screen == 0)
	gdk_pixbuf_copy_area(background, 0, 0, SIZE_X, SIZE_Y, front, 0, 0);
	else
	{ proc_move(); draw_grid(); }

	gtk_widget_queue_draw(GTK_WIDGET(render_space));

	return TRUE;
}

static void enter_callback( GtkWidget *widget,
                            GtkWidget *entry )
{
  const gchar *entry_text;
  entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
  add_new_score(entry_text, score, lines);
  save_scores();
  gtk_widget_destroy(options);
  print_scores();
}

void create_entry() {

	GtkWidget *box3,*edit;

	options = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	label = gtk_label_new("Enter Name for Highscore:");
	box3 = gtk_hbox_new (FALSE, 0);
	edit = gtk_entry_new();
	gtk_entry_set_max_length (GTK_ENTRY (edit), 50);
	g_signal_connect (G_OBJECT (edit), "activate",G_CALLBACK (enter_callback),(gpointer) edit);
	gtk_widget_set_usize(box3, 360, 150);
	gtk_container_add(GTK_CONTAINER(box3), label);
	gtk_container_add(GTK_CONTAINER(box3), edit);
	gtk_container_add(GTK_CONTAINER(options), box3);
	gtk_widget_show_all(box3);
	gtk_window_set_title(GTK_WINDOW(options), "Enter Your Name");
}

void create_highscore() {

	highscore = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	hlabel = gtk_label_new("txt");
	gtk_container_add(GTK_CONTAINER(highscore), hlabel);
	gtk_widget_set_usize(highscore, 480, 272);

}

int main(int argc, char **argv) {

	GtkWidget *root_menu, *menu,*menu_bar,*menu_items,*box,*box2;

	guint i = 0;
	init_pixels();
	init_scores();

	gtk_init(&argc, &argv);

	if(load_gfx() == FALSE) {
		fprintf(stderr, "Error loading graphics!");
		return -1;
	}
	front = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, SIZE_X , SIZE_Y);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	// build menu

	menu = gtk_menu_new();
	
	for(i = 0; menu_strings[i] != 0; i++) {
	menu_items = gtk_menu_item_new_with_label (menu_strings[i]);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_items);
	g_signal_connect_swapped (G_OBJECT (menu_items), "activate",
		                      G_CALLBACK (menuitem_response), 
                                      (gpointer) g_strdup (menu_strings[i]));

	}
	root_menu = gtk_menu_item_new_with_label("Game Menu");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(root_menu), menu);
	menu_bar = gtk_menu_bar_new ();
	gtk_menu_shell_append (GTK_MENU_SHELL (menu_bar), root_menu);
	gtk_widget_show(menu_bar);
	box = gtk_vbox_new (FALSE, 0);
	// add to container
	gtk_container_add (GTK_CONTAINER (box), menu_bar);
	gtk_container_add (GTK_CONTAINER (window), box);
	// set widget params
	gtk_widget_set_size_request(window, SIZE_X, SIZE_Y);
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
	gtk_window_set_title(GTK_WINDOW(window),"GMasterPiece - Select New Game from Menu to Play");
	// connect signals
	g_signal_connect(window, "destroy", G_CALLBACK(destroy), NULL);
	g_signal_connect(window, "key_press_event", G_CALLBACK(keydown), NULL);
	render_space = gtk_drawing_area_new();
	g_signal_connect(render_space, "expose_event", G_CALLBACK(render), NULL);
	gtk_container_add (GTK_CONTAINER(box), render_space);
	gtk_widget_show(box);
	gtk_widget_set_usize(render_space, 640, 460);
	// set timer
	timeout_id = g_timeout_add (GAME_TIME, logic, NULL);
	//idle_id = g_idle_add(logic, NULL);
	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}
