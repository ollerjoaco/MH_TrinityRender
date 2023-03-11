# Trinity-Renderer
This is a port of the original [Trinity Renderer](https://github.com/HLSources/Trinity-renderer) for [metahook](https://github.com/Nagist/metahook) so it can work in Counter Strike 1.6

Port was made by someone and published in Baidu, post no longer exists and this is what remains.


How To Install ?
------------------------------------------

This Metahook plugin is fully compatible with MetaHookSv so I recommend you to insatall MetaHookSv as its the most updated and maintained metahook version at the moment. [MetaHookSv](https://github.com/hzqst/MetaHookSv)


DOCUMENTATION 
------------------------------------------

Detail Textures in Trinity are loaded from gfx/textures/details
Detail Textures can be .tga o .dds
DDS compatible formats are DXT1 and DXT5, any other format would not work!


If you use Nvidia Texture Tools this can be useful:
DXT1 = BC1 y BC1a
DXT5 = BC3


CHANGES
-------------------------------------------

Changed detail textures file target from _detail to _detailHD to avoid original game engine and Trinity looking for same file and fail.
You no longer need to use -nofbo parameter in your game launch options. Thanks to [TheOverFloater](https://github.com/TheOverfloater)
