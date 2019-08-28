#ifndef NO_FONTLIB
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
       // CFTFont((char*)"serif_s24.glyphmap", 24);
    }
    
    void Init(char* fontname, int size) {
        font = nullptr;
		allok = false;
        //https://github.com/jtsiomb/libdrawtext/blob/master/examples/simple/simple.c
        /* XXX dtx_open_font opens a font file and returns a pointer to dtx_font */
        if(!(font = dtx_open_font_glyphmap(fontname))) {
            fprintf(stderr, "failed to open font\n");
            // return 1;
        }
        /* XXX select the font and size to render with by calling dtx_use_font
         * if you want to use a different font size, you must first call:
         * dtx_prepare(font, size) once.
         */
       // dtx_prepare(font, size);
        dtx_use_font(font, 12);
		allok = true;
	}
    void PrintText(char* text) {
        if (font!=nullptr) dtx_string(text);
    }
	void PrintTextGl(string txt, f3 color = f3(0.5,0.5,0.5), float scale = 1.0) {
		glPushMatrix();
		glScalef(scale, scale, scale);
		glRotatef(180.0, 1, 0, 0);
	//	if (font != nullptr) 
		glColor3f(color.x, color.y, color.z);
		dtx_string(txt.c_str());
		glColor3f(1.,1.,1.);
		glPopMatrix();
	}

    ~CFTFont() {
        dtx_flush();
        if (font!=nullptr && allok) dtx_close_font(font);
    }

};
#endif
#else
//BLANK FUNCTIONS
class CFTFont {
    public:
    CFTFont()  {}
    ~CFTFont() {}
    void PrintTextGl(string txt, f3 color = f3(0.5,0.5,0.5), float scale = 1.0) {}
    void PrintText(char* text) {}
    CFTFont(char* fontname, int size) {}
};

#endif
