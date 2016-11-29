#include <unistd.h>

#include <stdio.h>

#include <minui.h>

int g_width = 0;
int g_height = 0;

FILE *fout = NULL, *ferr = NULL;

int main()
{
	gr_init();

	g_width = gr_fb_width();
	g_height = gr_fb_height();

	fout = freopen("/data/local/out.txt", "w+", stdout); if (!fout) perror("fopen");
	ferr = freopen("/data/local/err.txt", "w+", stderr); if (!ferr) perror("fopen");

	printf("width: %d, height: %d\n", g_width, g_height);

	while (1) {
		gr_color(255, 255, 255, 255); gr_fill(0, 0, g_width, g_height); sleep(1);
		gr_color(255,   0,   0, 255); gr_fill(0, 0, g_width, g_height); sleep(1);
		gr_color(  0, 255,   0, 255); gr_fill(0, 0, g_width, g_height); sleep(1);
		gr_color(  0,   0, 255, 255); gr_fill(0, 0, g_width, g_height); sleep(1);
		gr_color(  0,   0,   0, 255); gr_fill(0, 0, g_width, g_height); sleep(1);
		printf("flush screen\n");
	}

	gr_exit();
	return 0;
}
