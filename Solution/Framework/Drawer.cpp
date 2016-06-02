#include "Drawer.h"
#include "Framework.h"
#include "DxLib.h"
#include <assert.h>

Drawer::Transform::Transform( ) :
sx( 0 ),
sy( 0 ),
tx( -1 ),
ty( -1 ),
tw( -1 ),
th( -1 ) {

}

Drawer::Transform::Transform( int sx_, int sy_, int tx_, int ty_, int tw_, int th_ ) :
sx( sx_ ),
sy( sy_ ),
tx( tx_ ),
ty( ty_ ),
tw( tw_ ),
th( th_ ) {

}

Drawer::Sprite::Sprite( ) :
res( -1 ),
blend( BLEND_NONE ) {

}

Drawer::Sprite::Sprite( Transform trans_ ,int res_, BLEND blend_, double ratio_ ) :
trans( trans_ ),
res( res_ ),
blend( blend_ ),
ratio( ratio_ ) {

}

DrawerPtr Drawer::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< Drawer >( fw->getTask( getTag( ) ) );
}

Drawer::Drawer( const char * directory ) :
_directory( directory ),
_sprite_idx( 0 ) {
}


Drawer::~Drawer( ) {
}

void Drawer::load( int res, const char * filename ) {
	std::string path = _directory;
	path += "/";
	path +=  filename;
	assert( res < ID_NUM );
	_id[ res ] = LoadGraph( path.c_str( ) );
	if ( _id[ res ] < 0 ) {
		path = "../" + path;
		_id[ res ] = LoadGraph( path.c_str( ) );
		assert( _id[ res ] >= 0 );
	}
}

void Drawer::set( const Sprite& sprite ) {
	assert( _sprite_idx < SPRITE_NUM );
	_sprite[ _sprite_idx ] = sprite;
	_sprite_idx++;
}

void Drawer::update( ) {
	// 画面更新
	ScreenFlip( );
	ClearDrawScreen( );

	// スプライト描画
	for ( int i = 0; i < _sprite_idx; i++ ) {
		const Sprite& sprite = _sprite[ i ];

		switch ( sprite.blend ) {
		case BLEND_ALPHA:
			SetDrawBlendMode( DX_BLENDMODE_ALPHA, ( int )( 255 * sprite.ratio ) );
			break;
		case BLEND_ADD:
			SetDrawBlendMode( DX_BLENDMODE_ADD  , ( int )( 255 * sprite.ratio ) );
			break;
		}

		if ( sprite.trans.tw < 0 ) {
			DrawGraph( sprite.trans.sx, sprite.trans.sy, _id[ sprite.res ], TRUE );
		} else {
			DrawRectGraph( sprite.trans.sx, sprite.trans.sy, sprite.trans.tx, sprite.trans.ty, sprite.trans.tw, sprite.trans.th, _id[ sprite.res ], TRUE, FALSE );
		}

		if ( sprite.blend != BLEND_NONE ) {
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );
		}
	}
	_sprite_idx = 0;
}

