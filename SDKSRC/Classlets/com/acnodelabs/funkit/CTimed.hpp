#ifdef CTIMED_INCLUDED
#else
#define CTIMED_INCLUDED
class CTimed {
public:
    
    float dst (float vel, float dt) { return vel*dt;}
    float spd (float dst, float dt) { return dst/dt;}
    
    float curr, from, to, speed;
    bool done;
    
    void Set(float from, float to, float speed) {
        this->curr = from;
        this->from = from;
        this->to   = to;
        this->speed = speed;
        done = false;
    }
    
    void ReDo() {
        this->curr = from;
        done = false;
    }
    
    float StepLinear(float dt) {
        
        if (done) return this->to;
        
        if (!done) {
            curr = curr + (from>to?-1:+1)* absolute(speed) * dt;
            if (to>from && curr>=to) done=true;
            if (to<from && curr<=to) done=true;
            if (to==from) done = true;
        } 
        return curr;
    }
    
    void Test() {
        
        while (true) {
            StepLinear(0.5f);
        }
        
    }
};
#endif
