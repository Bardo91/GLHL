//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for Image Processing  (GLHL)			//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-11-22											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	

#ifndef _GLHL_CORE_BASE_CONTEXT_H_
#define _GLHL_CORE_BASE_CONTEXT_H_
namespace GLHL{
	//-----------------------------------------------------------------------------------------------------------------
	// Context Traits.
	struct ContextTrait;

	template< class ContextTrait_>
	class Context{
	public:


	private:
		typedef ContextTrait_ Trait;

	private:



	};	//	class Context
}	//	namespace GLHL
#endif	//	_GLHL_CORE_BASE_CONTEXT_H_