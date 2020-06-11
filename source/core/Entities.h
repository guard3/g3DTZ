#pragma once
#include "Common.h"
#include "Maths.h"
#include "RslEngine.h"

class CReference;

/* This should normally be an extension of CPlaceable, but no idea what they did so I keep everything in one place */
class CEntity
{
protected:
	RslMatrix   m_matrix;
	RslMatrix*  m_attachment;
#ifdef LCS
	char        flags[8];     //
	CReference* m_firstref;   //
#else                         // The flags format seems different between LCS and VCS, but I could be wrong...
	CReference* m_firstref;   //
	char        flags[8];     //
#endif
	RslObject*  m_rslObject;
	uint16      m_scanCode;
	uint16      m_randomSeed; // In VCS this seems to be the same as m_modelIndex for some reason...
	int16       m_modelIndex;
	uint8       m_level;
	uint8       m_area;       // This field might not even exist since it's uninitialized in VCS...
	void*       vtable;

public:
	inline int GetModelIndex() { return m_modelIndex; }
	inline CVector GetTranslation() { return { m_matrix.pos.x, m_matrix.pos.y, m_matrix.pos.z }; }
	CQuaternion GetRotation();
	const char* GetModelName();
};

class CBuilding  : public CEntity   {};
class CTreadable : public CBuilding {};
class CDummy     : public CEntity   {};