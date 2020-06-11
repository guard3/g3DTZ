#include "Entities.h"
#include "ModelInfo.h"
#include <math.h>

CQuaternion CEntity::GetRotation()
{
	/* Rename the RslMatrix elements to something more manageable */
    float
        &m00 = m_matrix.right.x, &m01 = m_matrix.right.y, &m02 = m_matrix.right.z,
        &m10 = m_matrix.up.x,    &m11 = m_matrix.up.y,    &m12 = m_matrix.up.z,
        &m20 = m_matrix.at.x,    &m21 = m_matrix.at.y,    &m22 = m_matrix.at.z;

    /* Convert rotation matrix to quaternion */
    CQuaternion q;
    if (m00 + m11 + m22 > 0.0f)
    {
        float sq = sqrtf(1.0f + m00 + m11 + m22);
        float rp = 0.5f / sq;
        q = { rp * (m12 - m21), rp * (m20 - m02), rp * (m01 - m10), sq * 0.5f };
    }
    else if ((m00 > m11) && (m00 > m22))
    {
        float sq = sqrtf(1.0f + m00 - m11 - m22);
        float rp = 0.5f / sq;
        q = { sq * 0.5f, rp * (m10 + m01), rp * (m20 + m02), rp * (m12 - m21) };
    }
    else if (m11 > m22)
    {
        float sq = sqrtf(1.0f + m11 - m00 - m22);
        float rp = 0.5f / sq;
        q = { rp * (m10 + m01), sq * 0.5f, rp * (m21 + m12), rp * (m20 - m02) };
    }
    else
    {
        float sq = sqrtf(1.0f + m22 - m00 - m11);
        float rp = 0.5f / sq;
        q = { rp * (m20 + m02), rp * (m21 + m12), sq * 0.5f, rp * (m01 - m10) };
    }

    /* Quaternion in ipl files is inverted, so... invert again */
    q.Invert();

    /* Make sure there's no -0.0, we want output to be pretty! */
    for (auto& f : reinterpret_cast<float(&)[3]>(q))
        if (f == -0.0f)
            f = 0.0f;

    return q;
}

const char* CEntity::GetModelName()
{
    return CModelInfo::GetModelInfo(m_modelIndex)->GetModelName();
}