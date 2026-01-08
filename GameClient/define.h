#pragma once
#define SINGLE(Type) private: Type(); friend class singleton<Type>;