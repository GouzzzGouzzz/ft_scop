#pragma once

#include "matrix4.hpp"
#include "defines.hpp"
#include <GL/glx.h>

//add texture
//add rotation around sym axis (will have to use quarternion)

//add color (done but terrible, and can be optimized)
//scaling/zoom not perfect (works)
//translation works, may need a visual indicator
class RenderData{
	public:
		RenderData(const std::vector<GLfloat> &vertices);
		RenderData();
		~RenderData();
		void lookAtObj();
		//Rotation Handling
		//use quarterion for rotation
		//Translation Handling (Move object)
		void axeX(double step);
		void axeY(double step);
		void axeZ(double step);
		//Scaling Handling (Zoom in/out)
		void zoomIn(double step);
		void zoomOut(double step);
		Vector3 getObjCenter() const;
		std::array<std::array<float, 4>, 4> getMVP() const;
		//Color handling
		std::vector<GLfloat> getGrayScaleColor(uint8_t nbOfGray) const;
		std::vector<GLfloat> cycleColor(void) const;
		//temp
		void init(const std::vector<GLfloat> &vertices);
	private:
		const std::vector<GLfloat> *vertices;
		Matrix4 MVP;
		Matrix4 Model;
		Matrix4 Scale;
		float zoom;
		Matrix4 Rotate;
		Matrix4 Translate;
		float moveX;
		float moveY;
		float moveZ;
		Matrix4 View;
		Vector3 cameraPos;
		Matrix4 Proj;
		void calcMVP(void);
};
