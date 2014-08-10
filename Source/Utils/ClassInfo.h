#pragma once

#include "Array.h"
#include "Member.h"

#include <string>
#include <map>


class ClassInfo
{
public:
	ClassInfo();
	void _init(std::string name);
	void _add(Member::Type type, void* member, std::string name);
	bool _hasInit();
	void _setTarget(void* target);

	/// Returns name of the class
	std::string name();
	/// Returns member, or "nullptr" if member does not exist
	Member* member(char* name);

private:
	bool m_init;
	void* m_target;
	std::string m_name;
	Array<Member> m_array;
	std::map<std::string, Member> m_map;

	#pragma region Iterator
public:
	class Iterator
	{
	public:
		Iterator(ClassInfo* host, int index);
		void reset();
		bool operator!=(const Iterator& other) const;
		Member& operator*() const;
		Member* operator->() const;
		const Iterator& operator++();

	private:
		ClassInfo* m_host;
		int m_index;
	};
	Iterator begin();
	Iterator end();
	#pragma endregion
};
