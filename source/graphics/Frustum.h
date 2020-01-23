#ifndef INCLUDED_FRUSTUM
#define INCLUDED_FRUSTUM

#include "../maths/Plane.h"

//10 planes should be enough
#define MAX_NUM_FRUSTUM_PLANES		(10)

class CBoundingBoxAligned;
class CMatrix3D;

class CFrustum
{
public:
	CFrustum ();
	~CFrustum ();

	//Set the number of planes to use for
	//calculations. This is clipped to
	//[0,MAX_NUM_FRUSTUM_PLANES]
	void SetNumPlanes (size_t num);

	size_t GetNumPlanes() const { return m_NumPlanes; }

	void AddPlane (const CPlane& plane);

	void Transform(CMatrix3D& m);

	//The following methods return true if the shape is
	//partially or completely in front of the frustum planes
	bool IsPointVisible(const CVector3D& point) const;
	bool DoesSegmentIntersect(const CVector3D& start, const CVector3D& end) const;
	bool IsSphereVisible(const CVector3D& center, float radius) const;
	bool IsBoxVisible(const CVector3D& position, const CBoundingBoxAligned& bounds) const;
	bool IsBoxVisible(const CBoundingBoxAligned& bounds) const;

	CPlane& operator[](size_t idx) { return m_aPlanes[idx]; }
	const CPlane& operator[](size_t idx) const { return m_aPlanes[idx]; }

public:
	//make the planes public for ease of use
	CPlane m_aPlanes[MAX_NUM_FRUSTUM_PLANES];

private:
	size_t m_NumPlanes;
};

#endif
