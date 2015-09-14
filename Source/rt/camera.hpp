/*!
 * \file camera.hpp
 * \date 2015/09/13 14:24
 *
 * \author wangzs
 * Contact: wang.zhenshui@gmail.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/
#pragma once

#include "../core/math.hpp"
#include "ray.hpp"

namespace cgray {
	namespace rt {
		class Camera {
		public:
			Camera(Vector3f direction, Vector3f up);

			virtual Ray generateRay(int x, int y) const = 0;

			// get and set
			void setCameraParams(const Vector3f& direction, const Vector3f& up);
			const Vector3f& direction() const;
			const Vector3f& up() const;
			const Vector3f& right() const;

		protected:
			void norm();

		protected:
			Vector3f direction_;		// Viewing direction
			Vector3f up_;				// Up-vector
			Vector3f right_;			// Right-vector
		};

		class PerspectiveCamera : public Camera {
		public:
			PerspectiveCamera();

			PerspectiveCamera(Vector3f pos, Vector3f target, Vector3f up, float fov, int res_x, int res_y);

			virtual Ray generateRay(int x, int y) const override;


		private:
			Vector3f pos_;		// Camera origin
			float fov_;			// (Full) vertical opening angle of the viewing frustum (in degrees)
			int res_x_;			// Image resolution width
			int res_y_;			// Image resolution height
		};


		class OrthographicCamera : public Camera {
		public:
			OrthographicCamera();
			OrthographicCamera(Vector3f pos, Vector3f target, Vector3f up, int res_x, int res_y);

			virtual Ray generateRay(int x, int y) const override;

		private:
			Vector3f pos_;		// Camera origin
			int res_x_;			// Image resolution width
			int res_y_;			// Image resolution height
		};

		class FishEyeCamera : public Camera {
		public:

			virtual Ray generateRay(int x, int y) const override;

		private:

		};





	}
}

