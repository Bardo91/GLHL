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

#include <stdarg.h>
#include <cassert>
namespace GLHL{
	// Template vec
	template<typename Type_, unsigned size_>
	struct vecBase{		
		operator Type_* (){ return mData; }
		vecBase& operator=(const vecBase &_vec){ for (unsigned i = 0; i < size_; i++) { mData[i] = _vec[i]; } };

		unsigned size() { return mSize; };

	protected:
		Type_ mData[size_];
		const unsigned mSize = size_;

	protected:
		vecBase(){ };
	};
	
	template<typename Type_, unsigned size_>
	struct vec: public vecBase<Type_, size_>{ };

	// Template Specialization
	template<typename Type_>
	struct vec<Type_, 2> : public vecBase<Type_, 2>{
		vec(Type_ _x0, Type_ _x1){ mData[0] = _x0; mData[1] = _x1; };
	};

	template<typename Type_>
	struct vec<Type_, 3> : public vecBase<Type_, 3>{
		vec(Type_ _x0, Type_ _x1, Type_ _x2){ mData[0] = _x0; mData[1] = _x1;  mData[2] = _x2; };
	};


	template<typename Type_>
	struct vec<Type_, 4> : public vecBase<Type_, 4>{
		vec(Type_ _x0, Type_ _x1, Type_ _x2, Type_ _x3){ mData[0] = _x0; mData[1] = _x1;  mData[2] = _x2;  mData[3] = _x3; };
	};


	//---------------------------------------------------------------------------------------------------------
	// Template mat
	template<typename Type_, unsigned size_>
	struct mat{
		operator Type_* (){ return mData; }
		mat& operator=(const mat &_mat) { for (unsigned i = 0; i < size_; i++) { mData[i] = _mat[i]; } };

		unsigned size() { return mSize; };

	private:
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

