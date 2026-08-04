#include "pch.h"
#include "Model.h"

namespace nu
{
	void Model::CalculateRadius()
	{
		m_radius = 0.0f;

		//check for mesh radius
		for (auto& mesh : m_meshes)
		{
			//get mesh radius
			float radius = mesh.GetRadius();
			//update radius
			if (radius > m_radius)
			{
				m_radius = radius;
			}
		}
	}
}