class CCollide {
public:
	// Returns a Vector containing indexes of the detected first collided objects
	// Returns negative 1 if nothing collided so use carefully w.r.t indexes
	vec2 GetFirstCollisionInstance(vec2* positions1, vec2* positions2, int idxlimit, int radius) {
		vec2 indexes;
		bool collided = false;
		for (int i=0; i<idxlimit; i++) {
            for (int j=0; j<idxlimit; j++) {
                collided = positions1->subtract(positions1[i], positions2[j]).length()<radius;
                if (collided) {indexes.x=i; indexes.y=j;return indexes;}
            }
		}
		indexes.x=-1;
		indexes.y=-1;
		return indexes;
	}
    
	void Test() {
		vec2 p1[10]; vec2 p2[10];
		for (int t=0; t<10; t++) {
			p1[t].x = (t+1)*10; p1[t].y = (t+1)*10;
			p2[t].x = (10-t)*10; p2[t].y = (10-t)*10;
		}
        
		vec2 idx = GetFirstCollisionInstance(p1, p2, 10, 10.0f);
		
		if (idx.x>=0 && idx.y>=0) {
			

		}
        
	}
};
