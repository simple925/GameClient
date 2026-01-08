#pragma once
#define SINGLE(Type) private: Type(); ~Type(); friend class singleton<Type>;