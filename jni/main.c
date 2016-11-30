#include <unistd.h>

#include <stdio.h>

#include <minui.h>

int g_width = 0;
int g_height = 0;

int min(int x, int y) { return x < y ? x : y; }

FILE *fout = NULL, *ferr = NULL;

void color_test()
{
	int i;
	puts("\ndraw color test");
	for (i = 0; i < 1; i++) {
		gr_color(255, 255, 255, 255); gr_fill(0, 0, g_width, g_height); gr_flip(); sleep(1); // white
		gr_color(255,   0,   0, 255); gr_fill(0, 0, g_width, g_height); gr_flip(); sleep(1); // red
		gr_color(  0, 255,   0, 255); gr_fill(0, 0, g_width, g_height); gr_flip(); sleep(1); // green
		gr_color(  0,   0, 255, 255); gr_fill(0, 0, g_width, g_height); gr_flip(); sleep(1); // blue
		gr_color(  0,   0,   0, 255); gr_fill(0, 0, g_width, g_height); gr_flip(); sleep(1); // black
		printf("flush color once!\n");
	}
}

void text_test()
{
	int i, fx = 0, fy = 0;
	puts("\ndraw text test");
	gr_font_size(&fx, &fy);
	printf("font size: %d, %d\n", fx, fy);
	for (i = 0; i < 5; i++) {
		int t_wid = 0;
		char text[64];
		snprintf(text, sizeof(text), "Text-%d", i);
		printf("post %s\n", text);

		// white background
		gr_color(255, 255, 255, 255);
		gr_clear();

		// black text
		t_wid = gr_measure(text);
		gr_color(  0,   0,   0, 255);
		gr_text(g_width/2 - t_wid/2, g_height/2, text, 0);

		gr_flip();
		sleep(1);
	}
}

void image_test(const char* name)
{
	int i, rc, iw, ih, px, py;
	gr_surface img = NULL;

	puts("\ndraw image test");
	rc = res_create_display_surface(name, &img);
	if (rc < 0) { printf("res_create_display_surface failed!\n"); return; }

	iw = gr_get_width(img);
	ih = gr_get_height(img);
	for (i = 0; i < 5; i++) {
		gr_color(255, 255, 255, 255); gr_clear(); gr_flip(); sleep(1); // white

		gr_color(  0,   0,   0, 255); gr_clear();
		px = g_width/2 - iw/2;  if (px < 0) px = 0;
		py = g_height/2 - ih/2; if (py < 0) py = 0;
		gr_blit(img, 0, 0, min(iw, g_width), min(ih, g_width), px, py); gr_flip(); sleep(1);
	}
	res_free_surface(img);
}

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

void circle_test()
{
	int i, rmax, r, steps, dr;
	puts("draw circle test");

	steps = 20;
	rmax = min(g_width/2, g_height/2);
	r = dr = rmax / steps;
	gr_color(0, 0, 0, 255); gr_clear();
	for (i = 1; i <= 20; i++) {
		gr_color(255, 0, 0, 255);
		fill_circle(g_width/2, g_height/2, r);
		gr_flip();
		sleep(1);
		printf("radius: %d\n", r);

		r += dr;
	}
}

int main(int argc, char** argv)
{
	int i = 0, fx = 0, fy = 0;
	const char* imname;

	gr_init();

	g_width = gr_fb_width();
	g_height = gr_fb_height();
	printf("width: %d, height: %d\n", g_width, g_height);

#if 0
	fout = freopen("/data/local/out.txt", "w+", stdout); if (!fout) perror("fopen");
	ferr = freopen("/data/local/err.txt", "w+", stderr); if (!ferr) perror("fopen");
#endif

	color_test();

	text_test();

	imname = (argc > 1) ? argv[1] : "error";
	image_test(imname);

	circle_test();

	gr_exit();
	return 0;
}
