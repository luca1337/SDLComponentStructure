#ifndef ENGINE_UTILS_H
#define ENGINE_UTILS_H

// add here all casts type for each component is created?
#include <actor.h>

#define CastToComponent(this) (component_t*)this
#define CastToActor(this) (actor_t*)this
#define CastToFuncPtr(this, ptr) (void(*)(ptr*))this
#define CastTo(type, this) (type*)this

#endif