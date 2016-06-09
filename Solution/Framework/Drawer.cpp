#include "Drawer.h"
#include "Framework.h"
#include "DxLib.h"
#include <assert.h>

static const int REFRESH_COUNT = 60;	//平均を取るサンプル数
static const int FPS = 60;

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
_sprite_idx( 0 ),
_refresh_count( REFRESH_COUNT ),
_start_time( 0 ) {
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
	flip( );

	// スプライト描画
	drawSprite( );
}

void Drawer::drawSprite( ) {
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


void Drawer::flip( ) {
	if ( _refresh_count == REFRESH_COUNT ){ //60フレーム目なら平均を計算する
		_refresh_count = 0;
		_start_time = GetNowCount( );
	}
	_refresh_count++;

	int took_time = GetNowCount( ) - _start_time;	//かかった時間
	int wait_time = _refresh_count * 1000 / FPS - took_time;	//待つべき時間
	if ( wait_time > 0 ) {
		Sleep( wait_time );	//待機
	}

	ScreenFlip( );
	ClearDrawScreen( );
}
