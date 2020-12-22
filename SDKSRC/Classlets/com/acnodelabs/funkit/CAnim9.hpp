#ifdef CANIM9_INCLUDED
#else
#define CANIM9_INCLUDED


class CAnim9  {

	float top;
		float left;

		float texcoords[6*2];

		float getTop(int segment) {
			if (segment<3) return 0.33f;//seg<3
			if (segment<6) return 0.66f;//seg>5
			return 1.0f;
		}

		float getLeft(int segment) {
			if (segment==0 || segment==3 || segment==6) return 0.00f;
			if (segment==1 || segment==4 || segment==7) return 0.33f;
			if (segment==2 || segment==5 || segment==8) return 0.66f;
			return 0;
		}

		void genTexCoords() {
			
			texcoords[0] = left + 0.33f; texcoords[1] = top;
			texcoords[2] = left; texcoords[3] = top;
			texcoords[4] = left; texcoords[5] = top - 0.33f;
			
			texcoords[6] =left + 0.33f; texcoords[7] =top ;
			texcoords[8] = left; texcoords[9] = top-0.33f;
			texcoords[10] = left+0.33f; texcoords[11] = top-0.33f;
			
		}

		

		int setHeadingAndSeg9(bool active, float x1, float y1, float x2, float y2) {
			float M_PIE = 3.14159f;
			
			// make sure we're dealing with points
			if (!active) {seg9 = 4; return seg9;}	
			// All in radians
			double theta_radians = atan2(y2 - y1, x2 - x1);
			heading = (float)(theta_radians + M_PIE) * 360.0 / (2.0 * M_PIE);
			
			if (heading<0) {while (heading<0) {heading+=360;}}
			if (heading>=360) {	while (heading>360) {heading-=360;}}

			//See Dir9.tga
			if (heading >= 0 && heading <= 22.5)  {seg9 = 3; return seg9;}
			if (heading > 22.5  && heading <= 67.5)  {seg9 = 0; return seg9;}
			if (heading > 67.5  && heading <= 112.5)  {seg9 = 1; return seg9;}
			if (heading > 112.5 && heading <= 157.5) {seg9 = 2; return seg9;}
			if (heading > 157.5 && heading <= 202.5) {seg9 = 5; return seg9;}
			if (heading > 202.5 && heading <= 247.5) {seg9 = 8; return seg9;}
			if (heading > 247.5 && heading <= 292.5) {seg9 = 7; return seg9;}
			if (heading > 292.5 && heading <= 337.5) {seg9 = 6; return seg9;}
			if (heading > 337.5 && heading <= 360)  {seg9 = 3; return seg9;}
			return seg9;
		}

		float* getTexCoords(int segment) {
			top = getTop(segment); left = getLeft(segment);
			genTexCoords() ;
			return & texcoords[0];
		}

		int seg9;

		public:
		
		float heading;
		
		void UpdateModelTexCoordsFromHeading(float* tex_array, bool activ, float currX, float currY, float desiredX, float desiredY) {
			seg9 = setHeadingAndSeg9(activ, currX, currY, desiredX, desiredY);
			float* textCoods = getTexCoords(seg9);
			memcpy(tex_array, textCoods, sizeof(float)*12);	
		}

};
#endif