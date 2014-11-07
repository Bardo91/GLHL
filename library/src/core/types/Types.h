//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for Image Processing  (GLHL)			//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-11-06											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	Basic Types



#ifndef _GLHL_CORE_TYPES_h_
#define _GLHL_CORE_TYPES_h_

namespace GLHL{
	// Templates
	template<typename Type_, unsigned size_>
	struct vec{
		Type_ mData[size_];
		const unsigned mSize = size_;
	};

	template<typename Type_, unsigned size_>
	struct mat{
		Type_ mData[size_*size_];
		const unsigned mSize = size_;
	};

	// Definition

	typedef vec<unsigned, 2> vec2ui;
	typedef vec<unsigned, 3> vec3ui;
	typedef vec<unsigned, 4> vec4ui;

	typedef vec<int, 2> vec2i;
	typedef vec<int, 3> vec3i;
	typedef vec<int, 4> vec4i;
	
	typedef vec<float, 2> vec2f;
	typedef vec<float, 3> vec3f;
	typedef vec<float, 4> vec4f;


	typedef mat<unsigned, 2> mat2ui;
	typedef mat<unsigned, 3> mat3ui;
	typedef mat<unsigned, 4> mat4ui;

	typedef mat<int, 2> mat2i;
	typedef mat<int, 3> mat3i;
	typedef mat<int, 4> mat4i;

	typedef mat<float, 2> mat2f;
	typedef mat<float, 3> mat3f;
	typedef mat<float, 4> mat4f;
	


}	//	namespace GLHL

#endif // _GLHL_CORE_TYPES_h_

