#pragma once

#ifdef INOUACLIENTPROXY_EXPORTS
# define INO_EXPORT __declspec(dllexport)
#else
# define INO_EXPORT __declspec(dllimport)
#endif