#ifndef XFUNCTIONS_HPP
#define XFUNCTIONS_HPP
#include "CBaseV1_2.h"

class XFunction {

};

class XFunction_AutoScalingToFullScreen : public XFunction {
public:
	static const int AUTO_SCALING_FULLSCREEN = -1;
	static void GameObjectAdded(GameObject* g, float scale) {
		if (scale == AUTO_SCALING_FULLSCREEN) g->scale = scale;
	}

	static void GetDimensionsOf(PosRotScale* that, int *mm_width, int *mm_height) {
		if (that->scale == AUTO_SCALING_FULLSCREEN) {
			*mm_width = that->originalScale;
			*mm_height = that->originalScale / that->originalAspect;
		}
	}
	
};
#endif