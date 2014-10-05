#pragma once

#include <memory>

template <class T>
class singleton
{
public:
	template <typename... Args>
	static T& instance(Args... args)
	{
		if (!instance_)
		{
			instance_ = std::unique_ptr<T>(new T(std::forward<Args>(args)...));
		}

		return *instance_;
	}

private:
	static std::unique_ptr<T> instance_;
};

template <class T> std::unique_ptr<T> singleton<T>::instance_;
