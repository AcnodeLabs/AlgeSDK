class CAnim16 {
	int frameno;	
public:
	float texcoords[8];
	float texcoords_cube[48];
	
	
	void setcoords(float x, float y) {
		this->texcoords[0]= x;this->texcoords[1]= y;
		this->texcoords[2]= x;this->texcoords[3]= y + 0.25f;
		this->texcoords[4]= x+0.25f;this->texcoords[5]= y;
		this->texcoords[6]= x+0.25f;this->texcoords[7]= y + 0.25f;
	}
	
	void setframe(int f) {
		
		if (f==12) setcoords(0.00f,0.0f);
		if (f==13) setcoords(0.25f,0.0f);
		if (f==14) setcoords(0.50f,0.0f);
		if (f==15) setcoords(0.75f,0.0f);
		if (f==8) setcoords(0.00f,0.25f);
		if (f==9) setcoords(0.25f,0.25f);
		if (f==10) setcoords(0.50f,0.25f);
		if (f==11) setcoords(0.75f,0.25f);
		if (f==4) setcoords(0.00f,0.5f);
		if (f==5) setcoords(0.25f,0.5f);
		if (f==6) setcoords(0.50f,0.5f);
		if (f==7) setcoords(0.75f,0.5f);
		if (f==0) setcoords(0.00f,0.75f);
		if (f==1) setcoords(0.25f,0.75f);
		if (f==2) setcoords(0.50f,0.75f);
		if (f==3) setcoords(0.75f,0.75f);
		
		bool cubed = true;
		if (cubed) {
			for (int i=0; i<48; i+=8) {
				for (int j=0; j<8; j++) texcoords_cube[i+j]=texcoords[j];
			}
		}
	}
	
};