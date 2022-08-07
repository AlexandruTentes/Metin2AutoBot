#pragma once

#define SINGLETONIZE(T)			static T & get_instance() { static T instance; return instance; } \
								T() { } \
								T(const T &) = delete; \
								T operator = (const T &) = delete; \
								T(T &&) = delete; \
								T operator = (T &&) = delete; 

#define SINGLETONIZE_INIT(T)	static T & get_instance() { static T instance; return instance; } \
								T() { init(); } \
								T(const T &) = delete; \
								T operator = (const T &) = delete; \
								T(T &&) = delete; \
								T operator = (T &&) = delete; 

#define PARTIAL_SINGLETONIZE(T)					static T & get_instance() { static T instance; return instance; } \