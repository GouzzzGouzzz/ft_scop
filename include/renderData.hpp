#pragma once

#include "matrix4.hpp"
#include "defines.hpp"
#include <GL/glx.h>


class RenderData{
	public:
		RenderData();
		~RenderData();
		void applyRotation();
		void decreaseAngleX(double step);
		void decreaseAngleY(double step);
		void decreaseAngleZ(double step);
		void increaseAngleX(double step);
		void increaseAngleY(double step);
		void increaseAngleZ(double step);
		std::array<std::array<float, 4>, 4> getMVP() const;
		void lookAtObj(const std::vector<GLfloat> &vertices);
	private:
		Matrix4 MVP;
		Matrix4 Model;
		Matrix4 View;
		Vector3 cameraPos;
		Matrix4 Proj;
		double angleX;
		double angleY;
		double angleZ;

};
