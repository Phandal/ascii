#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

/* TODO: Get the width and height programatically */
#define HEIGHT 42
#define WIDTH 128

#define LEN(arr) (sizeof(arr) / (sizeof(arr[0])))

const char CHARACTERS[] = {' ', '.', ':', '-', '=', '+', '*', '#', '%', '@'};

void usage() { puts("USAGE: ascii path/to/input/file"); }

float get_brightness_from_pixel(bmp_pixel_t *pixel) {
  return (pixel->red * 0.2126f + pixel->green * 0.7152f +
          pixel->blue * 0.0722f) /
         255;
}

char get_character_from_brightness(float brightness) {
  int index = (brightness * (LEN(CHARACTERS)));
  return CHARACTERS[index];
}

int main(int argc, char **argv) {
  if (argc != 2) {
    usage();
    exit(EXIT_FAILURE);
  }

  char *input_path = argv[1];
  bmp_image_t *img;
  img = bmp_load(input_path);
  if (!img) {
    fprintf(stderr, "failed to load image\n");
    exit(EXIT_FAILURE);
  }

  printf("number of pixels: %ld\n", img->numberOfPixels);

  for (int h = HEIGHT; h >= 0; --h) {
    for (int w = 0; w < WIDTH; ++w) {
      unsigned long index = (w * (img->info.width / WIDTH)) +
                            (h * (img->info.height / HEIGHT) * img->info.width);
      bmp_pixel_t pixel = img->pixel[index];

      float brightness = get_brightness_from_pixel(&pixel);
      char c = get_character_from_brightness(brightness);

#ifdef LOG
      fprintf(stderr, "%ld | %f | %d | %c | %d | %d | %d\n", index, brightness,
              c, c, pixel.red, pixel.green, pixel.blue);
#endif
      printf("%c", c);
    }
    printf("\n");
  }

  bmp_destroy(img);
  return 0;
}
