class CHealthIndicator {
	CModel* mo;
	float width;
	float height;
public:

	void Init(CModel* sparemodel, float width, float height) {
		mo = sparemodel;
		mo->n_vertices = 6;
		this->width = width;
		this->height = height;
	}

	void glDraw(float OffestX, float OffsetY, float level) {
		float* v = mo->vertex_array;

		float h = height * level;

		v[0] = width/2;		v[1] = h;	v[2] = 0;
		v[3] = -width/2;	v[4] = h;	v[5] = 0;
		v[6] = -width/2;	v[7] = 0;	v[8] = 0;

		v[ 9] = width/2;	v[10] = h;	v[11] = 0;
		v[12] = -width/2;	v[13] = 0;	v[14] = 0;
		v[15] = width/2;	v[16] = 0;	v[17] = 0;
#ifndef NOGL
		glTranslatef(OffestX,OffsetY,0);
		mo->glDraw();
#endif
	}
};
