#include "FileManager.h"
#include "Model.h"
#include "Framework.h"
#include "DxLib.h"


void main( ) {
	FrameworkPtr fw = Framework::getInstance( );
	SetCameraPositionAndTarget_UpVecY( VGet( 90.0f, 100.0f, -100.0f ), VGet( 0.0f, 10.0f, 0.0f ) );
	FileManagerPtr fm = FileManagerPtr ( new FileManager );
	ModelPtr model = ModelPtr( new Model );
	int polygon_num = fm->getPolygonNum( );
	int point_num = polygon_num * 3;
	model->alloc( polygon_num );
	int texture_id = LoadGraph( "item02_DM.jpg" );
	model->setTexture( texture_id );
	for ( int i = 0; i < point_num; i++ ) {
		Model::VERTEX vertex = fm->getVERTEX( i );
		model->set( i, vertex );
	}
	while ( ProcessMessage( ) == 0 && CheckHitKey( KEY_INPUT_ESCAPE ) == 0 ) {
		ClearDrawScreen( );
		model->draw( );
		ScreenFlip( );
	}
}