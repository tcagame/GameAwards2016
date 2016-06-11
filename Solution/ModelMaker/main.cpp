#include "FileManager.h"
#include "Model.h"
#include "mathmatics.h"
#include "Framework.h"
#include "DxLib.h"


void main( ) {

	FrameworkPtr fw = Framework::getInstance( );
	
	FileManagerPtr file_manager = FileManagerPtr ( new FileManager );
	ModelPtr model = ModelPtr( new Model );
	int texture_id = LoadGraph( "model/texture.png" );

	float camera_x = 0;
	float camera_y = 0;
	float camera_z = -100;
	double angle_xz = 0;
	double r = 50;

	int texture_x = 0;
	int texture_y = 0;

	while ( ProcessMessage( ) == 0 && CheckHitKey( KEY_INPUT_ESCAPE ) == 0 ) {
		if ( CheckHitKey( KEY_INPUT_F2 ) ) {
			//DrawString( 0, 0, "Index : ", 0xffff );
			//DrawString( 15, 70, "XÀ•W : ", 0xffff );
			model->translate( Vector( 10, 0, 0 ) );
		}

		if ( CheckHitKey( KEY_INPUT_F3 ) ) {
			file_manager->loadData( texture_x, texture_y );
			int polygon_num = file_manager->getPolygonNum( );
			int point_num = polygon_num * 3;
			model->alloc( polygon_num );
			model->setTexture( texture_id );
			for ( int i = 0; i < point_num; i++ ) {
				Model::VERTEX vertex = file_manager->getVERTEX( i );
				model->set( i, vertex );
			}
		}

		camera_x = r * sin( angle_xz * PI / 180 );
		camera_z = r * cos( angle_xz * PI / 180 );

		if ( CheckHitKey( KEY_INPUT_F4 ) ) {
			file_manager->saveModelData( );
		}

		if ( CheckHitKey( KEY_INPUT_LEFT ) ) {
			angle_xz += 2;
		}
		if ( CheckHitKey( KEY_INPUT_RIGHT ) ) {
			angle_xz -= 2;
		}
		if ( CheckHitKey( KEY_INPUT_Z ) ) {
			r -= 2;
		}
		if ( CheckHitKey( KEY_INPUT_X ) ) { 
			r += 2;
		}
		if ( CheckHitKey( KEY_INPUT_UP ) ) {
			camera_y++;
		}
		if ( CheckHitKey( KEY_INPUT_DOWN ) ) {
			camera_y--;
		}

		SetCameraPositionAndTarget_UpVecY( VGet( camera_x, camera_y, camera_z ), VGet( 0.0f, 0.0f, 0.0f ) );
		model->draw( FALSE );
		ScreenFlip( );
		ClearDrawScreen( );
	}
}