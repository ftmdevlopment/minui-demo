#include <unistd.h>

#include <stdio.h>

#include <minui.h>

int g_width = 0;
int g_height = 0;

FILE *fout = NULL, *ferr = NULL;

void color_test()
{
	int i;
	puts("\ndraw color test");
	for (i = 0; i < 1; i++) {
		gr_color(255, 255, 255, 255); gr_fill(0, 0, g_width, g_height); gr_flip(); sleep(1); // white
		gr_color(255,   0,   0, 255); gr_fill(0, 0, g_width, g_height); gr_flip(); sleep(1); // blue
		gr_color(  0, 255,   0, 255); gr_fill(0, 0, g_width, g_height); gr_flip(); sleep(1); // green
		gr_color(  0,   0, 255, 255); gr_fill(0, 0, g_width, g_height); gr_flip(); sleep(1); // red
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
		gr_fill(0, 0, g_width, g_height);

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
	int i, rc, iw, ih;
	gr_surface img = NULL;

	puts("\ndraw image test");
	rc = res_create_display_surface(name, &img);
	if (rc < 0) { printf("res_create_display_surface failed!\n"); return; }

	iw = gr_get_width(img);
	ih = gr_get_height(img);
	for (i = 0; i < 5; i++) {
		gr_color(255, 255, 255, 255); gr_fill(0, 0, g_width, g_height); gr_flip(); sleep(1); // white
		gr_blit(img, 0, 0, iw, ih, g_width/2 - iw/2, g_height/2 - ih/2); gr_flip(); sleep(1);
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


	gr_exit();
	return 0;
}
