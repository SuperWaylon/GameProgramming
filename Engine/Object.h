#pragma once
#include <string>

namespace nu
{
	class Object
	{
	public:
		Object() = default;
		virtual ~Object() = default;

		const std::string& GetName() const { return m_name; }
		bool IsActive() const { return m_active; }
		void SetActive(bool active = true) { m_active = active; }


	protected:
		std::string m_name;
		bool m_active = true;
	private:
	};
}