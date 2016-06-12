#include "FileManager.h"
#include "Model.h"
#include "Camera.h"
#include "mathmatics.h"
#include "Framework.h"
#include "DxLib.h"


void main( ) {

	FrameworkPtr fw = Framework::getInstance( );
	
	FileManagerPtr file_manager = FileManagerPtr ( new FileManager );
	ModelPtr model = ModelPtr( new Model );
	CameraPtr camera = CameraPtr( new Camera );
	int texture_id = LoadGraph( "model/texture.png" );

	

	int texture_x = 0;
	int texture_y = 0;

	while ( ProcessMessage( ) == 0 && CheckHitKey( KEY_INPUT_ESCAPE ) == 0 ) {
		if ( CheckHitKey( KEY_INPUT_F3 ) ) {
			char filename[ 256 ];
			DrawString( 0, 0, "読み込み", 0xaaaa );
			DrawString( 15, 70, "ファイル名:", 0xaaaa );
			KeyInputSingleCharString( 115, 70, 256 , (TCHAR * )filename, TRUE );
			file_manager->loadData( texture_x, texture_y, filename );
			int polygon_num = file_manager->getPolygonNum( );
			int point_num = polygon_num * 3;
			model->alloc( polygon_num );
			model->setTexture( texture_id );
			for ( int i = 0; i < point_num; i++ ) {
				Model::VERTEX vertex = file_manager->getVERTEX( i );
				model->set( i, vertex );
			}

		}

	
		if ( CheckHitKey( KEY_INPUT_F4 ) ) {
			char filename[ 256 ];
			DrawString( 0, 0, "ファイル保存", 0xffff );
			DrawString( 15, 70, "ファイル名:", 0xffff );
			bool savePossible = KeyInputSingleCharString( 115, 70, 256 , (TCHAR * )filename, TRUE ) == 1;
			if ( savePossible ) {
			file_manager->saveModelData( filename );
			}
		}
		camera->update( );
		model->draw( FALSE );
		ScreenFlip( );
		ClearDrawScreen( );
	}
}