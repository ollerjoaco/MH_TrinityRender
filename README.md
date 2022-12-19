# Trinity-Renderer
This is a [metahook](https://github.com/Nagist/metahook) plugin, we change original [Trinity Renderer](http://www.moddb.com/mods/trinity-render-custom-edition) code, let it can use in Counter-Strike.


DOCUMENTATION

Detail Textures in Trinity are loaded from gfx/textures/details
Detail Textures can be .tga o .dds ( i1 )

i1 = Only DXT1 and DXT5 are supported!

If you use Nvidia Texture Tools this can be useful:
DXT1 = BC1 y BC1a
DXT5 = BC3


Changes since creation of this repository:

Changed detail textures file target from _detail to _detailHD to avoid original game engine and Trinity looking for same file and fail.
