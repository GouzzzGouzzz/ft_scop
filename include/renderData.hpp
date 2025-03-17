#pragma once

#include "matrix4.hpp"
#include "defines.hpp"
#include <GL/glx.h>

//add color
//add texture
//add rotation around sym axis
//moving object on x y z
//add scaling (zoom in/out)

class RenderData{
	public:
		RenderData(const std::vector<GLfloat> &vertices);
		RenderData();
		~RenderData();
		void lookAtObj();
		//Rotation Handling (might have to redo this in fact)
		void applyRotation();
		void decreaseAngleX(double step);
		void decreaseAngleY(double step);
		void decreaseAngleZ(double step);
		void increaseAngleX(double step);
		void increaseAngleY(double step);
		void increaseAngleZ(double step);
		//Translation Handling (Move object)
		void axeX(double step);
		void axeY(double step);
		void axeZ(double step);
		//Scaling Handling (Zoom in/out)
		void zoomIn(double step);
		void zoomOut(double step);
		Vector3 getObjCenter() const;
		std::array<std::array<float, 4>, 4> getMVP() const;
		//temp
		void init(const std::vector<GLfloat> &vertices);
	private:
		const std::vector<GLfloat> *vertices;
		Matrix4 MVP;
		Matrix4 Model;
		float zoom;
		float moveX;
		float moveY;
		float moveZ;
		Matrix4 View;
		Vector3 cameraPos;
		Matrix4 Proj;
		double angleX;
		double angleY;
		double angleZ;
};
