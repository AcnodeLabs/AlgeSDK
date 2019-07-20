#ifdef CFTFONT_INCLUDED
#else
#define CFTFONT_INCLUDED

#include "CFTFont_Dependencies/drawtext.h"

//use alPrintText(char*) instead

class CFTFont {
    struct dtx_font *font;
	bool allok = false;
public:
    
    CFTFont()  {
        CFTFont((char*)"C:\\OpenSans.ttf", 24);
    }
    CFTFont(char* fontname, int size) {
        font = nullptr;
		allok = false;
        //https://github.com/jtsiomb/libdrawtext/blob/master/examples/simple/simple.c
        /* XXX dtx_open_font opens a font file and returns a pointer to dtx_font */
        if(!(font = dtx_open_font(fontname, size))) {
            fprintf(stderr, "failed to open font\n");
            // return 1;
        }
        /* XXX select the font and size to render with by calling dtx_use_font
         * if you want to use a different font size, you must first call:
         * dtx_prepare(font, size) once.
         */
       // dtx_prepare(font, size);
        dtx_use_font(font, 24);
		allok = true;
	}
    void PrintText(char* text) {
        if (font!=nullptr) dtx_string(text);
    }
	void PrintTextGl(string text, float scale = 1.0) {
		glPushMatrix();
		glScalef(scale, scale, scale);
		if (font != nullptr) dtx_string(text.c_str());
		glPopMatrix();
	}

    ~CFTFont() {
        dtx_flush();
        if (font!=nullptr && allok) dtx_close_font(font);
    }

};
#endif
