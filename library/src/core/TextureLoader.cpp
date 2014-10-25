//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for Image Processing  (GLHL)			//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-10-25											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	



namespace GLHL{
	static class TextureLoader{
		static unsigned load2dTexture(std::string _texturePath);
		static unsigned override2dTexture(std::string _texturePath);

	};

}	//	namespace GLHL

#endif	//	_GLHL_CORE_TEXTURELOADER_H_