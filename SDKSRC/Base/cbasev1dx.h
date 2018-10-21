class CModel {

public:
	int index;
	char name[64];
	float vertex_array[512 * 512 * 6];
	float normals_array[512 * 512 * 6];
	unsigned char color_array[512 * 512 * 5];
	unsigned short indices_array[1024 * 3];
	float uv_array[512 * 512 * 4];

	float vertex_array_gl[1];
	float normals_array_gl[1];
	unsigned short indices_array_gl[1];
	float uv_array_gl[1];

	//TextureImage texture[1];

	int n_indices_accessors;
	int n_indices;
	int n_vertices;
	int n_normals;
	int n_uv;
	int n_colors;
	int INDICES_DRAWMODE;
	int* loaded;
	float fscale;
	unsigned int vbo;
	unsigned int vboNormals;

	bool noVBO;

	CModel() {
		n_vertices = 0;
		n_normals = 0;
		n_colors = 0;
		n_indices = 0;
		n_uv = 0;
		fscale = 1.0f;
		loaded = &n_vertices;
		index = 0;
		noVBO = false;
		_scaleX = 1;
		_scaleY = 1;
		_scaleZ = 1;
	}

	~CModel() {
	}

	//called by resourcemanager
	void onLoad() {
	}

	//tries to get max depth of model
	float boundz() {
		float zmax = 0;
		for (int i = 0; i<n_vertices * 3; i++) {
			zmax = (vertex_array[i]>zmax ? vertex_array[i] : zmax);
		}
		return zmax;
	}

	void info(char* o) {
		if (this->name[0]) { strcpy_s(o, 128, "Name="); strcat_s(o,128, this->name); }
		char stats[128];
		sprintf_s(stats,128, "\n%d Vertices\n%d Colors\n%d Normals\n%d Texture Coords\n%d Indices\ntexId=%d", this->n_vertices, this->n_colors, this->n_normals, this->n_uv, this->n_indices, 0);
		strcat_s(o,128, stats);
	}

	float _scaleX, _scaleY, _scaleZ;

	void scale(float v) {
		for (int i = 0; i< n_vertices * 3; i++)
		{
			vertex_array[i] *= v;
		}
		fscale *= v;
		//phys.boundz*=v;
	}

	void glDrawLocalAxis()
	{

	}

	void SetScale(float sx, float sy, float sz) {
		_scaleX = sx;
		_scaleY = sy;
		_scaleZ = sz;
	}

	void loadSeg(FILE* fl, short ver, char type, void* ptr)
	{

		int l = 0;
		if (type == 'V') n_vertices = l / sizeof(float) / 3;
		if (type == 'N') n_normals = l / sizeof(float) / 3;
		if (type == 'T') n_uv = l / sizeof(float) / 2;
		if (type == 'I') n_indices = l / sizeof(int);

		fread(ptr, 1, l, fl);
	}

	void loadVnt(char* objname)
	{
		char fname[64];
		sprintf(fname, "%s.vnt", objname);

		FILE*f = fopen(fname, "rb");
		short ver = 1;
		if (f)
		{
			loadSeg(f, ver, 'V', vertex_array_gl);
			loadSeg(f, ver, 'N', normals_array_gl);
			loadSeg(f, ver, 'T', uv_array_gl);
			loadSeg(f, ver, 'I', indices_array_gl);

			fclose(f);
		}

	}

	void saveSeg(FILE* fl, short ver, char type, int len, void* ptr)
	{
		fwrite(&ver, 1, sizeof(short), fl);
		fwrite(&type, 1, sizeof(char), fl);
		fwrite(&len, 1, sizeof(int), fl);
		fwrite(ptr, 1, len, fl);
	}

	void setFinalArray(char type, int n_items, float* array)
	{
		int nbytesrequired = 0;
		char* ptr = 0;

		switch (type) {
		case 'V':
		{n_vertices = n_items; ptr = (char*)vertex_array_gl; nbytesrequired = n_items * sizeof(float) * 3; }
			break;
		case 'N':
		{n_normals = n_items; ptr = (char*)normals_array_gl; nbytesrequired = n_items * sizeof(float) * 3; }
			break;
		case 'T':
		{n_uv = n_items; ptr = (char*)uv_array_gl; nbytesrequired = n_items * sizeof(float) * 2; }
			break;
		case 'I':
		{n_indices = n_items; ptr = (char*)indices_array_gl; nbytesrequired = n_items * sizeof(int); }
			break;
		default:
			break;
		}

		memcpy(ptr, array, nbytesrequired);

	}

	void saveVnt(char* objname)
	{
		char fname[64];
		sprintf(fname, "%s.vnt", objname);

		FILE*f = fopen(fname, "wb");
		short ver = 1;
		if (f)
		{
			saveSeg(f, ver, 'V', n_vertices * 3 * sizeof(float), vertex_array_gl);
			saveSeg(f, ver, 'N', n_normals * 3 * sizeof(float), normals_array_gl);
			saveSeg(f, ver, 'T', n_uv * 2 * sizeof(float), uv_array_gl);
			saveSeg(f, ver, 'I', n_indices*sizeof(int), indices_array_gl);

			fclose(f);
		}

	}

	void fillGLarrays()
	{
		int j = 0;
		int j_3 = 0;

		bool no_tex;
		bool no_normals;

		for (int i = 0; i<n_indices*n_indices_accessors; i += n_indices_accessors) {

			no_tex = (n_indices_accessors<3);
			no_normals = (n_indices_accessors<2);

			int iver = indices_array[i];
			int ino = indices_array[i + 1];
			int itx = indices_array[i + 2];

			float vx = vertex_array[3 * iver];
			float vy = vertex_array[3 * iver + 1];
			float vz = vertex_array[3 * iver + 2];

			float nx = normals_array[3 * ino];
			float ny = normals_array[3 * ino + 1];
			float nz = normals_array[3 * ino + 2];

			float tu = uv_array[2 * itx];
			float tv = uv_array[2 * itx + 1];

			indices_array_gl[j] = j;

			vertex_array_gl[j_3] = vx;
			vertex_array_gl[j_3 + 1] = vy;
			vertex_array_gl[j_3 + 2] = vz;

			if (!no_normals) {
				normals_array_gl[j_3] = nx;
				normals_array_gl[j_3 + 1] = ny;
				normals_array_gl[j_3 + 2] = nz;
			}

			if (!no_tex) {
				uv_array_gl[2 * j] = tu;
				uv_array_gl[2 * j + 1] = tv;
			}
			j++;
			j_3 += 3;
		}

		if (n_vertices) n_vertices = j;
		if (n_normals) n_normals = j;
		if (n_indices) n_indices = j;
		if (n_uv) n_uv = j;

		if (no_tex) n_uv = 0;
		if (no_normals) n_normals = 0;
	}


	void setName(char* n) {
		strcpy(name, n);
	}

};