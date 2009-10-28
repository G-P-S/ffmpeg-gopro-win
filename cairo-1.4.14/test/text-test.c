/*
 * Copyright © 2005 Tim Rowley
 *
 * Permission to use, copy, modify, distribute, and sell this software
 * and its documentation for any purpose is hereby granted without
 * fee, provided that the above copyright notice appear in all copies
 * and that both that copyright notice and this permission notice
 * appear in supporting documentation, and that the name of
 * Red Hat, Inc. not be used in advertising or publicity pertaining to
 * distribution of the software without specific, written prior
 * permission. Red Hat, Inc. makes no representations about the
 * suitability of this software for any purpose.  It is provided "as
 * is" without express or implied warranty.
 *
 * RED HAT, INC. DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS
 * SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS, IN NO EVENT SHALL RED HAT, INC. BE LIABLE FOR ANY SPECIAL,
 * INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER
 * RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR
 * IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * Author: Tim Rowley
 */

#include <windows.h>
#define CAIRO_BOILERPLATE_LOG(...) cairo_test_log (__VA_ARGS__)
#include "cairo-boilerplate.h"

#if   HAVE_STDINT_H
# include <stdint.h>
#elif HAVE_INTTYPES_H
# include <inttypes.h>
#elif HAVE_SYS_INT_TYPES_H
# include <sys/int_types.h>
#elif defined(_MSC_VER)
typedef __int8 int8_t;
typedef unsigned __int8 uint8_t;
typedef __int16 int16_t;
typedef unsigned __int16 uint16_t;
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
# ifndef HAVE_UINT64_T
#  define HAVE_UINT64_T 1
# endif
#else
#error Cannot find definitions for fixed-width integral types (uint8_t, uint32_t, \etc.)
#endif

#ifdef _MSC_VER
#define _USE_MATH_DEFINES
#endif

#include <math.h>

#include "cairo-lib.h"

typedef int (*lpCairoLib)(CAIROlib *lib);

CAIROlib cairo;




