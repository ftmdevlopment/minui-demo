#include <math.h>
#include <stdio.h>

#include "minui/minui.h"

int min(int x, int y) { return x < y ? x : y; }

void fill_circle(int x0, int y0, int radius)
{
	int x, y, r2, width, height;
	width = gr_fb_width();
	height = gr_fb_height();
	r2 = radius * radius;
	for (x = 0; x < width; x++) {
		for (y = 0; y < height; y++) {
			int dx = x - x0, dy = y - y0;
			if (dx * dx + dy * dy <= r2) {
				gr_fill(x, y, x+1, y+1);
			}
		}
	}
}

void fill_text(int x, int y, const char* text)
{
	int fw, fh, tw, th;
	gr_font_size(&fw, &fh);
	tw = gr_measure(text); th = fh;
	gr_text(x - tw/2, y - th/2, text, 0);
}

void fill_image(int x, int y, const char* name)
{

}

#define NCASES 25
#define BORDER 25
#define RACASE 15

void draw_clock_ui()
{
	int i, width, height, x0, y0;
	int outter_radius, inner_radius, case_radius, case_center_radius;
	struct {
		double x, y;
	} center[NCASES] = {0};

	width = gr_fb_width();
	height = gr_fb_height();

	x0 = width/2;
	y0 = height/2;
	outter_radius = min(width/2, height/2);
	inner_radius = outter_radius - BORDER;
	case_radius = RACASE;
	case_center_radius = inner_radius - 2*BORDER;

	// calculate each center
	for (i = 0; i < NCASES; i++) {
		double a = i * (2*M_PI/NCASES);
		center[i].x = x0 - case_center_radius * sin(a);
		center[i].y = y0 + case_center_radius * cos(a);
	}

	// background clear
	gr_color(   0,   0,   0, 255);
	gr_clear();

	// outter
	gr_color(   0,   0, 255, 255);
	fill_circle(x0, y0, outter_radius);

	// inner
	gr_color( 255,   0,   0, 255);
	fill_circle(x0, y0, inner_radius);

	gr_color( 255, 255, 255, 255);
	fill_text(x0, y0, "clock ui test");

	// cases
	for (i = 0; i < NCASES; i++) {
		char text[64];
		gr_color(   0, 255,   0, 255);
		fill_circle(center[i].x, center[i].y, case_radius);

		snprintf(text, sizeof(text), "%d", i);
		gr_color( 255, 255, 255, 255);
		fill_text(center[i].x, center[i].y, text);
	}

	gr_flip(); 
}


int main(int argc, char** argv)
{
	int i = 0, fx = 0, fy = 0;

	gr_init();

	draw_clock_ui();

	gr_exit();
	return 0;
}
