#ifndef INCLUDED_CAMERA
#define INCLUDED_CAMERA

#include "Frustum.h"
#include "../maths/BoundingBoxAligned.h"
#include "../maths/Matrix3D.h"

// view port
struct SViewPort
{
	int m_X;
	int m_Y;
	int m_Width;
	int m_Height;
};

class CCamera
{
	public:
		CCamera();
		~CCamera();

		// Methods for projection
		void SetProjection(float nearp, float farp, float fov);
		void SetProjection(const CMatrix3D& matrix) { m_ProjMat = matrix; }
		void SetProjectionTile(int tiles, int tile_x, int tile_y);
		CMatrix3D& GetProjection() { return m_ProjMat; }
		const CMatrix3D& GetProjection() const { return m_ProjMat; }

		CMatrix3D& GetOrientation() { return m_Orientation; }
		const CMatrix3D& GetOrientation() const { return m_Orientation; }

		CMatrix3D GetViewProjection() const { return m_ProjMat * m_Orientation.GetInverse(); }

		// Updates the frustum planes. Should be called
		// everytime the view or projection matrices are
		// altered.
		void UpdateFrustum(const CBoundingBoxAligned& scissor = CBoundingBoxAligned(CVector3D(-1.0f, -1.0f, -1.0f), CVector3D(1.0f, 1.0f, 1.0f)));
		void ClipFrustum(const CPlane& clipPlane);
		const CFrustum& GetFrustum() const { return m_ViewFrustum; }

		void SetViewPort(const SViewPort& viewport);
		const SViewPort& GetViewPort() const { return m_ViewPort; }

		// getters
		float GetNearPlane() const { return m_NearPlane; }
		float GetFarPlane() const { return m_FarPlane; }
		float GetFOV() const { return m_FOV; }

		// return four points in camera space at given distance from camera
		void GetCameraPlanePoints(float dist,CVector3D pts[4]) const;

		// Build a ray passing through the screen coordinate (px, py) and the camera
		/////////////////////////////////////////////////////////////////////////////////////////
		// BuildCameraRay: calculate origin and ray direction of a ray through
		// the pixel (px,py) on the screen
		void BuildCameraRay(int px, int py, CVector3D& origin, CVector3D& dir) const;

		// General helpers that seem to fit here

		// Get the screen-space coordinates corresponding to a given world-space position
		void GetScreenCoordinates(const CVector3D& world, float& x, float& y) const;

		// Get the point on the terrain corresponding to pixel (px,py) (or the mouse coordinates)
		// The aboveWater parameter determines whether we want to stop at the water plane or also get underwater points
		CVector3D GetWorldCoordinates(int px, int py, bool aboveWater=false) const;
		// Get the point on the plane at height h corresponding to pixel (px,py)
		CVector3D GetWorldCoordinates(int px, int py, float h) const;
		// Get the point on the terrain (or water plane) the camera is pointing towards
		CVector3D GetFocus() const;

		// Build an orientation matrix from camera position, camera focus point, and up-vector
		void LookAt(const CVector3D& camera, const CVector3D& orientation, const CVector3D& up);

		// Build an orientation matrix from camera position, camera orientation, and up-vector
		void LookAlong(const CVector3D& camera, CVector3D focus, CVector3D up);

		/**
		 * Render: Renders the camera's frustum in world space.
		 * The caller should set the color using glColorXy before calling Render.
		 *
		 * @param intermediates determines how many intermediate distance planes should
		 * be hinted at between the near and far planes
		 */
		void Render(int intermediates = 0) const;

	public:
		// This is the orientation matrix. The inverse of this
		// is the view matrix
		CMatrix3D		m_Orientation;

		// Should not be tweaked externally if possible
		CMatrix3D		m_ProjMat;

	private:
		float			m_NearPlane;
		float			m_FarPlane;
		float			m_FOV;
		SViewPort		m_ViewPort;

		CFrustum		m_ViewFrustum;
};

#endif
