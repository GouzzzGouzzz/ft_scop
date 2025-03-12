#pragma once

#include "matrix4.hpp"
#include "defines.hpp"


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
	private:
		Matrix4 MVP;
		Matrix4 Model;
		double angleX;
		double angleY;
		double angleZ;
		Matrix4 View;
		Matrix4 Proj;

};
