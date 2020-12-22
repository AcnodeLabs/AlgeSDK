#ifdef CBALLOONTEXT_INCLUDED
#else
#define CBALLOONTEXT_INCLUDED
#define NOGLHERE
class CFilledQuad {

	private:
		float R,G,B;
		float vertices[28];
		float padding[28];
		
	void v(int i, float x, float y, float z = 0) {
		vertices[i*3+ 0] = x;
		vertices[i*3+ 1] = y;
		vertices[i*3+ 2] = z;
		padding[i*3 + 0] = x * 1.05;
		padding[i*3 + 1] = y * 1.05;
		padding[i*3 + 2] = z * 1.05;
	}

	public :
		CFilledQuad(int width, int height) {
		float x = width/2.0f;
		float y = height/2.0f;
		 // Vertices for the square
          

		  v(0,  -x, -(y));  
          v(1, -x*0.9f,  -(y)*2.5f);  
          v(2,  -x*0.7f,  -(y));   

		  v(3, x, y);  
          v(4,  -x, y);  
          v(5, -x,  -y);  
          v(6, x,  y);  
          v(7,  -x,  -y);   
		  v(8,  x,  -y);   
		}

		void SetFillColor3i(int R, int G, int B) {
			this->R = R / 255.; this->G = G/255.; this->B = B/255.;
		}

		void Render() {
#ifndef NOGLHERE
			glEnableClientState(GL_VERTEX_ARRAY);
			glColor4f(0,0,0,1);
			glVertexPointer(3, GL_FLOAT, 0, padding);
			glDrawArrays(GL_TRIANGLES, 0, 9);
			glColor4f(R,G,B,1);
			glVertexPointer(3, GL_FLOAT, 0, vertices);
			glDrawArrays(GL_TRIANGLES, 0, 9);
			glDisableClientState(GL_VERTEX_ARRAY);
#endif
		}

	};


	class CBalloonText {
		
		FontMap16x16 fonts;
		void* _memtext;	
		CResourceManager * _rm;
		int modelId;
		
		float sinx;

	public:
		float pos[3];
		void Init(CResourceManager *rm, int MODEL_ID) {

			rm->loadAlxModel((char*) "font.alx", AUTO, MODEL_ID, 1);	// Fonts Loaded just like Model
			fonts.usetexof(rm->models[MODEL_ID]);						// Associate texure of Loaded Model to FontMap
			_rm = rm;
			modelId = MODEL_ID;
			sinx = 0;
		}
		
		void SetText(char* text, int strlength, float scale) {			
			_memtext =  malloc(strlength+1);
			memset(_memtext,0,strlength);
			sprintf((char*)_memtext, "%s", text);
			fonts.SetScale(scale);
			fonts.print((char*)_memtext);
		}

		CBalloonText() {
			_memtext = 0;
		}

		CBalloonText(char* text, int size) {SetText(text, size,1);};

		~CBalloonText() {
			if (_memtext) free(_memtext);
		}


		void Render(float dt) {
#ifndef NOGL
			glTranslatef(pos[0],pos[1],0);
			int z = 20;//m->boundz();			
			//Come Back After CQuad in Done
			CFilledQuad balloon_bg(z ,z/5);
			balloon_bg.SetFillColor3i(128,0,128);
			glTranslatef(z/2,0,0);
			balloon_bg.Render();
			glTranslatef(-z/2.9,0,0);
			glColor3f(1, 1, 0.5);
			fonts.m->glDraw();
			glColor3f(1, 1, 1);
#endif
		}
	};
#endif