void draw (cairo_t *cr, int width, int height)
{
  cairo_font_options_t *font_options;

  
  cairo.set_source_rgba (cr, 1, 1, 1, 0.5); // white at 50%
  //cairo.scale (cr, width, height);
  cairo.scale (cr, height, height);
  cairo.rectangle (cr, 0, 0, 2, 1);
  cairo.fill (cr);


 // cairo.select_font_face (cr, "Bitstream Vera Sans",
	 cairo.select_font_face (cr, "Courier New Bold",
			  CAIRO_FONT_SLANT_NORMAL,
			  CAIRO_FONT_WEIGHT_NORMAL);


  {
	  double xc = 128.0;
	double yc = 128.0;
	double radius = 100.0;
	double angle1 = 45.0  * (M_PI/180.0);  // angles are specified 
	double angle2 = 180.0 * (M_PI/180.0);  // in radians           

	cairo.set_source_rgba (cr, 0, 0, 0, 0.9);//black 90%

	cairo.scale (cr, 1.0/height, 1.0/height);
	cairo.set_line_width (cr, 10.0);
	cairo.arc_negative (cr, xc, yc, radius, angle1, angle2);
	cairo.stroke (cr);

	// draw helping lines
	cairo.set_source_rgba (cr, 1, 0.2, 0.2, 0.6);
	cairo.set_line_width (cr, 6.0);

	cairo.arc (cr, xc, yc, 10.0, 0, 2*M_PI);
	cairo.fill (cr);

	cairo.arc (cr, xc, yc, radius, angle1, angle1);
	cairo.line_to (cr, xc, yc);
	cairo.arc (cr, xc, yc, radius, angle2, angle2);
	cairo.line_to (cr, xc, yc);
	cairo.stroke (cr);
  }
  //cairo.scale (cr, width, height);
  cairo.scale (cr, height, height);

  // test rectangle - make sure the gradient is set correctly 
  cairo.set_source_rgba (cr, 1, 1, 1, 0.7); // white 70%
  cairo.rectangle (cr, 0, 0, 0.1, 1);
  cairo.fill (cr);

	font_options = cairo.font_options_create ();
	cairo.get_font_options (cr, font_options);
	cairo.font_options_set_antialias (font_options, CAIRO_ANTIALIAS_DEFAULT);
	cairo.set_font_options (cr, font_options);
	cairo.font_options_destroy (font_options);

  {
	cairo_text_extents_t extents;
	double fsize;

	cairo_pattern_t *pat;
	pat = cairo.pattern_create_linear (0.0, 0.0, 1, 1);
	cairo.pattern_add_color_stop_rgba (pat, 1, 1, 1, 0.5, 0.5);
	cairo.pattern_add_color_stop_rgba (pat, 0, 1, 1, 0.5, 1.0);

	cairo.set_font_size (cr, 1);
	cairo.text_extents(cr, "01:00:00:00", &extents);


	fsize = (2-0.1)/extents.width;
	cairo.set_font_size (cr, fsize);
	cairo.text_extents(cr, "01:00:00:00", &extents);

	//cairo.arc (cr, 1.05, 0.5, 0.9, 0, 2*M_PI);
	//cairo.clip (cr);

    cairo.set_source_rgba (cr, 0, 0, 0, 0.6); // black 60%
	cairo.rectangle (cr, 0.1-extents.height*0.1, 0.5-extents.height*1.2/2.0, extents.width+extents.height*0.2, extents.height*1.2);
	cairo.fill (cr);

	//cairo.set_source (cr, pat);  
	cairo.text_extents(cr, "01:00:00:00", &extents);
    cairo.set_source_rgba (cr, 1, 1, 0, 0.8); // yellow 80%
	cairo.move_to (cr, 0.1-extents.x_bearing, 0.5+extents.height/2.0);// + extents.);
	cairo.show_text (cr, "01:00:00:00");

	{
		int w,h;
		cairo_surface_t *image;

		image = cairo.image_surface_create_from_png ("pngtest.png");
		if(image)
		{
			w = cairo.image_surface_get_width (image);
			h = cairo.image_surface_get_height (image);

			cairo.scale (cr, 0.5/h, 0.5/h);

			cairo.set_source_surface (cr, image, 0.5, 0.75);
			cairo.paint (cr);

			cairo.surface_destroy (image);

		}
	}
 
	//cairo.set_source_rgba (cr, 1, 1, 0.5, 0.7); // yellow 70%
	//cairo.rotate(cr, 45.0  * (M_PI/180.0));

	cairo.pattern_destroy (pat);
  } 
  return;
}


int
main (void)
{
	unsigned char *data;
	int width=512,height=256;
	cairo_t *cr, *cr2;
	void *pLib = NULL;
	cairo_surface_t *surface;
	cairo_surface_t *surface2;
	char filePath[_MAX_PATH] = {'\0'};
	lpCairoLib		cairoLib;

	strcat(filePath, "C:\\HD\\misc\\cairo-1.4.10\\test\\MSTest\\debug\\libcairo.dll");

	pLib = (void*)LoadLibrary(filePath);
	if(pLib == NULL) 
	{
		return 0;
	}

	cairoLib = (lpCairoLib)GetProcAddress((HMODULE)pLib, "_cairo_lib");

	if(cairoLib)
	{
		if(cairoLib(&cairo))
		{
			printf("success\n");
		}
	}

	//surface = cairo_image_surface_create(CAIRO_FORMAT_A8, width, height);
	surface = cairo.image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
	if(surface)
	{
		cr = cairo.create(surface);
		if(cr)
		{
			draw(cr,width, height);

			surface2 = cairo.image_surface_create(CAIRO_FORMAT_ARGB32, width/2, height/2);
			cr2 = cairo.create(surface2);

			cairo.scale (cr2, 0.5, 0.5);

			//paint surface1 on and smaller surface2
			cairo.set_source_surface (cr2, surface, 0, 0); 
			cairo.paint (cr2);

			if(data = cairo.image_surface_get_data(surface2))
			{
				cairo.surface_write_to_png(surface, "surface.png");
				cairo.surface_write_to_png(surface2, "surface2.png");
				/*FILE *fp = fopen("RAW2.raw","wb");
				if(fp)
				{
					fwrite(data, 1, width*height*4/4, fp);
					fclose(fp);
				}*/
			}
		}
	}
	
	return 1;
}
