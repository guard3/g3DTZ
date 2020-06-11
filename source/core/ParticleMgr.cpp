#include "ParticleMgr.h"
#include <math.h>

const char* CParticleSystemData::GetCreateRange()
{
	return Precision(sqrtf(m_fCreateRange));
}