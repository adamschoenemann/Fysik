#ifndef FYSIK_H_INCLUDED
#define FYSIK_H_INCLUDED
#include <cmath>
#include <iostream>
#include <cassert>
#include <list>

namespace Fysik {
	typedef float real;
	using namespace std;
	#define real_pow powf
	#include "core.hpp"
	#include "dynamic.hpp"
	#include "collision.hpp"
	#include "shape.hpp"
	#include "intersect.hpp"
	#include "body.hpp"
	#include "world.hpp"
}

#endif // FYSIK_H_INCLUDED
