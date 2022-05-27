#ifndef _CC_TYPES_H
#define _CC_TYPES_H

#include <cstdint>
#include <cstddef>

namespace cc
{
	using Float = float;

	using i8  = int8_t;
	using i16 = int16_t;
	using i32 = int32_t;
	using i64 = int64_t;
	
	using u8  = uint8_t;
	using u16 = uint16_t;
	using u32 = uint32_t;
	using u64 = uint64_t;

	using f32 = float;
	using f64 = double;

	static constexpr Float FloatEps = Float(0.00001);
}

#endif //_CC_TYPES_H
