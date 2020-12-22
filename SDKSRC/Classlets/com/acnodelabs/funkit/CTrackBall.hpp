
class CTrackBall {

public:
	float radius;
	float saferadius;
	vec2 m_fingerStart, m_fingerEnd;
	bool m_spinning;
	CQuaternion m_orientation;
	CQuaternion m_prevOrientation;
	vec2 centerpoint;
    vec3 start;
    vec3 end;
    CQuaternion delta;
    vec2 touch1;
    vec2 touch2;
    
    
	CTrackBall() {
		radius = 106;
		saferadius = radius -1;
		reset();
        touch1.clear();
        touch2.clear();
        nFingers = 0;
	}

	void reset() {
		m_orientation.clear();
		m_prevOrientation.clear();
        touch1.clear();
        touch2.clear();
	}

    vec3 _color () {
        vec3 c;
        if (nFingers==1) c.x = 1.0f;
        if (nFingers==2) c.y = 1.0f;
        return c;
    }
    
    short nFingers;
    
    
	inline void processTouches(int command, int x, int y) {
	
      	switch (command) {
            case CMD_TOUCH_END2:
                touch2.clear();
                nFingers--;
                break;
			case CMD_TOUCH_START2:
                touch2.x = x; touch2.y = y;
                oldlen = touch2.subtract(touch2, touch1).length();
                m_spinning = false;
                nFingers++;
                break;
            case CMD_TOUCHMOVE2:
                touch2.x = x; touch2.y = y;
                m_spinning = false;
                break;
            case CMD_TOUCHMOVE:
            {
                if (m_spinning && !isPinching()) {
                    start = MapToSphere(m_fingerStart);
                    end   = MapToSphere(vec2(x,y));
                    delta = CQuaternion::CreateFromVectors(start, end);
                    m_orientation = delta.Rotated(m_prevOrientation);
                }
                
            }
            break;

			case CMD_TOUCH_START:
                touch1.x = x; touch1.y = y;
                onTouchDown(x,y);
                nFingers++;
                break;
			case CMD_TOUCH_END:
                touch1.x = x; touch1.y = y;
				onTouchUp(x,y);
              //  touch1.clear();
              //  touch2.clear();
                m_spinning = false;
                nFingers--;
                break;
            case CMD_SCREENSIZE:
                touch1.x = x; touch1.y = y;
				onScreenSize(x,y); 
    			break;
		}
	}

	void ApplyRotate() {m_orientation.alDoRotate();}

	void onScreenSize(int ix, int iy) {
        centerpoint.x = ix / 2;
		centerpoint.y = iy / 2;
        radius = ix /2 ;
        if (iy>ix)
        radius = iy /2 ;
        saferadius = radius -1;
	}
    
    float oldlen;
    
    inline bool isPinching() {
        if (touch1.x==0) return false;
        if (touch1.y==0) return false;
        if (touch2.x==0) return false;
        if (touch2.y==0) return false;
        if (touch2.x || touch2.y) return true; else return false;
    }
    
    
    inline short pinchDirection() {
        if (!isPinching()) return 0;
        short ret = 0;
        vec2 touch3 = touch2.subtract(touch2, touch1);
        float len = touch3.length();
        {
            if (len<oldlen) ret = 1;
            if (len>oldlen) ret = -1;
        }
        oldlen = len;
        return ret;
    }

	inline void onTouchDown(int ix, int iy) {
        m_fingerStart.x = ix; m_fingerStart.y = iy;
		m_prevOrientation.copy(m_orientation);
		m_spinning = true;
	}

	inline void onTouchUp(int ix, int iy) {
		m_spinning = false;
	}

	inline void onTouchMove(int ix, int iy) {
		if (m_spinning) {
			vec3 start = MapToSphere(m_fingerStart);
			vec3 end   = MapToSphere(vec2(ix,iy));
			CQuaternion delta = CQuaternion::CreateFromVectors(start, end);
			m_orientation = delta.Rotated(m_prevOrientation);
		}
	}

	vec3 MapToSphere(vec2 touchpoint) {	
		vec2 p = vec2::subtract(touchpoint, centerpoint);
		//p.y = -p.y;

		if (p.length() > saferadius) {
			float theta = atan2(p.y, p.x);
			p.x = saferadius * cos(theta);
			p.y = saferadius * sin(theta);
		}

		float z = sqrt(radius*radius - p.lengthsquared());
		vec3 mapped(p.x,p.y,z);
		vec3 ret(mapped.x, mapped.y, mapped.z);
		ret = ret.divide(radius);
		return ret;
	}
};
